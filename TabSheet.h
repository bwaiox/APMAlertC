#if !defined(AFX_TABSHEET_H__B1FC573C_3A46_4CA0_84AB_52E76D7D3177__INCLUDED_)
#define AFX_TABSHEET_H__B1FC573C_3A46_4CA0_84AB_52E76D7D3177__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabSheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTabSheet window
#define MAXPAGE 16
class CTabSheet : public CTabCtrl
{
// Construction
public:
	CTabSheet();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTabSheet();

public:
    int GetCurSel();
    int SetCurSel(int nItem);
    void Show();
    void SetRect();
    BOOL AddPage(LPCTSTR title, CDialog *pDialog, UINT ID);
	
    // Generated message map functions
protected:
    LPCTSTR m_Title[MAXPAGE];
    UINT m_IDD[MAXPAGE];
    CDialog* m_pPages[MAXPAGE];
    int m_nNumOfPages;
    int m_nCurrentPage;
    //{{AFX_MSG(CTabSheet)
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    //}}AFX_MSG
	// Generated message map functions

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABSHEET_H__B1FC573C_3A46_4CA0_84AB_52E76D7D3177__INCLUDED_)
