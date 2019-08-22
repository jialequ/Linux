//#include <iostream>
//#include <vector>
//using namespace std;
//
//enum State
//{
//	EMPTY,
//	EXIST,
//	DELETE
//};
//
//template <class K, class V>
//struct HashNode
//{
//	//定义哈希节点, 初始状态为空
//	pair<K, V> _data;
//	State _state = EMPTY;
//};
//
//template <class K, class V>
//class HashTable
//{
//public:
//	typedef HashNode<K, V> Node;
//	HashTable(const int n = 10)
//	{
//		//构造函数
//		_ht.resize(n);
//		//对创建的Hash表进行resize
//		_size = 0;
//	}
//
//	bool Insert(const pair<K,V>& data)
//	{
//		//插入之前先要检查是否需要扩容
//		CheckCapacity();
//		//创建索引
//		int index = data.first % _ht.size();
//		//判断当前位置是否有元素, 没有直接插入
//		while (_ht[index]._state == EXIST)
//		{
//			//新的元素除了EXIST状态其他都可以插入
//			//找到一个不存在元素的位置
//			if (_ht[index]._data.first == data.first)
//			{
//				return false;
//			}
//			++index;
//			if (index == _ht.size())
//			{
//				index = 0;
//			}
//		}
//
//		//插入
//		_ht[index]._data = data;
//		_ht[index]._state = EXIST;
//		++_size;
//
//		return true;
//	}
//
//	void CheckCapacity()
//	{
//		//判断是否需要扩容
//		if (_ht.size() == 0 || _size * 10 / _ht.size() >= 8)
//		{
//			//增容 : 
//			//1. 定义新表(大小为旧表的两倍)
//			int newS = _ht.size() == 0 ? 10 : 2 * _ht.size();
//			HashTable<K, V> newH(newS);
//			//2. 旧表元素重新插入到新表中
//			for (size_t i = 0; i < _ht.size(); i++)
//			{
//				if (_ht[i]._state == EXIST)
//				{
//					newH.Insert(_ht[i]._data);
//				}
//			}
//			//3. 旧表新表交换
//			swap(_ht, newH._ht);
//		}
//	}
//
//	Node* find(const K& key)
//	{
//		//创建索引
//		int index = key % _ht.size();
//		//遇到空结束
//		while (_ht[index]._state != EMPTY)
//		{
//			if (_ht[index]._state == EXIST)
//			{
//				if (_ht[index]._data.first == key)
//					return &_ht[index];
//			}
//
//			++index;
//			if (index == _ht.size())
//				index = 0;
//		}
//		return nullptr;
//	}
//
//	bool Erase(const K& key)
//	{
//		//查找
//		Node* pos = find(key);
//		//找到了改变状态.--size()
//		if (pos)
//		{
//			//pos是指针, ->访问
//			pos->_state = DELETE;
//			--_size;
//			return true;
//		}
//		return false;
//	}
//
//	void print()
//	{
//		for (size_t i = 0; i < _ht.size(); i++)
//		{
//			if (_ht[i]._state == EXIST)
//				cout << _ht[i]._data.first << endl;
//		}
//	}
//
//private:
//	vector<Node> _ht;
//	size_t _size;
//};
//
//
//void test()
//{
//	HashTable<int, int>  ht;
//	ht.Insert(make_pair(5, 5));
//	ht.Insert(make_pair(1, 1));
//	ht.Insert(make_pair(0, 0));
//	ht.Insert(make_pair(10, 10));
//	ht.Insert(make_pair(3, 3));
//	ht.Insert(make_pair(30, 30));
//	ht.Insert(make_pair(32, 32));
//	ht.Insert(make_pair(8, 8));
//	ht.Insert(make_pair(110, 110));
//	ht.Insert(make_pair(23, 23));
//
//	ht.print();
//	
//	ht.Erase(30);
//	ht.print();
//
//	HashTable<int, int>::Node* pos = ht.find(110);
//	pos = ht.find(130);
//}
//
//int main()
//{
//	test();
//	system("pause");
//	return 0;
//}