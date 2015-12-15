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

const int mmax = INT_MAX;

template<typename T> class Heap {
public:
	virtual T extractMin() = 0;
	virtual void insert(T val) = 0;
};