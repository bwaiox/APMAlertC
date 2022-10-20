// ConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "APMAlert.h"
#include "ConfigDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog


CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigDlg)
	//}}AFX_DATA_INIT
}


void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigDlg)
	DDX_Control(pDX, IDC_TAB1, m_tab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CConfigDlg)
	ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg message handlers


int CConfigDlg::DoModal() 
{

	return CDialog::DoModal();
}

BOOL CConfigDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CProjectCfg* cfg = CProjectCfg::getInstance();
	cfg->LoadCfg();
	m_page1.InitByCfg(cfg);
	m_page2.InitByCfg(cfg);
	m_page3.InitByCfg(cfg);
	// TODO: Add extra initialization here
	m_tab.AddPage("minapm", &m_page1, IDD_TAB1_DIALOG);
	m_tab.AddPage("liveapm", &m_page2, IDD_TAB2_DIALOG);
	m_tab.AddPage("clock", &m_page3, IDD_TAB3_DIALOG);
	
	m_tab.Show();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigDlg::OnBtnReset() 
{
	// TODO: Add your control notification handler code here
	CProjectCfg* cfg = CProjectCfg::getInstance();
	cfg->Reset();
	m_page1.InitByCfg(cfg);
	m_page1.UpdateData(FALSE);
	m_page2.InitByCfg(cfg);
	m_page2.UpdateData(FALSE);
	m_page3.InitByCfg(cfg);
	m_page3.UpdateData(FALSE);
	UpdateData(FALSE);
}

void CConfigDlg::OnOK() 
{
	// TODO: Add extra validation here
	CProjectCfg* cfg = CProjectCfg::getInstance();
	m_page1.UpdateToCfg(cfg);
	
	m_page2.UpdateToCfg(cfg);
	
	m_page3.UpdateToCfg(cfg);
	
	cfg->SaveCfg();
	
	CDialog::OnOK();
}
