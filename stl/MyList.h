#pragma once

namespace mystd {

	template<typename T>
	struct Node
	{
		T data;
		Node* prev = nullptr;
		Node* next = nullptr;
	};

	template<typename T>
	class listIterator;

	template<typename T>
	class list
	{
	public:
		list() {}

		listIterator<T> begin()
		{
			return listIterator<T>(_head);
		}
		listIterator<T> end()
		{
			return listIterator<T>(nullptr);
		}

		unsigned int size()
		{
			return _size;
		}

		T& front()
		{
			return _head->data;
		}
		T& back()
		{
			return _tail->data;
		}

		void push_back(const T& t)
		{
			Node<T>* node = new Node<T>();
			node->data = t;

			if (_tail == nullptr)
			{
				_head = node;
				_tail = node;
			}
			else
			{
				_tail->next = node;
				node->prev = _tail;
				_tail = node;
			}

			_size++;
		}
		void pop_back()
		{
			Node<T>* newTail = _tail->prev;
			delete _tail;

			if (newTail == nullptr)
			{
				_head = nullptr;
				_tail = nullptr;
			}
			else
			{
				newTail->next = nullptr;
				_tail = newTail;
			}

			_size--;
		}
		void push_front(const T& t)
		{
			Node<T>* newNode = new Node<T>();
			newNode->data = t;
			
			if (_head == nullptr)
			{
				_head = newNode;
				_tail = newNode;
			}
			else
			{
				_head->prev = newNode;
				newNode->next = _head;
				_head = newNode;
			}

			_size++;
		}
		void pop_front()
		{
			Node<T>* newHead = _head->next;
			delete _head;
			if (newHead == nullptr)
			{
				_head = nullptr;
				_tail = nullptr;
			}
			else
			{
				newHead->prev = nullptr;
				_head = newHead;
			}

			_size--;
		}

		listIterator<T> insert(const listIterator<T>& posIter, const T& t)
		{
			if (posIter._node == nullptr)
			{
				push_back(t);
				return listIterator<T>(_tail);
			}

			Node<T>* newNode = new Node<T>();
			newNode->data = t;

			Node<T>* current = posIter._node;
			Node<T>* before = current->prev;
			
			newNode->next = current;
			current->prev = newNode;

			if(before == nullptr)
			{ 
				_head = newNode;
			}
			else
			{
				before->next = newNode;
				newNode->prev = before;
			}

			_size++;

			return listIterator<T>(newNode);
		}
		listIterator<T> insert(listIterator<T>& posIter, listIterator<T>& startIter, listIterator<T>& endIter)
		{
			Node<T>* firstInserted = nullptr;
			for(;startIter != endIter; startIter++)
			{
				insert(posIter, *startIter);
				if (firstInserted == nullptr)
				{
					firstInserted = posIter._node->prev;
				}
			}

			return listIterator<T>(firstInserted);
		}

		listIterator<T> erase(listIterator<T>& posIter)
		{
			Node<T>* nodeAfterErased = nullptr;
			Node<T>* current = posIter._node;

			if (_tail == _head)
			{
				delete _tail;
				_head = nullptr;
				_tail = nullptr;
			}
			else if (current == _tail)
			{
				Node<T>* before = _tail->prev;
				delete _tail;
				before->next = nullptr;
				_tail = before;
			}
			else if (current == _head)
			{
				Node<T>* after = _head->next;
				delete _head;
				after->prev = nullptr;
				_head = after;
				nodeAfterErased = _head;
			}
			else
			{
				Node<T>* before = current->prev;
				Node<T>* after = current->next;
				delete current;
				before->next = after;
				after->prev = before;
				nodeAfterErased = after;
			}

			_size--;

			return listIterator<T>(nodeAfterErased);
		}
		listIterator<T> erase(listIterator<T>& startIter, listIterator<T>& endIter)
		{
			Node<T>* current = startIter._node;

			Node<T>* before = startIter._node->prev;
			Node<T>* after = endIter._node;

			int len = 0;
			for (; startIter != endIter; startIter++)
			{
				len++;
			}
			for(int i = 0; i < len; i++)
			{
				Node<T>* next = current->next;
				delete current;
				current = next;
			}

			if (before == nullptr)
			{
				_head = after;
				if (after)
				{
					after->prev = nullptr;
				}
			}
			else
			{
				before->next = after;
				if (after)
				{
					after->prev = before;
				}

			}

			if (after == nullptr)
			{
				_tail = before;
				if (before)
				{
					before->next = nullptr;
				}
			}
			else
			{
				after->prev = before;
				if (before)
				{
					before->next = after;
				}
			}

			return listIterator<T>(after);

		}

		void swap(const list<T>& l)
		{
			T* headTemp = l._head;
			T* tailTemp = l._tail;
			unsigned int sizeTemp = l._size;

			l._head = _head;
			l._tail = _tail;
			l._size = _size;

			_head = headTemp;
			_tail = tailTemp;
			_size = sizeTemp;
		}

	private:

		Node<T>* _head = nullptr;
		Node<T>* _tail = nullptr;
		unsigned int _size = 0;
	};

	template<typename T>
	class listIterator
	{
	public:
		listIterator(Node<T>* node) : _node(node) {}

		T* operator->()
		{
			return &(_node->data);
		}
		T& operator*()
		{
			return _node->data;
		}

		listIterator<T> operator++(int)
		{
			listIterator<T> temp(_node);
			_node = _node->next;
			return temp;
		}
		listIterator<T> operator--(int)
		{
			listIterator<T> temp(_node);
			_node = _node->prev;
			return temp;
		}

		bool operator==(const listIterator<T>& l)
		{
			if (_node == l._node)
			{
				return true;
			}
			return false;
		}
		bool operator!=(const listIterator<T>& l)
		{
			return !(*this == l);
		}

	private:
		Node<T>* _node;

		friend class list<T>;
	};
}
