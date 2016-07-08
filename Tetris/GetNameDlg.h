#pragma once


// CGetNameDlg dialog

class CGetNameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGetNameDlg)

public:
	CGetNameDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGetNameDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HERONAME_GET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_getname;
	afx_msg void OnBnClickedOk();
	void SetHeroData(CString name);
};
