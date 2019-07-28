#ifndef  __LAODY_LOG4C__
#define  __LAODY_LOG4C__

#include <stdarg.h>
#include <stdio.h>

// Author   : laody  -- Email -> laody@163.com
// CopyRight: ����laody��ȫ���������Ĵ��룬��ԭ�����������Ϣ

// ͨ����־�� 
// ʹ��ʾ��:
//     YLog4C log;
//     log.Fatal("ʾ��%d,��������������־.",1);
//     log.Error("ʾ��%d,����һ�������־.",2);
//     log.Warn ("ʾ��%d,���Ǹ澯��Ϣ��־.",3);
//     log.Info ("ʾ��%d,����������Ϣ��־.",4);
//     log.Buff ("ʾ��5,����������Ϣ��־.",18);
//     log.Debug("ʾ��%d,���ǵ�����Ϣ��־.",6);

typedef void (*LOG4C_FUNC)(const char*);

class YLog4C
{
public:
	YLog4C();
	~YLog4C();

	// ��־�ļ�����Ŀ¼+Ӧ�ó�������+��_"+����+".log"
	static void SetLogAppname(const char *lpszAppname); //����Ӧ�ó�������
	static void SetLogDir(const char *lpszDir); //����Ŀ¼
	static void SetLogFileMaxcnt(int n);//������־�ļ���������,��ÿ��һ���ļ�,������ÿ��������
	static void SetLog2Console(bool b); //�����Ƿ����������̨
	static void SetLog2File(bool b);    //�����Ƿ�������ļ�
	static void SetLog2Func(LOG4C_FUNC pFunc); //�����Ƿ����������
	static void SetLogLevel(int n);    //������־����
	static void SetLogDiary(bool b);   //�����Ƿ�ÿ��һ���ļ�
	static void SetLogMaxsize(int n);  //������־�ļ���󳤶� 100K<n<2G,Ĭ��100M
	static bool SetLog2MultiThread(bool b); //������־Ϊ���߳�ģʽ�����е�һ��д�ļ��������ļ�IO
  static bool SetLogThreadID(bool b); //�����Ƿ��ӡ�߳�ID,Ĭ�ϲ���ӡ
  static bool SetFlushRT(bool b);     //�����Ƿ�ʵʱˢ��

	void Info(const char *lpszFmt,...);
	void LogBuff(const char *lpszFile,int nLine,const char *lpBuf,int nSize);

	#define Buff(lpBuf,nSize) LogBuff(__FILE__,__LINE__,lpBuf,nSize);

public:
	enum
	{ //��־����
		LOG_FATAL   = 0,    //���ش���
		LOG_ERROR   = 1,    //����
		LOG_WARN    = 2,    //����
		LOG_INFO    = 3,    //��Ϣ
		LOG_DEBUG   = 4,    //����
		LOG_BUFF    = 5,    //����
	}LOG_LEVEL;

public: //������Ϊpublic����������Ϊ�������ö���ƣ������ⲿ����
#ifdef WIN32
	YLog4C& Log4C(const char *lpsz,int n) { m_lpszFile=lpsz;m_nLine=n;return *this;}

	#define Fatal Log4C(__FILE__,__LINE__).LogFatal
	#define Error Log4C(__FILE__,__LINE__).LogError
	#define Warn  Log4C(__FILE__,__LINE__).LogWarn
	#define Debug Log4C(__FILE__,__LINE__).LogDebug

	void LogFatal(const char *lpszFmt,...);
	void LogError(const char *lpszFmt,...);
	void LogWarn (const char *lpszFmt,...);
	void LogBuff (const char *lpBuf,int nSize);
	void LogDebug(const char *lpszFmt,...);
#else
	#define Fatal(fmt,arg...) Log(YLog4C::LOG_FATAL,__FILE__,__LINE__,fmt,##arg)
	#define Error(fmt,arg...) Log(YLog4C::LOG_ERROR,__FILE__,__LINE__,fmt,##arg)
	#define Warn(fmt,arg...)  Log(YLog4C::LOG_WARN ,__FILE__,__LINE__,fmt,##arg)
	#define Debug(fmt,arg...) Log(YLog4C::LOG_DEBUG,__FILE__,__LINE__,fmt,##arg)
#endif

public:
	void Log(int nLevel,const char *lpszFile,int nLine,const char *lpszFmt,...);
protected:	
	void LogV(int nLevel,const char *lpszFile,int nLine,const char *lpszFmt,va_list argList);
	
	bool OpenLog();
	void CloseLog();
	
	char m_strPrvFile[256];
	FILE *m_pFile;

private:
	const char *m_lpszFile;
	int   m_nLine;
};

#endif // __LAODY_LOG4C__

