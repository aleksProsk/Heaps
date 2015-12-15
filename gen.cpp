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

int main() {
	srand(time(NULL));
	int sz = 2;
	for (int i = 0; i < 10; i++) {
		std::cerr << i << std::endl;
		FILE * out = freopen((toStr(i) + ".txt").c_str(), "w", stdout);
		int M = 300000;
		int N = 5000000;
		sz = 2;
		std::cout << N << ' ' << M << std::endl;
		for (int j = 0; j < M; j++) {
			int type = rand() % 4;
			int x = rand() % N, y, z;
			if (!sz)
				type = 0;
			else {
				y = rand() % sz;
				z = rand() % sz;
			}
			std::cout << type << ' ';
			if (type == 0) {
				std::cout << x << std::endl;
			}
			else if (type == 1) {
				std::cout << y << ' ' << x << std::endl;
			}
			else if (type == 2) {
				std::cout << y << std::endl;
			}
			else if (type == 3) {
				std::cout << y << ' ' << z << std::endl;
			}
			if (type == 0)
				sz++;
			else if (type == 3)
				sz--;
		}
		fclose(out);
	}
	return 0;
}