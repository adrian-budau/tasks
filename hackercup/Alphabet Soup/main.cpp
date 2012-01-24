#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
	ifstream cin("soup.in");
	ofstream cout("soup.out");

	int T; cin >> T;
	cin.get();

	for (int i = 1; i <= T; ++i) {
		string S; getline(cin, S);

		vector<int> letter(256, 0);

		for (string::iterator it = S.begin(); it != S.end(); ++it)
			++letter[*it];

		int rez = min(min(min(letter['H'], letter['A']), min(letter['C'] / 2, letter['K'])), min(min(letter['E'], letter['R']), min(letter['U'], letter['P'])));
		cout << "Case #" << i << ": " << rez << "\n";
	}
}
