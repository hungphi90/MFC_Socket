// Test_WSAAsyncSelect_.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTest_WSAAsyncSelect_App:
// See Test_WSAAsyncSelect_.cpp for the implementation of this class
//

class CTest_WSAAsyncSelect_App : public CWinApp
{
public:
	CTest_WSAAsyncSelect_App();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CTest_WSAAsyncSelect_App theApp;