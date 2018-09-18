#pragma once

#include <vector>

//·Âº¯Êý
template<class T>
struct Lesser
{
	bool operator()(const T& l, const T& r)
	{
		return l < r;
	}
};

template<class T>
struct Greater
{
	bool operator()(const T& l, const T& r)
	{
		return l > r;
	}
};

template<class T, class Compare = Lesser<T>>
class Heap
{
public:
	Heap()
	{}

	Heap(const T* a, size_t size)
	{
		for (size_t i = 0; i < size; ++i)
		{
			_a.push_back(a[i]);
		}
		for (int i = (_a.size() - 2) / 2; i >= 0; --i)
		{
			_AdjustDown(i);
		}
	}

	void Push(const T& x)
	{
		_a.push_back(x);
		_AdjustUp(_a.size() - 1);
	}

	void Pop()
	{
		//assert(!_a.empty());

		swap(_a[0], _a[_a.size() - 1]);
		_a.pop_back();
		_AdjustDown(0);
	}

	T& Top()
	{
		//assert(!_a.empty());

		return _a[0];
	}

	bool Empty()
	{
		return _a.empty();
	}

	size_t Size()
	{
		return _a.size();
	}

protected:
	void _AdjustUp(int child)
	{
		Compare cmp;
		int parent = (child - 1) / 2;

		while (child > 0)//parent>=0 ?
		{
			if (cmp(_a[child], _a[parent]))
			{
				swap(_a[child], _a[parent]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
			{
				break;
			}
		}
	}

	void _AdjustDown(int parent)
	{
		Compare cmp;
		int child = parent * 2 + 1;

		while (child < _a.size())
		{
			if (child + 1 < _a.size() && cmp(_a[child + 1], _a[child]))
			{
				++child;
			}

			if (cmp(_a[child], _a[parent]))
			{
				swap(_a[child], _a[parent]);
				parent = child;
				child = parent * 2 + 1;
			}
			else
			{
				break;
			}
		}
	}

protected:
	vector<T> _a;
};