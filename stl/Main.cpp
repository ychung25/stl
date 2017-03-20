#include <stdio.h>
#include <string>

//#include <vector>
//#include <list>
//using namespace std;

#include "MyVector.h"
#include "MyList.h"
using namespace mystd;

void printNums(list<int>& nums)
{
	for (auto iter = nums.begin(); iter != nums.end(); iter++)
	{
		printf("%d ", *iter);
	}
	printf("\n");
}



int main()
{
	list<int> nums;
	nums.push_back(10);
	nums.push_back(20);
	nums.push_back(30);
	nums.push_back(40);
	nums.push_back(50);

	auto startIter = nums.begin();
	startIter++;
	auto endIter = nums.begin();
	endIter++;
	endIter++;
	endIter++;
	endIter++;

	nums.erase(startIter, endIter);

	printNums(nums);



	return 0;
}