#pragma once
#include <utility>

namespace mystd
{

	template<typename T>
	class setIterator;

	template<typename T>
	struct set_node
	{
		T data;
		set_node<T>* left = nullptr;
		set_node<T>* right = nullptr;
		set_node<T>* parent = nullptr;
	};

	template<typename T>
	class set
	{
	public:
		set()
		{

		}
		~set()
		{

		}

		unsigned int size()
		{
			return _size;
		}

		setIterator<T> begin()
		{
			set_node<T>* leftMost = _root;
			while (leftMost->left)
			{
				leftMost = leftMost->left;
			}
			return setIterator<T>(leftMost);
		}

		setIterator<T> end()
		{
			return setIterator<T>(nullptr);
		}

		std::pair<setIterator<T>,bool> insert(const T& t)
		{
			bool exists = false;
			set_node<T>* insertedNode = nullptr;

			_root = insert(t, _root, exists, insertedNode);
			return std::make_pair(setIterator<T>(insertedNode), exists);
		}

		setIterator<T> find(const T& t)
		{
			return find(t, _root);
		}

		setIterator<T> erase(setIterator<T> iter)
		{
			_size--;

			setIterator<T> nextIter = iter;
			nextIter++;

			if (deleteNode(iter._node))
			{
				return nextIter;
			}
			else
			{
				iter._node->data = nextIter._node->data;
				deleteNode(nextIter._node);
				return iter;
			}
		}

	private:

		bool deleteNode(set_node<T>* nodeToDelete)
		{

			if (nodeToDelete->left == nullptr && nodeToDelete->right == nullptr)
			{
				if (nodeToDelete->parent)
				{
					if (nodeToDelete->parent->left == nodeToDelete)
					{
						nodeToDelete->parent->left = nullptr;
					}
					else
					{
						nodeToDelete->parent->right = nullptr;
					}
				}
				else
				{
					_root = nullptr;
				}
				delete nodeToDelete;
				return true;
			}
			else if (nodeToDelete->left != nullptr && nodeToDelete->right == nullptr)
			{
				if (nodeToDelete->parent)
				{
					if (nodeToDelete->parent->left == nodeToDelete)
					{
						nodeToDelete->parent->left = nodeToDelete->left;
						nodeToDelete->left->parent = nodeToDelete->parent;
					}
					else
					{
						nodeToDelete->parent->right = nodeToDelete->left;
						nodeToDelete->left->parent = nodeToDelete->parent;
					}
				}
				else
				{
					nodeToDelete->left->parent = nullptr;
					_root = nodeToDelete->left;
				}

				delete nodeToDelete;
				return true;
			}
			else if (nodeToDelete->left == nullptr && nodeToDelete->right != nullptr)
			{
				if (nodeToDelete->parent)
				{
					if (nodeToDelete->parent->left == nodeToDelete)
					{
						nodeToDelete->parent->left = nodeToDelete->right;
						nodeToDelete->right->parent = nodeToDelete->parent;
					}
					else
					{
						nodeToDelete->parent->right = nodeToDelete->right;
						nodeToDelete->right->parent = nodeToDelete->parent;
					}
				}
				else
				{
					nodeToDelete->right->parent = nullptr;
					_root = nodeToDelete->right;
				}

				delete nodeToDelete;
				return true;
			}

			return false;
		}

		set_node<T>* insert(const T& t, set_node<T>* node, bool& exists, set_node<T>*& insertedNode)
		{
			if (node == nullptr)
			{
				set_node<T>* newNode = new set_node<T>();
				newNode->data = t;
				_size++;
				exists = false;
				insertedNode = newNode;
				return newNode;
			}
			
			if(t < node->data)
			{
				set_node<T>* childNode = insert(t, node->left, exists, insertedNode);
				node->left = childNode;
				childNode->parent = node;
			}
			else if (t > node->data)
			{
				set_node<T>* childNode = insert(t, node->right, exists, insertedNode);
				node->right = childNode;
				childNode->parent = node;
			}
			else
			{
				insertedNode = node;
				exists = true;
			}

			return node;
		}

		setIterator<T> find(const T& t, set_node<T>* node)
		{
			if (node == nullptr)
			{
				return setIterator<T>(nullptr);
			}
			
			if (t == node->data)
			{
				return setIterator<T>(node);
			}
			else if (t < node->data)
			{
				return find(t, node->left);
			}
			else
			{
				return find(t, node->right);
			}
		}

		set_node<T>* _root = nullptr;
		unsigned int _size = 0;
	};

	template<typename T>
	class setIterator
	{
	public:
		setIterator(set_node<T>* node) : _node(node)
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

		setIterator<T> operator++(int)
		{
			setIterator<T> temp(_node);

			//  go to most left of direct right
			if (_node->right)
			{
				set_node<T>* leftNode = _node->right;
				while (leftNode->left)
				{
					leftNode = leftNode->left;
				}
				_node = leftNode;
			}
			else
			{
				if (_node->parent == nullptr)
				{
					_node = nullptr;
				}
				else
				{
					if (_node->parent->left == _node)
					{
						// if left child, go to parent
						_node = _node->parent;
					}
					else
					{

						// if right child, go to top most parent that you follow up as left
						while (_node)
						{
							set_node<T>* currentNode = _node;
							set_node<T>* parentNode = _node->parent;
							_node = parentNode;
							if (parentNode == nullptr || parentNode->left == currentNode)
							{
								break;
							}
						}
					}
				}
			}


			return temp;
		}

		setIterator<T> operator--(int)
		{
			setIterator<T> temp(_node);
			// Just do the opposite of ++
			return temp;
		}

		bool operator==(setIterator<T> rhs)
		{
			if (_node == rhs._node)
			{
				return true;
			}
			return false;
		}
		bool operator!=(setIterator<T> rhs)
		{
			return !(*this == rhs);
		}

	private:
		set_node<T>* _node = nullptr;
		friend class set<T>;
	};
}