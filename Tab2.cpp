// Tab2.cpp : implementation file
//

#include "stdafx.h"
#include "APMAlert.h"
#include "Tab2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTab2 dialog


CTab2::CTab2(CWnd* pParent /*=NULL*/)
	: CDialog(CTab2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTab2)
	m_LiveX = 0;
	m_LiveY = 0;
	m_IsShowLive = FALSE;
	m_IsShowAll = FALSE;
	//}}AFX_DATA_INIT
}


void CTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTab2)
	DDX_Text(pDX, IDC_EDT_LIVEX, m_LiveX);
	DDX_Text(pDX, IDC_EDT_LIVEY, m_LiveY);
	DDX_Check(pDX, IDC_CHK_LIVEAPM, m_IsShowLive);
	DDX_Check(pDX, IDC_CHK_ALLAPM, m_IsShowAll);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTab2, CDialog)
	//{{AFX_MSG_MAP(CTab2)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTab2 message handlers

void CTab2::InitByCfg(CProjectCfg *pcfg)
{
	m_IsShowAll = pcfg->m_IsShowAllLiveAPM;
	m_IsShowLive = pcfg->m_IsShowLiveAPM;
	m_LiveX = pcfg->m_LiveAPM_X;
	m_LiveY = pcfg->m_LiveAPM_Y;
	//UpdateData(FALSE);
}

void CTab2::UpdateToCfg(CProjectCfg *pcfg)
{
	UpdateData(TRUE);
	pcfg->m_IsShowAllLiveAPM = m_IsShowAll;
	pcfg->m_IsShowLiveAPM = m_IsShowLive;
	pcfg->m_LiveAPM_X = m_LiveX;
	pcfg->m_LiveAPM_Y = m_LiveY;
}
