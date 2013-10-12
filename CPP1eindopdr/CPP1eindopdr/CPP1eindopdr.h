
// CPP1eindopdr.h : main header file for the CPP1eindopdr application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CCPP1eindopdrApp:
// See CPP1eindopdr.cpp for the implementation of this class
//

class CCPP1eindopdrApp : public CWinAppEx
{
public:
	CCPP1eindopdrApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnShapeRectangle();
	afx_msg void OnShapeCircle();
};

extern CCPP1eindopdrApp theApp;
