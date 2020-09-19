#include<iostream>
#include<vector>

using namespace std;

//����ռ�λ�õ�����״̬
enum State {
	Empty,
	Exist,
	Delete
};

template<class K,class V>
//�����ϣ�ڵ�
struct HashNode{
	pair<K, V> _val;
	State _state;

	HashNode(const pair<K, V>& val = pair<K, V>()) 
		:_val(val)
		,_state(Empty)
	{}
};

template<class K,class V>
//�����ϣ��
class HashTable {
public:
	HashTable(size_t n = 10) {
		_table.resize(n);
		_size = 0;
	}

	//����
	bool insert(const pair<K, V>& val) {
		//�������
		checkCapacity();
		//�����ϣλ��
		int id = val.first%_table.size();
		//����λ�õ�״̬�����Ƿ����,�Լ����Ҫ����������Ƿ��Ѿ�����
		while (_table[id]._state == Exist) {
			if (_table[id]._val.first == val.first) {
				return false;
			}
			id++;
			//�ߵ��ռ�Ľ�β���ص��ռ�Ŀ�ʼλ��
			if (id == _table.size()) {
				id = 0;
			}
		}
		//�ҵ��˺���λ��
		_table[id]._val = val;
		_table[id]._state = Exist;
		_size++;
		return true;
	}

	//��������Լ�����
	void checkCapacity() {
		//���ռ䱻ռ�ٷ�֮80��ʱ���������
		if (_size * 10 / _table.size() >= 8) {
			HashTable Newht(2 * _table.size());

			//�ɱ�Ԫ��Ҫ���²��뵽����֮����±�֮��
			for (int i = 0; i < _table.size(); i++) {
				if (_table[i]._state == Exist) {
					Newht.insert(_table[i]._val);
				}
			}
			//�±��滻�ɱ��������
			swap(_table, Newht._table);
		}
	}

	//����
	HashNode<K, V>* find(const K& key) {
		int id = key % _table.size();
		while (_table[id]._state != Empty) {
			if (id == _table.size()) {
				id = 0;
			}
			if (_table[id]._state == Exist && _table[id]._val.first == key) {
				cout << "���ҳɹ���KֵΪ" << key << "���������±�Ϊ" << id << "��λ��" << endl;
				return &_table[id];
			}
			else {
				id++;
			}
		}
		cout << "û���ҵ�KֵΪ" << key << "������" << endl;
		return nullptr;
	}

	//ɾ��
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