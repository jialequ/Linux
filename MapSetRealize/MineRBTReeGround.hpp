#include <iostream>
#include <time.h>
using namespace std;

enum Color
{
	Red,
	Black
};

template <class V>
struct RBTNode
{
	RBTNode(const V& data = V())
		: _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _data(data)
		, _color(Red)
	{}
	RBTNode<V>* _left;
	RBTNode<V>* _right;
	RBTNode<V>* _parent;
	V _data;
	Color _color;
};

template <class V>
class _RBTreeIterator
{
	//��װ������ڵ�
public:
	typedef RBTNode<V> Node;
	typedef Node* pNode;
	typedef _RBTreeIterator<V> Self;

	_RBTreeIterator(pNode node)
		:_node(node)
	{}

	V& operator*()
	{
		return _node->_data;
	}

	V* operator->()
	{
		return &_node->_data;
	}

	bool operator!=(const Self& it)
	{
		return _node != it._node;
	}

	bool operator==(const Self& it)
	{
		return _node == it._node;
	}

	Self& operator++()
	{
		//1. ���������� : ������������ڵ�
		//2. ������������ : ���ϻ���
		//	��ǰ�ڵ���parent�����/_node->_parent != parent, ֱ�ӵ���parent
		//	��ǰ�ڵ���parent���ұ�, ���ϵ���, ֱ��_node��Ϊparent���ұ�Ϊֹ
		if (_node->_right != nullptr)
		{
			_node = _node->_right;
			while (_node->_left)
			{
				_node = _node->_left;
			}
		}
		else
		{
			pNode parent = _node->_parent;
			while (parent->_right == _node)
			{
				_node = parent;
				parent = parent->_parent;
			}
			if (_node->_right != parent)
				_node = parent;
		}
		return *this;
	}

private:
	pNode _node;
};

//K,V : pair<K,V>
//KeyOfValue : ��ȡ��Ӧ���ݵ�Key
template <class K, class V, class KeyOfValue>
class RBTree
{
public:
	typedef RBTNode<V> Node;
	typedef Node* pNode;
	typedef _RBTreeIterator<V> iterator;

	RBTree(const V& data = V())
	{
		_header = new Node(data);
		_header->_left = _header;
		_header->_right = _header;
		_header->_parent = nullptr;
	}

	iterator begin()
	{
		return iterator(_header->_left);
	}

	iterator end()
	{
		return iterator(_header);
	}
	
	pair<iterator,bool> Insert(const V& data)
	{
		//�ж��Ƿ��ǿ���
		if (_header->_parent == nullptr)
		{
			//�������ڵ�
			pNode root = new Node(data);
			//���ڵ����ɫ�Ǻ�ɫ
			root->_color = Black;
			//����˫�����ӹ�ϵ,���ĸ���, ͷ������ָ��
			root->_parent = _header;
			_header->_parent = root;
			_header->_left = root;
			_header->_right = root;
			return make_pair(iterator(root),true);
		}

		//�������ʵ�λ��
		pNode cur = _header->_parent;
		pNode parent = nullptr;
		KeyOfValue kov;
		while (cur)
		{
			//���¸��ڵ�
			parent = cur;
			//�����ǰK����Ҫ�ҵ�K(��ֵ��), ����
			if (kov(cur->_data) > kov(data))
				cur = cur->_left;
			else if (kov(cur->_data) < kov(data))
				cur = cur->_right;
			else
				return make_pair(iterator(cur),false);
			//���, ����ʧ��
		}

		//����һ���µĽڵ�, ����˫������(ͨ��Kֵ�Ĺ�ϵ)
		cur = new Node(data);
		pNode newNode = cur;
		if (kov(parent->_data) > kov(data))
		{
			parent->_left = cur;
		}
		else
			parent->_right = cur;
		cur->_parent = parent;
		//���� : �޸���ɫ, ��ת
		while (cur != _header->_parent && cur->_parent->_color == Red)
		{
			pNode parent = cur->_parent;
			pNode gparent = parent->_parent;
			//0.�жϸ������游���ı�
			//1.������ڶ����Ǻ�ɫ 
			//  ֱ���޸���ɫ, ���ϸ���
			//2.���岻����/���ڶ����Ǻڵ�(��ת, ����֮�������ɫ,�������ϸ���)
			//  cur��parent����ͬ��, ˫��ת, parent����-->������(֮�󽻻�)������
			//  cur��parent��ͬ��, ����ת, ����->�ҵ���, ����->���� 
			if (gparent->_left == parent)
			{
				pNode uncle = gparent->_right;
				if (uncle && uncle->_color == Red)
				{
					//������ɫ
					parent->_color = uncle->_color = Black;
					gparent->_color = Red;
					//���ϸ���
					cur = gparent;
				}
				else
				{
					if (parent->_right == cur)
					{
						RotateLeft(parent);
						swap(cur, parent);
					}
					//����
					RotateRight(gparent);
					//������ɫʹ����������
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
		//���ڵ����ɫ����Ϊ��ɫ
		_header->_parent->_color = Black;

		//����֮������ܷ����仯
		_header->_left = leftMost();
		_header->_right = rightMost();

		return make_pair(iterator(newNode), true);
	}

	pNode leftMost()
	{
		//�Ӹ��ڵ㿪ʼ
		pNode cur = _header->_parent;
		//һֱ�������
		while (cur && cur->_left)
		{
			cur = cur->_left;
		}
		return cur;
	}

	pNode rightMost()
	{
		//�Ӹ��ڵ㿪ʼ
		pNode cur = _header->_parent;
		//һֱ���ұ���
		while (cur && cur->_right)
		{
			cur = cur->_right;
		}
		return cur;
	}

	void RotateLeft(pNode parent)
	{
		//����
		pNode subR = parent->_right;
		pNode subRL = subR->_left;

		//�ı����ӹ�ϵ
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
		//����, �õ������������������Һ���
		pNode subL = parent->_left;
		pNode subLR = subL->_right;

		//�ı����ӹ�ϵ
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
		//��Ϊ��
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

	//1. root ��
	//2. ��Ĳ�����
	//3. ����·���ڵ�������ͬ (ǰ�����ͳ������)	

	bool IsBRTree()
	{
		//����
		if (_header->_parent == nullptr)
		{
			return true;
		}
		//root��ɫ
		if (_header->_parent->_color == Red)
		{
			return false;
		}
		//ͳ��һ��·�Ϻ�ɫ�ڵ������
		int Blackcount = 0;
		pNode cur = _header->_parent;
		while (cur)
		{
			if (cur->_color == Black)
				++Blackcount;
			cur = cur->_left;
		}
		//����һ��ǰ������Ľ��
		return	_IsBRTree(_header->_parent, Blackcount, 0);
	}

	bool _IsBRTree(pNode root, int Blackcount, int Curcount)
	{
		//����(��ɫ�����Ƿ����)
		if (root == nullptr)
		{
			if (Blackcount != Curcount)
				return false;
			return true;
		}
		//�ۼӺڽڵ�
		if (root->_color == Black)
			++Curcount;
		//�ж��Ƿ��к�ɫ����
		if (root->_parent->_color == Red && root->_color == Red)
		{
			return false;
		}
		//���ҵݹ�
		return _IsBRTree(root->_left, Blackcount, Curcount)
			&& _IsBRTree(root->_right, Blackcount, Curcount);
	}
private:
	pNode _header;
};

