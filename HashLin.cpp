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
//	//�����ϣ�ڵ�, ��ʼ״̬Ϊ��
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
//		//���캯��
//		_ht.resize(n);
//		//�Դ�����Hash�����resize
//		_size = 0;
//	}
//
//	bool Insert(const pair<K,V>& data)
//	{
//		//����֮ǰ��Ҫ����Ƿ���Ҫ����
//		CheckCapacity();
//		//��������
//		int index = data.first % _ht.size();
//		//�жϵ�ǰλ���Ƿ���Ԫ��, û��ֱ�Ӳ���
//		while (_ht[index]._state == EXIST)
//		{
//			//�µ�Ԫ�س���EXIST״̬���������Բ���
//			//�ҵ�һ��������Ԫ�ص�λ��
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
//		//����
//		_ht[index]._data = data;
//		_ht[index]._state = EXIST;
//		++_size;
//
//		return true;
//	}
//
//	void CheckCapacity()
//	{
//		//�ж��Ƿ���Ҫ����
//		if (_ht.size() == 0 || _size * 10 / _ht.size() >= 8)
//		{
//			//���� : 
//			//1. �����±�(��СΪ�ɱ������)
//			int newS = _ht.size() == 0 ? 10 : 2 * _ht.size();
//			HashTable<K, V> newH(newS);
//			//2. �ɱ�Ԫ�����²��뵽�±���
//			for (size_t i = 0; i < _ht.size(); i++)
//			{
//				if (_ht[i]._state == EXIST)
//				{
//					newH.Insert(_ht[i]._data);
//				}
//			}
//			//3. �ɱ��±���
//			swap(_ht, newH._ht);
//		}
//	}
//
//	Node* find(const K& key)
//	{
//		//��������
//		int index = key % _ht.size();
//		//�����ս���
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
//		//����
//		Node* pos = find(key);
//		//�ҵ��˸ı�״̬.--size()
//		if (pos)
//		{
//			//pos��ָ��, ->����
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