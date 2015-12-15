#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <string>
#include <cmath>
#include <deque>
#include <queue>
#include <stack>
#include <climits>
#include <ctime>
#include <cstdio>
#include <bitset>
#include <cstring>
#include "Heap.h"

template<typename T> class BinomialHeap : public Heap<T> {
private:
	std::vector<BinomialHeap<T>*> nodes;
	T value;
	int degree;
	BinomialHeap<T> *parent;

public:

	int nodesSize;

	BinomialHeap() {
		parent = nullptr;
		nodesSize = 0;
	}

	BinomialHeap(T val) {
		value = val;
		degree = 1;
		parent = nullptr;
		nodesSize = 0;
	}

	T extractMin() {
		int mpos = 0;
		if (!nodes.size())
			return mmax;
		T minVal = nodes[0]->value;
		for (int i = 0; i < nodes.size(); i++) {
			if (nodes[i]->value < minVal) {
				minVal = nodes[i]->value;
				mpos = i;
			}
		}
		for (int i = mpos; i < nodes.size() - 1; i++) {
			std::swap(nodes[i], nodes[i + 1]);
		}
		BinomialHeap<T> *tmpHeap = new BinomialHeap<T>();
		tmpHeap->nodes = nodes[nodes.size() - 1]->nodes;
		nodes.pop_back();
		merge(tmpHeap);
		nodesSize = nodes.size();
		return minVal;
	}

	void merge(BinomialHeap<T> *addedHeap) {
		std::vector<BinomialHeap<T>*> tmpv;
		size_t pos1 = 0, pos2 = 0;
		while (pos1 < nodes.size() && pos2 < addedHeap->nodes.size()) {
			if (nodes[pos1]->degree < addedHeap->nodes[pos2]->degree) {
				tmpv.push_back(nodes[pos1]);
				pos1++;
			}
			else {
				tmpv.push_back(addedHeap->nodes[pos2]);
				pos2++;
			}
		}
		while (pos1 < nodes.size()) {
			tmpv.push_back(nodes[pos1]);
			pos1++;
		}
		while (pos2 < addedHeap->nodes.size()) {
			tmpv.push_back(addedHeap->nodes[pos2]);
			pos2++;
		}
		nodes.clear();
		for (size_t i = 0; i < tmpv.size(); i++) {
			if (i < tmpv.size() - 1 && tmpv[i]->degree == tmpv[i + 1]->degree) {
				BinomialHeap<T> *tmpNode, *nextNode;
				if (tmpv[i]->value < tmpv[i + 1]->value) {
					tmpNode = tmpv[i];
					nextNode = tmpv[i + 1];
				}
				else {
					tmpNode = tmpv[i + 1];
					nextNode = tmpv[i];
				}
				nextNode->parent = tmpNode;
				tmpNode->nodes.push_back(nextNode);
				tmpNode->degree = std::max(tmpNode->degree, nextNode->degree + 1);
				tmpv[i + 1] = tmpNode;
			}
			else if (i < tmpv.size() - 1 && tmpv[i]->degree > tmpv[i + 1]->degree) {
				std::swap(tmpv[i], tmpv[i + 1]);
				i--;
			}
			else {
				nodes.push_back(tmpv[i]);
			}
		}
		nodesSize = nodes.size();
	}

	void insert(T val) {
		BinomialHeap<T> *newHeap = new BinomialHeap<T>();
		newHeap->nodes.push_back(new BinomialHeap<T>(val));
		merge(newHeap);
	}

	~BinomialHeap() {
		if (parent != nullptr)
			delete parent;
	}
};