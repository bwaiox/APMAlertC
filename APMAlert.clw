; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
ClassCount=6
Class1=CAPMAlertApp
LastClass=CConfigDlg
NewFileInclude2=#include "APMAlert.h"
ResourceCount=4
NewFileInclude1=#include "stdafx.h"
Class2=CConfigDlg
LastTemplate=CTabCtrl
Resource1=IDD_TAB1_DIALOG (English (U.S.))
Class3=CTab1
Resource2=IDD_CONFIGDLG_DIALOG
Class4=CTab2
Resource3=IDD_TAB2_DIALOG (English (U.S.))
Class5=CTab3
Class6=CTabSheet
Resource4=IDD_TAB3_DIALOG (English (U.S.))

[CLS:CAPMAlertApp]
Type=0
HeaderFile=APMAlert.h
ImplementationFile=APMAlert.cpp
Filter=N
LastObject=CAPMAlertApp
BaseClass=CWinApp
VirtualFilter=AC

[DLG:IDD_CONFIGDLG_DIALOG]
Type=1
Class=CConfigDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_TAB1,SysTabControl32,1342177280
Control3=IDC_BTN_RESET,button,1342242816

[CLS:CConfigDlg]
Type=0
HeaderFile=ConfigDlg.h
ImplementationFile=ConfigDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CConfigDlg

[CLS:CTab1]
Type=0
HeaderFile=Tab1.h
ImplementationFile=Tab1.cpp
BaseClass=CDialog
Filter=D
LastObject=CTab1
VirtualFilter=dWC

[CLS:CTab2]
Type=0
HeaderFile=Tab2.h
ImplementationFile=Tab2.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_CHK_ALLAPM
VirtualFilter=dWC

[CLS:CTab3]
Type=0
HeaderFile=Tab3.h
ImplementationFile=Tab3.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDT_LY

[CLS:CTabSheet]
Type=0
HeaderFile=TabSheet.h
ImplementationFile=TabSheet.cpp
BaseClass=CTabCtrl
Filter=W

[DLG:IDD_TAB1_DIALOG (English (U.S.))]
Type=1
Class=CTab1
ControlCount=7
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDT_MINAPM,edit,1350639744
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDT_SOUND,edit,1350631552
Control5=IDC_BTN_OPENFILE,button,1342242816
Control6=IDC_BTN_TRYPLAY,button,1342242816
Control7=IDC_CHK_PLAY,button,1342242819

[DLG:IDD_TAB2_DIALOG (English (U.S.))]
Type=1
Class=CTab2
ControlCount=6
Control1=IDC_CHK_LIVEAPM,button,1342242819
Control2=IDC_CHK_ALLAPM,button,1342242819
Control3=IDC_EDT_LIVEX,edit,1350639744
Control4=IDC_EDT_LIVEY,edit,1350639744
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[DLG:IDD_TAB3_DIALOG (English (U.S.))]
Type=1
Class=CTab3
ControlCount=10
Control1=IDC_CHK_GLOCK,button,1342242819
Control2=IDC_EDT_GX,edit,1350639744
Control3=IDC_EDT_GY,edit,1350639744
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDT_LX,edit,1350639744
Control7=IDC_EDT_LY,edit,1350639744
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_CHK_LLOCK,button,1342242819

