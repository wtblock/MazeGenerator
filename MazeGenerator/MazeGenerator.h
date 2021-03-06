/////////////////////////////////////////////////////////////////////////////
// Copyright (c) W. T. Block, All Rights Reserved
/////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMazeGeneratorApp:
// See MazeGenerator.cpp for the implementation of this class
//

class CMazeGeneratorApp : public CWinAppEx
{
public:
	CMazeGeneratorApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMazeGeneratorApp theApp;
