#pragma once
#include<algorithm>
#include<vector>

//slot 基类
template<typename paramType>
class slotBase
{
public:
	virtual void exec(paramType param) = 0; //纯虚函数
};

template<typename classType,typename paramType>
class slotMap : public slotBase<paramType>
{
public:
	slotMap(classType* pObj, void (classType::* func)(paramType))
	{
		m_pObj = pObj;
		m_func = func;
	}
	void exec(paramType param)
	{
		(m_pObj->*m_func)(param);
	}

private:
	classType* m_pObj;
	void (classType::*m_func)(paramType);
};

template<typename paramType>
class Slots
{
public:
	template<typename classType>
	Slots(classType* pObj, void (classType::* func)(paramType))
	{
		m_pSlotBase = new slotMap<classType, paramType>(pObj, func);
	}
	~Slots()
	{
		delete m_pSlotBase;
	}
	void exec(paramType param)
	{
		m_pSlotBase->exec(param);
	}

private:
	slotBase<paramType> *m_pSlotBase;
};


//信号
template<typename paramType>
class Signal
{
public:
	template<typename classType>
	void bind(classType* pObj, void (classType::* func)(paramType))
	{
		m_pSlots.push_back(new Slots<paramType>(pObj, func));
	}
	~Signal()
	{
		for (int i = 0; i < m_pSlots.size(); ++i)
		{
			delete m_pSlots[i];
		}
	}
	void operator()(paramType param)
	{
		for (int i = 0; i < m_pSlots.size(); ++i)
		{
			m_pSlots[i]->exec(param);
		}
	}

private:
	std::vector<Slots<paramType>*> m_pSlots;
};

#define connect(sender, signal, receiver, method) (sender)->signal.bind(receiver, method)
#define emit  

