#pragma once

namespace mystd{

template <typename T>
class vectorIterator;

template <typename T>
class vector
{
public:
	vector()
	{
		init(0);
	}
	vector(unsigned int size)
	{
		init(size);
	}
	vector(unsigned int size, T arg)
	{
		init(size);
		for (int i = 0; i < size; i++)
		{
			_elements[i] = arg;
		}
	}
	vector(vector<T>& v)
	{	
		init(v.size());
		copy(v);
	}
	vector(vector<T>&& v)
	{
		_elements = v._elements;
		_size = v._size;
		_capacity = v._capacity;

		v._elements = nullptr;
		v._size = 0;
		v._capacity = 0;
	}
	~vector()
	{
		reset();
	}

	vector<T>& operator=(vector<T>& v)
	{
		reset();
		init(v.size());
		copy(v);

		return *this;
	}
	vector<T>& operator=(vector<T>&& v)
	{
		reset();
		_elements = v._elements;
		_size = v._size;
		_capacity = v._capacity;

		v._elements = nullptr;
		v._size = 0;
		v._capacity = 0;

		return *this;
	}
	T& operator[](int index)
	{
		return _elements[index];
	}

	void clear()
	{
		reset();
	}

	void push_back(T arg)
	{
		if (_size == _capacity)
		{
			// TODO : Handle _size = 0;
			if (_capacity == 0)
			{
				_capacity = 1;
			}

			unsigned int newCapacity = _capacity * 2;
			T* newElements = new T[newCapacity];
			for (int i = 0; i < _size; i++)
			{
				newElements[i] = _elements[i];
			}
			delete[] _elements;
			_elements = newElements;
			_capacity = newCapacity;
			
		}
		
		_elements[_size] = arg;
		_size++;
	}

	void pop_back()
	{
		if (_size > 0)
		{
			_size--;
		}
	}

	//void insert(vectorIterator<T>& iter, T)
	
	void swap(vector<T>& v)
	{
		T* tempElements = _elements;
		unsigned int tempSize = _size;
		unsigned int tempCapacity = _capacity;

		_elements = v._elements;
		_size = v._size;
		_capacity = v._capacity;

		v._elements = tempElements;
		v._size = tempSize;
		v._capacity = tempCapacity;
	}
	unsigned int size()
	{
		return _size;
	}
	unsigned int capacity()
	{
		return _capacity;
	}

	vectorIterator<T> begin()
	{
		return vectorIterator<T>(*this, 0);
	}
	vectorIterator<T> end()
	{
		return vectorIterator<T>(*this, _size);
	}

private:

	void init(unsigned int size)
	{
		_elements = nullptr;
		if (size)
		{
			_elements = new T[size];
		}

		_size = size;
		_capacity = size;
	}

	void reset()
	{
		if (_elements)
		{
			delete[] _elements;
		}
		_size = 0;
		_capacity = 0;
	}

	void copy(vector<T>& v)
	{
		if (v.size() > 0)
		{
			for (int i = 0; i < v.size(); i++)
			{
				_elements[i] = v[i];
			}
		}
	}

	T* _elements;
	unsigned int _size;
	unsigned int _capacity;
};



template <typename T>
class vectorIterator
{
public:
	vectorIterator(vector<T>& vector, unsigned int pos) : 
		_vector(vector), 
		_pos(pos) 
	{
	}

	T* operator -> ()
	{
		return &_vector[_pos];
	}
	T& operator * ()
	{
		return _vector[_pos];
	}
	vectorIterator<T> operator ++ (int)
	{
		_pos++;
		return *this;
	}
	vectorIterator<T> operator -- (int)
	{
		_pos--;
		return *this;
	}
	bool operator == (vectorIterator<T>& iter)
	{
		if (_pos == iter._pos)
			return true;
		return false;
	}
	bool operator != (vectorIterator<T>& iter)
	{
		if (_pos != iter._pos)
			return true;
		return false;
	}

private:
	unsigned int _pos;
	vector<T>& _vector;
};

}