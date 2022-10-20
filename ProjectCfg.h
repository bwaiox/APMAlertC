// ProjectCfg.h: interface for the CProjectCfg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTCFG_H__D4DB4D95_D765_4FAE_A774_FB6D00AB1094__INCLUDED_)
#define AFX_PROJECTCFG_H__D4DB4D95_D765_4FAE_A774_FB6D00AB1094__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Cfg.h"

class CProjectCfg : public CCfg  
{
public:
	bool LoadCfg();
	virtual ~CProjectCfg();
	bool SaveCfg();
	void Reset();

	static CProjectCfg* getInstance()
	{
		if (!m_Cfg)
			m_Cfg = new CProjectCfg();
		return m_Cfg;
	}

	static void releaseInstance()
	{
		if (m_Cfg)
		{
			delete m_Cfg;
			m_Cfg = NULL;
		}
	}


	BOOL m_IsPlaySound;
	std::string m_SoundFile;
	int  m_MinAPM;
	BOOL m_IsShowLiveAPM;
	BOOL m_IsShowAllLiveAPM;
	int  m_LiveAPM_X;
	int  m_LiveAPM_Y;
	BOOL m_IsShowLocalClock;
	int  m_LocalClock_X;
	int  m_LocalClock_Y;
	BOOL m_IsShowGameClock;
	int  m_GameClock_X;
	int  m_GameClock_Y;
	
	//CProjectCfg();
	CProjectCfg(char* ini = NULL);
	static CProjectCfg* m_Cfg;
};

#endif // !defined(AFX_PROJECTCFG_H__D4DB4D95_D765_4FAE_A774_FB6D00AB1094__INCLUDED_)
