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
	int m_level;			// ��¼�ȼ�
	CString m_name;			// ��¼����
	int m_score;			// ��¼����
	BOOL m_bWriteflg;		// ���ö�д��־
	DECLARE_MESSAGE_MAP()
};
