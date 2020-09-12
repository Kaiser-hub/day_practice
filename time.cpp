#include<iostream>

using namespace std;

class Date {
private:
	int _year;
	int _month;
	int _day;
public:
	//判断日期是否合法
	Date(int year = 2000, int month = 1, int day = 1) {
		if (year > 0 && month > 0 && day > 0
			&& month < 13 && day <= GetDay(year, month)) {
			_year = year;
			_month = month;
			_day = day;
		}
		else {
			cout << "该日期不合法" << endl;
			cout << "系统已帮您设置到默认日期2000-1-1" << endl;
			_year = 2000;
			_month = 1;
			_day = 1;
		}
	}
	
	//获取每月天数
	int GetDay(int year, int month) {
		static int monthday[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
		int day = monthday[month];
		//判断闰年的2月份天数
		if (month == 2 && (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))) {
			++day;
			return day;
		}
		return day;
	}

	//日期类+=实现，运算符重载函数实现
	//a += b;
	Date& operator+=(int day) {
		//a += -b -->a -= b
		if (day < 0) {
			return *this -= -day;
		}
		_day += day;
		//几种日期退位情况
		//2000.5.20 + 5 --> 2000.5.25
		//2000.5.20 + 15 --> 2000.5.35 --> 进位 --> -31 --> 月份进位 --> 2000.6.4
		//2000.12.21 +20 --> 2000.12.41 --> 进位 --> -31 --> 月份进位 --> 2000.13.10 --> -12 --> 年份进位 --> 2001.1.10
		//判断 += 之后日期是否需要进位
		while (_day > GetDay(_year, _month)) {
			//减去当月的天数，进位到下一个月
			_day -= GetDay(_year, _month);
			_month++;
			//判断月份是否溢出
			if (_month == 13) {
				//进位到下一年一月
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
		//几种日期退位情况
		//2000.5.20 - 10 --> 2000.5.10
		//2000.5.20 - 30 --> 2000.5.-10 --> 借位 --> +30 --> 月份退位 --> 2000.4.20 
		//2001.1.21 - 31 --> 2001.1.-10 --> 借位 --> +31 --> 月份退位 --> 2001.0.21 --> +12 --> 年份退位 --> 2000.12.21
		//判断 -= 之后日期是否需要退位
		while (_day <= 0) {
			//月份退位
			_month--;
			//判断月份是否小于1
			if (_month == 0) {
				//年份退位
				_month = 12;
				_year--;
			}
			_day += GetDay(_year, _month);
		}
		return *this;
	}

	//++d 前置++的实现，先++，然后返回++之后的数值
	Date& operator++() {
		return *this += 1;
	}

	//后置++: d++: 本身++， 返回++之前的值
	//前置++， 后置++都为单目运算符
	//如果为成员函数，则本质上不需要显式传参，编译器会自动传入this指针
	//int： 形参不是一个真正的参数，只是一个标记参数，编译器看到这样的定义，通过语法树搜索，可以解释为后置++
	Date operator++(int) {
		//先保存++之前的数值
		Date ret(*this);
		*this += 1;
		return ret;
	}

	//--d 前置--的实现，先--，然后返回--之后的数值
	Date& operator--() {
		return *this -= 1;
	}

	//后置--: d--: 本身--， 返回--之前的值
	//前置--， 后置--都为单目运算符
	//如果为成员函数，则本质上不需要显式传参，编译器会自动传入this指针
	//int： 形参不是一个真正的参数，只是一个标记参数，编译器看到这样的定义，通过语法树搜索，可以解释为后置--
	Date operator--(int) {
		//先保存++之前的数值
		Date ret(*this);
		*this -= 1;
		return ret;
	}

	// +, -运算符：不能修改操作数的内容
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

    //计算两个日期之间的差值
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

	//取地址运算符重载函数: operator&
	//一般不需要显示定义，直接用默认即可
	Date* operator&(){
		//return (Date*) 0x1234;
		return this;
	}

	void printD() {// 等价于 printD(Date* const this)
		cout << _year << "." << _month << "." << _day << endl;
		//可以修改内容
		//this->_year = 100;
		//可以调用const成员函数
		fun();
	}

	//const成员函数中的const修饰的为第一个参数，即this指针
	//const成员函数内部补能修改成员变量的值
	void printD() const { //等价于 printD(const Date* const this)
		cout << _year << " " << _month << " " << _day << endl;
		//不能修改内容
		//this->_year = 100;
		//不能调用非const成员函数，读写的权限不能被放大
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