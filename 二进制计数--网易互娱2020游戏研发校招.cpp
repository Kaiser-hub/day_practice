/*
小A刚学了二进制，他十分激动。为了确定他的确掌握了二进制，你给他出了这样一道题目：给定N个非负整数，将这N个数字按照二进制下1的个数分类，二进制下1的个数相同的数字属于同一类。求最后一共有几类数字？


输入描述:
输入的第一行是一个正整数T（0<T<=10），表示样例个数。对于每一个样例，第一行是一个正整数N（0<N<=100），表示有多少个数字。接下来一行是N个由空格分隔的非负整数，大小不超过2^31 – 1。，

输出描述:
对于每一组样例，输出一个正整数，表示输入的数字一共有几类。

输入例子1:
1
5
8 3 5 7 2

输出例子1:
3
*/

#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int Classification_by_1() {
	int N = 0;//每个样例中，给出的十进制数的个数
	cin >> N;

	vector<int> demo(N, 0);
	for (int i = 0; i < N; i++) {
		cin >> demo[i];
	}

	int count_of_1 = 0;//统计N个数中有按1的个数分类，有多少类
	vector<int> k(N, 0);//统计每个数的二进制形式有多少个1
	for (int i = 0; i < N; i++) {
		while (demo[i] >= 1) {
			int remainder = demo[i] % 2;
			if (remainder) {
				k[i]++;
			}
			demo[i] = demo[i] / 2;
		}
	}
	sort(k.begin(), k.end());
	for (int i = 0; i < N; i++) {
		if (i == 0) {
			count_of_1++;
		}
		else if (k[i] != k[i - 1]) {
			count_of_1++;
		}
	}
	return count_of_1;
}

/*int main() {
	int T = 0;
	cin >> T;
	while (T) {
		cout << Classification_by_1() << endl;
		T--;
	}
	return 0;
}*/