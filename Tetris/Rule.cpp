#include "stdafx.h"
#include "Rule.h"
#include <mmsystem.h>
#include "resource.h"
CRule::CRule()
{
	m_nLevel = 1;
}


CRule::~CRule()
{
}

void CRule::SetLevel(int nLevel)
{
	m_nLevel = nLevel;
}

int CRule::UpLevel(int nLine, int &countline)
{
	if (nLine / 2)					//如果可以整除，等级升级
	{
		m_nLevel++;
		PlaySound((LPCTSTR)IDR_UPGRADE_WAVE, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
		countline = 0;		// 行数清零
	}

	return m_nLevel;				//返回当前游戏等级
}

bool CRule::Win(int Now[4][4], int Russia[100][100], CPoint NowPosition)
{
	if (m_nLevel == 11)			//游戏等级超过最高
	{							//超过10级游戏结束
		PlaySound((LPCTSTR)IDR_VICTORY_WAVE, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
		return true;
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (Now[i][j] == 1)
			{//到了顶点
				if (Russia[i + NowPosition.x][j + NowPosition.y] == 1)
				{
					PlaySound((LPCTSTR)IDR_FAIL_WAVE, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
					return true;	//游戏结束
				}
			}
		}
	}
	return false;					//游戏未结束
}
