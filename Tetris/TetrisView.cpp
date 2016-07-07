
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

// CTetrisView ����/����

CTetrisView::CTetrisView()
	: CFormView(IDD_TETRIS_FORM)
{
	// TODO: �ڴ˴���ӹ������

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
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


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
	// TODO: Add your specialized code here and/or call the base class
	CRect rect;
	
	GetClientRect(&rect);
	m_russia.DrawBK(pDC, rect);
	
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
	// TODO: Add your command handler code here
	m_russia.GameStart();
	SetTimer(1, 100, NULL);
}


void CTetrisView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	Invalidate();
	m_russia.Move(3);		// �Զ������ƶ�
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
