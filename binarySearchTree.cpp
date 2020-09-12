#include<iostream>

using namespace std;

template <class T>
//定义结点的结构体
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
//定义二叉搜索树的类
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
		//根节点为空直接插入
		if (_root == nullptr) {
			_root = new Node(val);
			return true;
		}
		Node* cur = _root;
		Node* parent = nullptr;
		//插入合适的插入位置
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
		//判断放在parent的左边还是右边
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
		//查找要删除节点的位置
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
		//判断是否找到了要删除的节点
		if (cur == nullptr) {
			return false;
		}
		//1.度为0的节点
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
		//2.度为1的节点（左孩子为空）
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
		//3.度为1的节点（右孩子为空）
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
		//4.度为2的节点
		else {
			//找右子树的最左节点
			Node* leftMostChild = cur->_right;
			Node* parent = cur;
			while (leftMostChild->_left) {
				parent = leftMostChild;
				leftMostChild = leftMostChild->_left;
			}
			//值替换
			cur->_val = leftMostChild->_val;
			//删除最左或者最右节点
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