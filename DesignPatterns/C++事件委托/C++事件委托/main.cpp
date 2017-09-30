#include <iostream>
#include <map>

typedef unsigned int uint;
typedef unsigned char uchar;
/////////////////////////////////////////////////////////////////////////////////

/// \class FuncCache

/// \brief ��������Ĵ���y

/////////////////////////////////////////////////////////////////////////////////

template <typename ReturnType>
class FuncCache
{
     static const int SIZE = 48;
     typedef ReturnType (*func_caller)(FuncCache*);

     /// \class MemberFuncAssist

     /// \brief �����Ա�����Ĵ����ĸ�����

     class FuncCacheAssist
     {
     public:
         /// \brief ���캯������ʼ����
         FuncCacheAssist(FuncCache* pFunc)
         {
              m_Size = 0;
              m_pFunc = pFunc;

              // ��ȡ��ƫ�Ʊ����λ
              m_pFunc->m_Cur = 0;
         }

         /// \brief ����������
         ~FuncCacheAssist(void)
         {
              // ������ǰѹ��Ĳ���
              if (m_Size > 0)
                   m_pFunc->Pop(m_Size);
         }

         /// \brief ѹ��ָ����С�����ݡ�
         uint Push(const void* pData, uint size)
         {
              m_Size += size;
              return m_pFunc->Push(pData, size);
         }
         /// ѹ������Ĵ�С
         int                m_Size;

         /// �����Ա�����Ĵ���
         FuncCache*         m_pFunc;
     };

public:
     /// \brief ���캯������ʼ����
     FuncCache(func_caller func)
     {
         m_Size = 0;
         m_Cur = 0;
         m_Func = func;
     }

     /// \brief ѹ��ָ����С�����ݡ�
     uint Push(const void* pData, uint size)
     {
         size = (size <= SIZE - m_Size)? size : (SIZE - m_Size);
         memcpy(m_Buffer + m_Size, pData, size);
         m_Size += size;
         return size;
     }

     /// \brief ����ָ����С�����ݡ�
     uint Pop(uint size)
     {
         size = (size < m_Size)? size : m_Size;
         m_Size -= size;
         return size;
     }

     /// \brief ��ȡָ����С�����ݣ�����ָ�롣
     void* Read(uint size)
     {
         m_Cur += size;
         return (m_Buffer + m_Cur - size);
     }

     /// \brief ִ��һ�������ĺ�����
     ReturnType Execute(const void* pData)
     {
         // �ø����ṹ����
         FuncCacheAssist assist(this);

         // ѹ�����
         assist.Push(&pData, sizeof(void*));

         // ִ�к���
         return m_Func(this);
     }
protected:
     /// ���󣬺���������ָ��Ļ�����
     uchar         m_Buffer[SIZE];

     /// ��������С
     uint          m_Size;

     /// ��������ȡ�õ�ƫ��
     uint          m_Cur;

     /// ����������ָ��
     func_caller   m_Func;
};

/////////////////////////////////////////////////////////////////////////////////

/// \class MFuncCall_1

/// \brief һ�������ĳ�Ա����ִ����

/////////////////////////////////////////////////////////////////////////////////

template <typename ReturnType, typename Caller, typename Func, typename ParamType>
class MFuncCall_1
{
public:
     /// \brief ִ��һ�������ĳ�Ա������
     static ReturnType MFuncCall(FuncCache<ReturnType>* pMFunc)
     {
         // ��ö���ָ��
         Caller* pCaller = *(Caller**)pMFunc->Read(sizeof(Caller*));

		 /*
			Ϊʲôʹ��*(Caller**)��������*(Caller*)
			1.Ϊ�˻�ȡ���ö���ĵ�ַ
			2.�����ַ�洢��������ǰ4���ֽڣ�ֻ�н���ǿתΪ��Caller**������ָ�룬��ͨ����*��ȡ���ַ����С�պ�Ϊsizeof(Caller*)��4���ֽڡ�
			3.���ʹ�á�Caller*��ǿת����ͨ����*��ȡֵ����ô��ȡ��ֵ�Ĵ�СΪsizeof(Caller)���ֽڣ����ܳ���
		 */

         // ��ó�Ա����ָ��a
         Func func = *(Func*)pMFunc->Read(sizeof(Func));

         // ��ò�����ָ��
         ParamType* pData = *(ParamType**)pMFunc->Read(sizeof(ParamType*));
		 
         // ִ�г�Ա����
         return (pCaller->*func)(*pData);
     }
};

/////////////////////////////////////////////////////////////////////////////////

/// \class L_SignalRoot

/// \brief ���ͼ���ϸ���¼�ί��������

/////////////////////////////////////////////////////////////////////////////////

template <typename ReturnType>
class L_SignalRoot
{
public:
     /// \brief ָ���¼�����ж��ָ��������¼�ί������
     template <typename Caller>
     void MFuncUnregister(Caller* pCaller)
     {
         func_map& func_list = m_MemberFuncMap;

         func_map::iterator it = func_list.find(pCaller);
		 
         if (it != func_list.end())
              func_list.erase(it);
     }

     /// \brief ��������¼�ί������
     void MFuncClear(void)
     {
         m_MemberFuncMap.clear();
     }
protected:
     typedef std::map< void*, FuncCache<ReturnType> > func_map;
     /// �¼����Ͱ󶨵��¼�ί�������б�
     func_map m_MemberFuncMap;
};

/////////////////////////////////////////////////////////////////////////////////

/// \class L_Signal_1

/// \brief ���ͼ���ϸ�һ���������¼�ί����

/////////////////////////////////////////////////////////////////////////////////

template <typename ReturnType, typename ParamType>
class L_Signal_1 : public L_SignalRoot<ReturnType>
{
public:
     /// \brief ָ���¼�����ע���Ӧ��һ���������¼�ί������
     template <typename Caller, typename Func>
     void MFuncRegister(Caller* pCaller, Func func)
     {
         // ָ��ר�Ŵ���һ�������ĺ���ִ����
         FuncCache<ReturnType> mfunc(MFuncCall_1<ReturnType, Caller, Func, ParamType>::MFuncCall);

         // ѹ�����ͺ���
         mfunc.Push(&pCaller, sizeof(Caller*));
         mfunc.Push(&func, sizeof(Func));

         // ��ӵ��¼�ί�����б�
         m_MemberFuncMap.insert(std::make_pair(pCaller, mfunc));
     }

     /// \brief ָ���¼������������Ӧ��һ���������¼�ί������

     ReturnType MFuncCall(const ParamType& data)
     {
         // ��շ���ֵ
         ReturnType result;
         memset(&result, 0, sizeof(result));

         // ��������ί����������ע��ĺ���
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
     // ��������ֵ��bool���ͣ�������int���ͣ����������¼���
     L_Signal_1<bool, int> signal;
     EventCallerA callerA;
     EventCallerB callerB;

	// ע��ί�����������¼�
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