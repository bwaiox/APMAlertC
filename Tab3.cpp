// Tab3.cpp : implementation file
//

#include "stdafx.h"
#include "APMAlert.h"
#include "Tab3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTab3 dialog


CTab3::CTab3(CWnd* pParent /*=NULL*/)
	: CDialog(CTab3::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTab3)
	m_ShowGLock = FALSE;
	m_ShowLLock = FALSE;
	m_GX = 0;
	m_GY = 0;
	m_LX = 0;
	m_LY = 0;
	//}}AFX_DATA_INIT
}


void CTab3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTab3)
	DDX_Check(pDX, IDC_CHK_GLOCK, m_ShowGLock);
	DDX_Check(pDX, IDC_CHK_LLOCK, m_ShowLLock);
	DDX_Text(pDX, IDC_EDT_GX, m_GX);
	DDX_Text(pDX, IDC_EDT_GY, m_GY);
	DDX_Text(pDX, IDC_EDT_LX, m_LX);
	DDX_Text(pDX, IDC_EDT_LY, m_LY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTab3, CDialog)
	//{{AFX_MSG_MAP(CTab3)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTab3 message handlers

void CTab3::InitByCfg(CProjectCfg *pcfg)
{
	m_GX = pcfg->m_GameClock_X;
	m_GY = pcfg->m_GameClock_Y;
	m_LX = pcfg->m_LocalClock_X;
	m_LY = pcfg->m_LocalClock_Y;
	m_ShowGLock = pcfg->m_IsShowGameClock;
	m_ShowLLock = pcfg->m_IsShowLocalClock;
	//UpdateData(FALSE);
}

void CTab3::UpdateToCfg(CProjectCfg *pcfg)
{
	UpdateData(TRUE);
	pcfg->m_GameClock_X = m_GX;
	pcfg->m_GameClock_Y = m_GY;
	pcfg->m_LocalClock_X = m_LX;
	pcfg->m_LocalClock_Y = m_LY;
	pcfg->m_IsShowGameClock = m_ShowGLock;
	pcfg->m_IsShowLocalClock = m_ShowLLock;
}
