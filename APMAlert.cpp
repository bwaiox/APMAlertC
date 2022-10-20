// APMAlert.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "APMAlert.h"
#include "Logger.h"

#include "ProjectCfg.h"
#include "ConfigDlg.h"
#include "ApmThread.h"
#include <algorithm>
#include "ScopedHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CAPMAlertApp

BEGIN_MESSAGE_MAP(CAPMAlertApp, CWinApp)
	//{{AFX_MSG_MAP(CAPMAlertApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAPMAlertApp construction

CAPMAlertApp::CAPMAlertApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAPMAlertApp object

CAPMAlertApp theApp;

typedef struct TBWL_ExchangeData
{
	int PluginAPI;
	int StarCraftBuild;
	BOOL NotSCBWmodule;
	BOOL ConfigDialog;
}TBWL_ExchangeData;


char* PluginName = "APM";
int STARCRAFTBUILD = 13;
int PluginMajor = 1;
int PluginMinor = 0;


extern "C" void GetPluginAPI(TBWL_ExchangeData* Data)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//BWL Gets version from Resource - VersionInfo
	Data->PluginAPI = 4; //BWL 4
	Data->StarCraftBuild = STARCRAFTBUILD;    //1.15.2
	Data->ConfigDialog = TRUE; // We display a config dialog
	Data->NotSCBWmodule = TRUE; // No warning message
	
	CLogger::getinstance()->log("GetPluginAPI");
}



extern "C"  void GetData(char* name, char* des, char* updateurl)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	strcpy(name, PluginName);
	strcpy(des, "APM alert C++ verstion\r\nby nwao");
	strcpy(updateurl, "https://blog.csdn.net/nwao7890?type=blog");
	CLogger::getinstance()->log("GetData");
}

extern "C"  BOOL OpenConfig()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CLogger::getinstance()->log("OpenConfig");
	CConfigDlg dlg;
	dlg.DoModal();
	return TRUE;
}

extern "C" BOOL ApplyPatchSuspended(HANDLE hprocess, HANDLE processid)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CLogger::getinstance()->log("ApplyPatchSuspended");
	return TRUE;
}

extern "C" BOOL ApplyPatch(HANDLE hprocess, HANDLE processid)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CLogger::getinstance()->log("ApplyPatch");

	MEMORY_BASIC_INFORMATION mbi;
	static int dummy;  VirtualQuery( &dummy, &mbi, sizeof(mbi) );
    HMODULE hm = reinterpret_cast<HMODULE>(mbi.AllocationBase); 
    char buf[MAX_PATH];
	GetModuleFileName(hm, buf, sizeof(buf));

	CLogger::getinstance()->log("ApplyPatch,Module file %s", buf);
    
    HMODULE hker32 = GetModuleHandle("kernel32.dll");
    if (hker32 == NULL)
        return FALSE;
    HMODULE (WINAPI* loadLibAddr)(LPCSTR) = LoadLibraryA;
    CScopedVirtualAlloc pathstraddr(hprocess, NULL, strlen(buf) + 1, MEM_COMMIT, PAGE_READWRITE);
    if (pathstraddr.get() == NULL)
    {
        CLogger::getinstance()->log("ApplyPatch, alloc mem in starcraft fail");
        return FALSE;
    }
	DWORD tmpWrite = 0;
	BOOL ok = WriteProcessMemory(hprocess, pathstraddr.get(), buf, strlen(buf) + 1, &tmpWrite);
    if (!ok || tmpWrite != strlen(buf) + 1)
    {
        CLogger::getinstance()->log("ApplyPatch, write starcraft mem fail");
        return FALSE;
    }

	CLogger::getinstance()->log("LoadLibrary addr %d remote addr %d", loadLibAddr, pathstraddr.get());
    
    CScopedHandle hThread(CreateRemoteThread(hprocess, NULL, 0, (LPTHREAD_START_ROUTINE)loadLibAddr, pathstraddr.get(), 0, &tmpWrite));
	if (hThread.get() == NULL )
	{
        CLogger::getinstance()->log("remote thread create fail %d", GetLastError());
        return FALSE;
	}
	WaitForSingleObject(hThread.get(), INFINITE);
	
	DWORD exitcode;
	GetExitCodeThread(hThread.get(), &exitcode);
	if(exitcode == 0) 
    {
        CLogger::getinstance()->log("Error loading library remotely %d", GetLastError());
		return FALSE;
	}
	return TRUE;
}

BOOL CAPMAlertApp::InitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	// begin apm thread
	char buf[MAX_PATH];
	GetModuleFileName(NULL, buf, sizeof(buf));

    CLogger::getinstance()->log("InitInstance,APMAlert dll Be load by %s", buf);
    
    std::string full = buf;
    std::transform(full.begin(), full.end(), full.begin(), tolower);
    std::string exename = "starcraft.exe";
    if (full.find(exename) != std::string::npos)
        CApmThread::getInst()->Init();
	
	return CWinApp::InitInstance();
}

int CAPMAlertApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	CProjectCfg::releaseInstance();
	
    CLogger::releaseInstance();
    BWUtil::releaseInst();

	return CWinApp::ExitInstance();
}
