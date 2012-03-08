#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

const int mod = 666013;

class FenwickTree {
  public:
	FenwickTree(int N);
	void update(int, int);
	int query(int);
  private:
	vector<int> buffer;
};

inline FenwickTree::FenwickTree(int N) {
	buffer.resize(N);
}

inline void FenwickTree::update(int position, int value) {
	for (; position < static_cast<int>(buffer.size()); position += (position & -position))
		buffer[position] = (buffer[position] + value) % mod;
}

inline int FenwickTree::query(int position = -1) {
	if (position == -1)
		position += buffer.size();
	
	int sum = 0;
	for (; position > 0; position -= (position & -position))
		sum = (sum + buffer[position]) % mod;
	return sum;
}

int main() {
	int N, M, X, Y;
	assert(freopen("subsiruri.in", "r", stdin) != NULL);
	assert(freopen("subsiruri.out", "w", stdout) != NULL);

	assert(scanf("%d%d%d%d", &N, &M, &X, &Y) == 4);
	vector<int> A(N);
	for (int i = 0; i < N; ++i)
		assert(scanf("%d", &A[i]) == 1);

	vector< FenwickTree> trees(M, FenwickTree(*(max_element(A.begin(), A.end())) + 1));

	trees[0].update(1, 1);
	for (int i = 0; i < N; ++i) {
		vector<int> add(M);
		for (int j = 0; j < M; ++j) {
			int newj = (j + A[i]) % M;
			add[newj] = trees[j].query(A[i]);
		}
		
		for (int j = 0; j < M; ++j) 
			trees[j].update(A[i], add[j]);
	}

	trees[0].update(1, -1);
	int answer = 0;
	for (int i = X; i <= Y; ++i) 
		answer = (answer + trees[i].query()) % mod;

	answer = (mod + answer) % mod;
	printf("%d\n", answer);
}
