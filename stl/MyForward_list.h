#pragma once

namespace mystd {

	template<typename T>
	class forward_listIterator;
	
	namespace fl
	{
		template<typename T>
		struct Node
		{
			fl::Node<T>* next = nullptr;
			T data;
		};
	}

	template<typename T>
	class forward_list
	{
	public:
		forward_list() {}
		~forward_list()
		{
			if (_head) { delete[] _head; }
		}

		forward_listIterator<T> before_begin()
		{
			return forward_listIterator<T>(nullptr, true);
		}
		forward_listIterator<T> begin()
		{
			return forward_listIterator<T>(_head, false);
		}
		forward_listIterator<T> end()
		{
			return forward_listIterator<T>(nullptr, false);
		}

		T& front()
		{
			return _head->data;
		}
		void push_front(const T& t)
		{
			fl::Node<T>* newNode = new fl::Node<T>();
			newNode->data = t;
			newNode->next = _head;
			_head = newNode;
		}
		void pop_front()
		{
			fl::Node<T>* newHead = _head->next;
			delete _head;
			_head = newHead;
		}

		forward_listIterator<T> insert_after(forward_listIterator<T> posIter, T t)
		{
			if (posIter._isBeforeBegin == true)
			{
				push_front(t);
				return begin();
			}
			else
			{
				fl::Node<T>* newNode = new fl::Node<T>;
				newNode->data = t;

				fl::Node<T>* posNode = posIter._node;
				fl::Node<T>* nextNode = posNode->next;
				posNode->next = newNode;
				newNode->next = nextNode;
				return forward_listIterator<T>(newNode, false);
			}
		}
		forward_listIterator<T> erase_after(forward_listIterator<T> posIter)
		{
			if (posIter._isBeforeBegin == true)
			{
				pop_front();
				return begin();
			}
			else
			{
				fl::Node<T>* posNode = posIter._node;
				fl::Node<T>* nodeToDelete = posNode->next;
				if (nodeToDelete == nullptr)
				{
					// posNode was the last node
					return forward_listIterator<T>(nullptr, false);
				}
				else
				{
					posNode->next = nodeToDelete->next;
					delete nodeToDelete;
					return forward_listIterator<T>(posNode->next, false);
				}

			}
		}

	private:
		fl::Node<T>* _head = nullptr;
	};

	template<typename T>
	class forward_listIterator
	{
	public:
		forward_listIterator(fl::Node<T>* node, bool isBeforeBegin) : _node(node), _isBeforeBegin(isBeforeBegin)
		{
		}

		T* operator->()
		{
			return &_node->data;
		}
		T& operator*()
		{
			return _node->data;
		}
		forward_listIterator<T> operator++(int)
		{
			fl::Node<T>* temp = _node;
			_node = _node->next;
			return forward_listIterator<T>(temp, _isBeforeBegin);
		}
		bool operator==(forward_listIterator<T> rhs)
		{
			if (_node == rhs._node)
			{
				return true;
			}
			return false;
		}
		bool operator!=(forward_listIterator<T> rhs)
		{
			return !(*this == rhs);
		}
		
	private:
		bool _isBeforeBegin = false;
		fl::Node<T>* _node = nullptr;

		friend class forward_list<T>;
	};
}