
// TetrisView.cpp : CTetrisView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Tetris.h"
#endif

#include "TetrisDoc.h"
#include "TetrisView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 其他头文件
#include "HeroDlg.h"
#include "HelpDlg.h"


// CTetrisView

IMPLEMENT_DYNCREATE(CTetrisView, CFormView)

BEGIN_MESSAGE_MAP(CTetrisView, CFormView)
	ON_COMMAND(ID_HERO_LIST, &CTetrisView::OnHeroList)
	ON_COMMAND(ID_HELP_DOC, &CTetrisView::OnHelpDoc)
	ON_COMMAND(ID_NEW_GAME, &CTetrisView::OnNewGame)
	ON_WM_TIMER()
	ON_COMMAND(ID_EXIT_GAME, &CTetrisView::OnExitGame)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CTetrisView 构造/析构

CTetrisView::CTetrisView()
	: CFormView(IDD_TETRIS_FORM)
{
	// TODO: 在此处添加构造代码

}

CTetrisView::~CTetrisView()
{
}

void CTetrisView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CTetrisView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void CTetrisView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CTetrisView 诊断

#ifdef _DEBUG
void CTetrisView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTetrisView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CTetrisDoc* CTetrisView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTetrisDoc)));
	return (CTetrisDoc*)m_pDocument;
}
#endif //_DEBUG


// CTetrisView 消息处理程序


void CTetrisView::OnDraw(CDC* pDC)
{
	// TODO: Add your specialized code here and/or call the base class
	CRect rect;
	
	GetClientRect(&rect);
	m_russia.DrawBK(pDC, rect);
	
}


void CTetrisView::OnHeroList()
{
	// 打开英雄榜
	CHeroDlg herodlg;
	herodlg.DoModal();
}


void CTetrisView::OnHelpDoc()
{
	// 显示帮助文档
	CHelpDlg helpdlg;
	helpdlg.DoModal();
}


void CTetrisView::OnNewGame()
{
	// TODO: Add your command handler code here
	m_russia.GameStart();
	SetTimer(1, 100, NULL);
}


void CTetrisView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	Invalidate();
	m_russia.Move(3);		// 自动向下移动
	CFormView::OnTimer(nIDEvent);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_russia.Now[i][j] = m_russia.Will[i][j];
		}
	}
}


void CTetrisView::OnExitGame()
{
	// TODO: Add your command handler code here
	KillTimer(1);
}


BOOL CTetrisView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->wParam == VK_UP)
	{
		m_russia.Move(2);
		
		//AfxMessageBox(_T("Up_key"));
	}
	
	return CFormView::PreTranslateMessage(pMsg);
}


void CTetrisView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	int key;
	switch (nChar)
	{
	case VK_LEFT:
		key = 1;
		break;
	case VK_RIGHT:
		key = 2;
		break;
	case VK_DOWN:
		key = 3;
		break;
	case VK_UP:
		key = 4;
		break;
	default:
		key = 3;
		break;
	}
	m_russia.Move(key);
	CFormView::OnKeyDown(nChar, nRepCnt, nFlags);
}
