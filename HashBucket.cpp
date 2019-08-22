#include <iostream>
#include <vector>
using namespace std;

template <class K,class V>
struct HashNode
{
	HashNode(const pair<K, V>& data = pair<K,V>())
		:_data(data)
		, _next(nullptr)
	{}

	pair<K, V> _data;
	HashNode<K, V>* _next;
};

template <class K,class V>
class HashTable
{
public:
	typedef HashNode<K, V> Node;
	typedef Node* pNode;
	HashTable(const int n = 10)
	{
		_ht.resize(n);
		_size = 0;
	}

	bool Insert(const pair<K, V>& data)
	{
		//计算位置
		int index = data.first % _ht.size();
		//遍历单链表
		pNode cur = _ht[index];
		while (cur)
		{
			if (cur->_data.first == data.first)
			{
				return false;
			}
			cur = cur->_next;
		}

		//插入 : 头插
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
			//创建索引
			size_t newS = _ht.size() == 0 ? 10 : 2 * _ht.size();
			vector<pNode> newH;
			newH.resize(newS);
			for (size_t i = 0; i < _ht.size(); i++)
			{
				pNode cur = _ht[i];
				//遍历单链表
				while (cur)
				{
					pNode next = cur->_next;
					//重新计算位置
					int index = _ht[i]._data.first % newH.size();
					//头插
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
		while (cur)
		{
			if (cur->_data.first == key)
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

		while (cur)
		{
			if (cur->_data.first == key)
			{
				//头删
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
		for (size_t i = 0; i < _ht.size(); i++)
		{
			pNode cur = _ht[i];
			while(cur)
			{
				cout << cur->_data.first << endl;
				cur = cur->_next;
			}
		}
		cout << endl;
	}

private:
	//指针数组
	vector<pNode> _ht;
	size_t _size;
};

void test()
{
	HashTable<int, int>  ht;
	ht.Insert(make_pair(5, 5));
	ht.Insert(make_pair(1, 1));
	ht.Insert(make_pair(0, 0));
	ht.Insert(make_pair(10, 10));
	ht.Insert(make_pair(3, 3));
	ht.Insert(make_pair(30, 30));
	ht.Insert(make_pair(32, 32));
	ht.Insert(make_pair(8, 8));
	ht.Insert(make_pair(110, 110));
	ht.Insert(make_pair(23, 23));
	ht.print();

	cout << ht.Find(10)->_data.first << endl;
	cout << endl;

	ht.Erase(10);
	ht.print();



}

int main()
{
	test();
	system("pause");
	return 0;
}
