#pragma once

//��ֹ���ظ�����
#ifndef _RUSSIA_H_ 
#define _RUSSIA_H_
#include "Rule.h"
#define KEY_LEFT 1 
#define KEY_RIGHT 2
#define KEY_DOWN 3
#define KEY_UP 4

class CRussia
{
public:

	int Russia[100][100];
	int Now[4][4];//����ͼ��
	int Will[4][4];//�¸�ͼ��
	int After[4][4];
	CPoint NowPosition;//��ǰͼ�����Ͻ�����
	int Count;//ͼ���������
	bool end;  //������Ϸ������־
	int m_Level;
	int m_Speed;
	int m_Score;
	int m_CountLine;
	int m_RowCount;
	int m_ColCount;
	CBitmap fkMap;
	CBitmap bkMap;
	CBitmap leftFrame;
	CBitmap topFrame;
	CBitmap bottomFrame;
	CBitmap rightFrame;
	CBitmap middleFrame;
	CRule rule;

	CRussia();
	~CRussia();
	//ɾ����
	void LineDelete();
	//�����ƶ�
	void Move(int direction);
	//�ı䷽�����
	bool Change(int a[][4], CPoint p, int b[][100]);
	//��ײ���
	bool Meet(int a[][4], int direction, CPoint p);
	//���Ʒ���ͼ
	void DrawWill();
	//���ƽ���
	void DrawBK(CDC*pDC, CRect r);
	//���Ʒ���
	void DrawScore(CDC*pDC);
	//��ʼ��Ϸ
	void GameStart();
	//Ӣ�۰��ж�
	void HeroWrite();
};

#endif