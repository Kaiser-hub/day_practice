#include<iostream>
#include<string>

using namespace std;

template <class T>
class Vector {
private:
	T* _start;//首元素开始的位置
	T* _finish;//最后一个元素结束的位置
	T* _end;//空间的结束位置
public:
	Vector()
		:_start(nullptr)
		,_finish(nullptr)
		,_end(nullptr)
	{}

	size_t size() const {
		return _finish - _start;
	}

	size_t capacity() const {
		return _end - _start;
	}

	void reserve(size_t n) {
		if (n > capacity()) {
			//先保留原先的size，防止释放之后无法使用
			size_t oldsize = size();
			//开空间
			T* tmp = new T[n];
			//数据拷贝：内存拷贝，浅拷贝，memcpy不开新的空间，会导致二次释放的问题
			//memcpy(tmp, _start, sizeof(T)*size());
			
			//深拷贝：调用T类型的赋值运算符
			for (int i = 0; i < size(); i++) {
				tmp[i] = _start[i];
			}
			//释放原有空间
			delete[] _start;
			//更新空间的指向，以便更新容量
			_start = tmp;
			_finish = _start + oldsize;
			_end = _start + n;
		}
	}

	//尾插
	void pushBack(const T& val) {
		//检查容量
		if (_finish == _end) {
			size_t newC = capacity() == 0 ? 1 : 2 * capacity();
			reserve(newC);
		}
		//插入
		*_finish = val;
		//更新size
		_finish++;
	}

	//operator[]:可读可写
	T& operator[](size_t pos) {
		if (pos < size()){
			return _start[pos];
		} 
	}

	//operator[]：只读
	const T& operator[](size_t pos) const {
		if (pos < size()) {
			return _start[pos];
		}
	}

	//迭代器实现
	typedef T* iterator;
	typedef const T* const_iterator;

	//可读可写
	iterator begin() {
		return _start;
	}

	iterator end() {
		return _finish;
	}

	//只读
	const_iterator begin() const {
		return _start;
	}

	const_iterator end() const {
		return _finish;
	}

	//val默认值：内置类型：0值，自定义类型：调用无参构造
	void resize(size_t n, const T& val = T()) {
		if (n > capacity()) {
			reserve(n);
		}
		if (n > size()) {
			while (_finish != _start + n) {
				*_finish++ = val;
			}
		}
		//更新size
		_finish = _start + n;
	}

	//任意位置插入
	void insert(iterator pos, const T& val) {
		if (pos >= _start && pos <= _finish) {
			//检查容量
			if (_finish == _end) {
				//增容会导致迭代器失效，如果发生了增容，需要更新迭代器
				//保存当前位置与起始位置的偏移量
				int len = pos - _start;
				size_t newC = capacity() == 0 ? 1 : 2 * capacity();
				reserve(newC);
				//更新迭代器
				pos = _start + len;
			}
			//移动元素
			iterator end = _finish;
			while (end > pos) {
				*end = *(end - 1);
				end--;
			}
			//插入元素
			*pos = val;
			//更新size
			_finish++;
		}
	}

	//删除
	void erase(iterator pos) {
		if (pos >= _start && pos < _finish) {
			//移动元素
			iterator begin = pos + 1;
			while (bgein != _finish) {
				//不用begin+1 是为了防止访问越界
				*(begin - 1) = *begin;
				begin++;
			}
			//更新size
			_finish--;
		}
	}
};

//只读遍历
template<class T>
void printfVector(const Vector<T>& v) {
	cout << "operator[]:" << endl;
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;
	cout << "迭代器:" << endl;
	Vector<T>::iterator it = v.begin();
	while (it != v.end()) {
		cout << *it << " ";
		it++;
	}
	cout << endl;
	cout << "范围for" << endl;
	for (const T& str : v) {
		cout << str << " ";
	}
	cout << endl;
}

void test() {
	Vector<int> s;
	Vector<char> ch;
	s.pushBack(1);
	size_t size = s.size();
	size_t size1 = ch.size();
	size_t cap = s.capacity();
	size_t cap1 = ch.capacity();

	cout << size << cap << endl;
}

void test2() {
	Vector<string> s;
	s.pushBack("1");
	s.pushBack("2");
	s.pushBack("3");
	s.pushBack("4");
	s.pushBack("5");

	
	for (int i = 0; i < s.size(); i++) {
		cout << s[i] << " ";
		s[i] = "b";
	}

	cout << endl;
	for (int i = 0; i < s.size(); i++) {
		cout << s.operator[](i) << " ";
	}
	cout << endl;

	//迭代器
	Vector<string>::iterator it = s.begin();
	while (it != s.end()) {
		cout << *it << " ";
		it++;
	}
}

void test3() {
	Vector<int> v;
	Vector<char> v2;
	Vector<string> v3;

	v.resize(5);
	v2.resize(5);
	v3.resize(5);
}


int main() {
	test3();
	return 0;
}
//1:49:25