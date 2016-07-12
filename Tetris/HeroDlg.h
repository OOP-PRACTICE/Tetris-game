#pragma once
#include "afxwin.h"


// CHeroDlg dialog

class CHeroDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHeroDlg)

public:
	CHeroDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CHeroDlg();
	
// Dialog Data
public:
	int m_level = 1;			// 记录等级
	CString m_name;			// 记录名字
	int m_score = 0;			// 记录分数
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HERO_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnEnChangeLevelEdit();
	virtual BOOL OnInitDialog();
	void GetHeroData();
	void SetHeroData(int level, int score);		// 修改配置文件中的英雄信息（级别、分数）
};
