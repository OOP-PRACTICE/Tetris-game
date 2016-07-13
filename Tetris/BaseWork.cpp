#include "stdafx.h"
#include "BaseWork.h"


CBaseWork::CBaseWork()
{
}

CString CBaseWork::GetExePath(CString filename)
{
	TCHAR fullPath[MAX_PATH];
	GetModuleFileName(NULL, fullPath, 100);
	CString strPath = (CString)fullPath;
	int position = strPath.ReverseFind('\\'); //反向查找"\"所在的位置
	strPath = strPath.Left(position) + _T("\\");
	CString setupFilePath = strPath + filename;

	return setupFilePath;
}


CBaseWork::~CBaseWork()
{
}
