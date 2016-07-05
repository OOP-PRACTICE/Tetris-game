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
	m_bWriteflg = FALSE;
}

CHeroDlg::~CHeroDlg()
{
}

void CHeroDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LEVEL_EDIT, m_level);
	DDX_Text(pDX, IDC_NAME_EDIT, m_name);
	DDX_Text(pDX, IDC_SCORE_EDIT, m_score);
	DDV_MinMaxInt(pDX, m_score, 0, 10000);
}


BEGIN_MESSAGE_MAP(CHeroDlg, CDialogEx)
END_MESSAGE_MAP()


// CHeroDlg message handlers
