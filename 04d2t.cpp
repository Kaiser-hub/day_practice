#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

//M为需要转换的十进制数，N为转换为N进制的判定
void BaseConversion(int M , int N) {
	string Conversion("0123456789ABCDEF");//由于N最大为16，所以设置为“0123456789ABCDEF”
	string ret;
	int flag = 1;//flag用来判断是正数还是负数，正数flag为1，负数flag为0
	//先处理负数的情况
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
	//ret此时是一个倒序的结果，需要翻转字符串
	reverse(ret.begin(), ret.end());
	cout << ret << endl;
}

/*int main() {
	int M = 0, N = 0;
	cin >> M >> N;
	BaseConversion(M, N);
}*/