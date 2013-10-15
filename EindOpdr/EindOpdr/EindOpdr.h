
// EindOpdr.h : main header file for the EindOpdr application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CEindOpdrApp:
// See EindOpdr.cpp for the implementation of this class
//

class CEindOpdrApp : public CWinAppEx
{
public:
	CEindOpdrApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEindOpdrApp theApp;
