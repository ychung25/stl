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

            unsigned int tempSize = _size;
            _size = pq._size;
            pq._size = tempSize;

            std::function<bool(const T& a, const T& b)> tempComparator = _comparator;
            _comparator = pq._comparator;
            pq._comparator = tempComparator;

        }

        T& top()
        {
            return _elements.front();
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

        }

    private:
        std::vector<T> _elements;
        unsigned int _size = 0;
        std::function<bool(const T& a, const T& b)> _comparator;

        void heapifyup(unsigned int current)
        {
            if (current == 0) { return; }
            
            unsigned int parent = (current - 1) / 2;
            if (_comparator(current, parent)) { return;  }

            T tempVal = _elements[parent];
            _elements[parent] = _elements[current];
            _elements[current] = tempVal;

            heapifyup(parent);
        }

    };
}