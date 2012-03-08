#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cassert>

using namespace std;

const double eps = 1e-9;
const double compeps = 1e-6;
const double multiply = 1000;

inline int cmp(const double &a, const double &b) {
	if (a + eps < b)
		return -1;
	if (b + eps < a)
		return 1;
	
	return 0;
}

class point {
  public:
	point();
	point(const double &);
	point(const double&, const double&);
	point operator+(const point &) const;
	point operator-() const;
	point operator-(const point &) const;
	point operator*(const double &) const;
	point operator*(const point &) const;
	point operator/(const double &) const;

	bool operator<(const point &) const;

	point dual() const;

	double x, y;
};

// Constructors
inline point::point() {
	x = y = 0;
}

inline point::point(const double &that) {
	x = cos(that);
	y = sin(that);
}

inline point::point(const double &_x, const double &_y) {
	x = _x;
	y = _y;
}

// Arithmetic operations
inline point point::operator+(const point &that) const {
	return point(x + that.x, y + that.y);
}

inline point point::operator-() const {
	return point(-x, -y);
}

inline point point::operator-(const point &that) const {
	return point(x - that.x, y - that.y);
}

inline point point::operator*(const double &that) const {
	return point(x * that, y * that);
}

inline point point::operator*(const point &that) const {
	return point(x * that.x - y * that.y, x * that.y + y * that.x);
}

inline point point::operator/(const double &that) const {
	return point(x / that, y / that);
}

// Comparison
inline bool point::operator<(const point &that) const {
	if (cmp(x, that.x) == 0)
		return cmp(y, that.y) == -1;
	return cmp(x, that.x) == -1;
}

// Duality
inline point point::dual() const {
	return point(x / y * multiply, -1.0 / y * multiply);
}

inline point between(const point &a, const point &b) {
	double slope = (a.y - b.y) / (a.x - b.x);
	double intercept = (a.y - slope * a.x);
	return point(slope, intercept);
}

inline double area(const point &a, const point &b, const point &c) {
	return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
}

vector<point> convexHull(vector<point> &A) {
	sort(A.begin(), A.end());
	//for (auto &it: A)
	//	cerr << it.x << " " << it.x << "\n";
	//cerr << "\n";

	vector<int> stack;
	stack.push_back(0);
	stack.push_back(1);
	vector<bool> used(A.size());
	used[1] = true;

	int current = 1;
	int step = 1;
	int K = 1;

	while (used[0] == false) {
		if (current == static_cast<int>(A.size()) - 1)
			step = -1;

		while (used[current] == true)
			current += step;

		while (K && cmp(area(A[stack[K - 1]], A[stack[K]], A[current]), 0) < 0) {
			used[stack.back()] = false;
			stack.pop_back();
			--K;
		}

		used[current] = true;
		stack.push_back(current);
		++K;
	}

	vector<point> C;
	for (int i = 1; i <= K; ++i)
		C.push_back(between(A[stack[i - 1]], A[stack[i]]).dual());
	return C;
}		

int main() {
	assert(freopen("gsm.in", "r", stdin) != NULL);
	assert(freopen("gsm.out", "w", stdout) != NULL);

	int N; assert(scanf("%d", &N) == 1);

	point slightly(M_PI / 1000);
	vector<point> A(N);
	for (int i = 0; i < N; ++i) {
		double x, y;
		assert(scanf("%lf%lf", &x, &y) == 2);

		A[i] = point(x, y);
	}
	
	double x1, y1, x2, y2;
	assert(scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2) == 4);
	
	vector<point> margin;
	margin.push_back(point(x1, y1) * slightly);
	margin.push_back(point(x1, y2) * slightly);
	margin.push_back(point(x2, y2) * slightly);
	margin.push_back(point(x2, y1) * slightly);
	margin.push_back(margin[0]);
	
	for (int i = 0; i < N; ++i) {
		double dirx = eps, diry = eps;
		if (A[i].x > ((x1 + x2) / 2))
			dirx = -eps;
		if (A[i].y > ((y1 + y2) / 2))
			diry = -eps;

		A[i] = (A[i] + point(dirx, diry)) * slightly;
	}

	double best = -1;
	int where = -1;
	
	cerr.setf(ios::fixed, ios::floatfield);
	cerr.precision(10);

	for (int i = 0; i < N; ++i) {
		vector<point> B;
		B.reserve(N + 3);
		for (int j = 0; j < N; ++j)
			if (j != i) {
				point middle = (A[j] - A[i]) / 2;
				point rotation(M_PI / 2);

				point second = -middle * rotation + middle;
				B.push_back(between(middle, second).dual());
				//cerr << between(middle, second) << "\n";
			}

		for (int j = 1; j < 5; ++j) {
			B.push_back(between(margin[j] - A[i], margin[j - 1] - A[i]).dual());
			// cerr << between(margin[j] - A[i], margin[j - 1] - A[i]) << "\n";
		}
		//cerr << "\n";
 
		B = convexHull(B);
		double area = 0;
		for (size_t j = 1; j < B.size(); ++j) 
			area += B[j - 1].x * B[j].y - B[j].x * B[j - 1].y;

		area += B.back().x * B.front().y - B.front().x * B.back().y;
		area /= 2;
		//cerr << area << "\n";

		if (cmp(area - floor(area), compeps) == 1)
			area = ceil(area);
		else
			area = floor(area);

		if (cmp(area, best) == 1) {
			best = area;
			where = i + 1;
		}
	}

	printf("%d\n", where);
}
