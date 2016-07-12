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
	int m_level = 1;			// ��¼�ȼ�
	CString m_name;			// ��¼����
	int m_score = 0;			// ��¼����
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
	void SetHeroData(int level, int score);		// �޸������ļ��е�Ӣ����Ϣ�����𡢷�����
};
