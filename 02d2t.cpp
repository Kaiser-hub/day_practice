#include<iostream>
#include<string>

using namespace std;

void OverturnStr() {
	string s;
	getline(cin, s);
	//先按字符把整个语句翻转
	int begin = 0;
	int end = (s.length() - 1);
	while(begin < end) {
		char tmp = s[begin];
		s[begin] = s[end];
		s[end] = tmp;
		begin++;
		end--;
	}
	//再每个单词翻转回来
	int j = 0;
	for (int i = 0; i <= s.length(); i++) {
		int k = i - 1;
		if (s[i] == ' '||s[i]=='\0') {
			while (j < k) {
				char tmp = s[j];
				s[j] = s[k];
				s[k] = tmp;
				j++;
				k--;
			}
			j = i + 1;
		}
		
	}
	cout << s << endl;
}

/*int main() {
	OverturnStr();
	return 0;
}*/