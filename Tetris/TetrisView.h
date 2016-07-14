
// TetrisView.h : CTetrisView 类的接口
//

#pragma once
#include "Russia.h"

class CTetrisView : public CFormView
{
protected: // 仅从序列化创建
	CTetrisView();
	DECLARE_DYNCREATE(CTetrisView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_TETRIS_FORM };
#endif

// 特性
public:
	CTetrisDoc* GetDocument() const;
	bool m_start;
	CBitmap startBK;
	CButton *GameStartButton;
	CButton *HelpButton;
	CButton *AboutButton;
	CBaseWork baseWork;
// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用
	void DrawStartbk(CDC* pDC, CRect rect);
	void CreateMenuButtons(CRect rect);
	void showGameOver(CDC* pDC, CRect rect);
// 实现
public:
	virtual ~CTetrisView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	// member variables
protected:
	CRussia m_russia;
// 生成的消息映射函数
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

#ifndef _DEBUG  // TetrisView.cpp 中的调试版本
inline CTetrisDoc* CTetrisView::GetDocument() const
   { return reinterpret_cast<CTetrisDoc*>(m_pDocument); }
#endif

