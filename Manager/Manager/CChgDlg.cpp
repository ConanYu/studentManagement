// CChgDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "CChgDlg.h"
#include "afxdialogex.h"


// CChgDlg 对话框

IMPLEMENT_DYNAMIC(CChgDlg, CDialogEx)

CChgDlg::CChgDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CHG, pParent)
{

}

CChgDlg::~CChgDlg()
{
}

void CChgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit_name);
	DDX_Control(pDX, IDC_EDIT2, m_edit_number);
	DDX_Control(pDX, IDC_EDIT3, m_edit_oop);
	DDX_Control(pDX, IDC_EDIT4, m_edit_math);
}


BEGIN_MESSAGE_MAP(CChgDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CChgDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CChgDlg 消息处理程序

BOOL CChgDlg::OnInitDialog() {

	CDialogEx::OnInitDialog();
	const int idx = app->chg_pos;
	Management & manager = app->manager;
	m_edit_name.SetWindowTextW(manager.v[idx].getName());
	m_edit_number.SetWindowTextW(manager.v[idx].getNumber());
	CString str;
	str.Format(L"%d", manager.v[idx].getGradeOOP());
	m_edit_oop.SetWindowTextW(str);
	str.Format(L"%d", manager.v[idx].getGradeMath());
	m_edit_math.SetWindowTextW(str);

	return TRUE;
}

void CChgDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	Management & manager = app->manager;
	const int idx = app->chg_pos;
	CString chg_name;
	CString chg_number = manager.v[idx].getNumber();
	CString chg_oop;
	CString chg_math;
	m_edit_name.GetWindowTextW(chg_name);
	m_edit_oop.GetWindowTextW(chg_oop);
	m_edit_math.GetWindowTextW(chg_math);
	const int oop = _wtoi(chg_oop), math = _wtoi(chg_math);
	manager.v[idx] = Student(chg_name, chg_number, oop, math);
	CDialogEx::OnOK();
}
