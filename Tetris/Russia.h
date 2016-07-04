#pragma once

//防止被重复引用
#ifndef _RUSSIA_H_ 
#define _RUSSIA_H_

#define KEY_LEFT 1 
#define KEY_RIGHT 2
#define KEY_DOWN 3
#define KEY_UP 4

class CRussia
{
public:
	
	int Russia[100][100];
	int Now[4][4];//现在图形
	int Will[4][4];//下个图形
	int After[4][4];
	CPoint NowPosition;//当前图形左上角坐标
	int Count;//图形形状
	bool end;  //用于游戏结束标志
	int m_Level;
	int m_Speed;
	int m_Score;
	int m_CountLine;
	int m_RowCount;
	int m_ColCount;
	CBitmap fkMap;
	CBitmap bkMap;

	CRussia();
	~CRussia();
	//删除行
	void LineDelete();
	//方块移动
	void Move(int direction);
	//改变方块放向
	bool Chang(int a[][4], CPoint p, int b[][100]);
	//碰撞检测
	bool Meet(int a[][4], int direction, CPoint p);
	//绘制方块图
	void DrawWill();
	//绘制界面
	void DrawBK(CDC*pDC);
	//绘制分数
	void DrawScore(CDC*pDC);
	//开始游戏
	void GameStart();
	//英雄榜判断
	void HeroWrite();
};

#endif