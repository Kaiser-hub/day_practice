#include<iostream>
#include<vector>

using namespace std;

//定义空间位置的三种状态
enum State {
	Empty,
	Exist,
	Delete
};

template<class K,class V>
//定义哈希节点
struct HashNode{
	pair<K, V> _val;
	State _state;

	HashNode(const pair<K, V>& val = pair<K, V>()) 
		:_val(val)
		,_state(Empty)
	{}
};

template<class K,class V>
//定义哈希表
class HashTable {
public:
	HashTable(size_t n = 10) {
		_table.resize(n);
		_size = 0;
	}

	//插入
	bool insert(const pair<K, V>& val) {
		//检查容量
		checkCapacity();
		//计算哈希位置
		int id = val.first%_table.size();
		//检查该位置的状态，看是否可用,以及检查要插入的数据是否已经存在
		while (_table[id]._state == Exist) {
			if (_table[id]._val.first == val.first) {
				return false;
			}
			id++;
			//走到空间的结尾，回到空间的开始位置
			if (id == _table.size()) {
				id = 0;
			}
		}
		//找到了合适位置
		_table[id]._val = val;
		_table[id]._state = Exist;
		_size++;
		return true;
	}

	//检查容量以及扩容
	void checkCapacity() {
		//当空间被占百分之80的时候进行扩容
		if (_size * 10 / _table.size() >= 8) {
			HashTable Newht(2 * _table.size());

			//旧表元素要重新插入到扩容之后的新表之中
			for (int i = 0; i < _table.size(); i++) {
				if (_table[i]._state == Exist) {
					Newht.insert(_table[i]._val);
				}
			}
			//新表替换旧表，完成扩容
			swap(_table, Newht._table);
		}
	}

	//查找
	HashNode<K, V>* find(const K& key) {
		int id = key % _table.size();
		while (_table[id]._state != Empty) {
			if (id == _table.size()) {
				id = 0;
			}
			if (_table[id]._state == Exist && _table[id]._val.first == key) {
				cout << "查找成功，K值为" << key << "的数据在下标为" << id << "的位置" << endl;
				return &_table[id];
			}
			else {
				id++;
			}
		}
		cout << "没有找到K值为" << key << "的数据" << endl;
		return nullptr;
	}

	//删除
	bool erase(const K& key) {
		HashNode<K, V>* result = nullptr;
		int id = key % _table.size();
		while (_table[id]._state != Empty) {
			if (id == _table.size()) {
				id = 0;
			}
			if (_table[id]._state == Exist && _table[id]._val.first == key) {
				 result = &_table[id];
				 break;
			}
			else {
				id++;
			}
		}
		if (result) {
			result->_state = Delete;
			_size--;
			return true;
		}
		return false;
	}
private:
	vector<HashNode<K, V>> _table;
	size_t _size;
};


void testHashTable() {
	HashTable<int, int> ht;
	ht.insert(make_pair(1, 1));
	ht.insert(make_pair(2, 1));
	ht.insert(make_pair(13, 1));
	ht.insert(make_pair(3, 1));
	ht.insert(make_pair(12, 1));
	ht.insert(make_pair(14, 1));
	ht.insert(make_pair(4, 1));
	ht.insert(make_pair(10, 1));
	//ht.insert(make_pair(16, 1));
	//ht.insert(make_pair(17, 1));
	//ht.insert(make_pair(18, 1));

	ht.erase(10);
	ht.find(10);
	ht.find(20);
}

/*int main() {
	testHashTable();
	return 0;
}*/