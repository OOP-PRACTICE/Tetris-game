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
	// 获取可执行文件路径
	CString filePath;
	filePath = baseWork.GetExePath(_T("\config\\setup.ini"));
	// 读取配置文件	
	m_level = GetPrivateProfileInt(_T("HERO"), _T("level"), 0, filePath);
	GetPrivateProfileStringW(_T("HERO"), _T("name"), _T("XXX"), m_name.GetBuffer(127), 127, filePath);
	m_score = GetPrivateProfileInt(_T("HERO"), _T("score"), 0, filePath);
	// 显示在hero对话框中
	SetDlgItemInt(IDC_SHOW_LEVEL, m_level);
	SetDlgItemText(IDC_SHOW_NAME, (CString)m_name);
	SetDlgItemInt(IDC_SHOW_SCORE, m_score);
}

void CHeroDlg::SetHeroData(int level, int score)
{
	CString tm;
	CString filePath;
	filePath = baseWork.GetExePath(_T("\config\\setup.ini"));
	tm.Format(_T("%d"), level);
	WritePrivateProfileString(_T("HERO"), _T("level"), tm, filePath);
	tm.Format(_T("%d"), score);
	WritePrivateProfileString(_T("HERO"), _T("score"), tm, filePath);
}

