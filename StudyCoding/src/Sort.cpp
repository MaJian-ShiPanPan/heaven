/**
 * 知识点
 * 	排序算法
 * 
 * 题目1: 冒泡排序
 * 题目2: 插入排序
 * 题目3: 选择排序
*/

#include <iostream>
#include <vector>

void swap(std::vector<int>& vec, int i, int j)
{
	int temp = 0;
	temp = vec[i];
	vec[i] = vec[j];
	vec[j] = temp;
}

void BubbSort(std::vector<int>& vec)
{
	if(vec.empty() || 2 > vec.size())
	{
		return;
	}
	for(int i = 0; i < vec.size() - 1; ++i)
	{
		for(int j = 0; j < vec.size() - i - 1; ++j)
		{
			if(vec[j] > vec[j + 1])
			{
				swap(vec, j, j + 1);
			}
		}
	}
}

void InsertSort(std::vector<int>& vec)
{
	if(vec.empty() || 2 > vec.size())
	{
		return;
	}

	for(int i = 0; i < vec.size() - 1; ++i)
	{
		for(int j = i + 1; j > 0 && vec[j - 1] > vec[j]; --j)
		{
			swap(vec, j - 1, j);
		}
	}
}


void SelectSort(std::vector<int>& vec)
{
	if(vec.empty() || 2 > vec.size())
	{
		return;
	}
	
	for(int i = 0; i < vec.size() - 1; ++i)
	{
		int min = i;
		for(int j = i + 1; j < vec.size(); ++j)
		{
			if(vec[j] < vec[min])
			{
				min = j;
			}
		}
		swap(vec, i, min);
	}

}

int main()
{
	std::vector<int> Vec = {1, 5, 3, 4, 7, 8, 6, 10, 9};
	// SelectSort(Vec);
	// BubbSort(Vec);
	InsertSort(Vec);
	for(auto& e: Vec)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
	return EXIT_SUCCESS;
}
