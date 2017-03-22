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
    priority_queue<int> pq;
    srand(time(NULL));

    for (int i = 0; i < 100; i++)
    {
        pq.push(rand() % 10000);
    }

    unsigned int size = pq.size();
    int top = pq.top();

 	return 0;
}