#include <iostream>
#include <time.h>
using namespace std;

enum Color
{
	Red,
	Black
};

template <class K,class V>
struct RBTNode
{
	RBTNode(const pair<K,V>& data = pair<K,V>())
		: _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _data(data)
		, _color(Red)
	{}
	RBTNode<K,V>* _left; 
	RBTNode<K,V>* _right; 
	RBTNode<K,V>* _parent; 
	pair<K,V> _data; 
	Color _color;
};

template <class K,class V>
class RBTRee
{
public:
	typedef RBTNode<K,V> Node;
	typedef Node* pNode;
	RBTRee(const pair<K,V>& data = pair<K,V>())
	{
		_header = new Node(data);
		_header->_left = _header;
		_header->_right = _header;
		_header->_parent = nullptr;
	}

	bool Insert(const pair<K, V>& data)
	{
		//判断是否是空树
		if (_header->_parent == nullptr)
		{
			//创建根节点
			pNode root = new Node(data);
			//根节点的颜色是黑色
			root->_color = Black;
			//更新双向链接关系,根的父亲, 头的三个指向
			root->_parent = _header;
			_header->_parent = root;
			_header->_left = root;
			_header->_right = root;
			return true;
		}

		//搜索合适的位置
		pNode cur = _header->_parent;
		pNode parent = nullptr;
		while (cur)
		{
			//更新父节点
			parent = cur;
			//如果当前K大于要找的K(键值对), 向左
			if (cur->_data.first > data.first)
				cur = cur->_left;
			else if (cur->_data.first < data.first)
				cur = cur->_right;
			else
				return false;
			//相等, 插入失败
		}

		//创建一个新的节点, 进行双向链接(通过K值的关系)
		cur = new Node(data);
		if (parent->_data.first > data.first)
		{
			parent->_left = cur;
		}
		else
			parent->_right = cur;
		cur->_parent = parent;
		//调整 : 修改颜色, 旋转
		while (cur != _header->_parent && cur->_parent->_color == Red)
		{
			pNode parent = cur->_parent;
			pNode gparent = parent->_parent;
			//0.判断父亲在祖父的哪边
			//1.叔叔存在而且是红色 
			//  直接修改颜色, 向上更新
			//2.叔叔不存在/存在而且是黑的(旋转, 结束之后调整颜色,不在向上更新)
			//  cur与parent不是同向, 双旋转, parent在左-->先左旋(之后交换)再右旋
			//  cur与parent是同向, 单旋转, 左左->右单旋, 右右->左单旋 
			if (gparent->_left == parent)
			{
				pNode uncle = gparent->_right;
				if (uncle && uncle->_color == Red)
				{
					//调整颜色
					parent->_color = uncle->_color = Black;
					gparent->_color = Red;
					//向上更新
					cur = gparent;
				}
				else
				{
					if (parent->_right == cur)
					{
						RotateLeft(parent);
						swap(cur, parent);
					}
					//右旋
					RotateRight(gparent);
					//调整颜色使得满足条件
					parent->_color = Black;
					gparent->_color = Red;

					break;
				}

			}
			else
			{
				pNode uncle = gparent->_left;
				if (uncle && uncle->_color == Red)
				{
					parent->_color = uncle->_color = Black;
					gparent->_color = Red;

					cur = gparent;
				}
				else
				{
					if (parent->_left == cur)
					{
						RotateRight(parent);
						swap(cur, parent);
					}

					RotateLeft(gparent);
					parent->_color = Black;
					gparent->_color = Red;

					break;
				}
			}

		}
		//根节点的颜色必须为黑色
		_header->_parent->_color = Black;

		//调整之后根可能发生变化
		_header->_left = leftMost();
		_header->_right = rightMost();
		
		return true;
	}

	pNode leftMost()
	{
		//从根节点开始
		pNode cur = _header->_parent;
		//一直向左边走
		while (cur && cur->_left)
		{
			cur = cur->_left;
		}
		return cur;
	}

	pNode rightMost()
	{
		//从根节点开始
		pNode cur = _header->_parent;
		//一直向右边走
		while (cur && cur->_right)
		{
			cur = cur->_right;
		}
		return cur;
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
		if (parent == _header->_parent)
		{
			_header->_parent = subR;
			subR->_parent = _header;
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
		if (parent == _header->_parent)
		{
			_header->_parent = subL;
			subL->_parent = _header;
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

	}

	void _Inorder(pNode root)
	{
		//不为空
		if (root)
		{
			_Inorder(root->_left);
			cout << root->_data.first << " ";
			_Inorder(root->_right);
		}
	}
	
	void Inorder()
	{
		_Inorder(_header->_parent);
		cout << endl;
	}

	//1. root 黑
	//2. 红的不连续
	//3. 任意路径黑的数量相同 (前序遍历统计数量)	

	bool IsBRTree()
	{
		//空树
		if (_header->_parent == nullptr)
		{
			return true;
		}
		//root颜色
		if (_header->_parent->_color == Red)
		{
			return false;
		}
		//统计一条路上黑色节点的数量
		int Blackcount = 0;
		pNode cur = _header->_parent;
		while (cur)
		{
			if (cur->_color == Black)
				++Blackcount;
			cur = cur->_left;
		}
		//返回一个前序遍历的结果
		return	_IsBRTree(_header->_parent, Blackcount, 0);
	}

	bool _IsBRTree(pNode root,int Blackcount,int Curcount)
	{
		//空树(灰色数量是否相等)
		if (root == nullptr)
		{
			if (Blackcount != Curcount)
				return false;
			return true;
		}
		//累加黑节点
		if (root->_color == Black)
			++Curcount;
		//判断是否有红色连续
		if (root->_parent->_color == Red && root->_color == Red)
		{
			return false;
		}
		//左右递归
		return _IsBRTree(root->_left, Blackcount, Curcount)
			&& _IsBRTree(root->_right, Blackcount, Curcount);
	}
private:
	pNode _header;
};

void testRBTree()
{
	RBTRee<int, int> rbt;
	//rbt.Insert(make_pair(1, 1));
	//rbt.Insert(make_pair(8, 1));
	//rbt.Insert(make_pair(10, 1));
	//rbt.Insert(make_pair(5, 1));
	//rbt.Insert(make_pair(6, 1));
	//rbt.Insert(make_pair(7, 1));
	//rbt.Insert(make_pair(15, 1));
	//rbt.Insert(make_pair(16, 1));
	//rbt.Insert(make_pair(2, 1));
	//rbt.Insert(make_pair(9, 1));
	int n;
	cin >> n;
	srand(time(nullptr));
	for (int i = 0; i < n; i++)
	{
		int cur = rand();
		cout << cur << " ";
		rbt.Insert(make_pair(i, cur));
	}
	//rbt.Inorder();
	cout << endl;

	cout << rbt.IsBRTree() << endl;
}
int main()
{
	testRBTree();
	system("pause");
	return 0;	
}
