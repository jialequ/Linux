#include <iostream>
using namespace std;

template <class T>
struct AVLNode
{
	AVLNode(const T& data)
		:_data(data)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _bf(0)
	{}

	T _data;
	AVLNode<T>* _left;
	AVLNode<T>* _right;

	AVLNode<T>* _parent;
	int _bf;
};

template <class T>
class AVLTree
{
public:
	typedef AVLNode<T> Node;
	typedef Node* pNode;

	bool Insert(const T& data)
	{
		//判空
		if (_root == nullptr)
		{
			_root = new Node(data);
			return true;
		}

		//搜索
		pNode cur = _root;
		pNode parent = nullptr;
		while (cur)
		{
			parent = cur;
			if (cur->_data == data)
				return false;
			else if (cur->_data > data)
				cur = cur->_left;
			else
				cur = cur->_right;
		}

		//连接
		cur = new Node(data);
		if (parent->_data > data)
			parent->_left = cur;
		else
			parent->_right = cur;
		cur->_parent = parent;

		//调整
		while (parent)
		{
			//更新平衡因子
			//判断新插入的节点在左边还是右边
			if (parent->_right == cur)
			{
				++parent->_bf;
			}
			else
			{
				--parent->_bf;
			}

			if (parent->_bf == -1 || parent->_bf == 1)
			{
				//向上继续更新
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 0)
			{
				break;
			}
			else
			{
				//调整
				if (parent->_bf == -2 && cur->_bf == -1)
				{
					RotateRight(parent);
				}
				else if (parent->_bf == 2 && cur->_bf == 1)
				{
					RotateLeft(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == 1)
				{
					int bf = cur->_right->_bf;
					RotateLeft(cur);
					RotateRight(parent);
					if (bf == -1)
					{
						parent->_bf = 1;
					}
					else if (bf == 1)
						cur->_bf = -1;
				}
				else if (parent->_bf == 2 && cur->_bf == -1)
				{
					int flag = cur->_left->_bf;
					RotateRight(cur);
					RotateLeft(parent);
					if (flag == -1)
					{
						cur->_bf = 1;
					}
					else if (flag == 1)
						parent->_bf = -1;
				}
				break;
			}
		}
		return true;
	}

	void RotateRight(pNode parent)
	{
		//右旋, 拿到左子树和左子树的右孩子
		pNode subL = parent->_left;
		pNode subLR = subL->_right;

		//改变链接关系
		subL->_right = parent;
		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;
		if (parent == _root)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			if (parent->_parent->_left == parent)
			{
				parent->_parent->_left = subL;
			}
			else
				parent->_parent->_right = subL;
			subL->_parent = parent->_parent;
		}
		parent->_parent = subL;

		//更新平衡因子
		subL->_bf = parent->_bf = 0;
	}

	void RotateLeft(pNode parent)
	{
		//左旋
		pNode subR = parent->_right;
		pNode subRL = subR->_left;

		//改变链接关系
		subR->_left = parent;
		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;
		if (parent == _root)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else
		{
			pNode pparent = parent->_parent;
			if (pparent->_left == parent)
				pparent->_left = subR;
			else
				pparent->_right = subR;
			subR->_parent = pparent;
		}
		parent->_parent = subR;
		//更新平衡因子
		subR->_bf = parent->_bf = 0;
	}

	void Inorder()
	{
		_Inorder(_root);
		cout << endl;
	}
	void _Inorder(pNode root)
	{
		if (root)
		{
			_Inorder(root->_left);
			cout << root->_data << " ";
			_Inorder(root->_right);
		}
	}

	int _TreeHight(pNode root)
	{
		//空树为0
		if (root == nullptr)
			return 0;
		//计算左右子树
		int LeftHight = _TreeHight(root->_left);
		int RightHight = _TreeHight(root->_right);
		//返回较高子树的高度 + 1
		return LeftHight > RightHight ? (LeftHight + 1) : (RightHight + 1);
	}

	bool _IsBalance(pNode root)
	{
		//空树是平衡树
		if (root == nullptr)
			return true;
		//计算左右的高度差, 判断高度差是否满足, 不等于或者超出范围
		int LeftH = _TreeHight(root->_left);
		int RightH = _TreeHight(root->_right);
		int diff = RightH - LeftH;

		if (diff != root->_bf || (diff < -1 || diff > 1))
			return false;

		//返回左边和右边都平衡
		return _IsBalance(root->_left) && _IsBalance(root->_right);
	}
	bool IsBalance()
	{
		return _IsBalance(_root);
	}

private:
	pNode _root = nullptr;
};

void test()
{
	AVLTree<int> avl;
	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
		avl.Insert(a[i]);

	avl.Inorder();
	cout << avl.IsBalance() << endl;
}

int main()
{
	test();
	system("pause");
	return 0;	
}
