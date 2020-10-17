/*

小A很喜欢字母N，他认为连续的N串是他的幸运串。有一天小A看到了一个全部由大写字母组成的字符串，他被允许改变最多2个大写字母（也允许不改变或者只改变1个大写字母），使得字符串中所包含的最长的连续的N串的长度最长。你能帮助他吗？


输入描述:
输入的第一行是一个正整数T（0 < T <= 20），表示有T组测试数据。对于每一个测试数据包含一行大写字符串S（0 < |S| <= 50000，|S|表示字符串长度）。

数据范围：

20%的数据中，字符串长度不超过100；

70%的数据中，字符串长度不超过1000；

100%的数据中，字符串长度不超过50000。


输出描述:
对于每一组测试样例，输出一个整数，表示操作后包含的最长的连续N串的长度。
示例1

输入
3
NNTN
NNNNGGNNNN
NGNNNNGNNNNNNNNSNNNN

输出
4
10
18
*/

#include<iostream>
#include<algorithm>
#include<string>
#include<vector>

using namespace std;

//滑动窗口法
void Max_N() {
	string s;
	cin>>s;

	int not_N = 0;//当前s中不是N的字符个数
	vector<int> Not_N(0);//记录每一个不是N的字符在字符串第几个位置
	for (int i = 0; i < s.length(); i++) {
		if (s[i] != 'N') {
			Not_N.push_back(i + 1);
			not_N++;
		}
	}

	//如果非N字符不多于2个，那么N连续串最大为s.length()
	if (not_N <= 2) {
		cout << s.length() << endl;
	}
	//如果非N字符等于3个，那么N连续串最大为修改前两个或者修改后两个非N字符后的较大者
	else if(not_N == 3){
		cout << max((int)(s.length() - Not_N[0]), Not_N[2] - 1) << endl;
	}
	//如果非N字符大于3个，那么每次遇到非N字符就可以加上它的前一个非N字符和后一个非N字符当做3个非N字符的情况处理
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
	int T = 0;//T组数据
	cin >> T;
	while (T > 0) {
		Max_N();
		T--;
	}
	return 0;
}