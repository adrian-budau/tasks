#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>

const int mod = 0xfaceb00c;

using namespace std;

char S[1024];
int p = 1023;

void cit(int &N) {
	while (S[p] < '0' || S[p] > '9')
		if (++p == 1024)
			fread(S, 1, 1024, stdin), p =0;
	
	N = 0;
	while (S[p] >= '0' && S[p] <= '9') {
		N = N * 10 + S[p] - '0';
		if (++p == 1024)
			fread(S, 1, 1024, stdin), p = 0;
	}
}

void cit(char *s) {
	while (S[p] < '0' || S[p] > '9')
		if (++p == 1024)
			fread(S, 1, 1024, stdin), p =0;
	
	int K = 0;
	while (S[p] >= '0' && S[p] <= '9') {
		s[K++] = S[p];
		if (++p == 1024)
			fread(S, 1, 1024, stdin), p = 0;
	}
}

int main() {
	freopen("status.in", "r", stdin);
	freopen("status.out", "w", stdout);

	int T;
	cit(T);

	for (int i = 1; i <= T; ++i) {
		int N; cit(N);

		char token[10000];
		memset(token, 0, sizeof(token));
		cit(token + 1);

		int M = strlen(token + 1);
		vector<long long> dp(M + 2, 0);
		dp[0] = 1;
		for (int k = 1; k <= M; ++k)
			if (token[k] != '0') {
				int K = 0;
				for (int j = k; j <= M; ++j) {
					K = K * 10 + token[j] - '0';
					if (K > N)
						break;
					dp[j] = (dp[k - 1] + dp[j]) % mod;
				}
			}

		cout << "Case #" << i << ": " << dp[M] << "\n";
	}
}		
