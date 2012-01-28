#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int a[500][10];
int b[50][50];

int main() {
	ifstream cin("gxor.in");
	ofstream cout("gxor.out");

	int N, G; cin >> N >> G;
	for (int i = 1; i <= G; ++i) {
		cin >> a[i][0] >> a[i][1] >> a[i][2] >> a[i][3] >> a[i][4];
	}

	int sol = 0;
	for (int i = 0; i < (1 << (N * N)); ++i) {
		for (int j = 0; j < N * N; ++j)
			if ((1 << j) & i)
				b[j / N + 1][j % N + 1] = 1;
			else
				b[j / N + 1][j % N + 1] = 0;
		
		int j = 1;
		for (j = 1; j <= G; ++j) {
			int S = 0;
			for (int k = a[j][0]; k <= a[j][2]; ++k)
				for (int l = a[j][1]; l <= a[j][3]; ++l)
					S ^= b[k][l];
			if (S != a[j][4]) {
				break;
			}

		}
		if (j == G + 1)
			++sol;
	}
	
	cout << sol % 34949 << "\n";
}
