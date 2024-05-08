/**
 * 知识点
 * 	二分查找
 * 题目1：有一个有序数组，找某个数是否存在
 * 题目2：有一个有序数组，找>=某个数最左侧的位置
 * 题目3：有一个有序数组，找<=某个数最右侧的位置
 * 题目4：局部最小值的问题，对于一个数组找局部最小值[❌]
 */
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

// 题目1：在一个有序数组，找某个数是否存在
bool DichotomyFindNumber(std::vector<int>& vec, int num)
{
    if(vec.empty())
    {
        return false;
    }
    int L = 0;
    int R = vec.size() - 1;

    while(L < R)
    {
        int mid = L + ((R - L) >> 1);
        if(num == vec[mid])
        {
            return true;
        }

        if(num > vec[mid])
        {
            L = mid + 1;
        }
        else
        {
            R = mid - 1;
        }
    }
    return vec[L] == num;
}

// 题目2：有一个有序数组，找>=某个数最左侧的位置
int FindLeftNearestIndex(std::vector<int>& vec, int num)
{
	int iIndex = -1;
	if(vec.empty())
	{
		return iIndex;
	}
	int L = 0;
	int R = vec.size() - 1;
	while(L < R)
	{
		int mid = L + ((R - L) >> 1);
		if(num < vec[mid])
		{
			iIndex = mid;
			R = mid - 1;
		}
		else
		{
			L = mid + 1;
		}
	}
	if(num < vec[L])
	{
		iIndex = L;
	}
	return iIndex;
}

// 题目3：有一个有序数组，找<=某个数最右侧的位置
int FindRightNearestIndex(std::vector<int>&vec, int num)
{
	int iIndex = -1;
	if(vec.empty())
	{
		return iIndex;
	}

	int L = 0;
	int R = vec.size() - 1;
	
	while(L < R)
	{
		int mid = L + ((R - L) >> 1); // 注意：这个地方必须有括号才可以，因为+的运算符优先级高于>>
		if(num > vec[mid])
		{
			iIndex = mid;
			L = mid + 1;
		}
		else
		{
			R = mid - 1;
		}	
	}

	if(vec[L] < num)
	{
		iIndex = L;
	}

	return iIndex;
}

// 题目4：找一个局部最小值
int FindLocalMinimumValue(std::vector<int>&vec, int num)
{
	int iMinimumValue = 0;
	if()
	{
		
	}
	return iMinimumValue;
}

// 生成随机数组
std::vector<int> generateRandomArray(const int iMaxLength, const int iMaxValue)
{
    std::vector<int> vec;
    int iLength = rand() % (iMaxLength + 1);
    for(int i = 0; i < iLength; ++i)
    {
        vec.push_back((rand() % (iMaxValue + 1)) - (rand() % (iMaxValue + 1)));
    }
    return vec;
}

// 题目1的对数器
void Test1()
{
    const int iMaxLength = 10;    
    const int iMaxValue = 100;
    for(int i = 0; i < 100; i++)
    {
        std::vector<int> vec = generateRandomArray(iMaxLength, iMaxValue);
        int iNumber = rand() % (iMaxValue + 1) - rand() % (iMaxValue + 1);
        std::sort(vec.begin(), vec.end());
        bool bFindIndex = DichotomyFindNumber(vec, iNumber);
        std::cout << "Find result: " << bFindIndex << std::endl;
        if(!bFindIndex)
        {
            std::cout << "iNumber: " << iNumber << " vec:";
            for(auto& e: vec)
            {
                std::cout << e << " ";
            }
            std::cout << std::endl;
        }
    }
}

// 题目2的对数器
int Test2CheckMethod(std::vector<int>& vec, int iNum)
{
	if(vec.empty())
	{
		return -1;
	}
	
	if(iNum < vec[0])
	{
		return 0;
	}

	for(int i = 0; i < vec.size() - 1; ++i)
	{
		if((vec[i] <= iNum) && (vec[i + 1] > iNum))
		{
			return i + 1;
		}
	}
	return -1;
}

void Test2()
{
	const int kiMaxLength = 10;
	const int kiMaxValue = 100;
	const int kiLoopCount = 100;
	for(int i = 0; i < kiLoopCount; ++i)
	{
		std::vector<int> vec = generateRandomArray(kiMaxLength, kiMaxValue);
		int iNumber = rand() % (kiMaxValue + 1) - rand() % (kiMaxValue + 1);
		std::sort(vec.begin(), vec.end());
		int iFindLeftNearestIndex = FindLeftNearestIndex(vec, iNumber);
		int iFindLeftNearestIndexByCheckMethod 
			= Test2CheckMethod(vec, iNumber);
		if(iFindLeftNearestIndex == iFindLeftNearestIndexByCheckMethod)
		{
			std::cout << "Find Success:"
			    << ", result1: " << iFindLeftNearestIndex
		       	<< ", result2: " << iFindLeftNearestIndexByCheckMethod
			    << ", iNumber: " << iNumber
			    << ", vec:";
			for(auto& item: vec)
			{
				std::cout << item << " ";
			}
			std::cout << std::endl;
		}
		else
		{
			std::cout << "Find Failed:"
				<< ", result1: " << iFindLeftNearestIndex 
				<< ", result2: " << iFindLeftNearestIndexByCheckMethod
				<< ", iNumber: " << iNumber
				<< ", vec:";
			for(auto& item: vec)
			{
				std::cout << item << " ";
			}
			std::cout << std::endl;
		}
	}
}

// 题目3的对数器
int Test3CheckMethond(std::vector<int>& vec, int num)
{
	if(vec.empty())
	{
		return -1;
	}

	int iIndex = -1;
	for(int i = 0; i < vec.size(); ++i)
	{
		if(num > vec[i])
		{
			iIndex = i;
		}
		else
		{
			break;
		}
	}
	return iIndex;
}

void Test3()
{
	const int kiMaxLength = 10;
	const int kiMaxValue = 100;
	const int kiLoopCoutn = 10;
	std::vector<int> vec;
	for(int i = 0; i < kiLoopCoutn; ++i)
	{
		vec = generateRandomArray(kiMaxLength, kiMaxValue);
		std::sort(vec.begin(), vec.end());
		int iNumber = rand() % (kiMaxValue + 1) - rand() % (kiMaxValue + 1);
		int iFindRightNearestIndex = FindRightNearestIndex(vec, iNumber);
		int iFindRightNearestIndexByCheckMeathod = Test3CheckMethond(vec, iNumber);
		if(iFindRightNearestIndex == iFindRightNearestIndexByCheckMeathod)
		{
			std::cout << "Success"
				<< ": iFindRightNearestIndex = " << iFindRightNearestIndex
				<< ", iFindRightNearestIndexByCheckMethod = " << iFindRightNearestIndexByCheckMeathod
				<< ", iNumber = " << iNumber
				<< ", vec ={";
			for(auto& item: vec)
			{
				std::cout << item << " ";
			}
			std::cout << "}" << std::endl;
		}
	}
}

// 题目4的对数器
void Test4()
{
}

// 主函数
int main(int argc, char* argv[])
{
    // Test1();
    // Test2();
	Test3();
    return EXIT_SUCCESS;
}
