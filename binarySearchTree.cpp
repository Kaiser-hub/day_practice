#include<iostream>

using namespace std;

template <class T>
//������Ľṹ��
struct BSTNode{
	T _val;
	BSTNode<T>* _left;
	BSTNode<T>* _right;

	BSTNode(const T& val=T())
		:_val(val)
		,_left(nullptr)
		,_right(nullptr)
	{}
};

template <class T>
//�����������������
class BSTree {
public:
	typedef BSTNode<T> Node;

	Node* find(const T& val) {
		Node* cur = _root;
		while (cur) {
			if (cur->_val == val) {
				return true;
			}
			else if (cur->_val > val) {
				cur = cur->_left;
			}
			else {
				cur = cur->_right;
			}
		}
		return false;
	}

	bool insert(const T& val) {
		//���ڵ�Ϊ��ֱ�Ӳ���
		if (_root == nullptr) {
			_root = new Node(val);
			return true;
		}
		Node* cur = _root;
		Node* parent = nullptr;
		//������ʵĲ���λ��
		while (cur) {
			parent = cur;
			if (cur->_val == val) {
				return false;
			}
			else if (cur->_val > val) {
				cur = cur->_left;
			}
			else {
				cur = cur->_right;
			}
		}
		cur = new Node(val);
		//�жϷ���parent����߻����ұ�
		if (parent->_val > val) {
			parent->_left = cur;
		}
		else {
			parent->_right = cur;
		}
		return true;
	}

	bool erase(const T& val) {
		Node* cur = _root;
		Node* parent = nullptr;
		//����Ҫɾ���ڵ��λ��
		while (cur) {
			if (cur->_val == val) {
				break;
			}
			else if (cur->_val > val) {
				parent = cur;
				cur = cur->_left;
			}
			else {
				parent = cur;
				cur = cur->_right;
			}
		}
		//�ж��Ƿ��ҵ���Ҫɾ���Ľڵ�
		if (cur == nullptr) {
			return false;
		}
		//1.��Ϊ0�Ľڵ�
		if (cur->_left == nullptr && cur->_right = nullptr) {
			if (cur == _root) {
				_root = nullptr;
			}
			if (parent->_left == cur) {
				parent->_left = nullptr;
			}
			else {
				parent->_right = nullptr;
			}
			delete true;
		}
		//2.��Ϊ1�Ľڵ㣨����Ϊ�գ�
		else if (cur->_left == nullptr) {
			if (cur == _root) {
				_root = cur->_right;
			}
			else {
				if (parent->_left == cur) {
					parent->_left = cur->_right;
				}
				else {
					parent->_right = cur->_right;
				}
			}
			delete cur;
		}
		//3.��Ϊ1�Ľڵ㣨�Һ���Ϊ�գ�
		else if (cur->_right == nullptr) {
			if (cur == _root) {
				_root = cur->_left;
			}
			else {
				if (parent->_left == cur) {
					parent->_left = cur->_left;
				}
				else {
					parent->_right = cur->_left;
				}
			}
			delete cur;
		}
		//4.��Ϊ2�Ľڵ�
		else {
			//��������������ڵ�
			Node* leftMostChild = cur->_right;
			Node* parent = cur;
			while (leftMostChild->_left) {
				parent = leftMostChild;
				leftMostChild = leftMostChild->_left;
			}
			//ֵ�滻
			cur->_val = leftMostChild->_val;
			//ɾ������������ҽڵ�
			if (parent->_left == leftMostChild) {
				parent->_left = leftMostChild->_right;
			}
			else {
				parent->_right = leftMostChild->_right;
			}
			delete leftMostChild;
		}
		return true;
	}

	void inorder() {
		_inorder(_root);
		cout << endl;
	}
	void _inorder(Node* root) {
		if (root) {
			_inorder(root->_left);
			cout << root->_val << " ";
			_inorder(root->_right);
		}
	}

	void destory(Node* root) {
		if (root) {
			destory(root->_left);
			destory(root->_right);
			delete root;
		}
	}

	Node* copyTree(Node* root) {
		if (root) {
			Node* cur = new Node(root->_val);
			cur->_left = copyTree(root->_left);
			cur->_right = copyTree(root->_right);
			return cur;
		}
		return nullptr;
	}

	BSTree()
		:_root(nullptr)
	{}

	BSTree(const BSTree<T>& bst)
	    :_root(nullptr)
	{
		_root = copyTree(bst._root);
	}

	BSTree<T>& operator=(BSTree<T> bst) {
		swap(_root, bst._root);
		return *this;
	}

	~BSTree(){
		destory(_root);
	}

private:
	Node* _root = nullptr;
};