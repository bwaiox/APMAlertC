// Logger.h: interface for the CLogger class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGGER_H__ABEF772A_35FE_4616_B4C6_34D0ED50C420__INCLUDED_)
#define AFX_LOGGER_H__ABEF772A_35FE_4616_B4C6_34D0ED50C420__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

class CLogger  
{
public:
	static CLogger* getinstance();
	static void releaseInstance()
	{
		if (m_inst)
		{
			delete m_inst;
			m_inst = NULL;
		}
	}
	virtual ~CLogger();

	void log1(std::string msg);
    void log(const char* fmt, ...);
    void screenlog(const char* fmt, ...);
	
private:
    CLogger();
	HANDLE m_file;

	static CLogger* m_inst;
};

#endif // !defined(AFX_LOGGER_H__ABEF772A_35FE_4616_B4C6_34D0ED50C420__INCLUDED_)
