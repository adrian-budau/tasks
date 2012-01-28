#include <cstdio>
#include <cstring>
#include <vector>

const int mod = 2011;

using namespace std;

int main() {
	freopen("progresii.in", "r", stdin);
	freopen("progresii.out", "w", stdout);

	int N, X;
	scanf("%d%d", &N, &X);

	vector< vector<int> > ratios(X + 1);

	for (int i = 0; i < N; ++i) {
		int first, ratio; 
		scanf("%d%d", &first, &ratio);

		for (int j = first; j <= X; j += ratio)
			ratios[j].push_back(ratio);
	}

	vector<int> longest(X + 1, -X - 2), many(X + 1, 0);
	many[0] = longest[0] = 1;

	for (int i = 0; i < X; ++i)
		for (vector<int>::iterator it = ratios[i].begin(); it != ratios[i].end(); ++it) 
			if (i + *it <= X) {
				longest[i + *it] = max(longest[i + *it], longest[i] + 1);
				many[i + *it] += many[i];
				if (many[i + *it] >= mod)
					many[i + *it] -= mod;
			}
	
	printf("%d %d\n", many[X], longest[X]);
}
