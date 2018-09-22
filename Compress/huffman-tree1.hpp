#pragma once

#include "Heap1.hpp"

template<class T>
struct HuffmanTreeNode
{
	HuffmanTreeNode<T>* _left;
	HuffmanTreeNode<T>* _right;
	HuffmanTreeNode<T>* _parent;
	T _weight;

	HuffmanTreeNode(const T& weight)
		:_left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _weight(weight)
	{}
};

template<class T>
class HuffmanTree
{
	typedef HuffmanTreeNode<T> Node;

public:
	HuffmanTree()
		:_root(NULL)
	{}

	~HuffmanTree()
	{
		_Destory(_root);
	}

	HuffmanTree(const T* a, size_t size, const T& invalid)
	{
		_root = _CreateTree(a, size, invalid);
	}

	Node* GetRoot()
	{
		return _root;
	}

protected:
	Node* _CreateTree(const T* a, size_t size, const T& invalid)
	{
		//assert(a);

		struct Compare
		{
			bool operator()(const Node* l, const Node* r)
			{
				return l->_weight < r->_weight;
			}
		};

		Heap<Node*, Compare> minHeap;
		for (size_t i = 0; i < size; ++i)
		{
			if (a[i] != invalid)
			{
				minHeap.Push(new Node(a[i]));
			}
		}

		while (minHeap.Size() > 1)
		{
			Node* left = minHeap.Top();
			minHeap.Pop();
			Node* right = minHeap.Top();
			minHeap.Pop();

			Node* parent = new Node(left->_weight + right->_weight);
			parent->_left = left;
			parent->_right = right;
			left->_parent = parent;
			right->_parent = parent;

			minHeap.Push(parent);
		}

		return minHeap.Top();
	}

	void _Destory(Node* root)
	{
		if (root == NULL)
			return;

		_Destory(root->_left);
		_Destory(root->_right);
	}

protected:
	Node* _root;
};

void HuffmanTreeTest()
{
	int a[] = { 0,1,2,3,4,5,6,7,8,9 };
	HuffmanTree<int> ht(a, 10, -1);

}