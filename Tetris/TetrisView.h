
// TetrisView.h : CTetrisView ��Ľӿ�
//

#pragma once
#include "Russia.h"

class CTetrisView : public CFormView
{
protected: // �������л�����
	CTetrisView();
	DECLARE_DYNCREATE(CTetrisView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_TETRIS_FORM };
#endif

// ����
public:
	CTetrisDoc* GetDocument() const;
	bool m_start;
	CBitmap startBK;
	CButton *GameStartButton;
	CButton *HelpButton;
	CButton *AboutButton;
	CBaseWork baseWork;
// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���
	void DrawStartbk(CDC* pDC, CRect rect);
	void CreateMenuButtons(CRect rect);
	void showGameOver(CDC* pDC, CRect rect);
// ʵ��
public:
	virtual ~CTetrisView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	// member variables
protected:
	CRussia m_russia;
// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnDraw(CDC* /*pDC*/);
public:
	afx_msg void OnHeroList();
	afx_msg void OnHelpDoc();
	afx_msg void OnNewGame();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnExitGame();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnGameLevel();
	afx_msg void OnBkmusicOn();
	afx_msg void OnBkmusicOff();
	afx_msg void OnContinueGame();
	afx_msg void OnResumeGame();
	afx_msg void OnMenuGameStartButton();
	afx_msg void OnMenuHelpButton();
	CButton * NewMyButton(int nID, CRect rect, int nStyle);
};

#ifndef _DEBUG  // TetrisView.cpp �еĵ��԰汾
inline CTetrisDoc* CTetrisView::GetDocument() const
   { return reinterpret_cast<CTetrisDoc*>(m_pDocument); }
#endif

