/*
СA��ѧ�˶����ƣ���ʮ�ּ�����Ϊ��ȷ������ȷ�����˶����ƣ��������������һ����Ŀ������N���Ǹ�����������N�����ְ��ն�������1�ĸ������࣬��������1�ĸ�����ͬ����������ͬһ�ࡣ�����һ���м������֣�


��������:
����ĵ�һ����һ��������T��0<T<=10������ʾ��������������ÿһ����������һ����һ��������N��0<N<=100������ʾ�ж��ٸ����֡�������һ����N���ɿո�ָ��ķǸ���������С������2^31 �C 1����

�������:
����ÿһ�����������һ������������ʾ���������һ���м��ࡣ

��������1:
1
5
8 3 5 7 2

�������1:
3
*/

#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int Classification_by_1() {
	int N = 0;//ÿ�������У�������ʮ�������ĸ���
	cin >> N;

	vector<int> demo(N, 0);
	for (int i = 0; i < N; i++) {
		cin >> demo[i];
	}

	int count_of_1 = 0;//ͳ��N�������а�1�ĸ������࣬�ж�����
	vector<int> k(N, 0);//ͳ��ÿ�����Ķ�������ʽ�ж��ٸ�1
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