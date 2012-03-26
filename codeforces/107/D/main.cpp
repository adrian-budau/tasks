#include <iostream>
#include <string>
#include <vector>

using namespace std;

int solve(vector< vector<int> > &dp, string &S, int from, int to) {
	if (dp[from][to] != -1)
		return dp[from][to];
	

}
int main() {
	int N;
	vector<int> A(N);
	for (int i = 0; i < N; ++i)
		cin >> A[i];
	
	string S; cin >> S;
	N = S.size();
	
	vector< vector<int> > dp(N.size(), vector<int>(N.size(), -1));
	cout << solve(dp, S, 0, N - 1);
}
