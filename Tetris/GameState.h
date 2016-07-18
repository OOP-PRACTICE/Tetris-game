#pragma once
#include "stdafx.h"
#include "State.h"

class CGameState
{
public:
	BOOL main_menu;
	BOOL game_start;
	BOOL game_over;
public:

	CGameState()
		: main_menu(TRUE), game_start(FALSE), game_over(FALSE)
	{
	}
	int GetGameState()
	{
		if (main_menu)
		{
			return GMAE_MAIN_MENU;
		}
		else if (game_start)
		{
			if (game_over)
			{
				return GAME_OVER;
			}
			else
			{
				return GAME_START;
			}
		}

	}
	virtual ~CGameState()
	{
	}
};

