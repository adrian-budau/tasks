#include <iostream>
#include <fstream>
#include <vector>

const int maxN = 10010005;

using namespace std;

int main() {
	ifstream cin("checkpoint.in");
	ofstream cout("checkpoint.out");

	int T; cin >> T;

	vector<int> steps(maxN, maxN);
	steps[1] = 1;

	vector< vector<long long> > comb(1005, vector<long long>(1005, 0));
	comb[0][0] = 1;

	for (int i = 0; i <= 1000; ++i) 
		for (int j = 0; j <= i; ++j) {
			if (comb[i][j] > maxN)
				comb[i][j] = maxN;

			comb[i + 1][j] += comb[i][j];
			comb[i + 1][j + 1] += comb[i][j];

			if (i > 0 && comb[i][j] < maxN)
				steps[comb[i][j]] = min(steps[comb[i][j]], i);
		}

	for (int i = 1001; i <= 10000; ++i) {
		long long x = i * (i - 1);
		x /= 2;
		if (x < maxN)
			steps[x] = min(steps[x], i);
	}

	for (int i = 10001; i < maxN; ++i)
		steps[i] = min(steps[i], i);

	for (int i = 1; i <= T; ++i) {
		int N; cin >> N;

		int answer = maxN;
		for (int j = 1; j * j <= N; ++j)
			if (N % j == 0)
				answer = min(answer, steps[j] + steps[N / j]);

		cout << "Case #" << i << ": " << answer << "\n";
	}
}
