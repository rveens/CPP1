
// CPPweek4.h : main header file for the CPPweek4 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CCPPweek4App:
// See CPPweek4.cpp for the implementation of this class
//

class CCPPweek4App : public CWinAppEx
{
public:
	CCPPweek4App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnRectanglePress();
	afx_msg void OnCirclePress();
};

extern CCPPweek4App theApp;
