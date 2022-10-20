// ApmThread.cpp: implementation of the CApmThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "APMAlert.h"
#include "ApmThread.h"
#include "Logger.h"
#include "Math.h"
#include <mmsystem.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#include "BWUtil.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CApmThread* CApmThread::g_inst = NULL;

CApmThread::CApmThread()
{
    m_GameStartTm = 0;
    m_APM_UpdateTm = 0;
    m_hThread = INVALID_HANDLE_VALUE;
    m_bStop = FALSE;
    m_APM_LastAlertTm = 0;
    m_APM_passminapm = FALSE;
    m_APM_passminapm_tm = 0;
}

CApmThread::~CApmThread()
{
	if (m_hThread)
	{
		CloseHandle(m_hThread);
	}
}

void CApmThread::releaseInst()
{
	if (CApmThread::g_inst)
	{
		// stop thread
		if (CApmThread::g_inst->m_hThread)
		{
			CApmThread::g_inst->m_bStop = TRUE;
			WaitForSingleObject(CApmThread::g_inst->m_hThread, INFINITE);
		}
		delete CApmThread::g_inst;
		CApmThread::g_inst = NULL;
	}
}

void helpfun(byte actioncode, DWORD pnum1)
{
    if (actioncode == 55 || pnum1 >= 12)
        return;
    //CLogger::getinstance()->log("action hook %d %d", actioncode, pnum1);
    CApmThread::getInst()->m_apmCounter[pnum1] = CApmThread::getInst()->m_apmCounter[pnum1] + 1;
}

void __stdcall ActionHookTmp()
{
    byte* pactiontype;
    DWORD pnum1;//BWUtil::getInst()->GetSendActionPlayerID();
    byte actioncode;
    __asm{
        pushad
            mov edx, [SEND_ACTION_PNUM]
            mov edx,[edx]
            mov pnum1,edx
        mov pactiontype, esi
    }
    actioncode = *(byte*)pactiontype;
    helpfun(actioncode, pnum1);
    //CLogger::getinstance()->log("action hook %d %d", actioncode, pnum1);
    __asm{
        popad
        add esp, 8
        pop ebp
    }
}

void __stdcall CApmThread::refscreen()
{
    //CLogger::getinstance()->log("refscreen");

    BWUtil::getInst()->RefScreen();

}

int CApmThread::Init()
{
	m_hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadFun, this, CREATE_SUSPENDED, NULL);
	if (!m_hThread)
	{
        CLogger::getinstance()->log("CApmThread::Init,thread fail,%d", GetLastError());
		return -1;
	}
	// ×¢²á»­Í¼º¯Êý
	CProjectCfg* cfg = CProjectCfg::getInstance();
	cfg->LoadCfg();

	BWUtil* putil = BWUtil::getInst();
	putil->AddPatch2(HOOK_DRAW, (DWORD)&CApmThread::DrawHook, 0, 1);
    putil->AddPatch2(HOOK_REFRESH_SCREEN, (DWORD)&CApmThread::refscreen, 0, 1);
    putil->AddPatch2(HOOK_SEND_ACTION, (DWORD)&CApmThread::ActionHook, 0x53, 2);
    //putil->AddPatch2(HOOK_SEND_ACTION, (DWORD)ActionHookTmp, 0, 1);

	const unsigned short refreshMem1 = 0x9090;
	const unsigned short refreshMem2 = 0x04EB;
	//putil->AddPatchMem(PTCH_TEXTREFRESH1, (byte*)&refreshMem1, 2);
	//putil->AddPatchMem(PTCH_TEXTREFRESH2, (byte*)&refreshMem2, 2);
    
    for (int i = 0; i < 12; i++)
    {
        m_apmCounter[i] = 0;
        m_apmCounterStr[i] = "";
    }
    m_apmcalctime = 0;
	
	ResumeThread(m_hThread);
	return 0;
}

std::string GetElapsedTimeStr()
{
    DWORD nowtick = BWUtil::getInst()->GameTime() * 42;
    DWORD secs = nowtick / 1000;
    DWORD hours= secs / 3600;
    secs = secs - hours * 3600;
    DWORD mins = secs / 60;
    secs = secs - mins * 60;
    char buf[16];
    ZeroMemory(buf, 16);
    if (hours > 0)
        sprintf(buf, "%.2d:%.2d:%.2d", hours, mins, secs);
    else
        sprintf(buf, "%.2d:%.2d", mins, secs);
    return std::string(buf);
}

std::string GetLocalTimeStr()
{
    SYSTEMTIME tm;
    GetLocalTime(&tm);
    char buf[8];
    ZeroMemory(buf, 8);
    sprintf(buf, "%.2d:%.2d", tm.wHour, tm.wMinute);
    return std::string(buf);
}

char playercolortotextcolor(byte para)
{
    switch (para) {
    case 0x6F: return 0x08;
    case 0xA5: return 0x0E;
    case 0x9F: return 0x0F;
    case 0xA4: return 0x10;
    case 0x9C: return 0x11;
    case 0x13: return 0x15;
    case 0x54: return 0x16;
    case 0x87: return 0x17;
    case 0xB9: return 0x18;
    case 0x88: return 0x19;
    case 0x86: return 0x1B;
    case 0x33: return 0x1C;
    case 0x4D: return 0x1D;
    case 0x9A: return 0x1E;
    case 0x80: return 0x1F;
    default: return 0x02;
  }
}

void alertapm(CProjectCfg* cfg, DWORD tmms)
{
    if (!cfg->m_IsPlaySound)
        return;
    BWUtil* putil = BWUtil::getInst();
    if (putil->IsInObsMode() || putil->IsPaused())
        return;
    CApmThread* papmthread = CApmThread::getInst();
    if (tmms - papmthread->m_APM_LastAlertTm > 2000 && papmthread->m_APM_passminapm && tmms - papmthread->m_APM_passminapm_tm > 20000 )
    {
        sndPlaySound(cfg->m_SoundFile.c_str(), SND_ASYNC);
        papmthread->m_APM_LastAlertTm = tmms;
    }
}


const double APM_INTERVAL = 0.95;  // time after which actions are worth 1/e (in minutes)
void calcapm() 
{
    //CLogger::getinstance()->log("calcapm");
    CApmThread* papmthread = CApmThread::getInst();
    const UINT32 tmms = BWUtil::getInst()->GameTime() * 42;
    if (papmthread->m_apmcalctime != 0 && tmms <= (papmthread->m_apmcalctime + 500))
        return;
    //CLogger::getinstance()->log("calcapm 1 %d", tmms);

    INT32 tmdiff = tmms - papmthread->m_apmcalctime;
    for (int i = 0; i < 12; i++)//papmthread->m_apmCounter->size()
    {
        papmthread->m_apmCounter[i] *= exp(-tmdiff / (APM_INTERVAL * 60000));
    }
    //CLogger::getinstance()->screenlog("calcapm 2 %d", tmdiff);
    papmthread->m_apmcalctime = tmms;
    double gamedurationfactor = 1 - exp(-static_cast<INT32>(tmms-papmthread->m_GameStartTm) / (APM_INTERVAL * 60000));
    if (gamedurationfactor < 0.01)
        gamedurationfactor = 0.01;

    //CLogger::getinstance()->screenlog("calcapm 3 %f", gamedurationfactor);

    for (int j = 0; j < 12; j++)// papmthread->m_apmCounter->size()
    {
        std::string playername = BWUtil::getInst()->GetPlayerName(j);
        if (!playername.empty())
        {
            int apm = (int)(papmthread->m_apmCounter[j] / (APM_INTERVAL * gamedurationfactor) );
            if (j == BWUtil::getInst()->GetMyPlayerID() && !BWUtil::getInst()->IsInObsMode())
            {
                if (!papmthread->m_APM_passminapm)
                {
                    if (apm > CProjectCfg::getInstance()->m_MinAPM * 1.1 || tmms > 90000)
                    {
                        papmthread->m_APM_passminapm = TRUE;
                        papmthread->m_APM_passminapm_tm = tmms;
                    }
                }
                char buff[50];
                memset(buff, 0, 50);
                CProjectCfg* cfg = CProjectCfg::getInstance();
                if (apm < cfg->m_MinAPM)
                {
                    if (cfg->m_IsPlaySound)
                        alertapm(cfg, tmms);
                        
                    sprintf(buff, "\x04 APM: \x06 %d", apm); 
                }
                else
                {
                    sprintf(buff, "\x04 APM: \x07 %d", apm); 
                }
                papmthread->m_apmCounterStr[j] = std::string(buff);
                //CLogger::getinstance()->log("player apm str %d %s %d", j, papmthread->m_apmCounterStr[j].c_str(), papmthread->m_apmCounter[j]);
            }
            else
            {
                byte color = BWUtil::getInst()->GetPlayerColor(j);
                char buff[50];
                memset(buff, 0, 50);
                byte color2 = playercolortotextcolor(color);
                sprintf(buff, "\x04 %s: \x07 %d",  playername.c_str(), apm);
                
                papmthread->m_apmCounterStr[j] = std::string(buff);
                //CLogger::getinstance()->log("player apm str %d %s", j, papmthread->m_apmCounterStr[j].c_str());
            }
        }
        else
        {
            papmthread->m_apmCounterStr[j] = "";
        }
    }
    //CLogger::getinstance()->screenlog("calcapm 4");

}

const UINT32 LINE_SIZE = 12;
void DrawItFun()
{
    //CLogger::getinstance()->log("drawit");
    DWORD oldFormat = *(DWORD *)CUR_TEXT_FORMAT;
    BWFormatTextR(BWTF_NORMAL);
    //int textWidth = BWGetTextWidth(szTitle);
    //int centeredX = (width >> 1) - (textWidth >> 1) + xPos;
    //BWDrawText(centeredX,yPos+2, szTitle);
    CProjectCfg* cfg = CProjectCfg::getInstance();
    
    BWDrawText(cfg->m_GameClock_X,cfg->m_GameClock_Y, (char*)GetElapsedTimeStr().c_str());
    BWDrawText(cfg->m_LocalClock_X,cfg->m_LocalClock_Y, (char*)GetLocalTimeStr().c_str());
    CApmThread* papmthread = CApmThread::getInst();
    // draw apm
    calcapm();

    if (BWUtil::getInst()->IsInObsMode()) // show all apm
    {
        UINT32 linenum = 0;
        for (int ia = 0; ia < 12; ia++)//papmthread->m_apmCounterStr->size()
        {
            if (!papmthread->m_apmCounterStr[ia].empty() && !BWUtil::getInst()->IsObserver(ia))
            {
                std::string t = papmthread->m_apmCounterStr[ia];
                BWDrawText(cfg->m_LiveAPM_X, cfg->m_LiveAPM_Y + LINE_SIZE * linenum, (char*)t.c_str());
                linenum++;
            }
        }
    }
    else if (BWUtil::getInst()->GetMyPlayerID() < 12)
    {
        std::string t = papmthread->m_apmCounterStr[BWUtil::getInst()->GetMyPlayerID()];
        BWDrawText(cfg->m_LiveAPM_X, cfg->m_LiveAPM_Y, (char*)t.c_str());
    }

    BWRestoreTextFormat(oldFormat);	
}
/*
{Code in 1.16:
004BD504  |. E8 47F9FCFF    CALL StarCraf.0048CE50  ; overwrite
004BD509  |. E8 D22FFBFF    CALL StarCraf.004704E0  ; jump back
  }*/
void __stdcall CApmThread::DrawHook()
{
    /*__asm {
        call dword ptr [HOOK_DrawRepFunc]
        pushad
    }   */

    DrawItFun();

   /* __asm {
        popad
        jmp [HOOK_DRAWJMPBACK];
    }*/
}

const byte ACTION_TYPE_KEEPALIVE = 0x37;

// 1.16 Code:   handlecommond
/*{
    004F31BE  |. 52             PUSH EDX                       ; /Arg1
        004F31BF  |. 8D5D 0C        LEA EBX,DWORD PTR SS:[EBP+C]   ; |
        004F31C2  |. 894D 0C        MOV DWORD PTR SS:[EBP+C],ECX   ; |
        004F31C5  |. E8 06F1FBFF    CALL StarCraf.004B22D0         ; \StarCraf.004B22D0
  }*/

/*/ 1.16 code:
{
    00486C78  |. 52             |PUSH EDX                ; /Arg1 => 00000008
        00486C79  |. 8BDE           |MOV EBX,ESI             ; |
        00486C7B  |. E8 D0700400    |CALL StarCraf.004CDD50  ; \StarCraf.004CDD50
  }*/

void __stdcall CApmThread::ActionHook(const byte* pactiontype)
{
    CLogger::getinstance()->log("action hook");
    byte actioncode;
    DWORD pnum1 = BWUtil::getInst()->GetSendActionPlayerID();
    actioncode = *(byte*)pactiontype;
    CLogger::getinstance()->log("action hook %d %d", actioncode, pnum1);
    if (actioncode == ACTION_TYPE_KEEPALIVE || pnum1 >= 12)
        return;
    CLogger::getinstance()->log("action hook %d %d", actioncode, pnum1);
    CApmThread::getInst()->m_apmCounter[pnum1] = CApmThread::getInst()->m_apmCounter[pnum1] + 1;
}

unsigned int __stdcall CApmThread::ThreadFun(void* para)
{
    CLogger* plog = CLogger::getinstance();
    plog->log("ThreadFun begin");
	bool ingame = false;
	CApmThread* p = (CApmThread*)para;
    BWUtil* putil = BWUtil::getInst();
	while(!p->m_bStop)
	{
		if (!ingame && putil->IsInGame())
        {
            ingame = true;
            putil->Patch();
            p->m_GameStartTm = 0;//putil->GameTime() * 42;
            p->m_APM_UpdateTm = 0;//p->m_GameStartTm;
            plog->log("to ingame %d", p->m_GameStartTm);
        }
        else if (ingame && !putil->IsInGame())
        {
            ingame = false;
            plog->log("to outgame");
            putil->UnPatch();
        }

        Sleep(150);
	}
    plog->log("ThreadFun end");
	_endthreadex(0);
	return 0;
}