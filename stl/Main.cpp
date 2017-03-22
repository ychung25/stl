#include <stdio.h>
#include <iostream>
#include <string>

//#include <vector>
//#include <deque>
//#include <list>
//#include <forward_list>
//
//#include <stack>
//#include <queue>
//using namespace std;

#include "MyVector.h"
#include "MyDeque.h"
#include "MyList.h"
#include "MyForward_list.h"
#include "MyStack.h"
#include "MyQueue.h"
using namespace mystd;

void print(forward_list<int>& vec)
{
	for (auto iter = vec.begin(); iter != vec.end(); iter++)
	{
		printf("%d, ", *iter);
	}
	std::cout << "\n";
}



int main()
{
	forward_list<int> v;

	v.push_front(1);
	v.pop_front();
	v.push_front(40);
	v.push_front(30);
	v.push_front(20);
	v.push_front(10);
	// 10, 20, 30, 40


	auto iter = v.insert_after(v.before_begin(), 5);
	// 5, 10, 20, 30, 40. iter points to 5
	iter = v.insert_after(iter, 4);
	// 5, 4, 10, 20, 30, 40


	while (v.erase_after(iter) != v.end())
	{
	}


	print(v);




 	return 0;
}