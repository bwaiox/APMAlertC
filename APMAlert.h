// APMAlert.h : main header file for the APMALERT DLL
//

#if !defined(AFX_APMALERT_H__71C4EE60_8F52_4C2D_8D0D_524E2D309262__INCLUDED_)
#define AFX_APMALERT_H__71C4EE60_8F52_4C2D_8D0D_524E2D309262__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAPMAlertApp
// See APMAlert.cpp for the implementation of this class
//

class CAPMAlertApp : public CWinApp
{
public:
	CAPMAlertApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAPMAlertApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CAPMAlertApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APMALERT_H__71C4EE60_8F52_4C2D_8D0D_524E2D309262__INCLUDED_)
