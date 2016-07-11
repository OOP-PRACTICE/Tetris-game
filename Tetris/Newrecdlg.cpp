// Newrecdlg.cpp : implementation file
//

#include "stdafx.h"
#include "Tetris.h"
#include "Newrecdlg.h"
#include "afxdialogex.h"


// CNewrecdlg dialog

IMPLEMENT_DYNAMIC(CNewrecdlg, CDialogEx)

CNewrecdlg::CNewrecdlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NEWREC_DLG, pParent)
{

}

CNewrecdlg::~CNewrecdlg()
{
}

void CNewrecdlg::SetHeroData(int level, int score)
{
	CString tm;
	m_level = level;
	m_score = score;
	tm.Format(_T("%d"), level);
	WritePrivateProfileString((LPCWSTR)"HERO", (LPCWSTR)"level", tm, (LPCWSTR)".\\config\\setup.ini");
	tm.Format(_T("%d"), score);
	WritePrivateProfileString((LPCWSTR)"HERO", (LPCWSTR)"score", tm, (LPCWSTR)".\\config\\setup.ini");
}

void CNewrecdlg::ShowHeroData(int level, int score)
{
	/*CString temp;
	temp.Format(_T("等级: %d"), level);
	SetDlgItemInt(IDC_NEWLEVEL_INFO, level);
	SetDlgItemText(IDC_NEWLEVEL_INFO, temp);
	temp.Format(_T("分数: %d"), score);
	SetDlgItemText(IDC_SCORE_INFO, temp);*/
}

void CNewrecdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NEWLEVEL_INFO, m_staticShowLevel);
}


BEGIN_MESSAGE_MAP(CNewrecdlg, CDialogEx)
END_MESSAGE_MAP()


// CNewrecdlg message handlers

BOOL CNewrecdlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CString temp;
	temp.Format(_T("等级: %d"), m_level);
	SetDlgItemInt(IDC_NEWLEVEL_INFO, m_level);
	SetDlgItemText(IDC_NEWLEVEL_INFO, temp);
	temp.Format(_T("分数: %d"), m_score);
	SetDlgItemText(IDC_SCORE_INFO, temp);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
