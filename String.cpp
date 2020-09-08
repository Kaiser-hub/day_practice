#include<iostream>
#include<string>

using namespace std;

class String {
public:
	//string迭代器：通过指针实现
	typedef char* iterator;
	typedef const char* const_iterator;

	iterator begin() {
		//第一个元素的位置
		return _str;
	}

	iterator end() {
		//最后一个元素的下一个位置
		return _str + _size;
	}

	const_iterator begin() const {
		//第一个元素的位置
		return _str;
	}

	const_iterator end() const {
		//最后一个元素的下一个位置
		return _str + _size;
	}

	String()
		:_str(new char[16]),//多余一个位置存放'\0'
		_size(0),
		_capacity(0)
	{
		_str[_size] = '\0';
		_capacity = 15;
	}

	//含参构造
	String(const char* str) {
		_size = strlen(str);
		_str = new char[_size + 1];//多余一个位置存放'\0'
		strcpy(_str, str);
		_capacity = _size;
	}

	//拷贝构造（深拷贝）
	/*String(const String& str)
		//值拷贝
		:_str(new char[str._capacity + 1]),
		_size(str._size),
		_capacity(str._capacity)
	{
		//资源拷贝
		strcpy(_str, str._str);
	}*/

	//拷贝构造：现代写法,代码复用：构造函数
	String(const String& str)
		:_str(nullptr),
		_size(0),
		_capacity(0)
	{
		//调用构造函数
		String tmp(str._str);
		Swap(tmp);
	}

	//简单交换，没有开空间的操作，只交换成员和资源
	void Swap(String& str) {
		swap(_str, str._str);
		swap(_size, str._size);
		swap(_capacity, str._capacity);
	}

	/*String& operator=(const String& str) {
		if (this != &str) {
			//开空间
			char* tmp = new char[str._capacity + 1];
			//内容拷贝
			strcpy(tmp, str._str);
			//释放原有空间
			delete[] _str;
			//更新数据
			_str = tmp;
			_size = str._size;
			_capacity = str._capacity;
		}
		return *this;
	}*/

	//赋值运算符：现代写法，代码复用：拷贝构造（传参进行拷贝构造）
	String& operator=(String str) {
		Swap(str);
		return *this;
	}

	const char* c_str() const {
		return _str;
	}

	//析构函数
	~String() {
		if (_str) {
			delete[] _str;
			_size = _capacity = 0;
			_str = nullptr;
		}
		cout << "~String" << endl;
	}

	//尾插字符（实际可用insert实现）
	void pushBack(const char& ch) {
		//检查容量
		if (_size == _capacity) {
			size_t newC = _capacity==0 ? 15 : 2 * _capacity;
			reserve(newC);
		}
		//尾插
		_str[_size] = ch;
		//更新size
		_size++;
		_str[_size] = '\0';
	}

	//扩容
	void reserve(size_t n) {
		if (n > _capacity) {
			//开空间
			char* tmp = new char[n + 1];
			//拷贝
			strcpy(tmp, _str);
			//释放原有空间
			delete[] _str;
			//更新指向、容量
			_str = tmp;
			_capacity = n;
		}
	}

	//字符串有效长度
	size_t size() const {
		return _size;
	}

	//尾插字符串（实际可用insert实现）
	void Append(const char* str) {
		int len = strlen(str);//要插入字符串的长度
		//检查容量
		if (_size + len > _capacity) {
			reserve(_size + len);
		}
		//尾插
		strcpy(_str + _size, str);
		//更新size
		_size += len;
	}

	//+= 尾插字符（实际可用insert实现）
	String& operator+=(const char& ch) {
		pushBack(ch);
		return *this;
	}

	//+= 尾插字符串（实际可用insert实现）
	String& operator+=(const char* str) {
		Append(str);
		return *this;
	}

	//任意位置插入字符
	void insert(size_t pos, const char& ch) {
		//检查容量
		if (_size == _capacity) {
			size_t newC = _capacity == 0 ? 15 : 2 * _capacity;
			reserve(newC);
		}
		//移动元素[pos,_size]：从后向前移动,首先移动最右端的字符，防止覆盖
		size_t end = _size + 1;
		//end >= pos:当pos = 0时，会死循环，访问越界
		while (end > pos) {
			_str[end] = _str[end - 1];//不使用end + 1，防止访问越界
			end--;
		}
		//插入
		_str[pos] = ch;
		_size++;
	}

	//任意位置插入字符串
	void insert(size_t pos, const char* str) {
		if (pos > _size) {
			return;
		}
		int len = strlen(str);
		//检查容量
		if (_size + len > _capacity) {
			reserve(_size + len);
		}
		//移动元素[pos,_size]:从前向后移动，首先移动最右端字符，防止覆盖
		size_t end = _size + len;
		while (end > pos + len - 1) {
			_str[end] = _str[end - len];
			end--;
		}
		//插入
		for (int i = 0; i < len; i++) {
			_str[i + pos] = str[i];
		}
		//更新size
		_size += len;
	}

private:
	char* _str;
	size_t _size;
	size_t _capacity;
};

//迭代器遍历：可读可写操作
void EprintfString(String& str) {
	String::iterator it = str.begin();
	while (it != str.end()) {
		cout << *it << " ";
		*it = '0';
		it++;
	}
	cout << endl;
}

//迭代器遍历：只读操作
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
	cout << s.c_str() << "结束" << endl;
	String str("123");
	cout << str.c_str() << "结束" << endl;

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
