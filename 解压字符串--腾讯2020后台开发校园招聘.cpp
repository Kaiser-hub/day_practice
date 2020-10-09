/*
小Q想要给他的朋友发送一个神秘字符串，但是他发现字符串的过于长了，于是小Q发明了一种压缩算法对字符串中重复的部分进行了压缩，
对于字符串中连续的m个相同字符串S将会压缩为[m|S](m为一个整数且1 <= m <= 100)，
例如字符串ABCABCABC将会被压缩为[3|ABC]，
现在小Q的同学收到了小Q发送过来的字符串，你能帮助他进行解压缩么？

输入描述 :
输入第一行包含一个字符串s，代表压缩后的字符串。
S的长度 <= 1000;
S仅包含大写字母、[、]、 | ;
解压后的字符串长度不超过100000;
压缩递归层数不超过10层;


输出描述:
输出一个字符串，代表解压后的字符串。
示例1
输入
HG[3|B[2|CA]]F

输出
HGBCACABCACABCACAF

说明
HG[3 | B[2 | CA]]F− > HG[3 | BCACA]F− > HGBCACABCACABCACAF

*/





#include<iostream>
#include<string>
#include<stack>
#include<vector>

using namespace std;

//解法一：使用栈来解决问题
void StringZip(){
	string s;
	cin >> s;
	stack<char> sk;
	int i = 0;
	for (i; i < s.length(); i++) {
		//遇到左括号压入栈
		if (s[i] == '[') {
			sk.push(s[i]);
		}
		//遇到右括号，开始往前寻找最近的左括号，与之匹配
		else if (s[i] == ']') {
			char tmpc = sk.top();
			string tmp;
			//记录[]之中的需要展开的内容
			while (tmpc >= 'A'&&tmpc <= 'Z') {
				tmp = tmpc + tmp;
				sk.pop();//取出栈顶元素
				tmpc = sk.top();
			}
			//如果当前栈不为空，证明下一个栈顶元素必然是'|'
			if (!sk.empty()) {
				sk.pop();//取出'|'
			}
			//n用来记录当前需要展开内容的重复次数
			int n = 0;
			int cntn = 1;
			while (sk.top() >= '0'&&sk.top() <= '9') {
				n = n+(int)(sk.top() - '0')*cntn;
				sk.pop();
				cntn *= 10;
			}
			//tmp_n用来存放展开之后的内容
			string tmp_n;
			while (n > 0) {
				tmp_n += tmp;
				n--;
			}
			//如果当前栈不为空，证明下一个栈顶元素必然是'['
			if (!sk.empty()) {
				sk.pop();//取出'['
			}
			for (int j = 0; j < tmp_n.length(); j++) {
				sk.push(tmp_n[j]);
			}
		}
		//遇到字母以及‘|’压入栈
		else {
			sk.push(s[i]);
		}
	}
	string result;
	while (!sk.empty()) {
		result = sk.top() + result;
		sk.pop();
	}
	cout << result << endl;
}

//解法二：直接在原有的字符串上进行展开操作
void StringZip1() {
	string s;
	cin >> s;
	int i = 0;
	while (i < s.length()) {
		if (s[i] == ']') {
			int partner = i;//寻找与当前']'配对的'['
			int k = i;//寻找当前[]里的|的位置
			while(s[partner] != '[') {
				partner--;
			}
			while(s[k] != '|') {
				k--;
			}
			string s1 = s.substr(k + 1, i - 1 - k);//记录当前[]中的需要解码的重复的字符串内容
			//将n进制的字符串转化为十进制数
			int len = stoi(s.substr(partner + 1, k - partner));
			string s2;
			while (len > 0) {
				s2 += s1;
				len--;
			}
			s.replace(partner, i - partner + 1, s2);
			i = partner + s2.length() - 1;
		}
		i++;
	}
	cout << s << endl;
}

/*int main() {
	StringZip();
	//StringZip1();
	return 0;
}*/