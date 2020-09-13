//ÌâÄ¿Á´½Ó
//https://www.nowcoder.com/practice/f0db4c36573d459cae44ac90b90c6212?tpId=85&&tqId=29868&rp=1&ru=/activity/oj&qru=/ta/2017test/question-ranking
#include<iostream>
#include<string>

using namespace std;

void test() {
	string s1;
	string s2;
	getline(cin,s1);
	getline(cin, s2);
	const char* p2 = s2.c_str();
	while (*p2 != '\0') {
		if ((s1.find(*p2)) != string::npos) {
			s1.erase(s1.find(*p2), 1);
		}
		else
			p2++;
	}
	cout << s1 << endl;
}

/*int main() {
	test();
	return 0;
}*/