#include <iostream>

using namespace std;

int main() {
	int N = 100, M = 10000;
	cout << N << " " << M << "\n";
	for (int i = 0; i < N; ++i) {
		cout << N << " ";
		for (int j = 0; j < N - 1; ++j)
			cout << 100 << " ";
		cout << "100\n";
	}
	return 0;
}
