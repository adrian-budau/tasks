#include <cstdio>
#include <cstring>
#include <vector>
#include <bitset>
#include <map>
#include <iostream>
#include <algorithm>
#define mp make_pair

const int unknowns = 1616;
const int mod = 34949;

using namespace std;

inline void add(map< pair<int, int>, int> &M, const pair<int, int> &v, int &k) {
	if (M.find(v) == M.end()) {
		if (v.first <= 0 || v.second <= 0)
			M[v] = unknowns - 2;
		else
			M[v] = k++;
	}

	//cerr << "(" << v.first << ", " << v.second << ") -> " << M[v] << "\n";
}

int pow(int x, int y) {
	if (y == 0)
		return 1;
	if (y == 1)
		return x;
	
	int rez = pow(x, y / 2);
	rez = (rez * rez) % mod;
	
	if (y % 2)
		rez = (rez * x) % mod;
	
	return rez;
}

int main() {
	freopen("gxor.in", "r", stdin);
	freopen("gxor.out", "w", stdout);

	int N, G; scanf("%d%d", &N, &G);

	map< pair<int, int>, int> M;
	vector< bitset<unknowns> > equations(G);
	int K = 0;
	for (int i = 0; i < G; ++i) {
		int x1, y1, x2, y2, v;
		scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &v);

		add(M, mp(x1 - 1, y1 - 1), K);
		add(M, mp(x1 - 1, y2), K);
		add(M, mp(x2, y1 - 1), K);
		add(M, mp(x2, y2), K);

		equations[i][M[mp(x1 - 1, y1 - 1)]] = 1;
		equations[i][M[mp(x1 - 1, y2)]] = 1;
		equations[i][M[mp(x2, y1 - 1)]] = 1;
		equations[i][M[mp(x2, y2)]] = 1; 
		equations[i][unknowns - 1] = v;
		equations[i][unknowns - 2] = 0;
	}
	vector<bool> mark(G, false);
	int fixed = 0;
	for (size_t i = 0; i < M.size(); ++i) {
		int myrow = -1;

		for (int j = 0; j < G; ++j)
			if (mark[j] == false && equations[j][i]) {
				myrow = j;
				break;
			}

		if (myrow > -1) {
			mark[myrow] = true;
			++fixed;

			for (int j = 0; j < G; ++j)
				if (mark[j] == false && equations[j][i])
					equations[j] ^= equations[myrow];
		}
	}

	bitset<unknowns> test;
	test[unknowns - 1] = 1;
	for (int i = 0; i < G; ++i) {
		if (equations[i] == test) {
			printf("0\n");
			return 0;
		}
	}
	printf("%d\n", pow(2, N * N - fixed));
}
