# Microsoft Developer Studio Project File - Name="APMAlert" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=APMAlert - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "APMAlert.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "APMAlert.mak" CFG="APMAlert - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "APMAlert - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "APMAlert - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "APMAlert - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /c
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 winmm.lib /nologo /subsystem:windows /dll /machine:I386 /out:"Release/APMAlert.bwl"
# SUBTRACT LINK32 /incremental:yes
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy            /y            .\Release\APMAlert.bwl            E:\BaiduNetdiskDownload\StarCraft161\Chaoslauncher\ 
# End Special Build Tool

!ELSEIF  "$(CFG)" == "APMAlert - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_MBCS" /FR /Yu"stdafx.h" /GZ /c
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 winmm.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug/APMAlert.bwl" /pdbtype:sept
# SUBTRACT LINK32 /incremental:no
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy /y .\Debug\APMAlert.bwl E:\BaiduNetdiskDownload\StarCraft161\Chaoslauncher
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "APMAlert - Win32 Release"
# Name "APMAlert - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=".\APMAlert.cpp"
DEP_CPP_APMAL=\
	".\APMAlert.h"\
	".\ApmThread.h"\
	".\BWUtil.h"\
	".\Cfg.h"\
	".\ConfigDlg.h"\
	".\Logger.h"\
	".\ProjectCfg.h"\
	".\ScopedHelper.h"\
	".\StdAfx.h"\
	".\Tab1.h"\
	".\Tab2.h"\
	".\Tab3.h"\
	".\TabSheet.h"\
	
# End Source File
# Begin Source File

SOURCE=".\APMAlert.def"
# End Source File
# Begin Source File

SOURCE=".\APMAlert.rc"
# End Source File
# Begin Source File

SOURCE=.\ApmThread.cpp
DEP_CPP_APMTH=\
	".\APMAlert.h"\
	".\ApmThread.h"\
	".\BWUtil.h"\
	".\Cfg.h"\
	".\Logger.h"\
	".\ProjectCfg.h"\
	".\StdAfx.h"\
	
# End Source File
# Begin Source File

SOURCE=.\BWUtil.cpp
DEP_CPP_BWUTI=\
	".\APMAlert.h"\
	".\BWUtil.h"\
	".\StdAfx.h"\
	
# End Source File
# Begin Source File

SOURCE=".\Cfg.cpp"
DEP_CPP_CFG_C=\
	".\APMAlert.h"\
	".\Cfg.h"\
	".\StdAfx.h"\
	
# End Source File
# Begin Source File

SOURCE=".\ConfigDlg.cpp"
DEP_CPP_CONFI=\
	".\APMAlert.h"\
	".\Cfg.h"\
	".\ConfigDlg.h"\
	".\ProjectCfg.h"\
	".\StdAfx.h"\
	".\Tab1.h"\
	".\Tab2.h"\
	".\Tab3.h"\
	".\TabSheet.h"\
	
# End Source File
# Begin Source File

SOURCE=".\Logger.cpp"
DEP_CPP_LOGGE=\
	".\Logger.h"\
	".\StdAfx.h"\
	
# End Source File
# Begin Source File

SOURCE=.\ProjectCfg.cpp
DEP_CPP_PROJE=\
	".\APMAlert.h"\
	".\Cfg.h"\
	".\ProjectCfg.h"\
	".\StdAfx.h"\
	
# End Source File
# Begin Source File

SOURCE=.\ScopedHelper.cpp
DEP_CPP_SCOPE=\
	".\APMAlert.h"\
	".\ScopedHelper.h"\
	".\StdAfx.h"\
	
# End Source File
# Begin Source File

SOURCE=".\StdAfx.cpp"
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=".\Tab1.cpp"
DEP_CPP_TAB1_=\
	".\APMAlert.h"\
	".\Cfg.h"\
	".\ProjectCfg.h"\
	".\StdAfx.h"\
	".\Tab1.h"\
	
# End Source File
# Begin Source File

SOURCE=".\Tab2.cpp"
DEP_CPP_TAB2_=\
	".\APMAlert.h"\
	".\Cfg.h"\
	".\ProjectCfg.h"\
	".\StdAfx.h"\
	".\Tab2.h"\
	
# End Source File
# Begin Source File

SOURCE=".\Tab3.cpp"
DEP_CPP_TAB3_=\
	".\APMAlert.h"\
	".\Cfg.h"\
	".\ProjectCfg.h"\
	".\StdAfx.h"\
	".\Tab3.h"\
	
# End Source File
# Begin Source File

SOURCE=".\TabSheet.cpp"
DEP_CPP_TABSH=\
	".\APMAlert.h"\
	".\StdAfx.h"\
	".\TabSheet.h"\
	
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=".\APMAlert.h"
# End Source File
# Begin Source File

SOURCE=.\ApmThread.h
# End Source File
# Begin Source File

SOURCE=.\BWUtil.h
# End Source File
# Begin Source File

SOURCE=".\Cfg.h"
# End Source File
# Begin Source File

SOURCE=".\ConfigDlg.h"
# End Source File
# Begin Source File

SOURCE=".\Logger.h"
# End Source File
# Begin Source File

SOURCE=.\ProjectCfg.h
# End Source File
# Begin Source File

SOURCE=".\Resource.h"
# End Source File
# Begin Source File

SOURCE=.\ScopedHelper.h
# End Source File
# Begin Source File

SOURCE=".\StdAfx.h"
# End Source File
# Begin Source File

SOURCE=".\Tab1.h"
# End Source File
# Begin Source File

SOURCE=".\Tab2.h"
# End Source File
# Begin Source File

SOURCE=".\Tab3.h"
# End Source File
# Begin Source File

SOURCE=".\TabSheet.h"
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=".\res\APMAlert.rc2"
# End Source File
# End Group
# Begin Source File

SOURCE=".\ReadMe.txt"
# End Source File
# End Target
# End Project
