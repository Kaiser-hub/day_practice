#include<iostream>

using namespace std;

class Date {
private:
	int _year;
	int _month;
	int _day;
public:
	//�ж������Ƿ�Ϸ�
	Date(int year = 2000, int month = 1, int day = 1) {
		if (year > 0 && month > 0 && day > 0
			&& month < 13 && day <= GetDay(year, month)) {
			_year = year;
			_month = month;
			_day = day;
		}
		else {
			cout << "�����ڲ��Ϸ�" << endl;
			cout << "ϵͳ�Ѱ������õ�Ĭ������2000-1-1" << endl;
			_year = 2000;
			_month = 1;
			_day = 1;
		}
	}
	
	//��ȡÿ������
	int GetDay(int year, int month) {
		static int monthday[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
		int day = monthday[month];
		//�ж������2�·�����
		if (month == 2 && (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))) {
			++day;
			return day;
		}
		return day;
	}

	//������+=ʵ�֣���������غ���ʵ��
	//a += b;
	Date& operator+=(int day) {
		//a += -b -->a -= b
		if (day < 0) {
			return *this -= -day;
		}
		_day += day;
		//����������λ���
		//2000.5.20 + 5 --> 2000.5.25
		//2000.5.20 + 15 --> 2000.5.35 --> ��λ --> -31 --> �·ݽ�λ --> 2000.6.4
		//2000.12.21 +20 --> 2000.12.41 --> ��λ --> -31 --> �·ݽ�λ --> 2000.13.10 --> -12 --> ��ݽ�λ --> 2001.1.10
		//�ж� += ֮�������Ƿ���Ҫ��λ
		while (_day > GetDay(_year, _month)) {
			//��ȥ���µ���������λ����һ����
			_day -= GetDay(_year, _month);
			_month++;
			//�ж��·��Ƿ����
			if (_month == 13) {
				//��λ����һ��һ��
				_month = 1;
				_year++;
			}
		}
		return *this;
	}

	//a -= b;
	Date& operator-=(int day) {
		//a -= -b -->a += b
		if (day < 0) {
			return *this += -day;
		}
		_day -= day;
		//����������λ���
		//2000.5.20 - 10 --> 2000.5.10
		//2000.5.20 - 30 --> 2000.5.-10 --> ��λ --> +30 --> �·���λ --> 2000.4.20 
		//2001.1.21 - 31 --> 2001.1.-10 --> ��λ --> +31 --> �·���λ --> 2001.0.21 --> +12 --> �����λ --> 2000.12.21
		//�ж� -= ֮�������Ƿ���Ҫ��λ
		while (_day <= 0) {
			//�·���λ
			_month--;
			//�ж��·��Ƿ�С��1
			if (_month == 0) {
				//�����λ
				_month = 12;
				_year--;
			}
			_day += GetDay(_year, _month);
		}
		return *this;
	}

	//++d ǰ��++��ʵ�֣���++��Ȼ�󷵻�++֮�����ֵ
	Date& operator++() {
		return *this += 1;
	}

	//����++: d++: ����++�� ����++֮ǰ��ֵ
	//ǰ��++�� ����++��Ϊ��Ŀ�����
	//���Ϊ��Ա�����������ϲ���Ҫ��ʽ���Σ����������Զ�����thisָ��
	//int�� �ββ���һ�������Ĳ�����ֻ��һ����ǲ��������������������Ķ��壬ͨ���﷨�����������Խ���Ϊ����++
	Date operator++(int) {
		//�ȱ���++֮ǰ����ֵ
		Date ret(*this);
		*this += 1;
		return ret;
	}

	//--d ǰ��--��ʵ�֣���--��Ȼ�󷵻�--֮�����ֵ
	Date& operator--() {
		return *this -= 1;
	}

	//����--: d--: ����--�� ����--֮ǰ��ֵ
	//ǰ��--�� ����--��Ϊ��Ŀ�����
	//���Ϊ��Ա�����������ϲ���Ҫ��ʽ���Σ����������Զ�����thisָ��
	//int�� �ββ���һ�������Ĳ�����ֻ��һ����ǲ��������������������Ķ��壬ͨ���﷨�����������Խ���Ϊ����--
	Date operator--(int) {
		//�ȱ���++֮ǰ����ֵ
		Date ret(*this);
		*this -= 1;
		return ret;
	}

	// +, -������������޸Ĳ�����������
	// c = a + b
	Date operator+(int day) {
		Date ret = *this;
		ret += day;
		return ret;
	}

	Date operator-(int day) {
		Date ret = *this;
		ret -= day;
		return ret;
	}

	bool operator==(const Date& date) {
		return date._year == _year && date._month == _month && date._day == _day;
	}

	bool operator!=(const Date& date) {
		return !(*this == date);
	}

	bool operator>(const Date& date) {
		if (_year > date._year) {
			return true;
		}
		else if (_year == date._year) {
			if (_month > date._month) {
				return true;
			}
			else if (_month == date._month) {
				if (_day > date._day) {
					return true;
				}
			} 
		}
		return false;
	}

	bool operator>=(const Date& date) {
		return (*this > date) || (*this == date);
	}

	bool operator<(const Date& date) {
		return !(*this >= date);
	}

	bool operator<=(const Date& date) {
		return (*this < date) || (*this == date);
	}

    //������������֮��Ĳ�ֵ
	int operator-(Date& date) {
		Date d1(*this);
		Date d2(date);
		int num = 0;
		//d1-d2
		if (d1 > d2) {
			while (d1 > d2) {
				d1--;
				num++;
			}
			return num;
		}
		//d1<=d2
		else {
			while (d1 < d2) {
				d1++;
				num++;
			}
			return -num;
		}
	}

	//ȡ��ַ��������غ���: operator&
	//һ�㲻��Ҫ��ʾ���壬ֱ����Ĭ�ϼ���
	Date* operator&(){
		//return (Date*) 0x1234;
		return this;
	}

	void printD() {// �ȼ��� printD(Date* const this)
		cout << _year << "." << _month << "." << _day << endl;
		//�����޸�����
		//this->_year = 100;
		//���Ե���const��Ա����
		fun();
	}

	//const��Ա�����е�const���ε�Ϊ��һ����������thisָ��
	//const��Ա�����ڲ������޸ĳ�Ա������ֵ
	void printD() const { //�ȼ��� printD(const Date* const this)
		cout << _year << " " << _month << " " << _day << endl;
		//�����޸�����
		//this->_year = 100;
		//���ܵ��÷�const��Ա��������д��Ȩ�޲��ܱ��Ŵ�
		//++*this;
	}
	void fun()const{
	}
	friend istream& operator>>(istream& cin, Date& d);
};

istream& operator>>(istream& cin,Date& d) {
	cin >> d._year >> d._month >> d._day;
	return cin;
}

void test() {
	Date d;
	Date d1;
	//d.printD();
	//d += 32;
	//d.printD();
	//d -= 32;
	//d.printD();
	//d1 = --d;
	//d1.printD();
	cin >> d;
	d.printD();
}

int main() {
	test();
	return 0;
}