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
	vector(const vector<T>& v)
	{	
		init(v.size());
		copy(v);
	}
	~vector()
	{
		reset();
	}

	vector<T>& operator=(vector<T> v)
	{
		reset();
		init(v.size());
		copy(v);

		return *this;
	}

	T& operator[](int index)
	{
		return _elements[index];
	}

	void push_back(T arg)
	{
		increaseCapacityIfNeeded();
		_elements[_size] = arg;
		_size++;
	}
	void pop_back()
	{
		_size--;
	}

	void insert(vectorIterator<T> iter, T arg)
	{
		increaseCapacityIfNeeded();

		unsigned int pos = iter._pos;
		T* newElements = new T[_capacity];

		for (int i = 0; i < _size; i++)
		{
			if (i < pos)
			{
				newElements[i] = _elements[i];
			}
			else
			{
				newElements[i + 1] = _elements[i];
			}
		}
		newElements[pos] = arg;
		delete[] _elements;
		_elements = newElements;
		_size++;
	}
	void erase(vectorIterator<T> iter)
	{
		unsigned int pos = iter._pos;
		for (int i = pos; i < _size-1; i++)
		{
			_elements[i] = _elements[i + 1];
		}
		_size--;
	}

	void swap(vector<T> v)
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
	void clear()
	{
		reset();
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
		return vectorIterator<T>(_elements, 0);
	}
	vectorIterator<T> end()
	{
		return vectorIterator<T>(_elements, _size);
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

	void increaseCapacityIfNeeded()
	{
		if (_size == _capacity)
		{
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
	}

	T* _elements;
	unsigned int _size;
	unsigned int _capacity;
};



template <typename T>
class vectorIterator
{
public:
	vectorIterator(T* vector, unsigned int pos) : 
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
		vectorIterator<T> temp(_vector, _pos);
		_pos++;
		return temp;
	}
	vectorIterator<T> operator -- (int)
	{
		vectorIterator<T> temp(_vector, _pos);
		_pos--;
		return temp;
	}
	bool operator == (vectorIterator<T> iter)
	{
		if (_pos == iter._pos)
			return true;
		return false;
	}
	bool operator != (vectorIterator<T> iter)
	{
		return !(*this == iter);
	}

private:
	unsigned int _pos;
	T* _vector;

	friend class vector<T>;
};

}