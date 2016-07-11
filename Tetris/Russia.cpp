#include "stdafx.h"
#include "Russia.h"
#include "Tetris.h"
#include "Newrecdlg.h"
#include "GetNameDlg.h"

CRussia::CRussia()
{
	//CDC dcMemory;
	//dcMemory.CreateCompatibleDC(pDC);
	bkMap.LoadBitmapW(IDB_BKG);
	fkMap.LoadBitmapW(IDB_SQUARE);
	leftFrame.LoadBitmapW(IDB_LEFTCOL);
	topFrame.LoadBitmapW(IDB_TOP);
	bottomFrame.LoadBitmapW(IDB_BOTTOM);
	rightFrame.LoadBitmapW(IDB_RIGHTCOL);
	middleFrame.LoadBitmapW(IDB_MIDDLE);
	m_Level = 0;
}


CRussia::~CRussia()
{
}

//���д���
void CRussia::LineDelete()
{
	int m = 0;		//���ι���ȥ������
	bool flag = 0;
	for (int i = 0; i<m_RowCount; i++)//m_RowCount��
	{
		//���Ҫ��Ҫ����
		flag = true;
		for (int j = 1; j<m_ColCount; j++)
		{
			if (Russia[i][j] == 0)
			{
				flag = false;
			}
		}

		//���Ҫ
		if (flag == true)
		{
			m++;
			for (int k = i; k>0; k--)
			{
				//���и�����
				for (int l = 1; l<m_ColCount; l++)
				{
					Russia[k][l] = Russia[k - 1][l];
				}
			}
			//��һ��Ϊ��
			for (int l = 1; l<m_ColCount; l++)
			{
				Russia[0][l] = 0;
			}
		}
	}

	DrawWill();
	//�ӷ�
	switch (m)
	{
	case 1:
		m_Score = m_Score + 10 + m_Level * 10;
		break;
	case 2:
		m_Score = m_Score + 30 + m_Level * 10;
		break;
	case 3:
		m_Score = m_Score + 50 + m_Level * 10;
		break;
	case 4:
		m_Score = m_Score + 100 + m_Level * 10;
		break;
	default:
		break;
	}

	m_CountLine += m;

	m_Level = rule.UpLevel(m_CountLine, m_CountLine);
	

	end = rule.Win(Now, Russia, NowPosition);

	//�ٶ�
	m_Speed = 320 - m_Level * 20;

	if (end)
	{
		HeroWrite();
	}
}

void CRussia::Move(int direction)
{
	if (end) return;

	switch (direction)
	{
		//��
	case KEY_LEFT:
		if (Meet(Now, KEY_LEFT, NowPosition)) break;
		NowPosition.y--;
		break;
		//��
	case KEY_RIGHT:
		if (Meet(Now, KEY_RIGHT, NowPosition)) break;
		NowPosition.y++;
		break;
		//��
	case KEY_DOWN:
		if (Meet(Now, KEY_DOWN, NowPosition))
		{
			LineDelete();
			break;
		}
		NowPosition.x++;
		break;
		//��
	case KEY_UP:
		Meet(Now, KEY_UP, NowPosition);
		break;
	default:
		break;
	}
}

//��ת����
//������ת����false����֮����true
bool CRussia::Change(int a[][4], CPoint p, int b[][100])
{
	int tmp[4][4];
	int i, j;
	int k = 4, l = 4;

	for (i = 0; i<4; i++)
	{
		for (j = 0; j<4; j++)
		{
			tmp[i][j] = a[j][3 - i];
			After[i][j] = 0;	//��ű任��ķ������
		}
	}

	for (i = 0; i<4; i++)
	{
		for (j = 0; j<4; j++)
		{
			if (tmp[i][j] == 1)
			{
				if (k>i) k = i;
				if (l>j) l = j;
			}
		}
	}
	for (i = k; i<4; i++)
	{
		for (j = l; j<4; j++)
		{
			After[i - k][j - l] = tmp[i][j];
		}	//�ѱ任��ľ����Ƶ����Ͻ�
	}
	//�ж��Ƿ�Ӵ����ǣ�����ʧ��
	for (i = 0; i<4; i++)
	{
		for (j = 0; j<4; j++)
		{
			if (After[i][j] == 0)
			{
				continue;
			}
			if (((p.x + i) >= m_RowCount) || ((p.y + j)<0) || ((p.y + j) >= m_ColCount))
			{
				return false;
			}
			if (b[p.x + i][p.y + j] == 1)
			{
				return false;
			}
		}
	}
	return true;
}

//��ײ���
//����ײ����false����֮����true
bool CRussia::Meet(int a[][4], int direction, CPoint p)
{
	int i, j;
	//�Ȱ�ԭλ����0 
	for (i = 0; i<4; i++)
	{
		for (j = 0; j<4; j++)
		{
			if (a[i][j] == 1)
			{
				Russia[p.x + i][p.y + j] = 0;
			}
		}
	}

	for (i = 0; i<4; i++)
	{
		for (j = 0; j<4; j++)
		{
			if (a[i][j] == 1)
			{
				switch (direction)
				{
				case 1:	//����
					if ((p.y + j - 1)<1) goto exit;
					if (Russia[p.x + i][p.y + j - 1] == 1) goto exit;
					break;
				case 2://����
					if ((p.y + j + 1) >= m_ColCount) goto exit;
					if (Russia[p.x + i][p.y + j + 1] == 1) goto exit;
					break;
				case 3://����
					if ((p.x + i + 1) >= m_RowCount) goto exit;
					if (Russia[p.x + i + 1][p.y + j] == 1) goto exit;
					break;
				case 4://�任
					if (!Change(a, p, Russia)) goto exit;
					for (i = 0; i<4; i++)
					{
						for (j = 0; j<4; j++)
						{
							Now[i][j] = After[i][j];
							a[i][j] = Now[i][j];
						}
					}
					return false;
					break;
				}
			}
		}
	}

	int x, y;
	x = p.x;
	y = p.y;
	//�ƶ�λ�ã����¸����鸳ֵ
	switch (direction)
	{
	case 1:
		y--; break;
	case 2:
		y++; break;
	case 3:
		x++; break;
	case 4:
		break;
	}
	for (i = 0; i<4; i++)
	{
		for (j = 0; j<4; j++)
		{
			if (a[i][j] == 1)
			{
				Russia[x + i][y + j] = 1;
			}
		}
	}

	return false;
exit:
	for (i = 0; i<4; i++)
	{
		for (j = 0; j<4; j++)
		{
			if (a[i][j] == 1)
			{
				Russia[p.x + i][p.y + j] = 1;
			}
		}
	}
	return true;
}


void CRussia::DrawWill()
{
	int i, j;
	int k = 4, l = 4;

	//�ѽ�Ҫ���ֵķ������ǰ���飬���ѽ�Ҫ�������鸳ֵΪ��
	for (i = 0; i<4; i++)
	{
		for (j = 0; j<4; j++)
		{
			Now[i][j] = Will[i][j];
			Will[i][j] = 0;
		}
	}
	//��ʼ���漴������
	srand(GetTickCount());
	int nTemp = rand() % Count;
	//����ͼ��
	switch (nTemp)
	{
	case 0:
		Will[0][0] = 1;
		Will[0][1] = 1;
		Will[1][0] = 1;
		Will[1][1] = 1;
		break;
	case 1:
		Will[0][0] = 1;
		Will[0][1] = 1;
		Will[1][0] = 1;
		Will[2][0] = 1;
		break;
	case 2:
		Will[0][0] = 1;
		Will[0][1] = 1;
		Will[1][1] = 1;
		Will[2][1] = 1;
		break;
	case 3:
		Will[0][1] = 1;
		Will[1][0] = 1;
		Will[1][1] = 1;
		Will[2][0] = 1;
		break;
	case 4:
		Will[0][0] = 1;
		Will[1][0] = 1;
		Will[1][1] = 1;
		Will[2][1] = 1;
		break;
	case 5:
		Will[0][0] = 1;
		Will[1][0] = 1;
		Will[1][1] = 1;
		Will[2][0] = 1;
		break;
	case 6:
		Will[0][0] = 1;
		Will[1][0] = 1;
		Will[2][0] = 1;
		Will[3][0] = 1;
		break;
	default:
		break;
	}

	int tmp[4][4];
	for (i = 0; i<4; i++)
	{
		for (j = 0; j<4; j++)
		{
			tmp[i][j] = Will[j][3 - i];
		}
	}

	for (i = 0; i<4; i++)
	{
		for (j = 0; j<4; j++)
		{
			if (tmp[i][j] == 1)
			{
				if (k>i) k = i;
				if (l>j) l = j;
			}
		}
	}

	for (i = 0; i<4; i++)
	{
		for (j = 0; j<4; j++)
		{
			Will[i][j] = 0;
		}
	}
	//�ѱ任��ľ����Ƶ����Ͻ�
	for (i = k; i<4; i++)
	{
		for (j = l; j<4; j++)
		{
			Will[i - k][j - l] = tmp[i][j];
		}
	}
	//��ʼλ��
	NowPosition.x = 0;
	NowPosition.y = m_ColCount / 2;
}


void CRussia::DrawBK(CDC * pDC, CRect r)
{
	CDC Dc;
	int x, y;
	x = r.Width();
	y = r.Height();

	if (Dc.CreateCompatibleDC(pDC) == FALSE)//һ��CDC����,�������ǡ��ա���,û���豸����,CreateCompatibleDC���г�ʼ��
											//pDC=NULLʱ�ú�������һ����Ӧ�ó���ĵ�ǰ��ʾ�����ݵ��ڴ��豸�����Ļ�����
	{
		AfxMessageBox(L"Can't creat DC");
	}

	Dc.SelectObject(bkMap);
	pDC->BitBlt(0, 0, x, y, &Dc, 0, 0, SRCCOPY);//������,SRCCOPY��ֱ�Ӹ���ԭ�豸���߼��豸
	DrawScore(pDC);  // ���������ٶȡ��Ѷ�
	Dc.SelectObject(topFrame);//�ϱ߿�
	pDC->StretchBlt(0, 0, 29 * 20, 50, &Dc, 0, 0, 20, 30, SRCCOPY);
	Dc.SelectObject(bottomFrame);//�±߿�
	pDC->StretchBlt(0, y - 30, 29 * 20, 50, &Dc, 0, 0, 20, 30, SRCCOPY);
	Dc.SelectObject(leftFrame);//��߿�
	pDC->StretchBlt(0, 0, 32, y, &Dc, 0, 0, 15, 555, SRCCOPY);
	Dc.SelectObject(middleFrame);//�м�߿�
	pDC->StretchBlt(330, 20, 32, y, &Dc, 0, 0, 15, 567, SRCCOPY);
	Dc.SelectObject(rightFrame);//�ұ߿�
	pDC->StretchBlt(570, 0, 32, y, &Dc, 0, 0, 15, 555, SRCCOPY);
	//pDC->BitBlt(40, 0, x, y, &Dc, 0, 0, SRCCOPY);
	for (int i = 0; i < m_RowCount; i++) 
	{
		for (int j = 0; j < m_ColCount; j++)
		{
			if (Russia[i][j] == 1)
			{
				Dc.SelectObject(fkMap);
				pDC->BitBlt(j * 30, i * 30, 30, 30, &Dc, 0, 0, SRCCOPY);
			}
		}
	}
	for (int n = 0; n < 4; n++)
	{
		for (int m = 0; m < 4; m++)
		{
			if (Will[n][m] == 1)
			{
				Dc.SelectObject(fkMap);
				pDC->BitBlt(365 + m * 30, 240 + n * 30,
					30 * ((x + y) / 1090), 30 * ((x + y) / 1090), &Dc, 0, 0, SRCCOPY);
			}
		}
	}
}

void CRussia::DrawScore(CDC * pDC)
{
	int nOldDC = pDC->SaveDC();
	CFont font;
	// ���÷�����λ��
	int scoreYpos = 145, scoreXpos = 410;
	// �����ʾ
	pDC->TextOut(scoreXpos - 50, scoreYpos, _T("�ȼ�:"));
	pDC->TextOut(scoreXpos - 50, scoreYpos - 60, _T("����:"));
	pDC->TextOut(scoreXpos - 50, scoreYpos - 120, _T("�÷�:"));
	//��������
	VERIFY(font.CreatePointFont(300, _T("Comic Sans MS")));

	pDC->SelectObject(&font);
	
	CString str;
	pDC->SetTextColor(RGB(39, 244, 10));	//����������ɫ��������ɫ
	pDC->SetBkColor(RGB(255, 255, 0));

	str.Format(_T("%d"), m_Level);

	if (m_Level >= 0)
	{
		pDC->TextOut(scoreXpos, scoreYpos, str);	//����ȼ�����
	}
	str.Format(_T("%d"), m_CountLine);
	if (m_Speed >= 0)
	{
		pDC->TextOut(scoreXpos, scoreYpos - 60, str);		//�����������
	}
	str.Format(_T("%d"), m_Score);
	if (m_Score >= 0)
	{
		pDC->TextOut(scoreXpos, scoreYpos - 120, str);		//�������
	}
	pDC->RestoreDC(nOldDC);
}

//��ʼ��Ϸ
void CRussia::GameStart()
{

	end = false;
	m_Score = 0;
	m_RowCount = 20;//��ʼ������
	m_ColCount = 11;//��ʼ������
	Count = 7;
	m_CountLine = 0;//��ʼ����ȥ����Ϊ0
	TCHAR pszTmp[128] = { 0 };

	GetPrivateProfileString(_T("SETUP"), _T("level"), _T("1"), pszTmp, 127, _T(".\\setup.ini"));//��ȡ.ini�ļ�����ȡ��ǰ��Ϸ�ȼ�

	m_Level = _wtoi(pszTmp);// TCHARתΪint����ʼ���ȼ�
	m_Speed = 320 - m_Level * 20;//��ʼ���ٶ�

	for (int i = 0; i < m_RowCount; i++)//��ʼ������
	{
		for (int j = 0; j < m_ColCount; j++)
		{
			Russia[i][j] = 0;
		}
	}
	for (int i = 0; i < 4; i++)//��ʼ��ͼ��
	{
		for (int j = 0; j < 4; j++)
		{
			Now[i][j] = 0;
			Will[i][j] = 0;
		}
	}
	DrawWill();		// ��ʼ����ͼ��û�����ɣ����Ե�������
	DrawWill();
}

void CRussia::HeroWrite()
{
	/*CNewrecdlg newdlg;
	
	newdlg.DoModal();
	newdlg.ShowHeroData(m_Level, m_Score);*/
	
}