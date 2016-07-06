
// TetrisDoc.h : CTetrisDoc ��Ľӿ�
//


#pragma once


class CTetrisDoc : public CDocument
{
protected: // �������л�����
	CTetrisDoc();
	DECLARE_DYNCREATE(CTetrisDoc)

// ����
public:

// ����
public:
	void SetHeroData(CString name);		// �޸������ļ��е�Ӣ����Ϣ�����֣�
	void SetHeroData(int level, int score);		// �޸������ļ��е�Ӣ����Ϣ�����𡢷�����
	void SetHeroData(CString name, int level, int score);	// �޸������ļ��е�Ӣ����Ϣ
// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CTetrisDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
