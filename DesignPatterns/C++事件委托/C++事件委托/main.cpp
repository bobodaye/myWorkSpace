#include <iostream>
#include <map>

typedef unsigned int uint;
typedef unsigned char uchar;
/////////////////////////////////////////////////////////////////////////////////

/// \class FuncCache

/// \brief 函数对象寄存器y

/////////////////////////////////////////////////////////////////////////////////

template <typename ReturnType>
class FuncCache
{
     static const int SIZE = 48;
     typedef ReturnType (*func_caller)(FuncCache*);

     /// \class MemberFuncAssist

     /// \brief 对象成员函数寄存器的辅助器

     class FuncCacheAssist
     {
     public:
         /// \brief 构造函数，初始化。
         FuncCacheAssist(FuncCache* pFunc)
         {
              m_Size = 0;
              m_pFunc = pFunc;

              // 读取用偏移必须归位
              m_pFunc->m_Cur = 0;
         }

         /// \brief 析构函数。
         ~FuncCacheAssist(void)
         {
              // 弹出以前压入的参数
              if (m_Size > 0)
                   m_pFunc->Pop(m_Size);
         }

         /// \brief 压入指定大小的数据。
         uint Push(const void* pData, uint size)
         {
              m_Size += size;
              return m_pFunc->Push(pData, size);
         }
         /// 压入参数的大小
         int                m_Size;

         /// 对象成员函数寄存器
         FuncCache*         m_pFunc;
     };

public:
     /// \brief 构造函数，初始化。
     FuncCache(func_caller func)
     {
         m_Size = 0;
         m_Cur = 0;
         m_Func = func;
     }

     /// \brief 压入指定大小的数据。
     uint Push(const void* pData, uint size)
     {
         size = (size <= SIZE - m_Size)? size : (SIZE - m_Size);
         memcpy(m_Buffer + m_Size, pData, size);
         m_Size += size;
         return size;
     }

     /// \brief 弹出指定大小的数据。
     uint Pop(uint size)
     {
         size = (size < m_Size)? size : m_Size;
         m_Size -= size;
         return size;
     }

     /// \brief 读取指定大小的数据，返回指针。
     void* Read(uint size)
     {
         m_Cur += size;
         return (m_Buffer + m_Cur - size);
     }

     /// \brief 执行一个参数的函数。
     ReturnType Execute(const void* pData)
     {
         // 用辅助结构控制
         FuncCacheAssist assist(this);

         // 压入参数
         assist.Push(&pData, sizeof(void*));

         // 执行函数
         return m_Func(this);
     }
protected:
     /// 对象，函数，参数指针的缓冲区
     uchar         m_Buffer[SIZE];

     /// 缓冲区大小
     uint          m_Size;

     /// 缓冲区读取用的偏移
     uint          m_Cur;

     /// 操作函数的指针
     func_caller   m_Func;
};

/////////////////////////////////////////////////////////////////////////////////

/// \class MFuncCall_1

/// \brief 一个参数的成员函数执行体

/////////////////////////////////////////////////////////////////////////////////

template <typename ReturnType, typename Caller, typename Func, typename ParamType>
class MFuncCall_1
{
public:
     /// \brief 执行一个参数的成员函数。
     static ReturnType MFuncCall(FuncCache<ReturnType>* pMFunc)
     {
         // 获得对象指针
         Caller* pCaller = *(Caller**)pMFunc->Read(sizeof(Caller*));

		 /*
			为什么使用*(Caller**)？而不是*(Caller*)
			1.为了获取调用对象的地址
			2.对象地址存储在数组中前4个字节，只有将其强转为“Caller**”二级指针，再通过“*”取其地址，大小刚好为sizeof(Caller*)共4个字节。
			3.如果使用“Caller*”强转，再通过“*”取值，那么所取的值的大小为sizeof(Caller)个字节，可能出错。
		 */

         // 获得成员函数指针a
         Func func = *(Func*)pMFunc->Read(sizeof(Func));

         // 获得参数的指针
         ParamType* pData = *(ParamType**)pMFunc->Read(sizeof(ParamType*));
		 
         // 执行成员函数
         return (pCaller->*func)(*pData);
     }
};

/////////////////////////////////////////////////////////////////////////////////

/// \class L_SignalRoot

/// \brief 类型检查严格的事件委托器基类

/////////////////////////////////////////////////////////////////////////////////

template <typename ReturnType>
class L_SignalRoot
{
public:
     /// \brief 指定事件名，卸载指定对象的事件委托器。
     template <typename Caller>
     void MFuncUnregister(Caller* pCaller)
     {
         func_map& func_list = m_MemberFuncMap;

         func_map::iterator it = func_list.find(pCaller);
		 
         if (it != func_list.end())
              func_list.erase(it);
     }

     /// \brief 清空所有事件委托器。
     void MFuncClear(void)
     {
         m_MemberFuncMap.clear();
     }
protected:
     typedef std::map< void*, FuncCache<ReturnType> > func_map;
     /// 事件名和绑定的事件委托器的列表
     func_map m_MemberFuncMap;
};

/////////////////////////////////////////////////////////////////////////////////

/// \class L_Signal_1

/// \brief 类型检查严格，一个参数的事件委托器

/////////////////////////////////////////////////////////////////////////////////

template <typename ReturnType, typename ParamType>
class L_Signal_1 : public L_SignalRoot<ReturnType>
{
public:
     /// \brief 指定事件名，注册对应的一个参数的事件委托器。
     template <typename Caller, typename Func>
     void MFuncRegister(Caller* pCaller, Func func)
     {
         // 指定专门处理一个参数的函数执行体
         FuncCache<ReturnType> mfunc(MFuncCall_1<ReturnType, Caller, Func, ParamType>::MFuncCall);

         // 压入对象和函数
         mfunc.Push(&pCaller, sizeof(Caller*));
         mfunc.Push(&func, sizeof(Func));

         // 添加到事件委托器列表
         m_MemberFuncMap.insert(std::make_pair(pCaller, mfunc));
     }

     /// \brief 指定事件名，调用其对应的一个参数的事件委托器。

     ReturnType MFuncCall(const ParamType& data)
     {
         // 清空返回值
         ReturnType result;
         memset(&result, 0, sizeof(result));

         // 对于所有委托器，调用注册的函数
         func_map::iterator it = m_MemberFuncMap.begin();

         while (it != m_MemberFuncMap.end())
         {
              result = it->second.Execute(&data);
              ++it;
         }
         return result;
     }
};

class EventCallerA
{
public:
     bool Do(int event_id)
     {
         printf("EventCallerA do event %d.\r\n", event_id);
         return true;
     }

};

class EventCallerB
{
public:
     bool Run(int event_id)
     {
         printf("EventCallerB run event %d.\r\n", event_id);
         return true;
     }
};

int main()
{
     // 申明返回值是bool类型，参数是int类型，单参数的事件器
     L_Signal_1<bool, int> signal;
     EventCallerA callerA;
     EventCallerB callerB;

	// 注册委托器并调用事件
     signal.MFuncRegister(&callerA, &EventCallerA::Do);
     signal.MFuncRegister(&callerB, &EventCallerB::Run);

	 // signal.MFuncUnregister(&callerA);
	 // signal.MFuncClear();

     signal.MFuncCall(1);

	 return 0;
}

int main2()
{
	std::pair<int, double> p1;
	p1 = std::make_pair(1, 2.5);
	std::cout << p1.first << " " << p1.second << std::endl;
	return 0;
}