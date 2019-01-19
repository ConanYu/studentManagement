
// Manager.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "base.h"

// CManagerApp:
// 有关此类的实现，请参阅 Manager.cpp
//

class CManagerApp : public CWinApp
{
public:
	CManagerApp();

// 重写
public:
	virtual BOOL InitInstance();

public:
	// 全局变量
	Management manager;

	CString add_name;
	CString add_number;
	CString add_oop;
	CString add_math;

	int chg_pos;

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CManagerApp theApp;
