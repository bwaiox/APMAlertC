// Logger.cpp: implementation of the CLogger class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Logger.h"
#include "BWUtil.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CLogger* CLogger::m_inst = NULL;


CLogger::CLogger()
{
    if (1)
    {
        m_file = CreateFile("apmalertlog.txt",GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
        if (m_file == INVALID_HANDLE_VALUE)
		    m_file = CreateFile("apmalertlog.txt",GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    }
}

CLogger::~CLogger()
{
	if (m_file != NULL)
		CloseHandle(m_file);
}

CLogger* CLogger::getinstance()
{
	if (m_inst == NULL)
		m_inst = new CLogger();
	return m_inst;
}

void CLogger::log1(std::string msg)
{
    if (m_file == INVALID_HANDLE_VALUE)
        return;
	DWORD wed = 0;
	msg = msg + "\n";
	DWORD len = strlen(msg.c_str());
	WriteFile(m_file, msg.c_str(),  len, &wed, NULL);	
}

void CLogger::log(const char* fmt, ...)
{
    if (m_file == INVALID_HANDLE_VALUE)
        return;
    char buf[1024];
    va_list ap;
    va_start(ap, fmt);
    vsprintf(buf, fmt, ap);
    va_end(ap);
    log1(buf);
    //printf()
}

void CLogger::screenlog(const char* fmt, ...)
{
    char buf[1024];
    va_list ap;
    va_start(ap, fmt);
    vsprintf(buf, fmt, ap);
    va_end(ap);
    BWDrawText(20, 20, buf);
}
