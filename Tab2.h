#if !defined(AFX_TAB2_H__05E43A7F_7DD5_4E33_AA81_0C3892B49E6A__INCLUDED_)
#define AFX_TAB2_H__05E43A7F_7DD5_4E33_AA81_0C3892B49E6A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Tab2.h : header file
//

#include "ProjectCfg.h"

/////////////////////////////////////////////////////////////////////////////
// CTab2 dialog

class CTab2 : public CDialog
{
// Construction
public:
	void UpdateToCfg(CProjectCfg* pcfg);
	void InitByCfg(CProjectCfg* pcfg);
	CTab2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTab2)
	enum { IDD = IDD_TAB2_DIALOG };
	int		m_LiveX;
	int		m_LiveY;
	BOOL	m_IsShowLive;
	BOOL	m_IsShowAll;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTab2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTab2)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TAB2_H__05E43A7F_7DD5_4E33_AA81_0C3892B49E6A__INCLUDED_)
