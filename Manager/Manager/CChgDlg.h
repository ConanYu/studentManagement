#pragma once


// CChgDlg 对话框

class CChgDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChgDlg)

public:
	CChgDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CChgDlg();
	virtual BOOL OnInitDialog();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CHG };
#endif

private:
	CManagerApp * app = (CManagerApp *)AfxGetApp();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit_name;
	CEdit m_edit_number;
	CEdit m_edit_oop;
	CEdit m_edit_math;
	afx_msg void OnBnClickedOk();
};
