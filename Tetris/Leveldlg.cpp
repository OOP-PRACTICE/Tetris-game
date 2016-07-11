// Leveldlg.cpp : implementation file
//

#include "stdafx.h"
#include "Tetris.h"
#include "Leveldlg.h"
#include "afxdialogex.h"


// CLeveldlg dialog

IMPLEMENT_DYNAMIC(CLeveldlg, CDialogEx)

CLeveldlg::CLeveldlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GAME_LEVEL_DIALOG, pParent)
{
	m_level = 0;
}

CLeveldlg::~CLeveldlg()
{
}

void CLeveldlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_GAME_LEVEL_EDIT, m_level);
	DDV_MinMaxInt(pDX, m_level, 1, 10);
	DDX_Control(pDX, IDC_CHANGE_LEVEL_SPIN, m_level_spin);
}


BEGIN_MESSAGE_MAP(CLeveldlg, CDialogEx)
END_MESSAGE_MAP()


// CLeveldlg message handlers


BOOL CLeveldlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_level = 0;
	// 设置spin控件的调节范围
	m_level_spin.SetRange(1, 10);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
