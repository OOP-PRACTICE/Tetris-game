// HeroDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Tetris.h"
#include "HeroDlg.h"
#include "afxdialogex.h"


// CHeroDlg dialog

IMPLEMENT_DYNAMIC(CHeroDlg, CDialogEx)

CHeroDlg::CHeroDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HERO_DLG, pParent)
{
}

CHeroDlg::~CHeroDlg()
{
}

void CHeroDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHeroDlg, CDialogEx)
	ON_EN_CHANGE(IDC_LEVEL_EDIT, &CHeroDlg::OnEnChangeLevelEdit)
//	ON_BN_CLICKED(IDOK, &CHeroDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CHeroDlg message handlers


void CHeroDlg::OnEnChangeLevelEdit()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


BOOL CHeroDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	GetHeroData();
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CHeroDlg::GetHeroData()
{
	// 读取配置文件	
	m_level = GetPrivateProfileInt((LPCWSTR)"HERO", (LPCWSTR)"level", 0, (LPCWSTR)".\\config\\setup.ini");
	GetPrivateProfileString((LPCWSTR)"HERO", (LPCWSTR)"name", (LPCWSTR)"XXX", (LPWSTR)m_name, 127, (LPCWSTR)".\\config\\setup.ini");
	m_score = GetPrivateProfileInt((LPCWSTR)"HERO", (LPCWSTR)"score", 0, (LPCWSTR)".\\config\\setup.ini");
	// 显示在hero对话框中
	SetDlgItemInt(IDC_SHOW_LEVEL, m_level);
	SetDlgItemText(IDC_SHOW_NAME, (CString)m_name);
	SetDlgItemInt(IDC_SHOW_SCORE, m_score);
}

