// CAddDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "CAddDlg.h"
#include "afxdialogex.h"


// CAddDlg 对话框

IMPLEMENT_DYNAMIC(CAddDlg, CDialogEx)

CAddDlg::CAddDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ADD, pParent)
{

}

CAddDlg::~CAddDlg()
{
}

void CAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit_name);
	DDX_Control(pDX, IDC_EDIT2, m_edit_number);
	DDX_Control(pDX, IDC_EDIT3, m_edit_oop);
	DDX_Control(pDX, IDC_EDIT4, m_edit_math);
}


BEGIN_MESSAGE_MAP(CAddDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddDlg 消息处理程序
BOOL CAddDlg::OnInitDialog() {

	CDialogEx::OnInitDialog();
	
	app = (CManagerApp *)AfxGetApp();

	m_edit_name.SetLimitText(20);
	m_edit_number.SetLimitText(20);
	m_edit_oop.SetLimitText(20);
	m_edit_math.SetLimitText(20);

	m_edit_name.SetWindowTextW(L"张三");
	m_edit_number.SetWindowTextW(L"1806300001");
	m_edit_oop.SetWindowTextW(L"0");
	m_edit_math.SetWindowTextW(L"0");
	
	return TRUE;
}

void CAddDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_edit_name.GetWindowTextW(app->add_name);
	m_edit_number.GetWindowTextW(app->add_number);
	m_edit_oop.GetWindowTextW(app->add_oop);
	m_edit_math.GetWindowTextW(app->add_math);
	try {
		app->manager.add(Student(app->add_name, app->add_number, _wtoi(app->add_oop), _wtoi(app->add_math)));
		CDialogEx::OnOK();
	}
	catch (bad_exception) {
		AfxMessageBox(L"数据中已含有相同的学号");
		CDialogEx::OnInitDialog();
	}
}
