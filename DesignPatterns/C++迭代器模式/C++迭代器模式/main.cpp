#include <iostream>
#include <string>
#include <vector>
using namespace std;


template<class T>
class Iterator
{
public:
	virtual ~Iterator() {}
    virtual bool hasNext() = 0;
    virtual T next() = 0;
};

template<class T>
class Menu
{
public:
    virtual Iterator<T>* createIterator() = 0;
};

template<class T>
class CAggregateAIter : public Iterator<T>
{
public:
    CAggregateAIter(vector<T>& vData);
	~CAggregateAIter() { cout << "~CAggregateAIter() calling\n"; }
    bool hasNext();
    T next();
private:
    vector<T>& m_vData;
    int m_iPosition;
};

template<class T>
class CAggregateA : public Menu<T>
{
public:
    CAggregateA();
	void push_back(const T& data);
    Iterator<T>* createIterator();
private:
    vector<T> m_vData;
	//static const int count = 5;
};

template<class T>
CAggregateAIter<T>::CAggregateAIter(vector<T>& vData) : m_vData(vData)	//迭代器只引用数据，不保留数据的副本
{
    m_iPosition = 0;
}

template<class T>
bool CAggregateAIter<T>::hasNext()
{
    if (m_iPosition < m_vData.size())
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<class T>
T CAggregateAIter<T>::next()
{
    T iData = m_vData.at(m_iPosition);
    ++m_iPosition;
    return iData;
}

template<class T>
CAggregateA<T>::CAggregateA()
{
    /*for (int i = 0; i < count; ++i)
    {
        m_vData.push_back(i*(i+1));
    }*/
}

template<class T>
Iterator<T>* CAggregateA<T>::createIterator()
{
    return new CAggregateAIter<T>(m_vData);
}

template<class T>
void CAggregateA<T>::push_back(const T& data)
{
	m_vData.push_back(data);
}

template<class T>
void printAggr(Iterator<T>* piter)
{
    while(piter->hasNext())
    {
		cout << piter->next() << endl;
    }
}

int main()
{
	//Iterator<int>* iter = (new CAggregateA<int>())->createIterator();
	CAggregateA<int> m_aggrA;
	m_aggrA.push_back(10);
	m_aggrA.push_back(20);
	Iterator<int>* iter1 = m_aggrA.createIterator();
	printAggr(iter1);
	delete iter1;

	CAggregateA<string> m_aggrB;
	m_aggrB.push_back(string("lb"));
	m_aggrB.push_back(string("wzb"));
	Iterator<string>* iter2 = m_aggrB.createIterator();
	printAggr(iter2);
	delete iter2;

    return 0; 
}