
// Tetris.h : Tetris Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CTetrisApp:
// �йش����ʵ�֣������ Tetris.cpp
//

class CTetrisApp : public CWinApp
{
public:
	CTetrisApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTetrisApp theApp;
