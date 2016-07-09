#pragma once


// CNewrecdlg dialog

class CNewrecdlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNewrecdlg)

public:
	CNewrecdlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNewrecdlg();
	void SetHeroData(int level, int score);		// 修改配置文件中的英雄信息（级别、分数）
	void ShowHeroData(int level, int score);

// Dialog Data
public:
	int m_score;
	int m_level;
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEWREC_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	
};
