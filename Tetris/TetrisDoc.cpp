
// TetrisDoc.cpp : CTetrisDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Tetris.h"
#endif

#include "TetrisDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CTetrisDoc

IMPLEMENT_DYNCREATE(CTetrisDoc, CDocument)

BEGIN_MESSAGE_MAP(CTetrisDoc, CDocument)
END_MESSAGE_MAP()


// CTetrisDoc ����/����

CTetrisDoc::CTetrisDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CTetrisDoc::~CTetrisDoc()
{
}

void CTetrisDoc::SetHeroData(CString name)
{
	WritePrivateProfileString((LPCWSTR)"HERO", (LPCWSTR)"name", name, (LPCWSTR)".\\config\\setup.ini");
}

void CTetrisDoc::SetHeroData(int level, int score)
{
	CString tm;
	tm.Format(_T("%d"), level);
	WritePrivateProfileString((LPCWSTR)"HERO", (LPCWSTR)"level", tm, (LPCWSTR)".\\config\\setup.ini");
	tm.Format(_T("%d"), score);
	WritePrivateProfileString((LPCWSTR)"HERO", (LPCWSTR)"score", tm, (LPCWSTR)".\\config\\setup.ini");
}

void CTetrisDoc::SetHeroData(CString name, int level, int score)
{
	CString tm;
	WritePrivateProfileString((LPCWSTR)"HERO", (LPCWSTR)"name", name, (LPCWSTR)".\\config\\setup.ini");
	tm.Format(_T("%d"), level);
	WritePrivateProfileString((LPCWSTR)"HERO", (LPCWSTR)"level", tm, (LPCWSTR)".\\config\\setup.ini");
	tm.Format(_T("%d"), score);
	WritePrivateProfileString((LPCWSTR)"HERO", (LPCWSTR)"score", tm, (LPCWSTR)".\\config\\setup.ini");
}

BOOL CTetrisDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CTetrisDoc ���л�

void CTetrisDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CTetrisDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CTetrisDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CTetrisDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CTetrisDoc ���

#ifdef _DEBUG
void CTetrisDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTetrisDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTetrisDoc ����
