#include <iostream>
#include <vector>
#include <fstream>
#include <string>

const long long inf = (1LL << 60);

using namespace std;

int main() {
	int N, M; cin >> N >> M;
	
	vector<long long> best(N), high(N), low(N), total(N);

	for (int i = 0; i < N; ++i) {
		int K; cin >> K;

		long long localBest = -inf;
		long long localHigh = -inf;
		long long localLow = 0;

		long long sum = 0;
		for (int j = 0; j < K; ++j) {
			int v; cin >> v;
			sum += v;

			localHigh = max(localHigh, sum);
			localBest = max(localBest, sum - localLow);
			localLow = min(localLow, sum);
		}
		
		best[i] = localBest;
		high[i] = localHigh;
		low[i] = localLow;
		total[i] = sum;
	}

	long long Best = -inf;
	long long Low = 0;
	long long Total = 0;
	for (int i = 0; i < M; ++i) {
		int index; cin >> index;
		
		Best = max(Best, best[index - 1]);

		Best = max(Best, high[index - 1] + Total - Low);

		Low = min(Low, Total + low[index - 1]);

		Total += total[index - 1];
	}

	cout << Best;
}
