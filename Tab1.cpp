// Tab1.cpp : implementation file
//

#include "stdafx.h"
#include "APMAlert.h"
#include "Tab1.h"
#include <mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTab1 dialog


CTab1::CTab1(CWnd* pParent /*=NULL*/)
	: CDialog(CTab1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTab1)
	m_edtSound = _T("");
	m_minAPM = 0;
	m_chkPlay = FALSE;
	//}}AFX_DATA_INIT
}


void CTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTab1)
	DDX_Text(pDX, IDC_EDT_SOUND, m_edtSound);
	DDX_Text(pDX, IDC_EDT_MINAPM, m_minAPM);
	DDX_Check(pDX, IDC_CHK_PLAY, m_chkPlay);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTab1, CDialog)
	//{{AFX_MSG_MAP(CTab1)
	ON_BN_CLICKED(IDC_BTN_TRYPLAY, OnBtnTryplay)
	ON_BN_CLICKED(IDC_BTN_OPENFILE, OnBtnOpenfile)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTab1 message handlers

void CTab1::Reset()
{
	
}

void CTab1::OnBtnTryplay() 
{
	// TODO: Add your control notification handler code here
	sndPlaySound(m_edtSound, SND_ASYNC);
}

void CTab1::OnBtnOpenfile() 
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// TODO: Add your control notification handler code here
	//CFileDialog dlg(TRUE, "wav", "Select a sound file...", OFN_HIDEREADONLY, "Wav Files (*.wav)|*.wav|All Files|*.*", this);
	if (IDOK == pdlg->DoModal())
	{
		m_edtSound = pdlg->GetPathName();
		UpdateData(FALSE);
	}
	
	int a = 3 + 3;
}

BOOL CTab1::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	pdlg = new CFileDialog(TRUE, "wav", "Select a sound file...", OFN_HIDEREADONLY | OFN_EXPLORER, "Wav Files (*.wav)|*.wav|All Files|*.*", this);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTab1::InitByCfg(CProjectCfg *pcfg)
{
	m_minAPM = pcfg->m_MinAPM;
	m_edtSound = pcfg->m_SoundFile.c_str();
	m_chkPlay = pcfg->m_IsPlaySound;
}

void CTab1::UpdateToCfg(CProjectCfg *pcfg)
{
	UpdateData(TRUE);
	pcfg->m_MinAPM = m_minAPM;
	pcfg->m_SoundFile = (LPCTSTR)m_edtSound;
	pcfg->m_IsPlaySound = m_chkPlay;
}

void CTab1::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	delete pdlg;
	pdlg = NULL;
}
