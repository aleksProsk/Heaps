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

template<typename T> class SkewHeap : public Heap<T> {
	private:
	int distance;
	T value;
	SkewHeap *right, *left;

public:

	SkewHeap() {
		left = nullptr;
		right = nullptr;
	}

	SkewHeap(T val) {
		value = val;
		distance = 0;
		right = nullptr;
		left = nullptr;
	}

	SkewHeap(SkewHeap<T> *H) {
		value = H->value;
		distance = H->distance;
		right = H->right;
		left = H->left;
	}

	T extractMin() {
		T minVal = value;
		*this = *mergeHeaps(this->left, this->right);
		return minVal;
	}

	SkewHeap<T> *mergeHeaps(SkewHeap<T> *A, SkewHeap<T> *B) {
		if (A == nullptr)
			return B;
		else if (B == nullptr)
			return A;
		if (A->value > B->value)
			std::swap(A, B);
		A->right = mergeHeaps(A->right, B);
		std::swap(A->right, A->left);
		return A;
	}

	void merge(SkewHeap<T> *addedHeap) {
		if (addedHeap == nullptr)
			return;
		SkewHeap<T> *tmpHeap = new SkewHeap<T>(this);
		SkewHeap<T> *tmpHeap1 = mergeHeaps(tmpHeap, addedHeap);
		*this = *tmpHeap1;
	}

	void insert(T val) {
		SkewHeap<T> *newHeap = new SkewHeap<T>(val);
		merge(newHeap);
	}

	T getVal() {
		return value;
	}

	~SkewHeap() {
		if (left != nullptr)
			delete left;
		if (right != nullptr)
			delete right;
	}
};
