#include<iostream>
#include<utility>

using namespace std;

enum Color{
	Red,
	Black
};

template<class K,class V>
//定义节点
struct RBNode {
	pair<K, V> _val;
	Color _color;
	RBNode<K, V>* _parent;
	RBNode<K, V>* _left;
	RBNode<K, V>* _right;

	RBNode(const pair<K, V>& val = pair<K, V>()) 
		:_val(val)
		,_color(Red)
		,_parent(nullptr)
		,_left(nullptr)
		,_right(nullptr)
	{}
};

template<class K,class V>
//定义红黑树
class RBTree {
public:
	typedef RBNode<K, V> Node;

	RBTree()
		:_header(new Node)
	{
		//如果一棵树为空，那么_header的左右子树均指向它自己
		_header->_left = _header->_right = _header;
	}

	//插入及更新
	bool insert(const pair<K, V>& val) {
		//空树的情况
		if (_header->_parent == nullptr) {
			Node* root = new Node(val);
			_header->_parent = root;
			root->_parent = _header;
	
			root->_color = Black;

			_header->_left = root;
			_header->_right = root;
		}

		//非空树的情况
		Node* cur = _header->_parent;
		Node* parent = nullptr;

		while (cur) {
			parent = cur;
			//按照key值（pair.first）进行与已有的节点进行比较
			if (cur->_val.first == val.first) {
				return false;
			}
			if (cur->_val.first > val.first) {
				cur = cur->_left;
			}
			else {
				cur = cur->_right;
			}
		}

		cur = new Node(val);
		if (parent->_val.first > val.first) {
			parent->_left = cur;
		}
		else {
			parent->_right = cur;
		}

		cur->_parent = parent;

		//调整：颜色修改和旋转
		while (cur != _header->_parent && cur->_parent->_color == Red) {
			Node* p = cur->_parent;
			Node* g = p->_parent;

			if (p == g->_left) {
				Node* u = g->_right;
				//第一种情况（u存在且为红色）
				if (u && u->_color == Red) {
					//修改颜色
					u->_color = p->_color = Black;
					g->_color = Red;
					//向上更新
					cur = g;
				}
				//第二种情况（u不存在或者u为黑）
				else {
					if (cur == p->_right) {
						RotateL(p);
						swap(cur, p);
					}
					//cur在p的左边，右旋
					RotateR(g);
					p->_color = Black;
					g->_color = Red;

					break;
				}
			}
			else {
				Node* u = g->_left;
				if (u && u->_color == Red) {
					//修改颜色
					u->_color = p->_color = Black;
					g->_color = Red;
					//向上更新
					cur = g;
				}
				else {
					if (cur == p->_left) {
						RotateR(p);
						swap(cur, p);
					}
					//cur在p的左边，右旋
					RotateL(g);
					p->_color = Black;
					g->_color = Red;

					break;
				}
			}
		}

		//根节点颜色置为黑色
		_header->_parent->_color = Black;
		//更新_header的左右指向
		_header->_left = leftmost();
		_header->_right = rightmost();
		return true;
	}

	//获取树的最左端节点
	Node* leftmost(){
		Node* cur = _header->_parent;
		while (cur && cur->_left)
			cur = cur->_left;
		return cur;
	}

	//获取树的最右端节点
	Node* rightmost(){
		Node* cur = _header->_parent;
		while (cur && cur->_right)
			cur = cur->_right;
		return cur;
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
		if (parent == _header->_parent) {
			_header->_parent = subL;
			subL->_parent = _header;
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
		if (parent == _header->_parent) {
			_header->_parent = subR;
			subR->_parent = _header;
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
	}

	//中序遍历
	void inorder() {
		_inorder(_header->_parent);
		cout << endl;
	}
	void _inorder(Node* root){
		if (root) {
			_inorder(root->_left);
			cout << root->_val.first << " ";
			_inorder(root->_right);
		}
	}

	//判断是否是红黑树
	bool isRBTree() {
		Node* root = _header->_parent;
		if (root == nullptr) {
			return true;
		}
		//1.判断根节点是否是黑色
		if (root->_color != Black) {
			return false;
		}

		//2.判断每条路径上的黑色节点个数是否相同
		//3.判断是否存在连续的红色节点
		//首先获取一条路径的黑色节点个数作为一个基准值，和其他路径去比较
		int blackCount = 0;
		Node* cur = root;
		//拿最左侧的一条路径的黑色节点个数作为基准值
		while (cur) {
			if (cur->_color == Black) {
				blackCount++;
			}
			cur = cur->_left;
		}

		int curCount = 0;
		//遍历整棵树
		return _isRBTree(root, blackCount, curCount);
	}
	bool _isRBTree(Node* cur, int blackCount, int curCount) {
		//当前路径下黑色节点个数是否与基准值相同
		if (cur == nullptr) {
			if (blackCount != curCount) {
				return false;
			}
			return true;
		}

		//累加当前路径下黑色节点数
		if (cur->_color == Black) {
			curCount++;
		}

		Node* parent = cur->_parent;
		if (parent && parent->_color == Red && cur->_color == Red) {
			cout << "出现了连续的红色节点" << endl;
			return false;
		}

		return _isRBTree(cur->_left, blackCount, curCount) && _isRBTree(cur->_right, blackCount, curCount);
	}
private:
	//_header并不是根节点，它是指向根节点的一个头节点
	Node* _header;
};

void testRBTree() {
	RBTree<int, int> rbt;

	rbt.insert(make_pair(1, 1));
	rbt.insert(make_pair(2, 1));
	rbt.insert(make_pair(3, 1));
	rbt.insert(make_pair(4, 1));
	rbt.insert(make_pair(5, 1));
	rbt.insert(make_pair(0, 1));
	rbt.insert(make_pair(9, 1));
	rbt.insert(make_pair(8, 1));
	rbt.insert(make_pair(7, 1));
	rbt.insert(make_pair(6, 1));
	
	rbt.inorder();
	cout << rbt.isRBTree() << endl;
}

/*int main() {
	testRBTree();
	return 0;

}*/