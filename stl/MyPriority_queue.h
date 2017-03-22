#pragma once
#include <functional>
#include <vector>

namespace mystd {
    template <typename T>
    class priority_queue
    {
    public:
        priority_queue()
        {
            _comparator = [](const T& a, const T& b)
            {
                // default to max heap
                if (a < b)
                    return true;
                return false;
            };
        }
        priority_queue(std::function<bool(const T& a, const T& b)> comparator) : _comparator(comparator) {}
        ~priority_queue() {}

        unsigned int size()
        {
            return _size;
        }
        void clear()
        {
            _elements.clear();
            _size = 0;
        }
        void swap(priority_queue<T>& pq)
        {
            _elements.swap(pq._elements);
			swap(_size, pq._size);
			swap(_comparator, pq._comparator);
        }

        T& top()
        {
			return _elements[0];
        }
        void push(const T& t)
        {
            if (_size == _elements.size())
            {
                _elements.push_back(t);
                ++_size;
            }
            else
            {
                _elements[_size++] = t;
            }

            heapifyup(_size - 1);
        }
        void pop()
        {
			_elements[0] = _elements[_size-1];
			--_size;

			heapifydown(0);
        }

    private:
        std::vector<T> _elements;
        unsigned int _size = 0;
        std::function<bool(const T& a, const T& b)> _comparator;

		void swap(T& a, T& b)
		{
			T temp = a;
			a = b;
			b = temp;
		}

		bool IsInRange(unsigned int i)
		{
			if (i < _size)
				return true;
			return false;
		}

        void heapifyup(unsigned int currentPos)
        {
            if (currentPos == 0) { return; }
            
            unsigned int parentPos = (currentPos - 1) / 2;
            if (_comparator(_elements[currentPos], _elements[parentPos])) { return;  }

			swap(_elements[parentPos], _elements[currentPos]);

            heapifyup(parentPos);
        }

		void heapifydown(unsigned int currentPos)
		{
			unsigned int leftChildPos = (currentPos * 2) + 1;
			unsigned int rightChildPos = (currentPos * 2) + 2;

			if (!IsInRange(leftChildPos) && !IsInRange(rightChildPos)) // no children
			{
				return; 
			}
			else if (IsInRange(leftChildPos) && IsInRange(rightChildPos)) // have both children
			{
				if (_comparator(_elements[rightChildPos], _elements[leftChildPos]))
				{
					if (_comparator(_elements[currentPos], _elements[leftChildPos]))
					{
						swap(_elements[currentPos], _elements[leftChildPos]);
						heapifydown(leftChildPos);
					}
				}
				else
				{
					if (_comparator(_elements[currentPos], _elements[rightChildPos]))
					{
						swap(_elements[currentPos], _elements[rightChildPos]);
						heapifydown(rightChildPos);
					}
				}
			}
			else // only left child
			{
				if (_comparator(_elements[currentPos], _elements[leftChildPos]))
				{
					swap(_elements[currentPos], _elements[leftChildPos]);
					heapifydown(leftChildPos);
				}
			}
		}
    };
}