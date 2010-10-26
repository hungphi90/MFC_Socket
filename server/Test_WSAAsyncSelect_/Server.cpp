// Test_WSAAsyncSelect_.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTest_WSAAsyncSelect_App

BEGIN_MESSAGE_MAP(CTest_WSAAsyncSelect_App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CTest_WSAAsyncSelect_App construction

CTest_WSAAsyncSelect_App::CTest_WSAAsyncSelect_App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CTest_WSAAsyncSelect_App object

CTest_WSAAsyncSelect_App theApp;


// CTest_WSAAsyncSelect_App initialization

BOOL CTest_WSAAsyncSelect_App::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	
	CTest_WSAAsyncSelect_Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
