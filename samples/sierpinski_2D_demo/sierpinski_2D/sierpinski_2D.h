// sierpinski_2D.h : main header file for the sierpinski_2D application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Csierpinski_2DApp:
// See sierpinski_2D.cpp for the implementation of this class
//

class Csierpinski_2DApp : public CWinApp
{
public:
	Csierpinski_2DApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Csierpinski_2DApp theApp;