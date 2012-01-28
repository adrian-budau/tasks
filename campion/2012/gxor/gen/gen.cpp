#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

void gen(int N, int G) {
	ofstream in("gxor.in");
	in << N << " " << G << "\n";
	/*vector< vector<int> > A(N + 1, vector<int>(N + 1, 0));
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j) {
			A[i][j] = rand() % 2;
		}
*/
	for (int i = 0; i < G; ++i) {
		int x1 = rand() % N + 1, x2 = rand() % N + 1;
		int y1 = rand() % N + 1, y2 = rand() % N + 1;

		if (x1 > x2)
			swap(x1, x2);
		if (y1 > y2)
			swap(y1, y2);

		in << x1 << " " << y1 << " " << x2 << " " << y2 << " " << rand() % 2 << "\n"; //(A[x2][y2] ^ A[x1 - 1][y2] ^ A[x2][y1 - 1] ^ A[x1 - 1][y1 - 1]) << "\n";
	}
	in.close();
}

int test(char *source) {
	system(source);
	ifstream out("gxor.out");
	int val = -1; out >> val;
	out.close();
	system("rm gxor.out");
	return val;
}

int main() {
	cout << "T MAXN MAXG\n";
	int T, MAXN, MAXG; cin >> T >> MAXN >> MAXG;
	
	srand(time(NULL));

	for (int i = 1; i <= T; ++i) {
		int N = rand() % MAXN + 1;
		int G = rand() % (MAXG + 1);
		if (i == 1)
			N = MAXN, G = MAXG;
		gen(N, G);

		int val1 = test("./main");
		int val2 = test("./gxor");
		int val3 = val1;//test("./brut");

		cout << "Case " << i << ": " << val1  << " " << val2 << " -> ";
		if (val1  == val2 && val2 == val3) {
			cout << "OK!\n";
			continue;
		}

		cout << "Error!\n";
		return 0;
	}
}
