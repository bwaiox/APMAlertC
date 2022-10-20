#if !defined(AFX_TAB1_H__2E0E8D2E_3A19_4CFA_956F_A6065F76394B__INCLUDED_)
#define AFX_TAB1_H__2E0E8D2E_3A19_4CFA_956F_A6065F76394B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Tab1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTab1 dialog

#include "ProjectCfg.h"

class CTab1 : public CDialog
{
// Construction
public:
	CFileDialog* pdlg;
	void UpdateToCfg(CProjectCfg* pcfg);
	void InitByCfg(CProjectCfg* pcfg);
	void Reset();
	CTab1(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTab1)
	enum { IDD = IDD_TAB1_DIALOG };
	CString	m_edtSound;
	int		m_minAPM;
	BOOL	m_chkPlay;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTab1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTab1)
	afx_msg void OnBtnTryplay();
	afx_msg void OnBtnOpenfile();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TAB1_H__2E0E8D2E_3A19_4CFA_956F_A6065F76394B__INCLUDED_)
