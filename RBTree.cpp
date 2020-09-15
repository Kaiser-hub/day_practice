#include<iostream>
#include<utility>

using namespace std;

enum Color{
	Red,
	Black
};

template<class K,class V>
//����ڵ�
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
//��������
class RBTree {
public:
	typedef RBNode<K, V> Node;

	RBTree()
		:_header(new Node)
	{
		//���һ����Ϊ�գ���ô_header������������ָ�����Լ�
		_header->_left = _header->_right = _header;
	}

	//���뼰����
	bool insert(const pair<K, V>& val) {
		//���������
		if (_header->_parent == nullptr) {
			Node* root = new Node(val);
			_header->_parent = root;
			root->_parent = _header;
	
			root->_color = Black;

			_header->_left = root;
			_header->_right = root;
		}

		//�ǿ��������
		Node* cur = _header->_parent;
		Node* parent = nullptr;

		while (cur) {
			parent = cur;
			//����keyֵ��pair.first�����������еĽڵ���бȽ�
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

		//��������ɫ�޸ĺ���ת
		while (cur != _header->_parent && cur->_parent->_color == Red) {
			Node* p = cur->_parent;
			Node* g = p->_parent;

			if (p == g->_left) {
				Node* u = g->_right;
				//��һ�������u������Ϊ��ɫ��
				if (u && u->_color == Red) {
					//�޸���ɫ
					u->_color = p->_color = Black;
					g->_color = Red;
					//���ϸ���
					cur = g;
				}
				//�ڶ��������u�����ڻ���uΪ�ڣ�
				else {
					if (cur == p->_right) {
						RotateL(p);
						swap(cur, p);
					}
					//cur��p����ߣ�����
					RotateR(g);
					p->_color = Black;
					g->_color = Red;

					break;
				}
			}
			else {
				Node* u = g->_left;
				if (u && u->_color == Red) {
					//�޸���ɫ
					u->_color = p->_color = Black;
					g->_color = Red;
					//���ϸ���
					cur = g;
				}
				else {
					if (cur == p->_left) {
						RotateR(p);
						swap(cur, p);
					}
					//cur��p����ߣ�����
					RotateL(g);
					p->_color = Black;
					g->_color = Red;

					break;
				}
			}
		}

		//���ڵ���ɫ��Ϊ��ɫ
		_header->_parent->_color = Black;
		//����_header������ָ��
		_header->_left = leftmost();
		_header->_right = rightmost();
		return true;
	}

	//��ȡ��������˽ڵ�
	Node* leftmost(){
		Node* cur = _header->_parent;
		while (cur && cur->_left)
			cur = cur->_left;
		return cur;
	}

	//��ȡ�������Ҷ˽ڵ�
	Node* rightmost(){
		Node* cur = _header->_parent;
		while (cur && cur->_right)
			cur = cur->_right;
		return cur;
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
		if (parent == _header->_parent) {
			_header->_parent = subL;
			subL->_parent = _header;
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
		if (parent == _header->_parent) {
			_header->_parent = subR;
			subR->_parent = _header;
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
	}

	//�������
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

	//�ж��Ƿ��Ǻ����
	bool isRBTree() {
		Node* root = _header->_parent;
		if (root == nullptr) {
			return true;
		}
		//1.�жϸ��ڵ��Ƿ��Ǻ�ɫ
		if (root->_color != Black) {
			return false;
		}

		//2.�ж�ÿ��·���ϵĺ�ɫ�ڵ�����Ƿ���ͬ
		//3.�ж��Ƿ���������ĺ�ɫ�ڵ�
		//���Ȼ�ȡһ��·���ĺ�ɫ�ڵ������Ϊһ����׼ֵ��������·��ȥ�Ƚ�
		int blackCount = 0;
		Node* cur = root;
		//��������һ��·���ĺ�ɫ�ڵ������Ϊ��׼ֵ
		while (cur) {
			if (cur->_color == Black) {
				blackCount++;
			}
			cur = cur->_left;
		}

		int curCount = 0;
		//����������
		return _isRBTree(root, blackCount, curCount);
	}
	bool _isRBTree(Node* cur, int blackCount, int curCount) {
		//��ǰ·���º�ɫ�ڵ�����Ƿ����׼ֵ��ͬ
		if (cur == nullptr) {
			if (blackCount != curCount) {
				return false;
			}
			return true;
		}

		//�ۼӵ�ǰ·���º�ɫ�ڵ���
		if (cur->_color == Black) {
			curCount++;
		}

		Node* parent = cur->_parent;
		if (parent && parent->_color == Red && cur->_color == Red) {
			cout << "�����������ĺ�ɫ�ڵ�" << endl;
			return false;
		}

		return _isRBTree(cur->_left, blackCount, curCount) && _isRBTree(cur->_right, blackCount, curCount);
	}
private:
	//_header�����Ǹ��ڵ㣬����ָ����ڵ��һ��ͷ�ڵ�
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