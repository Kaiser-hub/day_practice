#include<iostream>
#include<string>

using namespace std;

class String {
public:
	//string��������ͨ��ָ��ʵ��
	typedef char* iterator;
	typedef const char* const_iterator;

	iterator begin() {
		//��һ��Ԫ�ص�λ��
		return _str;
	}

	iterator end() {
		//���һ��Ԫ�ص���һ��λ��
		return _str + _size;
	}

	const_iterator begin() const {
		//��һ��Ԫ�ص�λ��
		return _str;
	}

	const_iterator end() const {
		//���һ��Ԫ�ص���һ��λ��
		return _str + _size;
	}

	String()
		:_str(new char[16]),//����һ��λ�ô��'\0'
		_size(0),
		_capacity(0)
	{
		_str[_size] = '\0';
		_capacity = 15;
	}

	//���ι���
	String(const char* str) {
		_size = strlen(str);
		_str = new char[_size + 1];//����һ��λ�ô��'\0'
		strcpy(_str, str);
		_capacity = _size;
	}

	//�������죨�����
	/*String(const String& str)
		//ֵ����
		:_str(new char[str._capacity + 1]),
		_size(str._size),
		_capacity(str._capacity)
	{
		//��Դ����
		strcpy(_str, str._str);
	}*/

	//�������죺�ִ�д��,���븴�ã����캯��
	String(const String& str)
		:_str(nullptr),
		_size(0),
		_capacity(0)
	{
		//���ù��캯��
		String tmp(str._str);
		Swap(tmp);
	}

	//�򵥽�����û�п��ռ�Ĳ�����ֻ������Ա����Դ
	void Swap(String& str) {
		swap(_str, str._str);
		swap(_size, str._size);
		swap(_capacity, str._capacity);
	}

	/*String& operator=(const String& str) {
		if (this != &str) {
			//���ռ�
			char* tmp = new char[str._capacity + 1];
			//���ݿ���
			strcpy(tmp, str._str);
			//�ͷ�ԭ�пռ�
			delete[] _str;
			//��������
			_str = tmp;
			_size = str._size;
			_capacity = str._capacity;
		}
		return *this;
	}*/

	//��ֵ��������ִ�д�������븴�ã��������죨���ν��п������죩
	String& operator=(String str) {
		Swap(str);
		return *this;
	}

	const char* c_str() const {
		return _str;
	}

	//��������
	~String() {
		if (_str) {
			delete[] _str;
			_size = _capacity = 0;
			_str = nullptr;
		}
		cout << "~String" << endl;
	}

	//β���ַ���ʵ�ʿ���insertʵ�֣�
	void pushBack(const char& ch) {
		//�������
		if (_size == _capacity) {
			size_t newC = _capacity==0 ? 15 : 2 * _capacity;
			reserve(newC);
		}
		//β��
		_str[_size] = ch;
		//����size
		_size++;
		_str[_size] = '\0';
	}

	//����
	void reserve(size_t n) {
		if (n > _capacity) {
			//���ռ�
			char* tmp = new char[n + 1];
			//����
			strcpy(tmp, _str);
			//�ͷ�ԭ�пռ�
			delete[] _str;
			//����ָ������
			_str = tmp;
			_capacity = n;
		}
	}

	//�ַ�����Ч����
	size_t size() const {
		return _size;
	}

	//β���ַ�����ʵ�ʿ���insertʵ�֣�
	void Append(const char* str) {
		int len = strlen(str);//Ҫ�����ַ����ĳ���
		//�������
		if (_size + len > _capacity) {
			reserve(_size + len);
		}
		//β��
		strcpy(_str + _size, str);
		//����size
		_size += len;
	}

	//+= β���ַ���ʵ�ʿ���insertʵ�֣�
	String& operator+=(const char& ch) {
		pushBack(ch);
		return *this;
	}

	//+= β���ַ�����ʵ�ʿ���insertʵ�֣�
	String& operator+=(const char* str) {
		Append(str);
		return *this;
	}

	//����λ�ò����ַ�
	void insert(size_t pos, const char& ch) {
		//�������
		if (_size == _capacity) {
			size_t newC = _capacity == 0 ? 15 : 2 * _capacity;
			reserve(newC);
		}
		//�ƶ�Ԫ��[pos,_size]���Ӻ���ǰ�ƶ�,�����ƶ����Ҷ˵��ַ�����ֹ����
		size_t end = _size + 1;
		//end >= pos:��pos = 0ʱ������ѭ��������Խ��
		while (end > pos) {
			_str[end] = _str[end - 1];//��ʹ��end + 1����ֹ����Խ��
			end--;
		}
		//����
		_str[pos] = ch;
		_size++;
	}

	//����λ�ò����ַ���
	void insert(size_t pos, const char* str) {
		if (pos > _size) {
			return;
		}
		int len = strlen(str);
		//�������
		if (_size + len > _capacity) {
			reserve(_size + len);
		}
		//�ƶ�Ԫ��[pos,_size]:��ǰ����ƶ��������ƶ����Ҷ��ַ�����ֹ����
		size_t end = _size + len;
		while (end > pos + len - 1) {
			_str[end] = _str[end - len];
			end--;
		}
		//����
		for (int i = 0; i < len; i++) {
			_str[i + pos] = str[i];
		}
		//����size
		_size += len;
	}

private:
	char* _str;
	size_t _size;
	size_t _capacity;
};

//�������������ɶ���д����
void EprintfString(String& str) {
	String::iterator it = str.begin();
	while (it != str.end()) {
		cout << *it << " ";
		*it = '0';
		it++;
	}
	cout << endl;
}

//������������ֻ������
void printfString(const String& str){
	String::const_iterator it = str.begin();
	while (it != str.end()) {
		cout << *it << " ";
		it++;
	}
	cout << endl;
}
void test(){
	string s;
	cout << s.c_str() << "����" << endl;
	String str("123");
	cout << str.c_str() << "����" << endl;

}

void test2() {
	String s("123");
	String copy = s;
	String copy2(s);

	String s2("456");
	copy = s2;
	cout << s2.c_str() << endl;
	cout << copy.c_str() << endl;
}

void test3() {
	String s("abcdefg");
	EprintfString(s);
	printfString(s);
	
}

void test4() {
	String s;
	s += '1';
	printfString(s);
	s += "23";
	printfString(s);
}

void test5() {
	String s;
	s += "13459";
	s.insert(1, '2');
	printfString(s);
	s.insert(5, "678");
	printfString(s);
}
int main() {
	test5();
	return 0;
}
