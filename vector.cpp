#include<iostream>
#include<string>

using namespace std;

template <class T>
class Vector {
private:
	T* _start;//��Ԫ�ؿ�ʼ��λ��
	T* _finish;//���һ��Ԫ�ؽ�����λ��
	T* _end;//�ռ�Ľ���λ��
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
			//�ȱ���ԭ�ȵ�size����ֹ�ͷ�֮���޷�ʹ��
			size_t oldsize = size();
			//���ռ�
			T* tmp = new T[n];
			//���ݿ������ڴ濽����ǳ������memcpy�����µĿռ䣬�ᵼ�¶����ͷŵ�����
			//memcpy(tmp, _start, sizeof(T)*size());
			
			//���������T���͵ĸ�ֵ�����
			for (int i = 0; i < size(); i++) {
				tmp[i] = _start[i];
			}
			//�ͷ�ԭ�пռ�
			delete[] _start;
			//���¿ռ��ָ���Ա��������
			_start = tmp;
			_finish = _start + oldsize;
			_end = _start + n;
		}
	}

	//β��
	void pushBack(const T& val) {
		//�������
		if (_finish == _end) {
			size_t newC = capacity() == 0 ? 1 : 2 * capacity();
			reserve(newC);
		}
		//����
		*_finish = val;
		//����size
		_finish++;
	}

	//operator[]:�ɶ���д
	T& operator[](size_t pos) {
		if (pos < size()){
			return _start[pos];
		} 
	}

	//operator[]��ֻ��
	const T& operator[](size_t pos) const {
		if (pos < size()) {
			return _start[pos];
		}
	}

	//������ʵ��
	typedef T* iterator;
	typedef const T* const_iterator;

	//�ɶ���д
	iterator begin() {
		return _start;
	}

	iterator end() {
		return _finish;
	}

	//ֻ��
	const_iterator begin() const {
		return _start;
	}

	const_iterator end() const {
		return _finish;
	}

	//valĬ��ֵ���������ͣ�0ֵ���Զ������ͣ������޲ι���
	void resize(size_t n, const T& val = T()) {
		if (n > capacity()) {
			reserve(n);
		}
		if (n > size()) {
			while (_finish != _start + n) {
				*_finish++ = val;
			}
		}
		//����size
		_finish = _start + n;
	}

	//����λ�ò���
	void insert(iterator pos, const T& val) {
		if (pos >= _start && pos <= _finish) {
			//�������
			if (_finish == _end) {
				//���ݻᵼ�µ�����ʧЧ��������������ݣ���Ҫ���µ�����
				//���浱ǰλ������ʼλ�õ�ƫ����
				int len = pos - _start;
				size_t newC = capacity() == 0 ? 1 : 2 * capacity();
				reserve(newC);
				//���µ�����
				pos = _start + len;
			}
			//�ƶ�Ԫ��
			iterator end = _finish;
			while (end > pos) {
				*end = *(end - 1);
				end--;
			}
			//����Ԫ��
			*pos = val;
			//����size
			_finish++;
		}
	}

	//ɾ��
	void erase(iterator pos) {
		if (pos >= _start && pos < _finish) {
			//�ƶ�Ԫ��
			iterator begin = pos + 1;
			while (bgein != _finish) {
				//����begin+1 ��Ϊ�˷�ֹ����Խ��
				*(begin - 1) = *begin;
				begin++;
			}
			//����size
			_finish--;
		}
	}
};

//ֻ������
template<class T>
void printfVector(const Vector<T>& v) {
	cout << "operator[]:" << endl;
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;
	cout << "������:" << endl;
	Vector<T>::iterator it = v.begin();
	while (it != v.end()) {
		cout << *it << " ";
		it++;
	}
	cout << endl;
	cout << "��Χfor" << endl;
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

	//������
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