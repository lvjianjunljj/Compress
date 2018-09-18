#pragma once

#include <iostream>
#include <assert.h>
#include <queue>
#include <vector>

template <typename T>
struct HuffmanTreeNode2
{
	HuffmanTreeNode2(const T &data)
		: _weight(data)
		, pLeft(NULL)
		, pRight(NULL)
		, pParent(NULL)
	{}

	T 		_weight;
	HuffmanTreeNode2 *pLeft;
	HuffmanTreeNode2 *pRight;
	HuffmanTreeNode2 *pParent;
};

template <typename T>
struct bigger
{
	bool operator()(const T &left, const T &right)
	{
		return left->_weight > right->_weight;
	}
};


template <typename T>
class HuffmanTree2
{
public:
	HuffmanTree2(const T *weight, int size, const T &invalid)
		: pRoot(NULL)
		, _invalid(invalid)
	{
		assert(NULL != weight && size >= 0);
		_Create(weight, size);
	}

	~HuffmanTree2()
	{
		_Destroy(pRoot);
	}

	void LevelTraverse()
	{
		std::queue<HuffmanTreeNode2<T> *> q;
		if (NULL != pRoot)
			q.push(pRoot);

		while (!q.empty())
		{
			HuffmanTreeNode2<T> *pCur = q.front();
			q.pop();
			std::cout << pCur->_weight << " ";

			if (NULL != pCur->pLeft)
				q.push(pCur->pLeft);
			if (NULL != pCur->pRight)
				q.push(pCur->pRight);
		}

		std::cout << std::endl;
	}

	HuffmanTreeNode2<T> * GetRoot()
	{
		return pRoot;
	}

private:
	void _Destroy(HuffmanTreeNode2<T> * &pRoot)
	{
		if (NULL != pRoot)
		{
			_Destroy(pRoot->pLeft);
			_Destroy(pRoot->pRight);
			delete pRoot;
			pRoot = NULL;
		}
	}

	void _Create(const T *weight, int size)
	{
		if (0 == size)
			return;
		else if (1 == size)
		{
			if (*weight != _invalid)
				pRoot = new HuffmanTreeNode2<T>(*weight);
		}
		else
		{
			std::priority_queue<HuffmanTreeNode2<T> *, std::vector<HuffmanTreeNode2<T> *>, bigger<HuffmanTreeNode2<T> *> >
				heap;

			for (int i = 0; i < size; ++i)
			{
				if (weight[i] != _invalid)
				{
					HuffmanTreeNode2<T> *tmp = new HuffmanTreeNode2<T>(weight[i]);
					heap.push(tmp);
				}
			}

			HuffmanTreeNode2<T> *pLeft, *pRight;
			while (heap.size() >= 2)
			{
				pLeft = heap.top();
				heap.pop();
				pRight = heap.top();
				heap.pop();

				HuffmanTreeNode2<T> *pParent = new HuffmanTreeNode2<T>(pLeft->_weight + pRight->_weight);
				pParent->pLeft = pLeft;
				pParent->pRight = pRight;
				pLeft->pParent = pParent;
				pRight->pParent = pParent;

				heap.push(pParent);
			}
			if (!heap.empty())
				pRoot = heap.top();
		}
	}

private:
	HuffmanTreeNode2<T>	*pRoot;
	T					_invalid;
};