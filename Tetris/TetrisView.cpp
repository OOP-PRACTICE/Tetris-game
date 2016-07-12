
// TetrisView.cpp : CTetrisView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Tetris.h"
#endif

#include "TetrisDoc.h"
#include "TetrisView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ����ͷ�ļ�
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
	ON_COMMAND(ID_CONTINUE_GAME, &CTetrisView::OnContinueGame)
	ON_COMMAND(ID_RESUME_GAME, &CTetrisView::OnResumeGame)
END_MESSAGE_MAP()

// CTetrisView ����/����

CTetrisView::CTetrisView()
	: CFormView(IDD_TETRIS_FORM)
{
	m_start = false;
	// ���ر���ͼƬ
	startBK.LoadBitmapW(IDB_START_BK);
	OnBkmusicOn();
	GameStartButton = NewMyButton(IDS_GAMESTART_MYBUTTON, CRect();
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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	return CFormView::PreCreateWindow(cs);
}

void CTetrisView::OnInitialUpdate()
{
	/*CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();*/
	//SetTimer(1, 100, NULL);
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

//void CTetrisView::DrawStartButtons(CDC * pDC, CRect rect, int flag)
//{
//	CDC dc;
//	BITMAP bmp;
//	CBitmap *tbutton = NULL;
//	
//	switch (flag)
//	{
//	case 0:
//		tbutton = &startButtons.m_unclickedbutton;
//		break;
//	case 1:
//		tbutton = &startButtons.m_activatebutton;
//		break;
//	case 2:
//		tbutton = &startButtons.m_clickedbutton;
//		break;
//	default:
//		break;
//	}
//	tbutton->GetBitmap(&bmp);
//	dc.CreateCompatibleDC(pDC);
//	dc.SelectObject(*tbutton);
//	pDC->BitBlt((rect.Width() / 2) - (bmp.bmWidth / 2), (rect.Height() / 2) - (bmp.bmHeight / 2) - 80, bmp.bmWidth, bmp.bmHeight, &dc, 0, 0, SRCCOPY);
//}

//void CTetrisView::DrawHelpButtons(CDC * pDC, CRect rect, int flag)
//{
//	CDC dc;
//	BITMAP bmp;
//	CBitmap *tbutton = NULL;
//
//	switch (flag)
//	{
//	case 0:
//		tbutton = &helpButtons.m_unclickedbutton;
//		break;
//	case 1:
//		tbutton = &helpButtons.m_activatebutton;
//		break;
//	case 2:
//		tbutton = &helpButtons.m_clickedbutton;
//		break;
//	default:
//		break;
//	}
//	tbutton->GetBitmap(&bmp);
//	dc.CreateCompatibleDC(pDC);
//	dc.SelectObject(*tbutton);
//	pDC->BitBlt((rect.Width() / 2) - (bmp.bmWidth / 2), (rect.Height() / 2) - (bmp.bmHeight / 2) - 30, bmp.bmWidth, bmp.bmHeight, &dc, 0, 0, SRCCOPY);
//}


// CTetrisView ���

#ifdef _DEBUG
void CTetrisView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTetrisView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CTetrisDoc* CTetrisView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTetrisDoc)));
	return (CTetrisDoc*)m_pDocument;
}
#endif //_DEBUG


// CTetrisView ��Ϣ�������


void CTetrisView::OnDraw(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);
	
	if (!m_start)
	{
		// ��Ϸδ��ʼ��������Ϸ�˵�����
		DrawStartbk(pDC, rect);
	}
}


void CTetrisView::OnHeroList()
{
	// ��Ӣ�۰�
	CHeroDlg herodlg;
	
	herodlg.DoModal();
}


void CTetrisView::OnHelpDoc()
{
	// ��ʾ�����ĵ�
	CHelpDlg helpdlg;
	helpdlg.DoModal();
}


void CTetrisView::OnNewGame()
{
	// ��Ϸ��ʼ
	//Invalidate();		// ˢ����Ļ�����µȼ�
	m_start = true;
	CRect cr;
	GetClientRect(&cr);
	m_russia.GameStart();
	KillTimer(1);		// ��Ϸ��ʼ�رյ�һ��Timer
	SetTimer(2, m_russia.m_Speed, NULL);
}


void CTetrisView::OnTimer(UINT_PTR nIDEvent)
{
	if (m_start)
	{
		KillTimer(1);
		CRect cr;
		GetClientRect(cr);
		//����
		m_russia.Move(KEY_DOWN);
		//�ػ�
		m_russia.DrawBK(GetDC(), cr);
		//�ر�Timer2
		KillTimer(2);
		//�����ٶ�
		SetTimer(2, m_russia.m_Speed, NULL);
		CFormView::OnTimer(nIDEvent);
	}
	else
	{
		//Invalidate();
	}	
}


void CTetrisView::OnExitGame()
{
	// �˳���Ϸ
	m_start = false;
	KillTimer(2);
	//SetTimer(1, 1000, NULL);
	Invalidate();
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
	// ������Ϸ�ȼ�
	CLeveldlg leveldlg;
	leveldlg.m_level = m_russia.m_Level;

	if (leveldlg.DoModal() == IDOK)
	{
		m_russia.m_Level = leveldlg.m_level;
		m_russia.rule.SetLevel(m_russia.m_Level);
	}
}


void CTetrisView::OnBkmusicOn()
{
	// �򿪱�������
	LPCWSTR BGM = L".\\sound\\BGM.wav";
	sndPlaySound(BGM, SND_ASYNC | SND_LOOP);
}


void CTetrisView::OnBkmusicOff()
{
	// �رձ�������
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
	CRect rect;
	GetClientRect(&rect);
	ClientToScreen(&point);

	POINT p = point;
	bool isOnStartButton = (p.x >= ((rect.Width() / 2) - (194 / 2)) &&
		p.x <= ((rect.Width() / 2) + (194 / 2)) &&
		p.y >= ((rect.Height() / 2) - (41 / 2)) &&
		p.y <= ((rect.Height() / 2) + (41 / 2)));
	
	if (isOnStartButton && !m_start)
	{
		OnNewGame();
	}
	
	CFormView::OnLButtonDown(nFlags, point);
}


void CTetrisView::OnContinueGame()
{
	// ������Ϸ
	SetTimer(2, m_russia.m_Speed, NULL);
}


void CTetrisView::OnResumeGame()
{
	// ��ͣ��Ϸ
	KillTimer(2);
}


// �Զ��尴ť
CButton* CTetrisView::NewMyButton(int nID, CRect rect, int nStyle)
{
	CString m_Caption;
	m_Caption.LoadString(nID); //ȡ��ť����
	CButton *p_Button = new CButton();
	ASSERT_VALID(p_Button);
	p_Button->Create(m_Caption, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | nStyle, rect, this, nID); //������ť
	return p_Button;
}