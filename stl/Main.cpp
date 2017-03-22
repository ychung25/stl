#include <stdio.h>
#include <time.h>
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
#include "MyPriority_queue.h"

using namespace mystd;




int main()
{
	priority_queue<int> pq([](const int& a, const int& b)
	{
		// default to max heap
		if (a > b)
			return true;
		return false;
	});

	srand(time(NULL));
    for (int i = 0; i < 50; i++)
    {
        pq.push(rand() % 10000);
    }

    unsigned int size = pq.size();
	while (pq.size() != 0)
	{
		printf("%d, ", pq.top());
		pq.pop();
	}

 	return 0;
}