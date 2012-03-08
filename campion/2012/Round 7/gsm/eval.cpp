#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

void gen(int N, int MAXVAL) {
	int x1 = rand() % (MAXVAL + 1);
	int x2;
	do {
		x2 = rand() % (MAXVAL + 1);
	} while (x1 == x2);

	if (x1 > x2)
		swap(x1, x2);
	
	int y1 = rand() % (MAXVAL + 1);
	int y2;
	do {
		y2 = rand() % (MAXVAL + 1);
	} while (y1 == y2);

	if (y1 > y2)
		swap(y1, y2);
	
	vector< pair<int, int> > A;
	A.reserve((y2 - y1 + 1) * (x2 - x1 + 1));
	for (int i = x1; i <= x2; ++i)
		for (int j = y1; j <= y2; ++j)
			A.push_back(make_pair(i, j));
	
	random_shuffle(A.begin(), A.end());
	N = min(N, static_cast<int>(A.size()));
	
	ofstream in("gsm.in");
	in << N << "\n";
	for (int i = 0; i < N; ++i)
		in << A[i].first << " " << A[i].second << "\n";
	
	in << x1 << " " << y1 << " " << x2 << " " << y2 << "\n";
}

int eval(string s) {
	assert(system(s.c_str()) == 0);

	ifstream out("gsm.out");
	int val; out >> val;
	return val;
}

int main() {
	int T, MAXN, MAXVAL;
	cin >> T >> MAXN >> MAXVAL;

	srand(time(NULL));
	for (int i = 1; i <= T; ++i) {
		cout << "Case #" << i << ": ";
		if (i == T)
			gen(MAXN, MAXVAL);
		else
			gen(rand() % MAXN + 1, MAXVAL);

		int adrian = eval("./main 2> adrian.log");
		int brut = eval("./brut 2> brut.log");

		if (adrian != brut) {
			cout << adrian << "    " << brut << "   Wrong!\n";
			return 0;
		}
		cout << adrian << "    OK!\n";
	}
}
