
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
#include "Leveldlg.h"
#include <mmsystem.h>

// CTetrisView

IMPLEMENT_DYNCREATE(CTetrisView, CFormView)

BEGIN_MESSAGE_MAP(CTetrisView, CFormView)
	ON_COMMAND(ID_HERO_LIST, &CTetrisView::OnHeroList)
	ON_COMMAND(ID_HELP_DOC, &CTetrisView::OnHelpDoc)
	ON_COMMAND(ID_NEW_GAME, &CTetrisView::OnNewGame)
	ON_WM_TIMER()
	ON_COMMAND(ID_EXIT_GAME, &CTetrisView::OnExitGame)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_GAME_LEVEL, &CTetrisView::OnGameLevel)
	ON_COMMAND(ID_BKMUSIC_ON, &CTetrisView::OnBkmusicOn)
	ON_COMMAND(ID_BKMUSIC_OFF, &CTetrisView::OnBkmusicOff)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CTetrisView 构造/析构

CTetrisView::CTetrisView()
	: CFormView(IDD_TETRIS_FORM)
{
	m_start = false;
	startBK.LoadBitmapW(IDB_START_BK);
	startButtons.m_unclickedbutton.LoadBitmapW(IDB_UNCLICKED_START);
	startButtons.m_activatebutton.LoadBitmapW(IDB_ACTIVATE_START);
	startButtons.m_clickedbutton.LoadBitmapW(IDB_CLICKED_START);
	startButtons.flag = 0;
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
	/*CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();*/
	SetTimer(1, 1000, NULL);
	// m_nMapMode = -1;
}

void CTetrisView::DrawStartbk(CDC * pDC, CRect rect)
{
	CDC dc;
	BITMAP bmp;
	startBK.GetBitmap(&bmp);
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(startBK);
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &dc, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
}

void CTetrisView::DrawButtons(CDC * pDC, CRect rect, int flag)
{
	CDC dc;
	BITMAP bmp;
	CBitmap *tbutton = NULL;
	
	switch (flag)
	{
	case 0:
		tbutton = &startButtons.m_unclickedbutton;
		break;
	case 1:
		tbutton = &startButtons.m_activatebutton;
		break;
	case 2:
		tbutton = &startButtons.m_clickedbutton;
		break;
	default:
		break;
	}
	tbutton->GetBitmap(&bmp);
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(*tbutton);
	pDC->BitBlt((rect.Width() / 2) - (bmp.bmWidth / 2), (rect.Height() / 2) - (bmp.bmHeight / 2) - 80, bmp.bmWidth, bmp.bmHeight, &dc, 0, 0, SRCCOPY);
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
	CRect rect;
	GetClientRect(&rect);
	
	if (!m_start)
	{
		// 游戏未开始，加载游戏菜单界面
		DrawStartbk(pDC, rect);
		DrawButtons(pDC, rect, startButtons.flag);
	}
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
	// 游戏开始
	m_start = true;
	CRect cr;
	GetClientRect(&cr);
	m_russia.GameStart();
	KillTimer(1);		// 游戏开始关闭第一个Timer
	SetTimer(2, m_russia.m_Speed, NULL);
}


void CTetrisView::OnTimer(UINT_PTR nIDEvent)
{
	if (m_start)
	{
		CRect cr;
		GetClientRect(cr);
		//下移
		m_russia.Move(KEY_DOWN);
		//重画
		m_russia.DrawBK(GetDC(), cr);
		//关闭Timer2
		KillTimer(2);
		//调整速度
		SetTimer(2, m_russia.m_Speed, NULL);
		CFormView::OnTimer(nIDEvent);
	}
	else
	{
		Invalidate();
	}	
}


void CTetrisView::OnExitGame()
{
	// 退出游戏
	m_start = false;
	KillTimer(2);
}


BOOL CTetrisView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	return CFormView::PreTranslateMessage(pMsg);
}


void CTetrisView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (!m_start)
		return;

	switch (nChar)
	{
	case VK_LEFT:
		m_russia.Move(KEY_LEFT);
		break;
	case VK_RIGHT:
		m_russia.Move(KEY_RIGHT);
		break;
	case VK_UP:
		m_russia.Move(KEY_UP);
		break;
	case VK_DOWN:
		m_russia.Move(KEY_DOWN);
		break;
	}
	CFormView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CTetrisView::OnGameLevel()
{
	// 设置游戏等级
	CLeveldlg leveldlg;
	leveldlg.m_level = m_russia.m_Level;
	if (leveldlg.DoModal() == IDOK)
	{
		m_russia.m_Level = leveldlg.m_level;
	}
}


void CTetrisView::OnBkmusicOn()
{
	// 打开背景音乐
	LPCWSTR BGM = L".\\sound\\BGM.wav";
	sndPlaySound(BGM, SND_ASYNC | SND_LOOP);
}


void CTetrisView::OnBkmusicOff()
{
	// 关闭背景音乐
	sndPlaySound(NULL, SND_ASYNC);
}


void CTetrisView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CFormView::OnMouseMove(nFlags, point);
}


void CTetrisView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	POINT curPos;
	CRect rect;
	GetClientRect(&rect);
	GetCursorPos(&curPos);
	bool isOnButton = (curPos.x >= ((rect.Width() / 2) - (194 / 2)) &&
		curPos.x <= ((rect.Width() / 2) + (194 / 2)) &&
		curPos.y >= ((rect.Height() / 2) - (41 / 2)) &&
		curPos.y <= ((rect.Height() / 2) + (41 / 2)));
	if (isOnButton)
	{
		startButtons.flag = 2;
		OnNewGame();
	}
	else
	{
		startButtons.flag = 1;
	}
	startButtons.flag = 0;
	
	CFormView::OnLButtonDown(nFlags, point);
}
