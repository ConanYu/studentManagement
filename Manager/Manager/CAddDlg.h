#pragma once


// CAddDlg 对话框

class CAddDlg : public CDialogEx
{
	CManagerApp * app;
	DECLARE_DYNAMIC(CAddDlg)

public:
	CAddDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAddDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit_name;
	CEdit m_edit_number;
	CEdit m_edit_oop;
	CEdit m_edit_math;
	afx_msg void OnBnClickedOk();
};
