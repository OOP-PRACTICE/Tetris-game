#include "stdafx.h"
#include "Russia.h"
#include "Tetris.h"

CRussia::CRussia()
{
	//CDC dcMemory;
	//dcMemory.CreateCompatibleDC(pDC);
	bkMap.LoadBitmapW(IDB_BACKGROUND);
	fkMap.LoadBitmapW(IDB_DIAMOND);
}


CRussia::~CRussia()
{
}

//���д���
void CRussia::LineDelete()
{
	int m = 0;//�������еĴ���
	bool flag = 0;
	for (int i = 0; i < m_RowCount; i++)//����Ƿ�����
	{
		flag = true;
		for (int j = 0; j < m_ColCount; j++)
		{
			if (Russia[i][j] == 0)
			{
				flag = false;
			}
			if (flag == true)
			{
				m++;
				for (int k = i; k > 0; k--)
				{
					for (int l = 0; l < m_ColCount; l++)
					{
						Russia[k][l] = Russia[k - 1][l];//���и�����
					}
				}
				for (int l = 0; l < m_ColCount; l++)
				{
					Russia[0][l] = 0;//��һ��Ϊ0
				}
			}
		}
		DrawWill();//���ƽ�Ҫ���ֵķ���
		/**************************************************
		*
		*
		*
		*����ǿ
		*
		*
		***************************************************/


		end = rule.UpLevel(m_CountLine);


		/**************************************************
		*
		*
		*
		*����ǿ
		*
		*
		***************************************************/
		if (end)
		{
			AfxMessageBox(L"��Ϸ����!");
		}
	}
}

void CRussia::Move(int direction)
{
	if (end)//endΪ��Ϸ����Bool��
		return;
	switch (direction)
	{
	case KEY_LEFT:
		if (Meet(Now, KEY_LEFT, NowPosition))
		{break; }
		NowPosition.y--;
		break;
	case KEY_RIGHT:
		if(Meet(Now,KEY_RIGHT,NowPosition))
		{break; }
		NowPosition.y++;
		break;
	case KEY_DOWN:
		if (Meet(Now, KEY_DOWN, NowPosition))
		{
			LineDelete();//������
			break;
		}
		NowPosition.x++;
		break;
	case KEY_UP:
		Meet(Now, KEY_UP, NowPosition);
		break;
	default :
		break;
	}
}

//��ת����
//������ת����false����֮����true
bool CRussia::Change(int a[][4], CPoint p, int b[][100])
{
	int tep[4][4];
	int i, j;
	int k = 4, l = 4;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			tep[i][j] = a[j][3 - i];
			After[i][j] = 0;//��ʼ��AfterȫΪ0
		}
	}
	for (i = 0; i < 4;i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (tep[i][j] == 1)//�жϵ�ǰλ���Ƿ������
			{
				if (k > i)
					k = i;
				if (l > j)
					l = j;
			}
		}
	}
	for (i = k; i < 4; i++)
	{
		for (j = l; j < 4; j++)
		{
			After[i - k][j - l] = tep[i][j];//�任��ľ����Ƶ����Ͻ�
		}
	}
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (After[i][j] == 0)//���Ϊ�����������
			{
				continue;
			}
			if(((p.x+i)>m_RowCount)||((p.y+j)<0)||((p.y+j)>m_ColCount))//p�����ж�
			{
				return false;//��תʧ��
			}
			if (b[p.x + i][p.y + j] == 1)//����������
			{
				return false;//��תʧ��
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
				switch (direction)//����ƶ����Ƿ���Խ��
				{
				case KEY_LEFT:
					if ((p.y + j - 1) < 0)//����
					{
						goto exit;
					}
					if (Russia[p.x + i][p.y + j - 1] == 1)//�����з�����ײ
					{
						goto exit;
					}
					break;
				case KEY_RIGHT:
					if ((p.y + j + 1) >= m_ColCount)
					{
						goto exit;
					}
					if (Russia[p.x + i][p.y + j + 1] == 1)
					{
						goto exit;
					}
					break;
				case KEY_DOWN:
					if ((p.x + 1 + i) >= m_RowCount)
					{
						goto exit;
					}
					if (Russia[p.x + i + 1][p.y + j + 1] == 1)
					{
						goto exit;
					}
					break;
				case KEY_UP:
					if (!Change(a, p, Russia))//��תʧ�����˳�
					{
						goto exit;
					}
					for (i = 0; i < 4; i++)//����ı���ʽ
					{
						for (j = 0; j < 4; j++)
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
	case KEY_LEFT:
		y--; break;
	case KEY_RIGHT:
		y++; break;
	case KEY_DOWN:
		x++; break;
	case KEY_UP:
		break;
	}
	for (i = 0; i<4; i++)//���任���ͼ��
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

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			Now[i][j] = Will[i][j];
			Will[i][j] = 0;
		}
	}
	srand(GetTickCount());//��ʼ���������

	int nTemp = rand() % Count;
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
		Will[2][0] = 1;
		break;
	case 5:
		Will[0][0] = 1;
		Will[1][0] = 1;
		Will[1][1] = 1;
		Will[2][1] = 1;
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

	//ʵ���豸��Ӧ�߼�����
	int tmp[4][4];//��ʱ������ʽ����
	for (i = 0; i < 4; i++)//
	{
		for (j = 0; j < 4; j++)
		{
			tmp[i][j] = Will[j][3 - i];//�ѷ��黻������
		}
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (tmp[i][j] == 1)//ѡ����С�������
			{
				if (k > i)
					k = i;
				if (l > j)
					l = j;
			}
		}
	}
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			Will[i][j] = 0;//����
		}
	}

	for (i = k; i < 4; i++)//���任��ľ����Ƶ����Ͻ�
	{
		for (j = l; j < 4;j++)
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
	DrawScore(pDC);					//���������ٶȡ��Ѷ�

	for (int i = 0; i < m_RowCount; i++)
	{
		for (int j = 0; j < m_ColCount; j++)
		{
			if (Russia[i][j] == 1)
			{
				Dc.SelectObject(fkMap);
				pDC->BitBlt(j * 30, i * 30, (x / 10), (x / 10), &Dc, 0, 0, SRCCOPY);
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
			}
		}
	}
}

void CRussia::DrawScore(CDC * pDC)
{
	int nOldDC = pDC->SaveDC();
	CFont font;
	//��������
	VERIFY(font.CreatePointFont(300, _T("Comic Sans MS")));
	
	pDC->SelectObject(&font);
	
	CString str;
	pDC->SetTextColor(RGB(39, 244, 10));	//����������ɫ��������ɫ
	pDC->SetBkColor(RGB(255, 255, 0));
	
	str.Format(_T("%d"), m_Level);
	
	if (m_Level >= 0)
	{
		pDC->TextOut(420, 120, str);	//����ȼ�����
	}
	str.Format(_T("%d"), m_CountLine);
	if (m_Speed >= 0)
	{
		pDC->TextOut(420, 64, str);		//�����������
	}
	str.Format(_T("%d"), m_Score);
	if (m_Score >= 0)
	{
		pDC->TextOut(420, 2, str);		//�������
	}
	pDC->RestoreDC(nOldDC);
}

//��ʼ��Ϸ
void CRussia::GameStart()
{
	end = false;
	m_Score = 0;
	m_RowCount = 18;//��ʼ������
	m_ColCount = 12;//��ʼ������
	Count = 7;
	m_CountLine = 0;//��ʼ����ȥ����Ϊ0
	TCHAR pszTmp[128] = { 0 };

	GetPrivateProfileString(_T("SETUP"), _T("level"), _T("1"), pszTmp, 127, _T(".\\setup.ini"));//��ȡ.ini�ļ�����ȡ��ǰ��Ϸ�ȼ�

	m_Level = _wtoi(pszTmp);//TCHARתΪint����ʼ���ȼ�
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
	DrawWill();//��ʼ����ͼ��û�����ɣ����Ե�������
	DrawWill();
}

void CRussia::HeroWrite()
{
}
