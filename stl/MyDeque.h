#pragma once
// Deque is basically a vector with push_front and pop_front operations.

namespace mystd {

	template<typename T>
	class dequeIterator;

	template <typename T>
	class deque
	{
	public:
		deque() 
		{
		}
		deque(const deque<T>& rhs)
		{
			_capacity = rhs._capacity;
			_head = rhs._head;
			_tail = rhs._tail;

			_elements = new T[_capacity];
			for (int i = 0; i < _capacity; i++)
			{
				_elements[i] = rhs._elements[i];
			}
		}
		~deque()
		{
			if (_elements)
				delete[] _elements;
		}

		unsigned int size()
		{
			return _tail - _head - 1;
		}

		dequeIterator<T> begin()
		{
			return dequeIterator<T>(_elements, _head+1);
		}
		dequeIterator<T> end()
		{
			return dequeIterator<T>(_elements, _tail);
		}

		T& operator[](int i)
		{
			return _elements[_head + i + 1];
		}

		void push_back(const T& t)
		{
			if (_tail == _capacity)
			{
				unsigned int newCapacity;
				if (_capacity == 0)
				{
					newCapacity = 1;
				}
				else
				{
					newCapacity = _capacity * 2;
				}

				T* newElements = new T[newCapacity];
				for (unsigned int i = 0; i < _capacity; i++)
				{
					newElements[i] = _elements[i];
				}
				
				delete[] _elements;
				_elements = newElements;
				_capacity = newCapacity;
			}
			
			_elements[_tail++] = t;
		}
		void pop_back()
		{
			--_tail;
		}
		void push_front(const T& t)
		{
			if (_head == -1)
			{
				unsigned int newCapacity;
				if (_capacity == 0)
				{
					newCapacity = 1;
				}
				else
				{
					newCapacity = _capacity * 2;
				}

				T* newElements = new T[newCapacity];

				unsigned int diff = newCapacity - _capacity;

				for (int i = 0; i < _capacity; i++)
				{
					newElements[i + diff] = _elements[i];
				}

				_head += diff;
				_tail += diff;

				_capacity = newCapacity;
				delete[] _elements;
				_elements = newElements;
			}
			
			_elements[_head--] = t;
		}
		void pop_front()
		{
			++_head;
		}

		dequeIterator<T> insert(const dequeIterator<T>& posIter, const T& arg)
		{
			unsigned int diff = const_cast<dequeIterator<T>&>(posIter)._pos - _head;
			push_front(arg);
			T temp = _elements[_head + 1];

			for (unsigned int i = _head + 1; i < _head + diff; i++)
			{
				_elements[i] = _elements[i + 1];
			}
			_elements[_head + diff] = temp;
			
			return dequeIterator<T>(_elements, _head + diff);
		}
		dequeIterator<T> insert(dequeIterator<T>& posIter, dequeIterator<T>& startIter, dequeIterator<T>& endIter)
		{
			dequeIterator<T> temp(_elements, 0);
			for (; startIter != endIter; startIter++)
			{
				posIter = insert(posIter, *startIter);
				temp = posIter;
				posIter++;
			}

			return dequeIterator<T>(_elements, posIter._pos);

		}
		dequeIterator<T> erase(dequeIterator<T>& posIter)
		{
			unsigned int pos = posIter._pos;
			for (int i = pos; pos < _tail - 1; pos++)
			{
				_elements[pos] = _elements[pos + 1];
			}
			--_tail;
			return dequeIterator<T>(_elements, posIter._pos);
		}
		dequeIterator<T> erase(dequeIterator<T>& startIter, dequeIterator<T>& endIter)
		{
			unsigned int pos = startIter._pos;
			unsigned int diff = endIter._pos - startIter._pos + 1;
			for (int i = pos; (i < (_tail - 1)) && (pos + diff < _tail); pos++)
			{
				_elements[pos] = _elements[pos + diff];
			}
			_tail -= diff;
			return dequeIterator<T>(_elements, startIter._pos);
		}

		

	private:

		unsigned int _head = -1;
		unsigned int _tail = 0;
		unsigned int _capacity = 0;
		T* _elements = nullptr;
	};

	template<typename T>
	class dequeIterator
	{
	public:
		dequeIterator(T* d, unsigned int p) : _deque(d), _pos(p) {}

		T* operator->()
		{
			return &_deque[_pos];
		}
		T& operator*()
		{
			return _deque[_pos];
		}

		dequeIterator<T> operator++(int)
		{
			return dequeIterator<T>(_deque, _pos++);
		}
		dequeIterator<T> operator--(int)
		{
			return dequeIterator<T>(_deque, _pos--);
		}

		bool operator == (dequeIterator<T>& rhs)
		{
			if (_pos == rhs._pos)
				return true;
			return false;
		}

		bool operator != (dequeIterator<T>& rhs)
		{
			return !(*this == rhs);
		}

	private:
		unsigned int _pos;
		T* _deque;

		friend class deque<T>;
	};



}