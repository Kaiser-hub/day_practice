#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

//MΪ��Ҫת����ʮ��������NΪת��ΪN���Ƶ��ж�
void BaseConversion(int M , int N) {
	string Conversion("0123456789ABCDEF");//����N���Ϊ16����������Ϊ��0123456789ABCDEF��
	string ret;
	int flag = 1;//flag�����ж����������Ǹ���������flagΪ1������flagΪ0
	//�ȴ����������
	while (M < 0) {
		flag = 0;
		M = -M;
	}
	while (M) {
		ret += Conversion[M%N];
		M = M / N;
	}
	if (flag == 0) {
		ret += '-';
	}
	//ret��ʱ��һ������Ľ������Ҫ��ת�ַ���
	reverse(ret.begin(), ret.end());
	cout << ret << endl;
}

/*int main() {
	int M = 0, N = 0;
	cin >> M >> N;
	BaseConversion(M, N);
}*/