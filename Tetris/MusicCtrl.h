#pragma once
#include "BaseWork.h"

class CMusicCtrl
{
public:
	BOOL m_switch;
	CBaseWork m_base;
public:
	void PlayMusic(LPCWSTR music_name, UINT setting);
	void OffMusic();
	CMusicCtrl();
	virtual ~CMusicCtrl();
};

