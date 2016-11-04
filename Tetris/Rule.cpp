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
	if (nLine / 2)					//��������������ȼ�����
	{
		m_nLevel++;
		PlaySound((LPCTSTR)IDR_UPGRADE_WAVE, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
		countline = 0;		// ��������
	}

	return m_nLevel;				//���ص�ǰ��Ϸ�ȼ�
}

bool CRule::Win(int Now[4][4], int Russia[100][100], CPoint NowPosition)
{
	if (m_nLevel == 11)			//��Ϸ�ȼ��������
	{							//����10����Ϸ����
		PlaySound((LPCTSTR)IDR_VICTORY_WAVE, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
		return true;
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (Now[i][j] == 1)
			{//���˶���
				if (Russia[i + NowPosition.x][j + NowPosition.y] == 1)
				{
					PlaySound((LPCTSTR)IDR_FAIL_WAVE, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
					return true;	//��Ϸ����
				}
			}
		}
	}
	return false;					//��Ϸδ����
}
