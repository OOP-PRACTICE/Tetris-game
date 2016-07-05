#pragma once


// CHeroDlg dialog

class CHeroDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHeroDlg)

public:
	CHeroDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CHeroDlg();
	
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HERO_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
public:
	int m_level;			// 记录等级
	CString m_name;			// 记录名字
	int m_score;			// 记录分数
	BOOL m_bWriteflg;		// 设置读写标志
	DECLARE_MESSAGE_MAP()
};
