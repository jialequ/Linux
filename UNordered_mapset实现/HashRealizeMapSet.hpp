#include <iostream>
#include <vector>
using namespace std;

template <class V>
struct HashNode
{
	HashNode(const V& data = V())
		:_data(data)
		, _next(nullptr)
	{}

	V _data;
	HashNode<V>* _next;
};

template <class K, class V, class KeyOfValue>
struct _HashIterator;

template <class K, class V,class KeyOfValue>
class HashTable
{
public:
	typedef HashNode<V> Node;
	typedef Node* pNode;

	typedef _HashIterator<K, V, KeyOfValue> iterator;

	template <class K, class V, class KeyOfValue>
	friend struct _HashIterator;

	HashTable(const int n = 10)
	{
		_ht.resize(n);
		_size = 0;
	}

	iterator begin()
	{
		//�ҵ�����ķǿ�ͷ�ڵ�
		for (size_t i = 0; i < _ht.size(); i++)
		{
			if (_ht[i])
				return iterator(_ht[i], this);
		}
		return iterator(nullptr, this);
	}

	iterator end()
	{
		return iterator(nullptr, this);
	}

	bool Insert(const V& data)
	{
		//����λ��
		KeyOfValue kov;
		int index = kov(data) % _ht.size();
		//����������
		pNode cur = _ht[index];
		while (cur)
		{
			if (kov(cur->_data) == kov(data))
			{
				return false;
			}
			cur = cur->_next;
		}

		//���� : ͷ��
		cur = new Node(data);
		cur->_next = _ht[index];
		_ht[index] = cur;
		++_size;
		return true;
	}

	void CheckCapacity()
	{
		if (_ht.size() == _size)
		{
			//��������
			size_t newS = _ht.size() == 0 ? 10 : 2 * _ht.size();
			vector<pNode> newH;
			newH.resize(newS);
			KeyOfValue kov;
			for (size_t i = 0; i < _ht.size(); i++)
			{
				pNode cur = _ht[i];
				//����������
				while (cur)
				{
					pNode next = cur->_next;
					//���¼���λ��
					int index = kov(_ht[i]._data) % newH.size();
					//ͷ��
					cur->_next = newH[index];
					newH[index] = cur;
					cur = next;
				}
				_ht[i] = nullptr;
			}
			swap(_ht, newH);
		}
	}

	pNode Find(const K& key)
	{
		int index = key % _ht.size();
		pNode cur = _ht[index];
		KeyOfValue kov;
		while (cur)
		{
			if (kov(cur->_data) == key)
				return cur;
			cur = cur->_next;
		}
		return nullptr;
	}

	bool Erase(const K& key)
	{
		int index = key % _ht.size();
		pNode cur = _ht[index];
		pNode pre = nullptr;
		KeyOfValue kov;
		while (cur)
		{
			if (kov(cur->_data) == key)
			{
				//ͷɾ
				if (pre == nullptr)
				{
					_ht[index] = cur->_next;
				}
				else
				{
					pre->_next = cur->_next;
				}

				delete cur;
				--_size;

				return true;
			}

			pre = cur;
			cur = cur->_next;
		}
		return false;
	}

	void print()
	{
		KeyOfValue kov;
		for (size_t i = 0; i < _ht.size(); i++)
		{
			pNode cur = _ht[i];
			while (cur)
			{
				cout << kov(cur->_data) << endl;
				cur = cur->_next;
			}
		}
		cout << endl;
	}

private:
	//ָ������
	vector<pNode> _ht;
	size_t _size;
};

template <class K,class V,class KeyOfValue>
struct _HashIterator
{
public:
	typedef HashNode<V>* pNode;
	typedef HashTable<K, V, KeyOfValue> HTable;
	typedef _HashIterator<K, V, KeyOfValue> Self;

	_HashIterator(pNode node,HTable* pht)
		:_node(node)
		, _pht(pht)
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
		//������++, ���ص���Ȼ�ǵ�����
		if (_node->_next)
			_node = _node->_next;
		else
		{
			KeyOfValue kov;
			//���¶�λindex, ����һ����ʼ����
			size_t index = kov(_node->_data) % _pht->_ht.size();
			++index;
			while (index < _pht->_ht.size())
			{
				if (_pht->_ht[index])
				{
					_node = _pht->_ht[index];
					break;
				}
				++index;
			}

			if (index == _pht->_ht.size())
			{
				_node = nullptr;
			}
		}
		return  *this;
	}

private:
	pNode _node;
	HTable* _pht;
};