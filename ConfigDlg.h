#if !defined(AFX_CONFIGDLG_H__28B69668_E4B8_4D52_999D_F220A52AF6A9__INCLUDED_)
#define AFX_CONFIGDLG_H__28B69668_E4B8_4D52_999D_F220A52AF6A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigDlg.h : header file
//
#include "Tab1.h"
#include "Tab2.h"
#include "Tab3.h"


#include "TabSheet.h"

#include "ProjectCfg.h"
/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog

class CConfigDlg : public CDialog
{
// Construction
public:
	CConfigDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigDlg)
	enum { IDD = IDD_CONFIGDLG_DIALOG };
	CTabSheet	m_tab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigDlg)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnReset();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


	CTab1 m_page1;
	CTab2 m_page2;
	CTab3 m_page3;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGDLG_H__28B69668_E4B8_4D52_999D_F220A52AF6A9__INCLUDED_)
