#if !defined(AFX_TAB3_H__381F8C74_9C74_450F_9963_533E6E315DB8__INCLUDED_)
#define AFX_TAB3_H__381F8C74_9C74_450F_9963_533E6E315DB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Tab3.h : header file
//

#include "ProjectCfg.h"

/////////////////////////////////////////////////////////////////////////////
// CTab3 dialog

class CTab3 : public CDialog
{
// Construction
public:
	void UpdateToCfg(CProjectCfg* pcfg);
	void InitByCfg(CProjectCfg *pcfg);
	CTab3(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTab3)
	enum { IDD = IDD_TAB3_DIALOG };
	BOOL	m_ShowGLock;
	BOOL	m_ShowLLock;
	int		m_GX;
	int		m_GY;
	int		m_LX;
	int		m_LY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTab3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTab3)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TAB3_H__381F8C74_9C74_450F_9963_533E6E315DB8__INCLUDED_)
