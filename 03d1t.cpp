#include<iostream>
#include<string>

using namespace std;

void maxCount() {
	string s;
	string s2;
	getline(cin, s);
	int i = 0;
	int k = 0;//记录最长数字串的最后一个元素的位置
	int lenth = 0;//记录每一段数字串的长度
	int maxlenth = 0;//每次获取lenth的值，更新到lenth的最大值
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
			k = i - 1;//当maxlenth获取到最大值时，i此时是最长数字串的下一个非数字元素的位置，所以需要i-1
		}
	}
	s2.insert(0, s, k - maxlenth + 1, maxlenth);
	cout << s2 << endl;
}

/*int main() {
	maxCount();
	return 0;
}*/