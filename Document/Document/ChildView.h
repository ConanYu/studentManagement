
// ChildView.h: CChildView 类的接口
//


#pragma once
#include "base.h"

// CChildView 窗口

class CChildView : public CWnd
{
// 构造
public:
	CChildView();

// 特性
public:

// 操作
public:

// 重写
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CChildView();

	// 生成的消息映射函数
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
private:
	CButton OOPA;
	CButton OOPB;
	CButton MATA;
	CButton MATB;
protected:
	void PRINTOOPA();
	void PRINTOOPB();
	void PRINTMATA();
	void PRINTMATB();
private:
	void histogram(CDC *, const int *, int);
	void listChart(CDC *, const int *, int);
	Management manager;
	CString filePath;
	int a[MAXIMUM];
};
