#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

typedef vector<int>::iterator T;
typedef string::iterator X;

void print(T begin, T end) {
	while (begin != end) 
		cerr << *begin << " ", ++begin;
	
}

void merge(T begin, T mid,T end, X &ch) {
	T A = begin, B = mid;

	vector<int> result;
	while (A != mid && B != end) {
		if (*ch == '1') {
			result.push_back(*A);
			++A;
		} else {
			result.push_back(*B);
			++B;
		}
		++ch;
	}

	while (A != mid) {
		result.push_back(*A);
		++A;
	}

	while (B != end) {
		result.push_back(*B);
		++B;
	}

	for (T it = begin; it != end; ++it)
		*it = result[it - begin];
}

void merge_sort(T begin, T end, X &ch) {
	
	if (end - begin <= 1)
		return;
	
	T mid = begin + (end - begin) / 2;

	merge_sort(begin, mid, ch);
	merge_sort(mid, end, ch);

	merge(begin, mid, end, ch);
}

int checksum(vector<int> &A) {
	int result = 1;
	for (T it = A.begin(); it != A.end(); ++it)
		result = (31 * result + *it) % 1000003;
	
	return result;
}

int main() {
	ifstream cin("recover.in");
	ofstream cout("recover.out");

	int T; cin >> T;
	for (int i = 1; i <= T; ++i) {
		int N; cin >> N;
		string S; cin >> S;
		vector<int> array(N);
		for (int j = 0; j < N; ++j)
			array[j] = j;

		string::iterator it = S.begin();
		merge_sort(array.begin(), array.end(), it);


		vector<int> values(N);
		for (int j = 0; j < N; ++j)
			values[array[j]] = j + 1;
	
		cout << "Case #" << i << ": " << checksum(values) << "\n";
	}
}
