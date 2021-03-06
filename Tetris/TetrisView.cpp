
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
#include "Tetris.h"
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
	ON_COMMAND(ID_CONTINUE_GAME, &CTetrisView::OnContinueGame)
	ON_COMMAND(ID_RESUME_GAME, &CTetrisView::OnResumeGame)
	ON_COMMAND(IDS_GAMESTART_MYBUTTON, &CTetrisView::OnMenuGameStartButton)
	ON_COMMAND(IDS_HELP_MYBUTTON, &CTetrisView::OnMenuHelpButton)
	ON_COMMAND(IDS_MENUEXIT_BUTTON, &CTetrisView::OnMenuExitButton)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CTetrisView 构造/析构

CTetrisView::CTetrisView()
	: CFormView(IDD_TETRIS_FORM)
{
	m_start = false;
	// 加载背景图片
	startBK.LoadBitmapW(IDB_START_BK);
	OnBkmusicOn();
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
	CRect rect;
	GetClientRect(&rect);
	CreateMenuButtons(rect);
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

void CTetrisView::CreateMenuButtons(CRect rect)
{
	// 自定义按钮的位置
	int l = (rect.Width() / 2) - 90;
	int t = (rect.Height() / 2) - 21 - 60;
	int r = (rect.Width() / 2) + 90;
	int b = (rect.Height() / 2) + 21 - 60;
	int BtOffset = 80;
	GameStartButton = NewMyButton(IDS_GAMESTART_MYBUTTON, CRect(l, t, r, b), 0);
	HelpButton = NewMyButton(IDS_HELP_MYBUTTON, CRect(l, t + 2 * BtOffset, r, b + 2 * BtOffset), 0);
	ExitButton = NewMyButton(IDS_MENUEXIT_BUTTON, CRect(l, t + BtOffset, r, b + BtOffset), 0);
}

void CTetrisView::showGameOver(CDC * pDC, CRect rect)
{
	int x = rect.Width() / 2;
	int y = rect.Height() / 2;
	CFont font;
	font.CreatePointFont(500, _T("黑体"));
	CString szText = _T("GAME OVER");
	pDC->SelectObject(font);
	pDC->SetBkMode(TRANSPARENT);	// 设置字体为透明
	pDC->TextOutW(20, y - 60, szText);
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
	}
	if (m_russia.gameover)
	{

		showGameOver(pDC, rect);
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
	// 防止二次释放按钮
	if (!m_start)
	{
		// 游戏开始删除三个按钮
		delete GameStartButton;
		delete HelpButton;
		delete ExitButton;
	}
	// 游戏开始
	//Invalidate();		// 刷新屏幕，更新等级
	m_start = true;
	m_russia.gameover = false;
	m_russia.m_Level = 1;
	CString filePath;
	CString tm;
	filePath = baseWork.GetExePath(_T("\config\\setup.ini"));
	tm.Format(_T("%d"), 1);
	WritePrivateProfileString(_T("SETUP"), _T("level"), tm, filePath);
	CRect cr;
	GetClientRect(&cr);
	m_russia.GameStart();
	KillTimer(1);		// 游戏开始关闭第一个Timer
	SetTimer(2, m_russia.m_Speed, NULL);
	SetFocus();
}


void CTetrisView::OnTimer(UINT_PTR nIDEvent)
{
	CDC *pDC = GetDC();
	CDC dc;
	CBitmap *cacheBitmap = new CBitmap;
	CRect cr;
	GetClientRect(cr);

	dc.CreateCompatibleDC(pDC);
	cacheBitmap->CreateCompatibleBitmap(pDC, cr.Width(), cr.Height());
	CBitmap *pOldBit = dc.SelectObject(cacheBitmap);

	if (m_start)
	{
		KillTimer(1);
		
		//下移
		m_russia.Move(KEY_DOWN);
		//重画
		m_russia.DrawBK(&dc, cr);
		//关闭Timer2
		KillTimer(2);
		//调整速度
		SetTimer(2, m_russia.m_Speed, NULL);
		if (m_russia.gameover)
		{
			showGameOver(&dc, cr);
		}
		pDC->BitBlt(0, 0, cr.Width(), cr.Height(), &dc, 0, 0, SRCCOPY);
		CFormView::OnTimer(nIDEvent);
	}
}


void CTetrisView::OnExitGame()
{
	CRect rect;
	GetClientRect(&rect);
	// 退出游戏
	m_start = false;
	m_russia.gameover = false;
	KillTimer(2);
	//SetTimer(1, 1000, NULL);
	Invalidate();
	CreateMenuButtons(rect);
	OnBkmusicOff();
	Sleep(200);
	OnBkmusicOn();
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
		int tLevel = leveldlg.m_level;
		m_russia.m_Level = leveldlg.m_level;
		m_russia.rule.SetLevel(m_russia.m_Level);
		CString filePath;
		CString tm;
		filePath = baseWork.GetExePath(_T("\config\\setup.ini"));
		tm.Format(_T("%d"), tLevel);
		WritePrivateProfileString(_T("SETUP"), _T("level"), tm, filePath);
	}
}


void CTetrisView::OnBkmusicOn()
{
	// 打开背景音乐
	PlaySound((LPCTSTR)IDR_BGM_WAVE, AfxGetInstanceHandle(), SND_RESOURCE | SND_SYNC | SND_LOOP);
}


void CTetrisView::OnBkmusicOff()
{
	// 关闭背景音乐
	sndPlaySound(NULL, SND_ASYNC);
}

void CTetrisView::OnContinueGame()
{
	// 继续游戏
	SetTimer(2, m_russia.m_Speed, NULL);
}


void CTetrisView::OnResumeGame()
{
	// 暂停游戏
	KillTimer(2);
}

void CTetrisView::OnMenuGameStartButton()
{
	OnNewGame();
}

void CTetrisView::OnMenuHelpButton()
{
	OnHelpDoc();
}

void CTetrisView::OnMenuExitButton()
{
	// 退出游戏
	PostQuitMessage(0);
}


// 自定义按钮
CButton* CTetrisView::NewMyButton(int nID, CRect rect, int nStyle)
{
	CString m_Caption;
	m_Caption.LoadString(nID); //取按钮标题
	CButton *p_Button = new CButton();
	ASSERT_VALID(p_Button);
	p_Button->Create(m_Caption, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | nStyle, rect, this, nID); //创建按钮
	return p_Button;
}

BOOL CTetrisView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	//return CFormView::OnEraseBkgnd(pDC);
	return TRUE;
}
