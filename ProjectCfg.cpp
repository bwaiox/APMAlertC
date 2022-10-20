// ProjectCfg.cpp: implementation of the CProjectCfg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "APMAlert.h"
#include "ProjectCfg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CProjectCfg* CProjectCfg::m_Cfg;

//CProjectCfg::CProjectCfg(): CCfg(NULL)
//{

//}

CProjectCfg::CProjectCfg(char* ini) : CCfg(ini)
{
	Reset();
}

CProjectCfg::~CProjectCfg()
{
	
}

void CProjectCfg::Reset()
{
	m_IsPlaySound = TRUE;
	m_SoundFile = "";
	m_MinAPM = 60;
	m_IsShowLiveAPM = TRUE;
	m_IsShowAllLiveAPM = TRUE;
	m_LiveAPM_X = 4;
	m_LiveAPM_Y = 2;
	m_IsShowLocalClock = TRUE;
	m_LocalClock_X = 14;
	m_LocalClock_Y = 284;
	m_IsShowGameClock = TRUE;
	m_GameClock_X = 286;
	m_GameClock_Y = 2;
}

bool CProjectCfg::LoadCfg()
{
    HKEY openkey;
    LONG ret = RegOpenKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\BWProgrammers\\APMAlert\\APM", 0, KEY_QUERY_VALUE, &openkey);
    if (ret == ERROR_SUCCESS)
	{
		m_IsPlaySound = RegReadInt(openkey, "IsPlaySound", 0);
		m_SoundFile = RegReadString(openkey, "SoundFile", "");
		m_MinAPM = RegReadInt(openkey, "MinAPM", 0);
		m_IsShowLiveAPM = RegReadInt(openkey, "IsShowLiveAPM", 1);
		m_IsShowAllLiveAPM = RegReadInt(openkey, "IsShowAllLiveAPM", 1);
		m_LiveAPM_X = RegReadInt(openkey, "LiveAPM_X", 0);
		m_LiveAPM_Y = RegReadInt(openkey, "LiveAPM_Y", 0);
		RegCloseKey(openkey);
	}
	
	ret = RegOpenKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\BWProgrammers\\APMAlert\\Clock", 0, KEY_QUERY_VALUE, &openkey);
    if (ret == ERROR_SUCCESS)
    {
		m_IsShowLocalClock = RegReadInt(openkey, "IsShowLocalClock", 0);
		m_LocalClock_X = RegReadInt(openkey, "LocalClock_X", 0);
		m_LocalClock_Y = RegReadInt(openkey, "LocalClock_Y", 0);
		m_IsShowGameClock = RegReadInt(openkey, "IsShowGameClock", 0);
		m_GameClock_X = RegReadInt(openkey, "GameClock_X", 0);
		m_GameClock_Y = RegReadInt(openkey, "GameClock_Y", 0);
		RegCloseKey(openkey);
	}

	return true;
}

bool CProjectCfg::SaveCfg()
{
	HKEY openkey;
	LONG ret = RegCreateKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\BWProgrammers\\APMAlert\\APM", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &openkey, NULL);
	if (ret == ERROR_SUCCESS)
	{
		RegWriteInt(openkey, "IsPlaySound", m_IsPlaySound);
		DWORD dw = GetLastError();
		RegWriteString(openkey, "SoundFile", m_SoundFile.c_str(), m_SoundFile.size() + 1);
		RegWriteInt(openkey, "MinAPM", m_MinAPM);
		RegWriteInt(openkey, "IsShowLiveAPM", m_IsShowLiveAPM);
		RegWriteInt(openkey, "IsShowAllLiveAPM", m_IsShowAllLiveAPM);
		RegWriteInt(openkey, "LiveAPM_X", m_LiveAPM_X);
		RegWriteInt(openkey, "LiveAPM_Y", m_LiveAPM_Y);

		RegCloseKey(openkey);
	}

	ret = RegCreateKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\BWProgrammers\\APMAlert\\Clock", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &openkey, NULL);
	if (ret == ERROR_SUCCESS)
	{
		RegWriteInt(openkey, "IsShowLocalClock", m_IsShowLocalClock);
		RegWriteInt(openkey, "LocalClock_X", m_LocalClock_X);
		RegWriteInt(openkey, "LocalClock_Y", m_LocalClock_Y);
		RegWriteInt(openkey, "IsShowGameClock", m_IsShowGameClock);
		RegWriteInt(openkey, "GameClock_X", m_GameClock_X);
		RegWriteInt(openkey, "GameClock_Y", m_GameClock_Y);
		
		RegCloseKey(openkey);
	}

	return true;
}
