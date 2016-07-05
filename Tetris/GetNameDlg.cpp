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
END_MESSAGE_MAP()


// CGetNameDlg message handlers
