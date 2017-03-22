#pragma once
#include "MyList.h"
#include "MyVector.h"

namespace mystd {
	template<typename T>
	class listStack;

	template<typename T>
	class vectorStack;

	template<typename T>
	class stack
	{
	public:
		void useVectorStack() { _useListStack = false; }

		T& top()
		{
			if (_useListStack)
				return _listStack.top();
			else
				return _vectorStack.top();
		}

		unsigned int size()
		{
			if (_useListStack)
				return _listStack.size();
			else
				return _vectorStack.size();
		}

		void push(const T& t)
		{
			if (_useListStack)
				return _listStack.push(t);
			else
				return _vectorStack.push(t);
		}

		void pop()
		{
			if (_useListStack)
				return _listStack.pop();
			else
				return _vectorStack.pop();
		}

	private:
		bool _useListStack = true;
		listStack<T> _listStack;
		vectorStack<T> _vectorStack;
	};

	template<typename T>
	class listStack
	{
	public:
		unsigned int size() { return _list.size(); }

		T& top()
		{
			return _list.back();
		}
		void push(const T& t)
		{
			_list.push_back(t);
		}
		void pop()
		{
			_list.pop_back();
		}
	private:
		list<T> _list;
	};


	template<typename T>
	class vectorStack
	{
	public:
		unsigned int size() { return _vector.size(); }
		T& top() { return _vector[_vector.size()-1]; }

		void push(const T& t)
		{
			_vector.push_back(t);
		}
		void pop()
		{
			_vector.pop_back();
		}

	private:
		vector<T> _vector;
	};
}