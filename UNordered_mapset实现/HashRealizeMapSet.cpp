#include "HashRealizeMapSet.hpp"

template <class K, class V>
class UMap
{
	struct MapKeyOfValue
	{
		const K& operator()(const pair<K, V>& data)
		{
			return data.first;
		}
	};

public:
	typedef typename HashTable<K, pair<K, V>, MapKeyOfValue>::iterator iterator;

	iterator begin()
	{
		return _ht.begin();
	}

	iterator end()
	{
		return _ht.end();
	}

	bool Insert(const pair<K,V>& data)
	{
		return _ht.Insert(data);
	}

	V& operator[](const K& Key)
	{
		pair<iterator, bool> ret = _ht.Insert(make_pair(Key, V()));
		return ret.first->second;
	}

private:
	HashTable<K, pair<K, V>, MapKeyOfValue> _ht;

};

template <class K>
class USet
{
	struct SetKeyOfValue
	{
		const K& operator()(const K& data)
		{
			return data;
		}
	};
public:
	typedef typename HashTable<K, K, SetKeyOfValue>::iterator iterator;
	iterator begin()
	{
		return _ht.begin();
	}

	iterator end()
	{
		return _ht.end();
	}

	bool Insert(const K& data)
	{
		return _ht.Insert(data);
	}

private:
	HashTable<K, K, SetKeyOfValue> _ht;
};

void testU()
{
	UMap<int, int> umap;
	umap.Insert(make_pair(1, 1));
	umap.Insert(make_pair(5, 5));
	umap.Insert(make_pair(6, 6));
	umap.Insert(make_pair(9, 9));

	for (const auto& e : umap)
	{
		cout << e.first << "--->" << e.second << endl;
		//cout << e << endl;
	}

	cout << "Set:" << endl;
	USet<int> uset;
	uset.Insert(1);
	uset.Insert(5);
	uset.Insert(6);
	uset.Insert(9);
	for (auto& e : uset)
	{
		cout << e << endl;
	}
}

int main()
{
	testU();
	system("pause");
	return 0;
}
