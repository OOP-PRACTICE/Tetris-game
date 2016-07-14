#include "stdafx.h"
#include "Rule.h"
#include <mmsystem.h>

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
	LPCWSTR UPM = L".\\sound\\upgrade.wav";
	if (nLine / 2)					//��������������ȼ�����
	{
		m_nLevel++;
		sndPlaySound(UPM, SND_ASYNC);
		countline = 0;		// ��������
	}

	return m_nLevel;				//���ص�ǰ��Ϸ�ȼ�
}

bool CRule::Win(int Now[4][4], int Russia[100][100], CPoint NowPosition)
{
	LPCWSTR VM = L".\\sound\\victory.wav";
	LPCWSTR FM = L".\\sound\\fail.wav";
	if (m_nLevel == 11)			//��Ϸ�ȼ��������
	{							//����10����Ϸ����
		sndPlaySound(VM, SND_ASYNC);

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
					sndPlaySound(FM, SND_ASYNC);
					return true;	//��Ϸ����
				}
			}
		}
	}
	return false;					//��Ϸδ����
}
