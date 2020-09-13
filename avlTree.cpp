#include<iostream>

using namespace std;

template<class T>
struct AVLNode {
	T _val;
	int _bf;//ƽ������
	AVLNode<T>* _left;
	AVLNode<T>* _right;
	AVLNode<T>* _parent;

	AVLNode(const T& val = T())
		:_val(val)
		,_bf(0)
		,_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
	{}
};

template<class T>
class AVLTree {
public:
	typedef AVLNode<T> Node;

	AVLTree()
		:_root(nullptr)
	{}

	bool insert(const T& val) {
		if (_root == nullptr) {
			_root =new Node(val);
			return true;
		}
		Node* cur = _root;
		Node* parent = nullptr;
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
		if (parent->_val > val) {
			parent->_left = cur;
		}
		else {
			parent->_right = cur;
		}
		cur->_parent = parent;

		//����ƽ�����ӣ��������Ľṹ
		while (parent) {
			//����parent��ƽ������
			if (parent->_left == cur) {
				parent->_bf--;
			}
			else {
				parent->_bf++;
			}
			//�ж��Ƿ���Ҫ�������ϸ���
			if (parent->_bf == 0) {
				//�ڵ�ƽ�����Ӹ���Ϊ0�����ʾ�����������Ƚڵ���˵��������ĸ߶Ȳ�Ӱ�����Ƚڵ�ĸ߶�
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1) {
				//�������ϸ���
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == -2 || parent->_bf == 2) {
				//��Ҫ�������Ľṹ
				if (parent->_bf == -2 && cur->_bf == -1) {
					//��ߵ���߸ߣ�����
					RotateR(parent);
					cout << "insert: " << val << "������" << parent->_val << endl;
				}
				else if (parent->_bf == 2 && cur->_bf == 1) {
					//�ұߵ��ұ߸ߣ�����
					RotateL(parent);
					cout << "insert: " << val << "������" << parent->_val << endl;
				}
				else if (parent->_bf == 2 && cur->_bf == -1) {
					//�ұߵ���߸�
					cout << "insert: " << val << "����˫��" << parent->_val << " " << cur->_val << endl;
					Node* subR = parent->_right;
					Node* subRL = subR->_left;
					int bf = subRL->_bf;
					//����curΪ������
					RotateR(cur);
					//����parentΪ������
					RotateL(parent);

					//����ƽ������
					if (bf == 1) {
						//subRL����������
						subR->_bf = 0;
						parent->_bf = -1;
					}
					else if (bf == -1) {
						//subRL����������
						subR->_bf = 1;
						parent->_bf = 0;
					}
				}
				else if (parent->_bf == -2 && cur->_bf == 1) {
					//��ߵ��ұ߸�
					cout << "insert: " << val << "����˫��" << parent->_val << " " << cur->_val << endl;
					Node* subL = parent->_left;
					Node* subLR = subL->_right;
					int bf = subLR->_bf;
					//����curΪ������
					RotateL(cur);
					//����parentΪ������
					RotateR(parent);

					//����ƽ������
					if (bf == -1) {
						//subLR����������
						subL->_bf = 0;
						parent->_bf = 1;
					}
					else if (bf == 1) {
						//subLR����������
						subL->_bf = -1;
						parent->_bf = 0;
					}
				}
				break;
			}
		}
		return true;
	}

	//��������
	void RotateR(Node* parent) {
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		//����subL��subLR��parent�Լ�parent->_parent,�ĸ��ڵ�֮�����������
		subL->_right = parent;
		parent->_left = subLR;

		if (subLR) {
			subLR->_parent = parent;
		}

		//û��parent->_parent�����
		if (parent == _root) {
			_root = subL;
			subL->_parent = nullptr;
		}
		//��parent->_parent�����
		else {
			Node* pp = parent->_parent;
			subL->_parent = pp;
			if (pp->_left == parent) {
				pp->_left = subL;
			}
			else {
				pp->_right = subL;
			}
		}
		parent->_parent = subL;
		parent->_bf = subL->_bf = 0;
	}

	//��������
	void RotateL(Node* parent) {
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		//����subR��subRL��parent�Լ�parent->_parent,�ĸ��ڵ�֮�����������
		subR->_left = parent;
		parent->_right = subRL;

		if (subRL) {
			subRL->_parent = parent;
		}

		//û��parent->_parent�����
		if (parent == _root) {
			_root = subR;
			subR->_parent = nullptr;
		}
		//��parent->_parent�����
		else {
			Node* pp = parent->_parent;
			subR->_parent = pp;
			if (pp->_left == parent) {
				pp->_left = subR;
			}
			else {
				pp->_right = subR;
			}
		}
		parent->_parent = subR;
		parent->_bf = subR->_bf = 0;
	}
	
	//�������
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

	//����Ƿ���AVL��
	bool isAVLTree() {
		return _isAVLTree(_root);
	}
	bool _isAVLTree(Node* root) {
		if (root == nullptr) {
			return true;
		}

		int subL = Height(root->_left);
		int subR = Height(root->_right);

		if (root->_bf != subR - subL) {
			cout << "�ڵ㣺" << root->_val << "�쳣��bf��" << root->_bf << "�߶Ȳ" << subR - subL << endl;
			return false;
		}
		return abs(root->_bf) < 2 && _isAVLTree(root->_left) && _isAVLTree(root->_right);
	}
	
	//��¼��rootΪ�������ĸ߶�
	int Height(Node* root) {
		if (root == nullptr) {
			return 0;
		}
		int left = Height(root->_left);
		int right = Height(root->_right);
		return left > right ? left + 1 : right + 1;
	}
private:
	Node* _root;
};

void testAVLTree() {
	int arr[] = { 0,9,1,4,3,5,6,8,7,2};
	AVLTree<int> avl;

	for (const auto& e : arr) {
		avl.insert(e);
	}
	avl.inorder();
	cout << avl.isAVLTree() << endl;
}

/*int main() {
	testAVLTree();
	return 0;
}*/