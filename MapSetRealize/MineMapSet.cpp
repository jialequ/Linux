#include "MineRBTReeGround.hpp"

template <class K, class V>
class Map
{
	struct MapKeyOfValue
	{
		//ÖØÔØ()ÔËËã·û, ·Âº¯Êı
		const K& operator()(const pair<K, V>& data)
		{
			return data.first;
		}
	};
public:
	typedef typename RBTree<K, pair<K, V>, MapKeyOfValue>::iterator iterator;

	iterator begin()
	{
		return _rbt.begin();
	}

	iterator end()
	{
		return _rbt.end();
	}

	pair<iterator, bool> Insert(const pair<K, V>& data)
	{
		return _rbt.Insert(data);
	}

	V& operator[](const K& key)
	{
		pair<iterator, bool> ret = _rbt.Insert(make_pair(key, V()));
		return ret.first->second;
	}

private:
	RBTree<K, pair<K, V>, MapKeyOfValue> _rbt;
};


template <class K>
class Set
{
	struct SetKeyOfValue
	{
		const K& operator()(const K& data)
		{
			return data;
		}
	};

public:
	typedef typename RBTree<K, K, SetKeyOfValue>::iterator iterator;

	pair<iterator, bool> Insert(const K& data)
	{
		return  _rbt.Insert(data);
	}

	iterator begin()
	{
		return _rbt.begin();
	}

	iterator end()
	{
		return _rbt.end();
	}

private:
	RBTree<K, K, SetKeyOfValue> _rbt;
};


void test()
{
	Map<int, int> M;
	M.Insert(make_pair(10, 1));
	M.Insert(make_pair(3, 1));
	M.Insert(make_pair(9, 1));
	M.Insert(make_pair(2, 1));
	M.Insert(make_pair(1, 1));

	for (auto e : M)
	{
		cout << e.first << "--->" << e.second << endl;
	}

	M[1] = 100;
	M[50] = 50;

	for (auto e : M)
	{
		cout << e.first << "--->" << e.second << endl;
	}

	Set<int> s;
	s.Insert(1);
	s.Insert(3);
	s.Insert(9);
	s.Insert(2);
	s.Insert(1);
	for (auto e : s)
	{
		cout << e << "--->" << e << endl;
	}

}

int main()
{
	test();
	system("pause");
	return 0;
}