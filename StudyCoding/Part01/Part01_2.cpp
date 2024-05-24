#include <iostream>
#include <memory>
#include <random>
#include <sstream>
#include <vector>
#include "catch2/catch_all.hpp"
#include <windows.h>
#include <Psapi.h>

using integral_type = int;
static const size_t gkstBlockElementNum = 1024 * 32;
static size_t gstBlockNum = 32;
#define TOTAL_ELEMENT_NUM (gkstBlockElementNum * gstBlockNum)

class CPODClass
{
public:
    CPODClass()
    {
    }
    virtual ~CPODClass()
    {
    }

    void CopyData(integral_type* pRandomData)
    {
        memcpy(m_aIntegralData, pRandomData, sizeof(integral_type) * gkstBlockElementNum);
    }

private:
    integral_type m_aIntegralData[gkstBlockElementNum];
};

class CPageFaultCounterForBenchmark
{
public:
    using PageFaultAutoCounter = std::unique_ptr<CPageFaultCounterForBenchmark>;
    static PageFaultAutoCounter CreateCounter()
    {
        return std::make_unique<CPageFaultCounterForBenchmark>();
    }
    
public:
    CPageFaultCounterForBenchmark()
    {
        m_hProcess = GetCurrentProcess();
    }
    virtual ~CPageFaultCounterForBenchmark()
    {
        DWORD dwTotalFaultsInSamples = 0;
        for (auto& faults : m_vecBenchmarkFaults)
        {
            dwTotalFaultsInSamples += faults;
        }
        std::cout << "Benchmark invoke " << m_vecBenchmarkFaults.size() << " samples and invoke " << dwTotalFaultsInSamples << " page faults." << std::endl;
    }
    void BenchmarkPageFaultStart()
    {
        GetProcessMemoryInfo(m_hProcess, &m_scPMC, sizeof(m_scPMC));
        m_dwPageFaultAtBenchmarkStart = m_scPMC.PageFaultCount;
    }
    void BenchmarkPageFaultEnd()
    {
        GetProcessMemoryInfo(m_hProcess, &m_scPMC, sizeof(m_scPMC));
        m_dwPageFaultAtBenchmarkEnd = m_scPMC.PageFaultCount;
        m_vecBenchmarkFaults.push_back(m_dwPageFaultAtBenchmarkEnd - m_dwPageFaultAtBenchmarkStart);
    }
private:
    HANDLE m_hProcess = NULL;
    PROCESS_MEMORY_COUNTERS m_scPMC;
    DWORD m_dwPageFaultAtBenchmarkStart = 0;
    DWORD m_dwPageFaultAtBenchmarkEnd = 0;
    std::vector<DWORD> m_vecBenchmarkFaults;
};

CATCH_SCENARIO("使用new逐一构造整型并赋值")
{
    CATCH_GIVEN("一个用于存储整型指针的数组")
    {
        using integral_ptr_type = integral_type*;
        size_t const kstAllocateCount = TOTAL_ELEMENT_NUM;
        integral_ptr_type* pDataPtr = new integral_ptr_type[kstAllocateCount];
        CATCH_AND_GIVEN("一个存储随机数据的数组")
        {
            integral_type* pRandomData = new integral_type[kstAllocateCount];
            for (size_t i = 0; i < kstAllocateCount; ++i)
            {
                pRandomData[i] = static_cast<integral_type>(std::rand());
            }
            CATCH_WHEN("使用new构造整型并使用随机数赋值")
            {
                auto pagefaultCounter = CPageFaultCounterForBenchmark::CreateCounter();
                CATCH_BENCHMARK("逐一构造整型并赋值")
                {
                    pagefaultCounter->BenchmarkPageFaultStart();
                    for (size_t i = 0; i < kstAllocateCount; ++i)
                    {
                        pDataPtr[i] = new integral_type;
                        *pDataPtr[i] = pRandomData[i];
                    }
                    for (size_t i = 0; i < kstAllocateCount; ++i)
                    {
                        delete pDataPtr[i];
                        pDataPtr[i] = nullptr;
                    }
                    pagefaultCounter->BenchmarkPageFaultEnd();
                };
                pagefaultCounter.reset();
                CATCH_THEN("释放分配的资源")
                {
                    delete[] pRandomData;
                    delete[] pDataPtr;
                }
            }
        }
    }
}

CATCH_SCENARIO("使用new分配连续内存并按整型逐一赋值")
{
    CATCH_GIVEN("一个存储随机数据的数组")
    {
        size_t const kstAllocateCount = TOTAL_ELEMENT_NUM;
        integral_type* pRandomData = new integral_type[kstAllocateCount];
        for (size_t i = 0; i < kstAllocateCount; ++i)
        {
            pRandomData[i] = static_cast<integral_type>(std::rand());
        }
        CATCH_WHEN("使用new分配连续内存并使用随机数逐一赋值")
        {
            auto pagefaultCounter = CPageFaultCounterForBenchmark::CreateCounter();
            CATCH_BENCHMARK("分配内存并逐一赋值整型")
            {
                pagefaultCounter->BenchmarkPageFaultStart();
                integral_type* pData = new integral_type[kstAllocateCount];
                for (size_t i = 0; i < kstAllocateCount; ++i)
                {
                    pData[i] = pRandomData[i];
                }
                delete[] pData;
                pagefaultCounter->BenchmarkPageFaultEnd();
            };
            pagefaultCounter.reset();
            CATCH_THEN("释放分配的资源")
            {
                delete[] pRandomData;
            }
        }
    }
}

CATCH_SCENARIO("使用new分配连续内存并用memcpy批量赋值")
{
    CATCH_GIVEN("一个存储随机数据的数组")
    {
        size_t const kstAllocateCount = TOTAL_ELEMENT_NUM;
        integral_type* pRandomData = new integral_type[kstAllocateCount];
        for (size_t i = 0; i < kstAllocateCount; ++i)
        {
            pRandomData[i] = static_cast<integral_type>(std::rand());
        }
        CATCH_WHEN("使用new分配连续内存并用memcpy批量赋值")
        {
            auto pagefaultCounter = CPageFaultCounterForBenchmark::CreateCounter();
            CATCH_BENCHMARK("分配内存并批量赋值整型")
            {
                pagefaultCounter->BenchmarkPageFaultStart();
                integral_type* pData = new integral_type[kstAllocateCount];
                memcpy(pData, pRandomData, kstAllocateCount * sizeof(integral_type));
                delete[] pData;
                pagefaultCounter->BenchmarkPageFaultEnd();
            };
            pagefaultCounter.reset();
            CATCH_THEN("释放分配的资源")
            {
                delete[] pRandomData;
            }
        }
    }
}

CATCH_SCENARIO("复用连续内存并按整型逐一赋值")
{
    CATCH_GIVEN("一个整型类型的数组")
    {
        size_t const kstAllocateCount = TOTAL_ELEMENT_NUM;
        integral_type* pData = new integral_type[kstAllocateCount];
        CATCH_AND_GIVEN("一个存储随机数据的数组")
        {
            integral_type* pRandomData = new integral_type[kstAllocateCount];
            for (size_t i = 0; i < kstAllocateCount; ++i)
            {
                pRandomData[i] = static_cast<integral_type>(std::rand());
            }
            CATCH_WHEN("使用随机数逐一赋值")
            {
                auto pagefaultCounter = CPageFaultCounterForBenchmark::CreateCounter();
                CATCH_BENCHMARK("逐一赋值")
                {
                    pagefaultCounter->BenchmarkPageFaultStart();
                    for (size_t i = 0; i < kstAllocateCount; ++i)
                    {
                        pData[i] = pRandomData[i];
                    }
                    pagefaultCounter->BenchmarkPageFaultEnd();
                };
                pagefaultCounter.reset();
                CATCH_THEN("释放分配的资源")
                {
                    delete[] pData;
                    delete[] pRandomData;
                }
            }
        }
    }
}

CATCH_SCENARIO("复用连续内存并用memcpy批量赋值")
{
    CATCH_GIVEN("一个整型类型的数组")
    {
        size_t const kstAllocateCount = TOTAL_ELEMENT_NUM;
        integral_type* pData = new integral_type[kstAllocateCount];
        CATCH_AND_GIVEN("一个存储随机数据的数组")
        {
            integral_type* pRandomData = new integral_type[kstAllocateCount];
            for (size_t i = 0; i < kstAllocateCount; ++i)
            {
                pRandomData[i] = static_cast<integral_type>(std::rand());
            }
            CATCH_WHEN("用memcpy批量赋值")
            {
                auto pagefaultCounter = CPageFaultCounterForBenchmark::CreateCounter();
                CATCH_BENCHMARK("批量赋值")
                {
                    pagefaultCounter->BenchmarkPageFaultStart();
                    memcpy(pData, pRandomData, sizeof(integral_type) * kstAllocateCount);
                    pagefaultCounter->BenchmarkPageFaultEnd();
                };
                pagefaultCounter.reset();
                CATCH_THEN("释放分配的资源")
                {
                    delete[] pData;
                    delete[] pRandomData;
                }
            }
        }
    }
}

CATCH_SCENARIO("使用allocator分配内存再逐一构造整型并赋值")
{
    CATCH_GIVEN("一个整型类型的allocator")
    {
        std::allocator<integral_type> integral_allocator;
        CATCH_AND_GIVEN("通过allocator分配的内存")
        {
            size_t const kstAllocateCount = TOTAL_ELEMENT_NUM;
            integral_type* pData = integral_allocator.allocate(kstAllocateCount);
            CATCH_AND_GIVEN("一个存储随机数据的数组")
            {
                integral_type* pRandomData = new integral_type[kstAllocateCount];
                for (size_t i = 0; i < kstAllocateCount; ++i)
                {
                    pRandomData[i] = static_cast<integral_type>(std::rand());
                }
                CATCH_WHEN("使用allocator构造整型并使用随机数赋值")
                {
                    auto pagefaultCounter = CPageFaultCounterForBenchmark::CreateCounter();
                    CATCH_BENCHMARK("使用allocator构造整型并赋值")
                    {
                        pagefaultCounter->BenchmarkPageFaultStart();
                        for (size_t i = 0; i < kstAllocateCount; ++i)
                        {
                            integral_allocator.construct(pData + i, pRandomData[i]);
                        }
                        for (size_t i = 0; i < kstAllocateCount; ++i)
                        {
                            integral_allocator.destroy(pData + i);
                        }
                        pagefaultCounter->BenchmarkPageFaultEnd();
                    };
                    pagefaultCounter.reset();
                    CATCH_THEN("释放分配的资源")
                    {
                        integral_allocator.deallocate(pData, kstAllocateCount);
                        delete[] pRandomData;
                    }
                }
            }
            
        }
    }
}

CATCH_SCENARIO("使用new逐一构造POD对象")
{
    CATCH_GIVEN("一个用于存储POD对象指针的数组")
    {
        size_t const kstAllocateCount = gstBlockNum;
        size_t const kszBlockSize = gkstBlockElementNum;
        using POD_type = CPODClass;
        using POD_ptr_type = POD_type*;
        POD_ptr_type* pPODObjects = new POD_ptr_type[kstAllocateCount];
        CATCH_AND_GIVEN("一个存储随机数据的数组")
        {
            integral_type* pRandomData = new integral_type[kszBlockSize * kstAllocateCount];
            for (size_t i = 0; i < kszBlockSize * kstAllocateCount; ++i)
            {
                pRandomData[i] = static_cast<integral_type>(std::rand());
            }
            CATCH_WHEN("使用new逐一构造POD对象并复制随机数据到POD对象中")
            {
                auto pagefaultCounter = CPageFaultCounterForBenchmark::CreateCounter();
                CATCH_BENCHMARK("使用new逐一构造POD对象并复制数据")
                {
                    pagefaultCounter->BenchmarkPageFaultStart();
                    for (size_t i = 0; i < kstAllocateCount; ++i)
                    {
                        pPODObjects[i] = new POD_type;
                        pPODObjects[i]->CopyData(pRandomData + i * kszBlockSize);
                    }
                    for (size_t i = 0; i < kstAllocateCount; ++i)
                    {
                        delete pPODObjects[i];
                        pPODObjects[i] = nullptr;
                    }
                    pagefaultCounter->BenchmarkPageFaultEnd();
                };
                pagefaultCounter.reset();
                CATCH_THEN("释放分配的资源")
                {
                    delete[] pRandomData;
                }
            }
        }
    }
}

CATCH_SCENARIO("使用allocator分配内存再逐一构造POD对象")
{
    CATCH_GIVEN("一个POD类型的allocator")
    {
        using POD_type = CPODClass;
        std::allocator<POD_type> pod_allocator;
        CATCH_AND_GIVEN("通过allocator分配的内存")
        {
            size_t const kstAllocateCount = gstBlockNum;
            size_t const kstBlockSize = gkstBlockElementNum;
            POD_type* pObjects = pod_allocator.allocate(kstAllocateCount);
            CATCH_AND_GIVEN("一个存储随机数据的数组")
            {
                integral_type* pRandomData = new integral_type[kstBlockSize];
                for (size_t i = 0; i < kstBlockSize; ++i)
                {
                    pRandomData[i] = static_cast<integral_type>(std::rand());
                }
                CATCH_WHEN("使用allocator逐一构造POD对象并复制随机数据到POD对象中")
                {
                    
                    auto pagefaultCounter = CPageFaultCounterForBenchmark::CreateCounter();
                    CATCH_BENCHMARK("使用allocator逐一构造POD对象并复制数据")
                    {
                        pagefaultCounter->BenchmarkPageFaultStart();
                        for (size_t i = 0; i < kstAllocateCount; ++i)
                        {
                            POD_type* pObject = pObjects + i;
                            pod_allocator.construct(pObject);
                            pObject->CopyData(pRandomData);
                        }
                        for (size_t i = 0; i < kstAllocateCount; ++i)
                        {
                            pod_allocator.destroy(pObjects + i);
                        }
                        pagefaultCounter->BenchmarkPageFaultEnd();
                    };
                    pagefaultCounter.reset();
                    CATCH_THEN("释放分配的资源")
                    {
                        pod_allocator.deallocate(pObjects, kstAllocateCount);
                        delete[] pRandomData;
                    }
                }
            }
            
        }
    }
}

CATCH_SCENARIO("使用与数据总大小一样的共享内存，按区块进行映射并复制数据")
{
    CATCH_GIVEN("一个数据总大小的共享内存")
    {
        size_t const kstBlockElementNum = gkstBlockElementNum;
        size_t const kstBlockSize = sizeof(integral_type) * kstBlockElementNum;
        size_t const kstBlockNum = gstBlockNum;
        size_t const kstTotalSize = kstBlockSize * kstBlockNum;

        HANDLE hSharedMemory = CreateFileMapping(
            INVALID_HANDLE_VALUE,
            NULL,
            PAGE_READWRITE,
            0,
            kstTotalSize,
            (std::stringstream() << "Global\\TestSharedMemory").str().c_str()
        );

        char* pAllBlocks = static_cast<char*>(MapViewOfFile(
            hSharedMemory,
            FILE_MAP_ALL_ACCESS,
            0,
            0,
            kstTotalSize
        ));
        CATCH_AND_GIVEN("保存在共享内存中的随机数据")
        {
            integral_type* pData = new integral_type[kstBlockElementNum];
            for (size_t i = 0; i < kstBlockElementNum; ++i)
            {
                pData[i] = static_cast<integral_type>(std::rand());
            }
            for (size_t i = 0; i < kstBlockNum; ++i)
            {
                memcpy(pAllBlocks + kstBlockSize * i, pData, kstBlockSize);
            }
            UnmapViewOfFile(pAllBlocks);
            delete[] pData;

            CATCH_WHEN("按区块映射共享内存并复制数据到本地内存")
            {
                integral_type* pDataOut = new integral_type[kstBlockElementNum * kstBlockNum];
                memset(pDataOut, 0, kstTotalSize);
                auto pagefaultCounter = CPageFaultCounterForBenchmark::CreateCounter();
                CATCH_BENCHMARK("按区块映射并复制数据")
                {
                    pagefaultCounter->BenchmarkPageFaultStart();
                    for (int i = 0; i < kstBlockNum; ++i)
                    {
                        LPVOID pBlock = MapViewOfFile(
                            hSharedMemory,
                            FILE_MAP_ALL_ACCESS,
                            0,
                            kstBlockSize * i,
                            kstBlockSize
                        );
                        memcpy(pDataOut + i * kstBlockElementNum, pBlock, kstBlockSize);
                        UnmapViewOfFile(pBlock);
                    }
                    pagefaultCounter->BenchmarkPageFaultEnd();
                };
                pagefaultCounter.reset();
                CATCH_THEN("释放分配的资源")
                {
                    delete[] pDataOut;
                    CloseHandle(hSharedMemory);
                }
            }
        }
    }
}

CATCH_SCENARIO("使用与数据总大小一样的共享内存，进行完整映射并复制数据")
{
    CATCH_GIVEN("一个数据总大小的共享内存")
    {
        size_t const kstBlockElementNum = gkstBlockElementNum;
        size_t const kstBlockSize = sizeof(integral_type) * gkstBlockElementNum;
        size_t const kstBlockNum = gstBlockNum;
        size_t const kstTotalSize = kstBlockSize * kstBlockNum;

        HANDLE hSharedMemory = CreateFileMapping(
            INVALID_HANDLE_VALUE,
            NULL,
            PAGE_READWRITE,
            0,
            kstTotalSize,
            (std::stringstream() << "Global\\TestSharedMemory").str().c_str()
        );

        char* pAllBlocks = static_cast<char*>(MapViewOfFile(
            hSharedMemory,
            FILE_MAP_ALL_ACCESS,
            0,
            0,
            kstTotalSize
        ));
        CATCH_AND_GIVEN("保存在共享内存中的随机数据")
        {
            integral_type* pData = new integral_type[kstBlockElementNum];
            for (size_t i = 0; i < kstBlockElementNum; ++i)
            {
                pData[i] = static_cast<integral_type>(std::rand());
            }
            for (size_t i = 0; i < kstBlockNum; ++i)
            {
                memcpy(pAllBlocks + kstBlockSize * i, pData, kstBlockSize);
            }
            UnmapViewOfFile(pAllBlocks);
            delete[] pData;

            CATCH_WHEN("完整映射共享内存并复制数据到本地内存")
            {
                integral_type* pDataOut = new integral_type[kstBlockElementNum * kstBlockNum];
                memset(pDataOut, 0, kstTotalSize);
                auto pagefaultCounter = CPageFaultCounterForBenchmark::CreateCounter();
                CATCH_BENCHMARK("完整映射并复制数据")
                {
                    pagefaultCounter->BenchmarkPageFaultStart();
                    LPVOID pAllBlock = MapViewOfFile(
                        hSharedMemory,
                        FILE_MAP_ALL_ACCESS,
                        0,
                        0,
                        kstTotalSize
                    );
                    memcpy(pDataOut, pAllBlock, kstTotalSize);
                    UnmapViewOfFile(pAllBlock);
                    pagefaultCounter->BenchmarkPageFaultEnd();
                };
                pagefaultCounter.reset();
                CATCH_THEN("释放分配的资源")
                {
                    delete[] pDataOut;
                    CloseHandle(hSharedMemory);
                }
            }
        }
    }
}

CATCH_SCENARIO("使用一个区块大小的共享内存作为交换区来传输数据")
{
    CATCH_GIVEN("一个区块大小的共享内存")
    {
        size_t const kstBlockElementNum = gkstBlockElementNum;
        size_t const kstBlockSize = sizeof(integral_type) * kstBlockElementNum;
        size_t const kstBlockNum = gstBlockNum;
        size_t const kstTotalSize = kstBlockSize * kstBlockNum;

        HANDLE hSharedMemory = CreateFileMapping(
            INVALID_HANDLE_VALUE,
            NULL,
            PAGE_READWRITE,
            0,
            kstBlockSize,
            (std::stringstream() << "Global\\TestSharedMemory").str().c_str()
        );

        char* pWriteBuffer = static_cast<char*>(MapViewOfFile(
            hSharedMemory,
            FILE_MAP_ALL_ACCESS,
            0,
            0,
            kstBlockSize
        ));
        CATCH_AND_GIVEN("在本地内存中的随机数据")
        {
            integral_type* pData = new integral_type[kstBlockElementNum * kstBlockNum];
            for (size_t i = 0; i < kstBlockElementNum; ++i)
            {
                pData[i] = static_cast<integral_type>(std::rand());
            }
            for (size_t i = 1; i < kstBlockNum; ++i)
            {
                memcpy(reinterpret_cast<char*>(pData) + kstBlockSize * i, pData, kstBlockSize);
            }

            CATCH_WHEN("映射共享内存并通过它在两个本地内存间传输数据")
            {
                int* pReadBuffer = static_cast<int*>(MapViewOfFile(
                    hSharedMemory,
                    FILE_MAP_ALL_ACCESS,
                    0,
                    0,
                    kstBlockSize
                ));
                integral_type* pDataOut = new integral_type[kstBlockElementNum * kstBlockNum];
                memset(pDataOut, 0, kstTotalSize);
                auto pagefaultCounter = CPageFaultCounterForBenchmark::CreateCounter();
                CATCH_BENCHMARK("使用区块共享内存传输数据")
                {
                    pagefaultCounter->BenchmarkPageFaultStart();
                    for (int i = 0; i < kstBlockNum; ++i)
                    {
                        memcpy(pWriteBuffer, pData + i * kstBlockElementNum, kstBlockSize);
                        memcpy(pDataOut + i * kstBlockElementNum, pReadBuffer, kstBlockSize);
                    }
                    pagefaultCounter->BenchmarkPageFaultEnd();
                };
                pagefaultCounter.reset();
                CATCH_THEN("释放分配的资源")
                {
                    delete[] pDataOut;
                    delete[] pData;
                    UnmapViewOfFile(pReadBuffer);
                    UnmapViewOfFile(pWriteBuffer);
                    CloseHandle(hSharedMemory);
                }
            }
        }
    }
}

int main(int argc, char* argv[])
{
    using namespace Catch::Clara;
    Catch::Session session;
    auto cli = session.cli()
        | Opt(gstBlockNum, "BlockNum")
        ["--blocknum"]
        ("Use how many blocks for benchmark");
    session.cli(cli);
    int parseCode = session.applyCommandLine(argc, argv);
    if (0 != parseCode)
    {
        return parseCode;
    }
    if (0 == gstBlockNum)
    {
        std::cout << "Block number is 0, so no test is runned." << std::endl;
        return 0;
    }

    return session.run();
}