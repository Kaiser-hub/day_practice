/*
СQ������һ�����г�Ϊ��ת����:
��������n��m, ����n�ܱ�2m����������һ������������������1, 2, 3, 4..., ÿ��m�����ŷ�תһ��, �������Ϊ'-';��
����n = 8, m = 2, ���о���: -1, -2, +3, +4, -5, -6, +7, +8.
��n = 4, m = 1, ���о���: -1, +2, -3, + 4.
СQ����ϣ�����ܰ�������ǰn���Ϊ���١�

��������:
���������������n��m(2 <= n <= 109, 1 <= m), ��������n�ܱ�2m������

�������:
���һ������, ��ʾǰn��͡�

��������1:
8 2

�������1:
8
*/

#include<iostream>
#include<vector>

using namespace std;

long long Flip_Series() {
	long long n = 0, m = 0;
	cin >> n >> m;

	long long result = (n / 2) * m;//��¼���ս��

	return result;
}

/*int main(int argc, char* argv[]) {
	cout << Flip_Series() << endl;
	return 0;
}*/