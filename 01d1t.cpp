//队伍的水平值等于该队伍队员中第二高水平值，为了所有队伍的水平值总和最大的解法，也就是说每个队伍
//的第二个值是尽可能大的值。所以实际值把最大值放到最右边，最小是放到最左边
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;


int maxval() {
	int n = 0;
	long long max = 0;
	cin >> n;
	vector<int> v(3 * n);
	for (int i = 0; i < 3 * n; i++) {
		cin >> v[i];
	}
	sort(v.begin(), v.end());
	for (int i = n; i < 3 * n - 1; i += 2) {
		max += v[i];
	}

	cout << max << endl;
	return max;
}
/*int main() {
	maxval();
	return 0;
}*/