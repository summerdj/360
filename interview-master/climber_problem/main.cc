#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <iostream>
#include <vector>
using namespace std;
#define H_ARRAYSIZE(a) \
    ((sizeof(a) / sizeof(*(a))) / \
    static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))
	
int getLongestDistance(vector<vector<int> > dataset);
int isMoutain(vector<vector<int> > dataset, int currentheight, int currentposition);
int isCliff(vector<vector<int> > dataset, int currentheight, int currentposition);
int resolve(const char* input)
{
	char aa[100] = { 0 };
	strcpy(aa, input);
	//char* delim = "\n";
	//char* p = strtok(aa, delim);
	char* p = strtok(aa, "\n");
	int total;
	int start, end, height;
	vector<vector<int> > dataset;
	sscanf(p, "%d", &total);
	printf("%d\n", total);
	p = strtok(NULL, "\n");
	while (p)
	{
		sscanf(p, "%d,%d,%d", &start, &end, &height);
		printf("%d,%d,%d\n", start, end, height);
		vector<int> temp;
		temp.push_back(start);
		temp.push_back(end);
		temp.push_back(height);
		dataset.push_back(temp);
		p = strtok(NULL, "\n");
	}
	//int dataset_size = dataset.size();
	int horizontaldistance = getLongestDistance(dataset);
	int totaldistance = 0;
	int currentheight = 0;
	int testCliff, testMoutain;
	for (int i = 0; i <= horizontaldistance; i++)
	{
		testMoutain = isMoutain(dataset, currentheight, i);
		if (testMoutain)
		{
			totaldistance += (testMoutain - currentheight);
			currentheight = testMoutain;
			printf("find a Mountain in %d,the height is %d,the distance increase to %d,currentheight is %d\n", i, testMoutain, totaldistance, currentheight);
			continue;
		}
		else
		{
			testCliff = isCliff(dataset, currentheight, i);
			if (testCliff != -1)
			{
				totaldistance += (currentheight - testCliff);
				currentheight = testCliff;
				printf("find a Cliff in %d,the luojiaodian is %d,the distance increase to %d,currentheight is %d\n", i, testCliff, totaldistance, currentheight);
				continue;
			}
			else
			{
				printf("Can't find a Moutain or a Cliff in %d,continue..,current height is %d\n", i, currentheight);
			}
		}
	}
	printf("the vertical distance is %d,the horizontal distance is %d, the total is %d\n", totaldistance, horizontaldistance, totaldistance + horizontaldistance);

	return horizontaldistance+totaldistance;
}

//获得最远横轴距离
int getLongestDistance(vector<vector<int> > dataset) 
{
	int result = 0;
	for (unsigned int i = 0; i < dataset.size(); i++)
	{
		if (result < dataset[i][1])
			result = dataset[i][1];
	}
	return result;
}

//判断是否上升，返回往上爬后的高度
int isMoutain(vector<vector<int> > dataset, int currentheight,int currentposition)
{
	int result = 0;
	for (unsigned int i = 0; i < dataset.size(); i++)
	{
		if (dataset[i][0] == currentposition && currentheight < dataset[i][2])
		{
			if (result < dataset[i][2])
				result = dataset[i][2];
		}
	}
	return result;
}

//判断是否下降，返回－1表示不下降，否则返回下降至的高度
int isCliff(vector<vector<int> > dataset, int currentheight, int currentposition)
{
	int result = -1;
	for (unsigned int i = 0; i < dataset.size(); i++)
	{
		if (dataset[i][1] == currentposition && currentheight == dataset[i][2])
		{
			int luojiaodian = 0;
			for (unsigned int j = 0; j < dataset.size(); j++)
			{
				if (currentposition >= dataset[j][0] && currentposition < dataset[j][1])
				{
					if (luojiaodian < dataset[j][2])
						luojiaodian = dataset[j][2];
				}
			}
			return luojiaodian;
		}
	}
	return result;
}

int main(int argc, char* argv[]) 
{
    const char* input[] = {
        "3\n1,3,2\n2,4,4\n6,7,5\n", //The giving example
        "1\n1,2,1\n",
        "2\n1,2,1\n2,3,2",
        "3\n1,2,1\n2,3,2\n3,6,1",
        "4\n1,2,1\n2,3,2\n3,6,1\n5,8,2",
        "5\n1,2,1\n2,3,2\n3,6,1\n5,8,2\n7,9,1",
        "1\n0,1,1",
        "2\n0,1,1\n2,4,3",
        "3\n0,1,1\n2,4,3\n3,5,1",
        "4\n0,1,1\n2,4,3\n3,5,1\n5,6,1",
        "5\n0,1,1\n2,4,3\n3,5,1\n5,6,1\n6,8,3",
        //TODO please add more test case here
        };
    int expectedSteps[] = {25, 4, 7, 10, 14, 15, 3, 12, 13, 14, 20};
  
    for (size_t i = 0; i < H_ARRAYSIZE(input); ++i)
    {
        assert(resolve(input[i]) == expectedSteps[i]);
//	assert(25 == expectedSteps[0]);	
    }
  	return 0;
}
