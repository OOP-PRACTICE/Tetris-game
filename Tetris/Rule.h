#pragma once

#ifndef __RULE_H__
#define __RULE_H__

class CRule
{
public:
	CRule();
	~CRule();
	void SetLevel(int nLevel);//���õȼ�
	int UpLevel(int nLine, int &countline);//�����ж�
	bool Win(int Now[4][4], int Russia[100][100], CPoint NowPosition);//ʤ���ж�

private:
	int m_nLevel;//��ǰ�ȼ�
};

#endif
