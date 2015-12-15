#pragma once

#include <conio.h>
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
#include "BinomialHeap.h"
#include "LeftistHeap.h"
#include "SkewHeap.h"

std::string toStr(int val) {
	std::string tmp = "";
	if (!val)
		return "0";
	while (val) {
		tmp += (val % 10) + '0';
		val /= 10;
	}
	std::string tmp1 = "";
	for (int i = tmp.length() - 1; i >= 0; i--)
		tmp1 += tmp[i];
	return tmp1;
}

std::vector<int> v1, v2, v3;

bool checkVectors() {
	for (size_t i = 0; i < v1.size(); i++) {
		if (v1[i] != v2[i] || v1[i] != v3[i] || v2[i] != v3[i]) {
			return false;
		}
	}
	return true;
}

int main() {
	double sum1 = 0, sum2 = 0, sum3 = 0;
	int k1 = 0, k2 = 0, k3 = 0;
	std::vector<BinomialHeap<int> *> binomialHeaps;
	std::vector<LeftistHeap<int> *> LeftistHeaps;
	std::vector<SkewHeap<int> *> SkewHeaps;
	for (int i = 0; i < 10; i++) {
		binomialHeaps.clear();
		SkewHeaps.clear();
		LeftistHeaps.clear();
		v1.clear();
		v2.clear();
		v3.clear();
		//for BinomialHeap
		FILE * in = freopen((toStr(i) + ".txt").c_str(), "r", stdin);
		int N, M, x, y, z;
		double start = clock();
		std::cin >> N >> M;
		for (int j = 0; j < M; j++) {
			std::cin >> x;
			if (x == 0) {
				std::cin >> y;
				binomialHeaps.push_back(new BinomialHeap<int>());
				binomialHeaps[binomialHeaps.size() - 1]->insert(y);
				k1++;
			}
			else if (x == 1) {
				std::cin >> y >> z;
				if (y >= (int)binomialHeaps.size())
					continue;
				binomialHeaps[y]->insert(z);
				k1++;
			}
			else if (x == 2) {
				std::cin >> y;
				if (y >= (int)binomialHeaps.size() || binomialHeaps[y]->nodesSize == 0)
					continue;
				int tval = binomialHeaps[y]->extractMin();
				v1.push_back(tval);
				k1++;
			}
			else if (x == 3) {
				std::cin >> y >> z;
				if (!(y != z && y < (int)binomialHeaps.size() && z < (int)binomialHeaps.size()))
					continue;
				binomialHeaps[y]->merge(binomialHeaps[z]);
				std::swap(binomialHeaps[z], binomialHeaps[binomialHeaps.size() - 1]);
				binomialHeaps.pop_back();
				k1++;
			}
		}
		sum1 += (clock() - start) / (double)CLOCKS_PER_SEC;
		fclose(in);
		//for LeftistHeap
		in = freopen((toStr(i) + ".txt").c_str(), "r", stdin);
		N, M, x, y, z;
		start = clock();
		std::cin >> N >> M;
		for (int j = 0; j < M; j++) {
			std::cin >> x;
			if (x == 0) {
				std::cin >> y;
				LeftistHeaps.push_back(new LeftistHeap<int>(mmax));
				LeftistHeaps[LeftistHeaps.size() - 1]->merge(new LeftistHeap<int>(y));
				k2++;
			}
			else if (x == 1) {
				std::cin >> y >> z;
				if (y >= (int)LeftistHeaps.size())
					continue;
				LeftistHeaps[y]->insert(z);
				k2++;
			}
			else if (x == 2) {
				std::cin >> y;
				if (y >= (int)LeftistHeaps.size() || LeftistHeaps[y]->getVal() == mmax)
					continue;
				int tval = LeftistHeaps[y]->extractMin();
				v2.push_back(tval);
				k2++;
			}
			else if (x == 3) {
				std::cin >> y >> z;
				if (!(y != z && y < (int)LeftistHeaps.size() && z < (int)LeftistHeaps.size()))
					continue;
				LeftistHeaps[y]->merge(LeftistHeaps[z]);
				std::swap(LeftistHeaps[z], LeftistHeaps[LeftistHeaps.size() - 1]);
				LeftistHeaps.pop_back();
				k2++;
			}
		}
		sum2 += (clock() - start) / (double)CLOCKS_PER_SEC;
		fclose(in);
		//for SkewHeap
		in = freopen((toStr(i) + ".txt").c_str(), "r", stdin);
		N, M, x, y, z;
		start = clock();
		std::cin >> N >> M;
		for (int j = 0; j < M; j++) {
			std::cin >> x;
			if (x == 0) {
				std::cin >> y;
				SkewHeaps.push_back(new SkewHeap<int>(mmax));
				SkewHeaps[SkewHeaps.size() - 1]->merge(new SkewHeap<int>(y));
				k3++;
			}
			else if (x == 1) {
				std::cin >> y >> z;
				if (y >= (int)SkewHeaps.size())
					continue;
				SkewHeaps[y]->insert(z);
				k3++;
			}
			else if (x == 2) {
				std::cin >> y;
				if (y >= (int)SkewHeaps.size() || SkewHeaps[y]->getVal() == mmax)
					continue;
				int tval = SkewHeaps[y]->extractMin();
				v3.push_back(tval);
				k3++;
			}
			else if (x == 3) {
				std::cin >> y >> z;
				if (!(y != z && y < (int)SkewHeaps.size() && z < (int)SkewHeaps.size()))
					continue;
				SkewHeaps[y]->merge(SkewHeaps[z]);
				std::swap(SkewHeaps[z], SkewHeaps[SkewHeaps.size() - 1]);
				SkewHeaps.pop_back();
				k3++;
			}
		}
		sum3 += (clock() - start) / (double)CLOCKS_PER_SEC;
		fclose(in);
		if (!checkVectors()) {
			printf("Incorrect!\n");
			getch();
			return 0;
		}
	}
	printf("Binomial Heap: time %.9lf  operations %d\n", sum1 / 10.0, k1);
	printf("Leftist Heap: time %.9lf  operations %d\n", sum2 / 10.0, k2);
	printf("Skew Heap: time %.9lf  operations %d\n", sum3 / 10.0, k3);
	printf("Correct!\n");
	getch();
	return 0;
}