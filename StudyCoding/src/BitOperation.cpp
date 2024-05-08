/**
 * 知识点：
 *  位运算：0^N=N; N^N=0
 * 
 * 习题1: 交换两个数的位置
 * 习题2: 一个数组中有一种数出现了奇数次，其它数出现了偶数次，怎么打印这个数
 * 习题3: 怎么把一个int类型的数，提取处最右侧的1来
 * 习题4: 一个数组中有两种数出现了奇数次，其它的均为偶数次，怎么打印这两个数
*/

#include <iostream>
#include <cstdlib>
#include <vector>

// 习题1: 交换两个数的位置
void Swap(int& iNumA, int& iNumB)
{
    iNumA = iNumA ^ iNumB;
    iNumB = iNumA ^ iNumB;
    iNumA = iNumA ^ iNumB;
}
// 习题2: 一个数组中有一种数出现了奇数次，其它数出现了偶数次，怎么打印这个数
int FindOddNumber(std::vector<int>& vec)
{
    int iNumber = 0;
    for(auto& item: vec)
    {
        iNumber ^= item;
    }
    return iNumber;
}

// 习题3: 怎么把一个int类型的数，提取处最右侧的1来
int FindRightOne(int iNumber)
{
    // 注意：在C++中按位取反是~； 而!表示逻辑非, 用于对bool值取反
    return (~iNumber + 1) & (iNumber);
}

// 习题4: 一个数组中有两种数出现了奇数次，其它的均为偶数次，怎么打印这两个数
std::vector<int> FindTwoOddNumber(std::vector<int>& vec)
{
    int temp = 0;
    for(auto& item: vec)
    {
        temp ^= item;
    }

    // 找到这两个奇数的区别
    temp = (~temp + 1) & temp;

    int iFirstOddNumber = 0;
    int iSecondOddNumber = 0;
    for(auto& item: vec)
    {
        if(0 != (item & temp))
        {
            iSecondOddNumber ^= item;
        }
        else
        {
            iFirstOddNumber ^= item;
        }
    }
    return std::vector<int>{iFirstOddNumber, iSecondOddNumber};
}

// 习题1: 对数器
void Test1()
{
    int a = 1;
    int b = 2;
    Swap(a, b);
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
}

// 习题2: 对数器
void Test2()
{
    std::vector<int> vec = {1, 2, 2, 3, 3, 3, 3};
    std::cout << FindOddNumber(vec) << std::endl;
}

// 习题3: 对数器
int Test3CheckMethod(int iNumber)
{
    for(int i = 0; i < 32; i++)
    {
        if(0 != (iNumber & (1 << i)))
        {
            return 1 << i;
        }
    }
    return 0;
}


void Test3()
{
    const int kiMaxValue =  1000;
    for(int i = 0; i <  1000; ++i)
    {
        int iNumber = rand() % (kiMaxValue + 1);
        int iFindRightOne = FindRightOne(iNumber);
        int iTest3CheckMethod = Test3CheckMethod(iNumber);
        if(iFindRightOne == iTest3CheckMethod)
        {
            std::cout << "Success, iNumber: " << iNumber
                << ", Right one: "<< iFindRightOne
                << ", Test3 Check Method: " << iTest3CheckMethod << std::endl;
        }
        else
        {
            std::cout << "Failed, iNumber: " << iNumber
                << ", Right one: "<< iFindRightOne
                << ", Test3 Check Method: " << iTest3CheckMethod << std::endl;
        }
    }
}

// 习题4：对数器
void Test4()
{
    std::vector<int> vec = {1, 2, 2, 3, 3, 5, 6, 6, 6, 6};
    for(auto& item: FindTwoOddNumber(vec))
    {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

// 主函数
int main(int argc, char* argv[])
{
    // Test1();
    // Test2();
    // Test3();
    Test4();
    return 0;
}
