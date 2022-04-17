#include <iostream>
#include <map>
#include <utility>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
using namespace std;

pair<int, int> Check(map<int, short int> C, int S, int amount = 0, int count = 0);

int main()
{
	string S_str, M_str;
	ifstream in;

	in.open("input.txt");

	getline(in, S_str, ',');
	getline(in, M_str);

	const char* S_chr = S_str.c_str();
	int S = atoi(S_chr);

	const char* M_chr = M_str.c_str();
	short int M = atoi(M_chr);

	map<int, short int> C;
	string line_of_c;
	getline(in, line_of_c);

	in.close();

	string::iterator it_start = line_of_c.begin();
	int amount = 0;
	for (short int i = 0; i < M; ++i) {
		string::iterator it_end = find(it_start, line_of_c.end(), ',');
		C[(short int)atoi((string(it_start, it_end)).c_str())] = 2;
		amount += (short int)atoi((string(it_start, it_end)).c_str()) * 2;
		if (i + 1 < M)
			it_start = (it_end + 1);
	}

	ofstream out;
	out.open("output.txt");

	if (amount < S) {
		out << -1;
		return 0;
	}

	pair<int, int> num = Check(C, S, amount, C.size() * 2);

	if (num.first == S)
		out << num.second;

	if (num.first == -1)
		out << 0;
	return 0;
}

pair<int, int> Check(map<int, short int> C, int S, int amount, int count) {
	if (amount == S)
		return make_pair(amount, count);

	if (amount < S)
		return make_pair(amount, 0);

	for (map<int, short int>::iterator it = C.begin(); it != C.end(); ++it)
	{
		if (it->second != 0) {

			if (amount > S) {
				int val = it->first;
				if (it->second > 0) {
					map<int, short int> new_C(C);
					new_C[it->first]--;
					pair<int, short int> check = Check(new_C, S, amount - val, count - 1);
					if (check.first < S) {
						continue;
					}
					return make_pair(check.first, check.second);
				}

			}
		}
	}
	return make_pair(-1, count + 1);
}
	