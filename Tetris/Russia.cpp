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

//消行处理
void CRussia::LineDelete()
{
	int m = 0;//连续消行的次数
	bool flag = 0;
	for (int i = 0; i < m_RowCount; i++)//检查是否消行
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
						Russia[k][l] = Russia[k - 1][l];//上行给下行
					}
				}
				for (int l = 0; l < m_ColCount; l++)
				{
					Russia[0][l] = 0;//第一行为0
				}
			}
		}
		DrawWill();//绘制将要出现的方块
		/**************************************************
		*
		*
		*
		*迟玉强
		*
		*
		***************************************************/


		end = rule.UpLevel(m_CountLine);


		/**************************************************
		*
		*
		*
		*迟玉强
		*
		*
		***************************************************/
		if (end)
		{
			AfxMessageBox(L"游戏结束!");
		}
	}
}

void CRussia::Move(int direction)
{
	if (end)//end为游戏结束Bool型
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
			LineDelete();//消除行
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

//旋转函数
//不能旋转返回false，反之返回true
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
			After[i][j] = 0;//初始化After全为0
		}
	}
	for (i = 0; i < 4;i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (tep[i][j] == 1)//判断当前位置是否有填充
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
			After[i - k][j - l] = tep[i][j];//变换后的矩阵移到左上角
		}
	}
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (After[i][j] == 0)//如果为空则继续插找
			{
				continue;
			}
			if(((p.x+i)>m_RowCount)||((p.y+j)<0)||((p.y+j)>m_ColCount))//p碰界判断
			{
				return false;//旋转失败
			}
			if (b[p.x + i][p.y + j] == 1)//碰其他方块
			{
				return false;//旋转失败
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
				switch (direction)//检测移动后是否发生越界
				{
				case KEY_LEFT:
					if ((p.y + j - 1) < 0)//出框
					{
						goto exit;
					}
					if (Russia[p.x + i][p.y + j - 1] == 1)//与已有方块碰撞
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
					if (!Change(a, p, Russia))//旋转失败则退出
					{
						goto exit;
					}
					for (i = 0; i < 4; i++)//方块改变样式
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
	//移动位置，重新给数组赋值
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
	for (i = 0; i<4; i++)//填充变换后的图形
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
	srand(GetTickCount());//初始化随机种子

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

	//实际设备对应逻辑坐标
	int tmp[4][4];//临时方块样式数组
	for (i = 0; i < 4; i++)//
	{
		for (j = 0; j < 4; j++)
		{
			tmp[i][j] = Will[j][3 - i];//把方块换个方向
		}
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (tmp[i][j] == 1)//选出最小填充坐标
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
			Will[i][j] = 0;//置零
		}
	}

	for (i = k; i < 4; i++)//将变换后的矩阵移到左上角
	{
		for (j = l; j < 4;j++)
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
	DrawScore(pDC);					//画分数、速度、难度

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
	//设置字体
	VERIFY(font.CreatePointFont(300, _T("Comic Sans MS")));
	
	pDC->SelectObject(&font);
	
	CString str;
	pDC->SetTextColor(RGB(39, 244, 10));	//设置字体颜色及背景颜色
	pDC->SetBkColor(RGB(255, 255, 0));
	
	str.Format(_T("%d"), m_Level);
	
	if (m_Level >= 0)
	{
		pDC->TextOut(420, 120, str);	//输出等级数字
	}
	str.Format(_T("%d"), m_CountLine);
	if (m_Speed >= 0)
	{
		pDC->TextOut(420, 64, str);		//输出消除行数
	}
	str.Format(_T("%d"), m_Score);
	if (m_Score >= 0)
	{
		pDC->TextOut(420, 2, str);		//输出分数
	}
	pDC->RestoreDC(nOldDC);
}

//开始游戏
void CRussia::GameStart()
{
	end = false;
	m_Score = 0;
	m_RowCount = 18;//初始化行数
	m_ColCount = 12;//初始化列数
	Count = 7;
	m_CountLine = 0;//初始化消去行数为0
	TCHAR pszTmp[128] = { 0 };

	GetPrivateProfileString(_T("SETUP"), _T("level"), _T("1"), pszTmp, 127, _T(".\\setup.ini"));//读取.ini文件，读取当前游戏等级

	m_Level = _wtoi(pszTmp);//TCHAR转为int，初始化等级
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
	DrawWill();//初始化的图形没有生成，所以调用俩次
	DrawWill();
}

void CRussia::HeroWrite()
{
}
