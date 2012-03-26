#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int N, M, C; cin >> N >> M >> C;
	vector<int> X(N, 0);
	for (int i = 0; i < N; ++i)
		cin >> X[i];
	
	vector<int> P(N - 1);
	for (int i = 0; i < N - 1; ++i)
		cin >> P[i];
	
	vector<int> mars(N);
	for (int i = 0; i < M; ++i) {
		int x, y; cin >> x >> y;
		//cerr << " ---- " << x << " ----  " << y << " ---- \n";
		--x; --y;
		mars[x]++;
		mars[y]--;
	}

	vector<double> expecting(N), best(N);
	expecting[0] = best[0] = 0;
	int users = mars[0];
	for (int i = 1; i < N; ++i) {
		//cerr << i << " -> " << users << "\n";
		expecting[i] = max(expecting[i - 1], 0.0) - C * P[i - 1] * users / 100.0 + users * (X[i] - X[i - 1]) / 2.0;
		best[i] = max(best[i - 1], expecting[i]);
		users += mars[i];
	}

	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(8);
	cout << best[N - 1] << "\n";
}
