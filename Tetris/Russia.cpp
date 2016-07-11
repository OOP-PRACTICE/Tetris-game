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

//消行处理
void CRussia::LineDelete()
{
	int m = 0;		//本次共消去的行数
	bool flag = 0;
	for (int i = 0; i<m_RowCount; i++)//m_RowCount行
	{
		//检查要不要消行
		flag = true;
		for (int j = 1; j<m_ColCount; j++)
		{
			if (Russia[i][j] == 0)
			{
				flag = false;
			}
		}

		//如果要
		if (flag == true)
		{
			m++;
			for (int k = i; k>0; k--)
			{
				//上行给下行
				for (int l = 1; l<m_ColCount; l++)
				{
					Russia[k][l] = Russia[k - 1][l];
				}
			}
			//第一行为零
			for (int l = 1; l<m_ColCount; l++)
			{
				Russia[0][l] = 0;
			}
		}
	}

	DrawWill();
	//加分
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

	//速度
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
		//左
	case KEY_LEFT:
		if (Meet(Now, KEY_LEFT, NowPosition)) break;
		NowPosition.y--;
		break;
		//右
	case KEY_RIGHT:
		if (Meet(Now, KEY_RIGHT, NowPosition)) break;
		NowPosition.y++;
		break;
		//下
	case KEY_DOWN:
		if (Meet(Now, KEY_DOWN, NowPosition))
		{
			LineDelete();
			break;
		}
		NowPosition.x++;
		break;
		//上
	case KEY_UP:
		Meet(Now, KEY_UP, NowPosition);
		break;
	default:
		break;
	}
}

//旋转函数
//不能旋转返回false，反之返回true
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
			After[i][j] = 0;	//存放变换后的方块矩阵
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
		}	//把变换后的矩阵移到左上角
	}
	//判断是否接触，是：返回失败
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

//碰撞检测
//无碰撞返回false，反之返回true
bool CRussia::Meet(int a[][4], int direction, CPoint p)
{
	int i, j;
	//先把原位置清0 
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
				case 1:	//左移
					if ((p.y + j - 1)<1) goto exit;
					if (Russia[p.x + i][p.y + j - 1] == 1) goto exit;
					break;
				case 2://右移
					if ((p.y + j + 1) >= m_ColCount) goto exit;
					if (Russia[p.x + i][p.y + j + 1] == 1) goto exit;
					break;
				case 3://下移
					if ((p.x + i + 1) >= m_RowCount) goto exit;
					if (Russia[p.x + i + 1][p.y + j] == 1) goto exit;
					break;
				case 4://变换
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
	//移动位置，重新给数组赋值
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

	//把将要出现的方块给当前数组，并把将要出现数组赋值为零
	for (i = 0; i<4; i++)
	{
		for (j = 0; j<4; j++)
		{
			Now[i][j] = Will[i][j];
			Will[i][j] = 0;
		}
	}
	//初始化随即数种子
	srand(GetTickCount());
	int nTemp = rand() % Count;
	//各种图形
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
	//把变换后的矩阵移到左上角
	for (i = k; i<4; i++)
	{
		for (j = l; j<4; j++)
		{
			Will[i - k][j - l] = tmp[i][j];
		}
	}
	//开始位置
	NowPosition.x = 0;
	NowPosition.y = m_ColCount / 2;
}


void CRussia::DrawBK(CDC * pDC, CRect r)
{
	CDC Dc;
	int x, y;
	x = r.Width();
	y = r.Height();

	if (Dc.CreateCompatibleDC(pDC) == FALSE)//一个CDC对象,声明后是“空”的,没有设备属性,CreateCompatibleDC进行初始化
											//pDC=NULL时该函数创建一个与应用程序的当前显示器兼容的内存设备上下文环境。
	{
		AfxMessageBox(L"Can't creat DC");
	}

	Dc.SelectObject(bkMap);
	pDC->BitBlt(0, 0, x, y, &Dc, 0, 0, SRCCOPY);//画背景,SRCCOPY是直接复制原设备到逻辑设备
	DrawScore(pDC);  // 画分数、速度、难度
	Dc.SelectObject(topFrame);//上边框
	pDC->StretchBlt(0, 0, 29 * 20, 50, &Dc, 0, 0, 20, 30, SRCCOPY);
	Dc.SelectObject(bottomFrame);//下边框
	pDC->StretchBlt(0, y - 30, 29 * 20, 50, &Dc, 0, 0, 20, 30, SRCCOPY);
	Dc.SelectObject(leftFrame);//左边框
	pDC->StretchBlt(0, 0, 32, y, &Dc, 0, 0, 15, 555, SRCCOPY);
	Dc.SelectObject(middleFrame);//中间边框
	pDC->StretchBlt(330, 20, 32, y, &Dc, 0, 0, 15, 567, SRCCOPY);
	Dc.SelectObject(rightFrame);//右边框
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
	// 设置分数的位置
	int scoreYpos = 145, scoreXpos = 410;
	// 输出提示
	pDC->TextOut(scoreXpos - 50, scoreYpos, _T("等级:"));
	pDC->TextOut(scoreXpos - 50, scoreYpos - 60, _T("行数:"));
	pDC->TextOut(scoreXpos - 50, scoreYpos - 120, _T("得分:"));
	//设置字体
	VERIFY(font.CreatePointFont(300, _T("Comic Sans MS")));

	pDC->SelectObject(&font);
	
	CString str;
	pDC->SetTextColor(RGB(39, 244, 10));	//设置字体颜色及背景颜色
	pDC->SetBkColor(RGB(255, 255, 0));

	str.Format(_T("%d"), m_Level);

	if (m_Level >= 0)
	{
		pDC->TextOut(scoreXpos, scoreYpos, str);	//输出等级数字
	}
	str.Format(_T("%d"), m_CountLine);
	if (m_Speed >= 0)
	{
		pDC->TextOut(scoreXpos, scoreYpos - 60, str);		//输出消除行数
	}
	str.Format(_T("%d"), m_Score);
	if (m_Score >= 0)
	{
		pDC->TextOut(scoreXpos, scoreYpos - 120, str);		//输出分数
	}
	pDC->RestoreDC(nOldDC);
}

//开始游戏
void CRussia::GameStart()
{

	end = false;
	m_Score = 0;
	m_RowCount = 20;//初始化行数
	m_ColCount = 11;//初始化列数
	Count = 7;
	m_CountLine = 0;//初始化消去行数为0
	TCHAR pszTmp[128] = { 0 };

	GetPrivateProfileString(_T("SETUP"), _T("level"), _T("1"), pszTmp, 127, _T(".\\setup.ini"));//读取.ini文件，读取当前游戏等级

	m_Level = _wtoi(pszTmp);// TCHAR转为int，初始化等级
	m_Speed = 320 - m_Level * 20;//初始化速度

	for (int i = 0; i < m_RowCount; i++)//初始化界面
	{
		for (int j = 0; j < m_ColCount; j++)
		{
			Russia[i][j] = 0;
		}
	}
	for (int i = 0; i < 4; i++)//初始化图形
	{
		for (int j = 0; j < 4; j++)
		{
			Now[i][j] = 0;
			Will[i][j] = 0;
		}
	}
	DrawWill();		// 初始化的图形没有生成，所以调用俩次
	DrawWill();
}

void CRussia::HeroWrite()
{
	/*CNewrecdlg newdlg;
	
	newdlg.DoModal();
	newdlg.ShowHeroData(m_Level, m_Score);*/
	
}