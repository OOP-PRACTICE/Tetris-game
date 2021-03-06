// GetNameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Tetris.h"
#include "GetNameDlg.h"
#include "afxdialogex.h"


// CGetNameDlg dialog

IMPLEMENT_DYNAMIC(CGetNameDlg, CDialogEx)

CGetNameDlg::CGetNameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HERONAME_GET, pParent)
{

}

CGetNameDlg::~CGetNameDlg()
{
}

void CGetNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_GETNAME_EDIT, m_getname);
}


BEGIN_MESSAGE_MAP(CGetNameDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CGetNameDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CGetNameDlg message handlers

void CGetNameDlg::OnBnClickedOk()
{
	// 设置英雄姓名，并更新配置文件
	SetHeroData(m_getname);
	CDialogEx::OnOK();
}

void CGetNameDlg::SetHeroData(CString name)
{
	CString filePath;
	filePath = baseWork.GetExePath(_T("\config\\setup.ini"));
	WritePrivateProfileString(_T("HERO"), _T("name"), name, filePath);
}