#include<iostream>
#include<string>

using namespace std;

void maxCount() {
	string s;
	string s2;
	getline(cin, s);
	int i = 0;
	int k = 0;//��¼����ִ������һ��Ԫ�ص�λ��
	int lenth = 0;//��¼ÿһ�����ִ��ĳ���
	int maxlenth = 0;//ÿ�λ�ȡlenth��ֵ�����µ�lenth�����ֵ
	while (s[i] != '\0') {
		if ((s[i] >= '1') && (s[i] <= '9')) {
			lenth++;
			i++;
		}
		else {
			lenth = 0;
			i++;
		}
		if (lenth > maxlenth) {
			maxlenth = lenth;
			k = i - 1;//��maxlenth��ȡ�����ֵʱ��i��ʱ������ִ�����һ��������Ԫ�ص�λ�ã�������Ҫi-1
		}
	}
	s2.insert(0, s, k - maxlenth + 1, maxlenth);
	cout << s2 << endl;
}

/*int main() {
	maxCount();
	return 0;
}*/