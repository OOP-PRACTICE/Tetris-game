#pragma once


// CNewrecdlg dialog

class CNewrecdlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNewrecdlg)

public:
	CNewrecdlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNewrecdlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEWREC_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
