#include<iostream>

using namespace std;

template<class T>
struct AVLNode {
	T _val;
	int _bf;//平衡因子
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

		//更新平衡因子，调整树的结构
		while (parent) {
			//更新parent的平衡因子
			if (parent->_left == cur) {
				parent->_bf--;
			}
			else {
				parent->_bf++;
			}
			//判断是否需要继续向上更新
			if (parent->_bf == 0) {
				//节点平衡因子更新为0，则表示对于它的祖先节点来说，它本身的高度不影响祖先节点的高度
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1) {
				//继续向上更新
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == -2 || parent->_bf == 2) {
				//需要调整树的结构
				if (parent->_bf == -2 && cur->_bf == -1) {
					//左边的左边高，右旋
					RotateR(parent);
					cout << "insert: " << val << "右旋：" << parent->_val << endl;
				}
				else if (parent->_bf == 2 && cur->_bf == 1) {
					//右边的右边高，左旋
					RotateL(parent);
					cout << "insert: " << val << "左旋：" << parent->_val << endl;
				}
				else if (parent->_bf == 2 && cur->_bf == -1) {
					//右边的左边高
					cout << "insert: " << val << "右左双旋" << parent->_val << " " << cur->_val << endl;
					Node* subR = parent->_right;
					Node* subRL = subR->_left;
					int bf = subRL->_bf;
					//先以cur为轴右旋
					RotateR(cur);
					//再以parent为轴左旋
					RotateL(parent);

					//调整平衡因子
					if (bf == 1) {
						//subRL的右子树高
						subR->_bf = 0;
						parent->_bf = -1;
					}
					else if (bf == -1) {
						//subRL的左子树高
						subR->_bf = 1;
						parent->_bf = 0;
					}
				}
				else if (parent->_bf == -2 && cur->_bf == 1) {
					//左边的右边高
					cout << "insert: " << val << "左右双旋" << parent->_val << " " << cur->_val << endl;
					Node* subL = parent->_left;
					Node* subLR = subL->_right;
					int bf = subLR->_bf;
					//先以cur为轴左旋
					RotateL(cur);
					//再以parent为轴右旋
					RotateR(parent);

					//调整平衡因子
					if (bf == -1) {
						//subLR的左子树高
						subL->_bf = 0;
						parent->_bf = 1;
					}
					else if (bf == 1) {
						//subLR的右子树高
						subL->_bf = -1;
						parent->_bf = 0;
					}
				}
				break;
			}
		}
		return true;
	}

	//右旋操作
	void RotateR(Node* parent) {
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		//更新subL、subLR、parent以及parent->_parent,四个节点之间的六个连接
		subL->_right = parent;
		parent->_left = subLR;

		if (subLR) {
			subLR->_parent = parent;
		}

		//没有parent->_parent的情况
		if (parent == _root) {
			_root = subL;
			subL->_parent = nullptr;
		}
		//有parent->_parent的情况
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

	//左旋操作
	void RotateL(Node* parent) {
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		//更新subR、subRL、parent以及parent->_parent,四个节点之间的六个连接
		subR->_left = parent;
		parent->_right = subRL;

		if (subRL) {
			subRL->_parent = parent;
		}

		//没有parent->_parent的情况
		if (parent == _root) {
			_root = subR;
			subR->_parent = nullptr;
		}
		//有parent->_parent的情况
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
	
	//中序遍历
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

	//检查是否是AVL树
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
			cout << "节点：" << root->_val << "异常：bf：" << root->_bf << "高度差：" << subR - subL << endl;
			return false;
		}
		return abs(root->_bf) < 2 && _isAVLTree(root->_left) && _isAVLTree(root->_right);
	}
	
	//记录以root为根的树的高度
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