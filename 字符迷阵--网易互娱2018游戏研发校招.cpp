/*
�ַ�������һ�־����������Ϸ�������Ҫ�ڸ����ľ��ε��ַ�������Ѱ���ض��ĵ��ʡ�
������Ĺ����У����������¹涨�ģ�
1. ���ַ�������ѡȡһ���ַ���Ϊ���ʵĿ�ͷ��
2. ѡȡ�ҷ����·���������45�ȷ�����Ϊ���ʵ����췽��
3. �Կ�ͷ���ַ�����ѡ�������췽�򣬰������õ��������ַ�ƴ����һ�����Ϊһ�����ʡ�

��ͼ1Ϊ�������Ҫ������Ѱ�ҵ���"WORD"������ɫ������ʾ�Ķ��ǺϷ��ķ���������ɫ������ʾ�Ķ��ǲ��Ϸ��ķ�����
���ڵ������ǣ�����һ���ַ����󣬼�һ��ҪѰ�ҵĵ��ʣ��������ַ��������ҵ����ٸ��õ��ʵĺϷ�������ע��Ϸ������ǿ����ص��ģ���ͼ1��ʾ���ַ��������е���"WORD"�ĺϷ�������4�֡�

��������:
����ĵ�һ��Ϊһ��������T����ʾ�������������� ��������T�����ݡ�ÿ�����ݵĵ�һ�а�����������m��n����ʾ�ַ��������������������������m�У�ÿһ��Ϊһ������Ϊn���ַ�������˳���ʾÿһ��֮�е��ַ����ٽ���������һ�а���һ���ַ�������ʾҪѰ�ҵĵ��ʡ�  ���ݷ�Χ�� �����������ݣ�������1<=T<=9�������������λ���ַ�����͵����е��ַ���Ϊ��д��ĸ��ҪѰ�ҵĵ������Ϊ2���ַ����Ϊ9���ַ����ַ����������������СΪ1�����Ϊ99�� ��������50%�������ļ����ַ������������������Ϊ���Ϊ20��

�������:
����ÿһ�����ݣ����һ�У�����һ��������Ϊ�ڸ������ַ��������ҵ������ĵ��ʵĺϷ���������

��������1:
3
10 10
AAAAAADROW
WORDBBBBBB
OCCCWCCCCC
RFFFFOFFFF
DHHHHHRHHH
ZWZVVVVDID
ZOZVXXDKIR
ZRZVXRXKIO
ZDZVOXXKIW
ZZZWXXXKIK
WORD
3 3
AAA
AAA
AAA
AA
5 8
WORDSWOR
ORDSWORD
RDSWORDS
DSWORDSW
SWORDSWO
SWORD

�������1:
4
16
5
*/

#include<iostream>
#include<string>
#include<vector>

using namespace std;

void Find_word() {
	int m = 0, n = 0;//m��ʾ�ַ������������n��ʾ�ַ����������
	cin >> m >> n;

	string str;
	vector<string> MN;

	for (int i = 0; i < m; i++) {
		cin >> str;
		MN.push_back(str);
	}

	string find_word;
	cin >> find_word;

	int count = 0;
	for (int i = 0; i < MN.size(); i++) {
		for (int j = 0; j < str.size(); j++) {
			if (MN[i][j] == find_word[0]) {
				//������
				for (int k = 1; k < find_word.size(); k++) {
					if (j + k >= n)
						break;
					if (MN[i][j + k] != find_word[k])
						break;
					if (k == find_word.size() - 1)
						count++;
				}

				//������
				for (int k = 1; k < find_word.size(); k++) {
					if (i + k >= m)
						break;
					if (MN[i + k][j] != find_word[k])
						break;
					if (k == find_word.size() - 1)
						count++;
				}

				//��������
				for (int k = 1; k < find_word.size(); k++) {
					if (i + k >= m || j + k >= n)
						break;
					if (MN[i + k][j + k] != find_word[k])
						break;
					if (k == find_word.size() - 1)
						count++;
				}
			}
		}
	}

	cout << count << endl;
}

//int main(int argc, char* argv[]) {
//	int T = 0;//�������ݵ�����
//	cin >> T;
//	while (T > 0) {
//		Find_word();
//		T--;
//	}
//	return 0;
//}