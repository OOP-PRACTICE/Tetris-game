#pragma once
#include "afxcmn.h"


// CLeveldlg dialog

class CLeveldlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLeveldlg)

public:
	CLeveldlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLeveldlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_LEVEL_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	// 调节游戏等级
	CSpinButtonCtrl m_level_spin;
	int m_level;			// 游戏等级
	virtual BOOL OnInitDialog();
};
