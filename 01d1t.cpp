//�����ˮƽֵ���ڸö����Ա�еڶ���ˮƽֵ��Ϊ�����ж����ˮƽֵ�ܺ����Ľⷨ��Ҳ����˵ÿ������
//�ĵڶ���ֵ�Ǿ����ܴ��ֵ������ʵ��ֵ�����ֵ�ŵ����ұߣ���С�Ƿŵ������
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