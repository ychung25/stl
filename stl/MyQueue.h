#pragma once
#include "MyList.h"
#include "MyDeque.h"


namespace mystd {

	//template<typename T>
	//class queue
	//{
	//public:
	//	unsigned int size() { return _list.size(); }
	//	T& front() { return _list.front(); }
	//	T& back() { return _list.back(); }
	//	void push(const T& t)
	//	{
	//		_list.push_back(t);
	//	}
	//	void pop()
	//	{
	//		_list.pop_front();
	//	}
	//private:
	//	list<T> _list;
	//};

	template<typename T>
	class queue
	{
	public:
		unsigned int size() { return _deque.size(); }
		T& front() { return _deque[0]; }
		T& back() { return _deque[size()-1]; }
		void push(const T& t)
		{
			_deque.push_back(t);
		}
		void pop()
		{
			_deque.pop_front();
		}
	private:
		deque<T> _deque;
	};
}