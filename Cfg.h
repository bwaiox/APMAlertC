// Cfg.h: interface for the CCfg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CFG_H__DCDB4CF1_ACB1_4DE2_9E36_7C0EF788B39F__INCLUDED_)
#define AFX_CFG_H__DCDB4CF1_ACB1_4DE2_9E36_7C0EF788B39F__INCLUDED_



#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

class CCfg
{
public:
	CCfg(char* ini = NULL);
	virtual ~CCfg();

protected:
    int RegReadInt(HKEY hkey,const char* subkey, int defaultval);
    std::string RegReadString(HKEY hkey,const char* subkey,const char* defaultval);

	BOOL RegWriteInt(HKEY hkey,const char* subkey, int tval);
	BOOL RegWriteString(HKEY hkey,const char* subkey,const char* val, int len);

	int IniReadInt(const char* section,const char* subkey, int defaultval);
	std::string IniReadString(const char *section,const char *subkey,const char *defaultval);
private:

    static const int regbufsize;// = 256;
    char m_regbuf[256];

	std::string m_IniFile;




};

#endif // !defined(AFX_CFG_H__DCDB4CF1_ACB1_4DE2_9E36_7C0EF788B39F__INCLUDED_)
