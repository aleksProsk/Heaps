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

template<typename T> class LeftistHeap : public Heap<T> {
private:
	int distance;
	T value;
	LeftistHeap *right, *left;

public:

	LeftistHeap() {
		left = nullptr;
		right = nullptr;
	}

	LeftistHeap(T val) {
		value = val;
		distance = 0;
		right = nullptr;
		left = nullptr;
	}

	LeftistHeap(LeftistHeap<T> *H) {
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

	LeftistHeap<T> *mergeHeaps(LeftistHeap<T> *A, LeftistHeap<T> *B) {
		if (A == nullptr)
			return B;
		else if (B == nullptr)
			return A;
		if (A->value > B->value)
			std::swap(A, B);
		A->right = mergeHeaps(A->right, B);
		if (A->right != nullptr && A->left != nullptr && A->right->distance > A->left->distance)
			std::swap(A->right, A->left);
		else if (A->right != nullptr && A->left == nullptr)
			std::swap(A->right, A->left);
		if (A->left != nullptr && A->right != nullptr)
			A->distance = std::min(A->left->distance, A->right->distance) + 1;
		else
			A->distance = 0;
		return A;
	}

	void merge(LeftistHeap<T> *addedHeap) {
		if (addedHeap == nullptr)
			return;
		LeftistHeap<T> *tmpHeap = new LeftistHeap<T>(this);
		LeftistHeap<T> *tmpHeap1 = mergeHeaps(tmpHeap, addedHeap);
		*this = *tmpHeap1;
	}

	void insert(T val) {
		LeftistHeap<T> *newHeap = new LeftistHeap<T>(val);
		merge(newHeap);
	}

	T getVal() {
		return value;
	}

	~LeftistHeap() {
		if (left != nullptr)
			delete left;
		if (right != nullptr)
			delete right;
	}
};