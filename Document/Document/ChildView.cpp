
// ChildView.cpp: CChildView 类的实现
//

#include "stdafx.h"
#include "Document.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_COMMAND(1, PRINTOOPA)
	ON_COMMAND(2, PRINTOOPB)
	ON_COMMAND(3, PRINTMATA)
	ON_COMMAND(4, PRINTMATB)
END_MESSAGE_MAP()



// CChildView 消息处理程序

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	
	// TODO: 在此处添加消息处理程序代码
	
	// 不要为绘制消息而调用 CWnd::OnPaint()
}



int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	{
		// create
		OOPA.Create(L"OOP成绩直方图", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(10, 10, 130, 40), this, 1);
		OOPB.Create(L"OOP成绩折线图", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(140, 10, 260, 40), this, 2);
		MATA.Create(L"数学成绩直方图", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(10, 50, 130, 80), this, 3);
		MATB.Create(L"数学成绩折线图", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(140, 50, 260, 80), this, 4);
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
		manager = Management();
		manager.set(filePath + L"data.csv");
	}
	return 0;
}


void CChildView::PRINTOOPA()
{
	// TODO: 在此处添加实现代码.
	memcpy(a, manager.data.OOP, sizeof(int) * MAXIMUM);
	InvalidateRect(NULL);
	UpdateWindow();
	histogram(GetDC(), a, manager.sz);
}


void CChildView::PRINTOOPB()
{
	// TODO: 在此处添加实现代码.
	memcpy(a, manager.data.OOP, sizeof(int) * MAXIMUM);
	InvalidateRect(NULL);
	UpdateWindow();
	listChart(GetDC(), a, manager.sz);
}


void CChildView::PRINTMATA()
{
	// TODO: 在此处添加实现代码.
	memcpy(a, manager.data.MAT, sizeof(int) * MAXIMUM);
	InvalidateRect(NULL);
	UpdateWindow();
	histogram(GetDC(), a, manager.sz);
}


void CChildView::PRINTMATB()
{
	// TODO: 在此处添加实现代码.
	memcpy(a, manager.data.MAT, sizeof(int) * MAXIMUM);
	InvalidateRect(NULL);
	UpdateWindow();
	listChart(GetDC(), a, manager.sz);
}



void CChildView::histogram(CDC * pDC, const int *score, int n) // 直方图
{
	// TODO: 在此处添加实现代码.
	
	// 数据处理
	int data[5] = { 0 };
	for (int i = 0; i < n; i++) {
		int cur = score[i] / 10 - 5;
		if (cur < 0) {
			cur = 0;
		}
		else if (cur > 4) {
			cur = 4;
		}
		data[cur]++;
	}
	int mx = 0;
	for (int i = 0; i < 5; i++) {
		mx = mx > data[i] ? mx : data[i];
	}
	
	// print
	CRect rc;
	GetClientRect(rc);
	rc.DeflateRect(280, 40);
	CBrush brush1(HS_FDIAGONAL, RGB(0, 0, 192)), brush2(HS_BDIAGONAL, RGB(0, 0, 192));
	CPen pen(PS_INSIDEFRAME, 2, RGB(0, 0, 192));
	CBrush * oldBrush(pDC->SelectObject(&brush1));
	CPen * oldPen(pDC->SelectObject(&pen));
	CRect rcSeg(rc);
	const int width = rc.Width() / 5;
	rcSeg.right = rcSeg.left + width;
	const CString str[] = { L"小于60", L"60到69", L"70到79", L"80到89", L"大于等于90" };
	for (int i = 0; i < 5; i++) {
		pDC->SelectObject(i & 1 ? &brush2 : &brush1);
		if (mx != 0) {
			rcSeg.top = rcSeg.bottom - data[i] * (rc.Height() / mx) - 2;
		}
		pDC->Rectangle(rcSeg);
		if (data[i] > 0) {
			CString tmp;
			tmp.Format(L"%d", data[i]);
			pDC->DrawText(tmp, rcSeg, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		CRect rcStr = rcSeg;
		rcStr.top = rcStr.bottom + 2;
		rcStr.bottom += 20;
		pDC->DrawText(str[i], rcStr, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		rcSeg.OffsetRect(width, 0);
	}
	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);

}

void CChildView::listChart(CDC* pDC, const int* score, int n)//折线图
{
	// TODO: 在此处添加实现代码.

	// 数据处理
	int data[5] = { 0 };
	for (int i = 0; i < n; i++) {
		int cur = score[i] / 10 - 5;
		if (cur < 0) {
			cur = 0;
		}
		else if (cur > 4) {
			cur = 4;
		}
		data[cur]++;
	}
	int mx = 0;
	for (int i = 0; i < 5; i++) {
		mx = mx > data[i] ? mx : data[i];
	}

	// print
	CDC* pControlDC = pDC;
	pControlDC->SelectStockObject(BLACK_BRUSH);
	CString tmp;
	const CString str[] = { L"<60", L"60-70", L"70-80", L"80-90", L">=90" };
	pControlDC->MoveTo(280, 40);
	pControlDC->LineTo(280, 380);
	pControlDC->MoveTo(280, 380);
	pControlDC->LineTo(1050, 380);
	if (n != 0) {
		for (int i = 0; i < 5; i++) {
			const int x = i * 140 + 350, y = 380 - (380 * data[i] / n);
			if (i == 0) {
				pControlDC->MoveTo(x, y);
			}
			else {
				pControlDC->LineTo(x, y);
			}
			tmp.Format(L"%d人", data[i]);
			pControlDC->TextOut(i * 140 + 350, 380 - (380 * data[i] / n) - 20, tmp);
			pControlDC->TextOut(i * 140 + 350, 390, str[i]);
		}
	}
}
