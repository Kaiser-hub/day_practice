/*

СA��ϲ����ĸN������Ϊ������N�����������˴�����һ��СA������һ��ȫ���ɴ�д��ĸ��ɵ��ַ�������������ı����2����д��ĸ��Ҳ�����ı����ֻ�ı�1����д��ĸ����ʹ���ַ����������������������N���ĳ���������ܰ�������


��������:
����ĵ�һ����һ��������T��0 < T <= 20������ʾ��T��������ݡ�����ÿһ���������ݰ���һ�д�д�ַ���S��0 < |S| <= 50000��|S|��ʾ�ַ������ȣ���

���ݷ�Χ��

20%�������У��ַ������Ȳ�����100��

70%�������У��ַ������Ȳ�����1000��

100%�������У��ַ������Ȳ�����50000��


�������:
����ÿһ��������������һ����������ʾ������������������N���ĳ��ȡ�
ʾ��1

����
3
NNTN
NNNNGGNNNN
NGNNNNGNNNNNNNNSNNNN

���
4
10
18
*/

#include<iostream>
#include<algorithm>
#include<string>
#include<vector>

using namespace std;

//�������ڷ�
void Max_N() {
	string s;
	cin>>s;

	int not_N = 0;//��ǰs�в���N���ַ�����
	vector<int> Not_N(0);//��¼ÿһ������N���ַ����ַ����ڼ���λ��
	for (int i = 0; i < s.length(); i++) {
		if (s[i] != 'N') {
			Not_N.push_back(i + 1);
			not_N++;
		}
	}

	//�����N�ַ�������2������ôN���������Ϊs.length()
	if (not_N <= 2) {
		cout << s.length() << endl;
	}
	//�����N�ַ�����3������ôN���������Ϊ�޸�ǰ���������޸ĺ�������N�ַ���Ľϴ���
	else if(not_N == 3){
		cout << max((int)(s.length() - Not_N[0]), Not_N[2] - 1) << endl;
	}
	//�����N�ַ�����3������ôÿ��������N�ַ��Ϳ��Լ�������ǰһ����N�ַ��ͺ�һ����N�ַ�����3����N�ַ����������
	else {
		int Max = 0;
		for (int j = 0; j < Not_N.size(); j++) {
			if (j == 0) {
				Max = max(Max, Not_N[j + 2] - 1);
			}
			else if (j == Not_N.size() - 2) {
				Max = max(Max, (int)(s.length() - Not_N[j - 1] ));
				cout << Max << endl;
				return;
			}
			else {
				Max = max(Max, Not_N[j + 2] - Not_N[j - 1] - 1);
			}
		}
	}
}

int main() {
	int T = 0;//T������
	cin >> T;
	while (T > 0) {
		Max_N();
		T--;
	}
	return 0;
}