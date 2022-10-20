// Cfg.cpp: implementation of the CCfg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "APMAlert.h"
#include "Cfg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const int CCfg::regbufsize = 256;

CCfg::CCfg(char* ini)
{
	if (ini)
		m_IniFile = ini;
}

CCfg::~CCfg()
{
	
}

int CCfg::RegReadInt(HKEY hkey,const char* subkey,const int defaultval)
{
    DWORD datatype;
    DWORD bufsize = CCfg::regbufsize;
	ZeroMemory(m_regbuf, bufsize);
	int ret = RegQueryValueEx(hkey, subkey, NULL, &datatype, (LPBYTE)m_regbuf, &bufsize);
    if (ret == ERROR_SUCCESS)
	{
		int* val = (int*)m_regbuf;
        return *val;
	}
    return defaultval;
}

std::string CCfg::RegReadString(HKEY hkey,const char* subkey,const char* defaultval)
{
    DWORD datatype;
    DWORD bufsize = CCfg::regbufsize;
	ZeroMemory(m_regbuf, bufsize);
	int ret = RegQueryValueEx(hkey, subkey, NULL, &datatype, (LPBYTE)m_regbuf, &bufsize);
    if (ret == ERROR_SUCCESS)
        return std::string(m_regbuf);
    return defaultval;
}


BOOL CCfg::RegWriteInt(HKEY hkey,const char* subkey, int tval)
{
	return RegSetValueEx(hkey, subkey, 0, REG_DWORD, (const byte*)&tval, sizeof(int)) == ERROR_SUCCESS;
}

BOOL CCfg::RegWriteString(HKEY hkey,const char* subkey, const char* val, int len)
{
	return RegSetValueEx(hkey, subkey, 0, REG_SZ,  (const byte*)val, len) == ERROR_SUCCESS;;
}

int CCfg::IniReadInt(const char* section,const char* subkey, int defaultval)
{
	return GetPrivateProfileInt(section,subkey, defaultval, m_IniFile.c_str());
}

std::string CCfg::IniReadString(const char *section,const char *subkey,const char *defaultval)
{
	DWORD bufsize = CCfg::regbufsize;
	ZeroMemory(m_regbuf, bufsize);
	GetPrivateProfileString(section, subkey, defaultval, m_regbuf, bufsize, m_IniFile.c_str());
	return std::string(m_regbuf);
}



