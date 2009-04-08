// frustum_demo.h : main header file for the frustum_demo application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Cfrustum_demoApp:
// See frustum_demo.cpp for the implementation of this class
//

class Cfrustum_demoApp : public CWinApp
{
public:
	Cfrustum_demoApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Cfrustum_demoApp theApp;