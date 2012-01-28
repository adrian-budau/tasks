#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int main() {
	ifstream cin("billboards.in");
	ofstream cout("billboards.out");

	int T; cin >> T;
	
	for (int i = 1; i <= T; ++i) {
		int W, H; cin >> W >> H;

		vector<string> S, copy;
		do {
			char x = 0;
			x = cin.get();
			if (x != ' ')
				break;

			string s; cin >> s;
			S.push_back(s);
		} while (1);
		
		for (int j = 1; j <= W + 1; ++j) {
			copy = S;

			int h = j, w = -j;
			while (S.size() > 0) {
				if (h > H)
					break;
				if (w + j + S.back().size() * j > W) {
					h += j;
					w = -j;
				} else {
					w += S.back().size() * j + j;
					S.pop_back();
				}
			}
			if (S.size() > 0 || h > H) {
				cout << "Case #" << i << ": " << j - 1 << "\n";
				break;
			}

			S = copy;
		}
	}
}

