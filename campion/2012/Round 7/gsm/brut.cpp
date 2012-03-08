#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

const int maxN = 210;
const double eps = 5e-3;
const double eps2 = 5e-2;
const double inf = 1e12;

int N;
pair <double, double> P[maxN];
pair <double, double> rectDown, rectUp;
int pMin;
double distMin;
double area[maxN];

inline double dist(double x1, double y1, double x2, double y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

inline int pula(double T) {
	if (fabs(T - floor(T)) <= eps2)
		return T;
	return ceil(T);
}

int main() {
	int i, j;
	freopen("gsm.in", "r", stdin);
	freopen("gsm.out", "w", stdout);

	scanf("%d", &N);

	for (i = 1; i <= N; i++) 
		scanf("%lf%lf", &P[i].first, &P[i].second);
	
	scanf("%lf%lf%lf%lf", &rectDown.first, &rectDown.second, &rectUp.first, &rectUp.second);
	
	for (double x = rectDown.first; x <= rectUp.first; x += eps)
		for (double y = rectDown.second; y <= rectUp.second; y += eps) {
			distMin = inf;
			for (i = 1; i <= N; i++)
				if (dist(x, y, P[i].first, P[i].second) < distMin) {
					distMin = dist(x, y, P[i].first, P[i].second);
					pMin = i;
				}

			area[pMin] += eps * eps;
		}

	distMin = 0;

	for (i = 1; i <= N; i++) {
		fprintf(stderr, "%lf\n", area[i]);
		if (pula(area[i]) > distMin) {
			distMin = pula(area[i]);
			pMin = i;
		}
	}

	printf("%d\n", pMin);

	return 0;
}
