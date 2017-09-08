#ifndef DICT_H
#define DICT_H
#include <string>
#include <cstring>
#include <iostream>
#include "sigil.h"
#include "log.h"

using namespace std;

template <typename K>
unsigned int hashFunction(const K &key)
{
	std::hash<std::string> h;
	unsigned int n = h(key);
	return n;
}

template <typename K, typename V>
class DictEntry
{
  public:
	K m_nKey;
	V m_nValue;
	DictEntry *m_pNext;

  public:
	DictEntry() : m_pNext(nullptr)
	{
		LOG(Info) << "class DictEntry construct" << std::endl;
	}
	~DictEntry()
	{
		m_pNext = nullptr;
		LOG(Info) << "class DictEntry destory" << std::endl;
	}
};

template <typename K, typename V>
class DictTable
{
  public:
	DictEntry<K, V> **m_pTable;
	size_t m_nSize;
	size_t m_nSizeMask;
	size_t m_nUsed;

	DictTable(size_t size = 2);
	bool insertPair(const K &, const V &);
	V findPair(const K &);
	bool deletePair(const K &);

	V operator[](const K &);
	~DictTable();

  private:
	unsigned int m_fGetIndex(const K &);
	DictEntry<K, V> *m_fGetEntry(const K &);
	DictEntry<K, V> *m_fFindEntry(const K &);
};

template <typename K>
class DictFunctor
{
	unsigned int m_fHashFunction(const K &);
	//dup,compare
};

template <typename K, typename V>
class Dict
{
  private:
	std::string m_nDictName;
	DictFunctor<K> *m_pFunctor;
	DictTable<K, V> *m_pTables[2];
	int m_nReHash;

  public:
	Dict(const std::string &name) : m_nDictName(name),
									m_pFunctor(nullptr),
									m_nReHash(0)
	{
		m_pTables[0] = new DictTable<K, V>;
		m_pTables[1] = new DictTable<K, V>;
		std::cout << "class Dict construct\n";
	};

	bool dictSet(K key, V value)
	{
		LOG(Info) << std::endl;
		if (!m_nReHash)
		{
			return m_pTables[0]->insertPair(key, value);
		}
		else
		{
			return m_pTables[1]->insertPair(key, value);
		}
	}
	V dictGet(K key)
	{
		if (!m_nReHash)
		{
			return m_pTables[0]->findPair(key);
		}
		else
		{
			return m_pTables[1]->findPair(key);
		}
	}
	int dictLen()
	{
		if (!m_nReHash)
			return m_pTables[0]->m_nUsed;
		else
			return m_pTables[0]->m_nUsed + m_pTables[1]->m_nUsed;
	}

	~Dict()
	{
		std::cout << "class Dict destory\n";
	}
};

//regit

bool hsetCommand(std::deque<std::string> &args);
bool hmsetCommand(std::deque<std::string> &args);
bool hgetCommand(std::deque<std::string> &args);
bool hlenCommand(std::deque<std::string> &args);
bool hclearCommand(std::deque<std::string> &args);
// RegisterCommand("hset",hsetCommand);

//........api.............//

template <typename K, typename V>
DictTable<K, V>::DictTable(size_t size)
{
	m_nSize = size;
	m_nSizeMask = size - 1;
	m_nUsed = 0;
	m_pTable = new DictEntry<K, V> *[size];
	for (int i = 0; i < size; i++)
		m_pTable[i] = nullptr;
}

template <typename K, typename V>
unsigned int DictTable<K, V>::m_fGetIndex(const K &k)
{
	LOG(Info) << std::endl;
	LOG(Info) << k << std::endl;
	unsigned int hash = hashFunction(k);
	unsigned int index = hash % m_nSize;
	return index;
}

template <typename K, typename V>
DictEntry<K, V> *DictTable<K, V>::m_fFindEntry(const K &k)
{
	LOG(Info) << std::endl;
	//if exists return a pointer,else return nullptr;
	unsigned int index = m_fGetIndex(k);
	if (m_pTable[index] == nullptr)
		return nullptr;

	DictEntry<K, V> *cur = m_pTable[index];
	while (cur != nullptr)
	{
		if (cur->m_nKey == k)
			return cur;
		else
		{
			cur = cur->m_pNext;
		}
	}
	return nullptr;
}

template <typename K, typename V>
DictEntry<K, V> *DictTable<K, V>::m_fGetEntry(const K &k)
{
	LOG(Info) << std::endl;

	DictEntry<K, V> *find = m_fFindEntry(k);
	if (find == nullptr)
	{
		unsigned int index = m_fGetIndex(k);
		find = new DictEntry<K, V>();
		if (find == nullptr)
		{
			LOG(Info) << "can't new DictEntry\n";
			return nullptr;
		}
		find->m_nKey = k;
		find->m_pNext = m_pTable[index];
		m_pTable[index] = find;
		m_nUsed++;
	}
	return find;
}

template <typename K, typename V>
bool DictTable<K, V>::insertPair(const K &k, const V &v)
{
	LOG(Info) << std::endl;

	DictEntry<K, V> *get = m_fGetEntry(k);
	if (get != nullptr)
		get->m_nValue = v;

	return true;
}

template <typename K, typename V>
V DictTable<K, V>::findPair(const K &k)
{
	DictEntry<K, V> *find = m_fFindEntry(k);
	if (find == nullptr)
	{
		V tmp;
		return tmp;
	}
	else if (find->m_nKey == k)
		return find->m_nValue;
}

template <typename K, typename V>
V DictTable<K, V>::operator[](const K &k)
{
	return findPair(k);
}
template <typename K, typename V>
bool DictTable<K, V>::deletePair(const K &k)
{
	//delete
}

template <typename K, typename V>
DictTable<K, V>::~DictTable()
{
	int tmp = 0;
	for (int i = 0; i < m_nSize; i++)
	{
		if (m_pTable[i])
		{
			DictEntry<K, V> *cur = m_pTable[i], *pre = cur;
			while (pre)
			{
				cur = cur->m_pNext;
				tmp++;
				delete pre;
				pre = cur;
			}
		}

		m_pTable[i] = nullptr;
	}
	std::cout << "dalete " << tmp << " entry\n";
	delete m_pTable;
	m_pTable = nullptr;
	m_nSize = 0;
	m_nSizeMask = 0;
	m_nUsed = 0;
}

#endif
