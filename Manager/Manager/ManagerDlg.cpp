
// ManagerDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "ManagerDlg.h"
#include "afxdialogex.h"
#include "CAddDlg.h"
#include "CChgDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CManagerDlg 对话框



CManagerDlg::CManagerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MANAGER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CManagerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(HDN_BEGINTRACK, 0, &CManagerDlg::OnBegintrackList1)
	ON_BN_CLICKED(IDC_BUTTON3, &CManagerDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &CManagerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CManagerDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &CManagerDlg::OnBnClickedButton2)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, &CManagerDlg::OnColumnclickList1)
END_MESSAGE_MAP()


// source path
CString filePath;

void CManagerDlg::update(const Management & obj) {
	// delete what in screen
	int delItemsCount = m_list.GetItemCount();
	for (int i = 0; i < delItemsCount; i++) {
		m_list.DeleteItem(0);
	}

	CString str;
	const int n = obj.v.size();

	for (int i = n - 1; i >= 0; i--) {
		CString name = obj.v[i].getName(), number = obj.v[i].getNumber();
		name.ReleaseBuffer();
		number.ReleaseBuffer();
		m_list.InsertItem(0, name);
		m_list.SetItemText(0, 1, number);
		str.Format(L"%d", obj.v[i].getGradeOOP());
		m_list.SetItemText(0, 2, str);
		str.Format(L"%d", obj.v[i].getGradeMath());
		m_list.SetItemText(0, 3, str);
	}
	Management & manager = app->manager;
	manager.output(filePath + "tmp.csv");
}


// CManagerDlg 消息处理程序

BOOL CManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	app = (CManagerApp *)AfxGetApp();
	Management & manager = app->manager;

	{
		// m_list初始化
		const CString STR[] = { L"姓名", L"学号", L"面向对象程序设计成绩", L"高等数学成绩" };
		const int LENTH[] = {100, 142, 145, 145};
		for (int i = 0; i < 4; i++) {
			m_list.InsertColumn(i, STR[i], 0, LENTH[i]);
		}
		m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	}
	
	{
		// get source path
		CString path = AfxGetApp()->m_pszHelpFilePath;
		int idx = 0;
		const int len = path.GetLength();
		for (int i = 0; i < len; i++) {
			if (path[i] == '\\') {
				idx = i;
			}
		}
		filePath = path.Left(idx + 1);
		// update from source path
		manager = Management(filePath + L"data.csv");
		status = manager.sort();
		update(manager);
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 禁止拖动表头
void CManagerDlg::OnBegintrackList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = TRUE;
}

//del
void CManagerDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION line = m_list.GetFirstSelectedItemPosition();
	CString str;
	if (line == NULL) {
		AfxMessageBox(L"你没有选中任何人！");
	}
	else {
		Management & manager = app->manager;
		int nItem = m_list.GetNextSelectedItem(line);
		manager.erase(nItem);
		update(manager);
	}
}

//add
void CManagerDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CAddDlg dlg;
	dlg.DoModal();
	update(app->manager);
}

//save
void CManagerDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	app->manager.output(filePath + L"data.csv");
	AfxMessageBox(L"保存成功");
}

//chg
void CManagerDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION line = m_list.GetFirstSelectedItemPosition();
	if (line == NULL) {
		AfxMessageBox(L"你没有选中任何人！");
	}
	else {
		app->chg_pos = m_list.GetNextSelectedItem(line);
		CChgDlg dlg;
		dlg.DoModal();
		update(app->manager);
	}
}

//sort
void CManagerDlg::OnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int idx = pNMLV->iSubItem; // get the clicked column
	idx = (idx == 0 || idx == 1) ? (1 - idx) : idx;
	bool rev = false;

	switch (idx) {
	case 0:rev = status == 0; break;
	case 1:rev = status == 2; break;
	case 2:rev = status == 4; break;
	case 3:rev = status == 6; break;
	}
	Management & manager = app->manager;
	status = manager.sort(idx, rev);
	update(manager);


	*pResult = 0;
}
