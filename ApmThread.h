// ApmThread.h: interface for the CApmThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_APMTHREAD_H__8E1FA89C_6870_4D2A_B6A6_291677A40E58__INCLUDED_)
#define AFX_APMTHREAD_H__8E1FA89C_6870_4D2A_B6A6_291677A40E58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <PROCESS.H>
#include "ProjectCfg.h"
#include "BWUtil.h"

class CApmThread  
{
public:
	int Init();

	static CApmThread* getInst() {
		if (!g_inst)
		{
			g_inst = new CApmThread();
		}
		return g_inst;
	}
	static void releaseInst();
	
	virtual ~CApmThread();

	static unsigned int __stdcall ThreadFun(void* para);
	static void __stdcall DrawHook();
    static void __stdcall ActionHook(const byte* actiontype);
    static void __stdcall refscreen();
    
    UINT32 m_apmCounter[12];
    std::string m_apmCounterStr[12];
    UINT32 m_apmcalctime;

    DWORD m_GameStartTm;

    DWORD m_APM_UpdateTm;

    DWORD m_APM_LastAlertTm;
    BOOL m_APM_passminapm;
    DWORD m_APM_passminapm_tm;

	HANDLE m_hThread;
	BOOL m_bStop;
	static CApmThread* g_inst;
private:
    CApmThread();
};

#endif // !defined(AFX_APMTHREAD_H__8E1FA89C_6870_4D2A_B6A6_291677A40E58__INCLUDED_)
