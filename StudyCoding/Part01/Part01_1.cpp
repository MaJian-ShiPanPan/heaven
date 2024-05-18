/**
 * 题目1：Fabonacci数列求解，求第n项的Fabonacci数列值。
 * 题目2：矩阵覆盖问题，用2*1的矩形覆盖大的矩形，有多少种方法。
 * 题目3：青蛙跳台阶，一次只能跳一级或者二级，问跳n级有多少种跳法。
*/

#include <iostream>
#include <cstdlib>
#include <chrono>

// 题目1：Fabonacci数列求解，求第n项的Fabonacci数列值。
int Fabonacci_Recur(int n)
{
    if(n < 2) return n;
    return Fabonacci_Recur(n - 1) + Fabonacci_Recur(n - 2);
}

int Fabonacci_Dynamic(int n)
{
    if(n < 2) return n;
    int *arr = new int[n + 1];
    arr[0] = 0;
    arr[1] = 1;
    for(int i = 2; i <= n; ++i)
    {
        arr[i] = arr[i - 1] + arr[i - 2];
    }
    return arr[n];
}

// 对Fabonacci_Dynamic优化一下：由于这个问题直接求值，所以不需要搞个数组
int Fabonacci_Dynamic_op(int n)
{
    if(n < 2) return n;
    int a = 0;
    int b = 1;
    for(int i = 2; i <= n; ++i)
    {
        int c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int GetRandomNumber(int iMaxValue)
{
    return rand() % (iMaxValue + 1);
}

void Test01()
{
    const int kiLoopCount = 100;
    const int kiMaxValue = 39;
    for(int i = 0; i < kiLoopCount; ++i)
    {
        int iRandomNumber = GetRandomNumber(kiMaxValue);
        auto start1 = std::chrono::high_resolution_clock::now();
        int iResultByRecur = Fabonacci_Recur(iRandomNumber);
        auto end1 = std::chrono::high_resolution_clock::now();

        auto start2 = std::chrono::high_resolution_clock::now();
        int iResultByDynamic = Fabonacci_Dynamic(iRandomNumber);
        auto end2 = std::chrono::high_resolution_clock::now();

        if(iResultByRecur ==  iResultByDynamic)
        {
            std::cout << "The result is right, the iRandomNumber: " << iRandomNumber
                << ", the value of fabonacci value is: " << iResultByRecur
                << ", the value of Fabonacci_Dynamic_op value is: " << Fabonacci_Dynamic_op(iRandomNumber)
                << ", Fabonacci_Recur cost time: " << (end1 - start1).count()
                << ", Fabonacci_Dynamic cost time: " << (end2 - start2).count()
                << std::endl;
        }
        else
        {
            std::cout << "The result is error, the iRandomNumber: " << iRandomNumber
                << ", the value of fabonacci value by Dynamic is: " << iResultByDynamic
                << ", the value of Fabonacci_Dynamic_op value is: " << Fabonacci_Dynamic_op(iRandomNumber)
                << ", the value of fabonacci value by Recur is: " << iResultByRecur
                << ", Fabonacci_Recur cost time: " << (end1 - start1).count()
                << ", Fabonacci_Dynamic cost time: " << (end2 - start2).count()
                << std::endl;
            break;
        }
    }
    std::cout << "Test Over" << std::endl;
}

// 题目2：矩阵覆盖问题，用2*1的矩形覆盖大的矩形，有多少种方法。
// 题目3：青蛙跳台阶，一次只能跳一级或者二级，问跳n级有多少种跳法。
// 方法1见题目1

int FindResult02_03ByDynamic(int n)
{
    if(n < 3) return n;
    int *arr = new int[n + 1];

    for(int i = 3; i <= n; ++i)
    {
        arr[i] = arr[i - 1] + arr[i -2];
    }
    return arr[n];
}

int Factorial(int n)
{
    if()
}

int Combin(int iSum, int iTypeBNumber)
{
    return 
}

int FindResult02_03byCombin(int n)
{
    // 用A表示小的，用B表示大的
    int iTypeA = n % 2;
    int iTypeB = n / 2;
    int iSum = iTypeA + iTypeB;
    int iResult = 0;

    for(int i = 0; i <= iTypeB; ++i)
    {
        int iTypeANumber = iTypeA + i * 2;
        int iTypeBNumber = iTypeB - i;
        iSum = iTypeANumber + iTypeBNumber;
        iResult += Combin(iSum, iTypeBNumber);
    }
    return iResult;
}

void Test02_03()
{

}

int main(int argc, char* argv[])
{
    Test01();
    return EXIT_SUCCESS;
}
