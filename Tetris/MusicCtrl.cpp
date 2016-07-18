#include "stdafx.h"
#include "MusicCtrl.h"
#include "Mmsystem.h"

void CMusicCtrl::PlayMusic(LPCWSTR music_name, UINT setting)
{
	CString filePath, musicPath;
	filePath = m_base.GetExePath(_T("\sound\\"));
	musicPath = filePath + music_name;
	if (!m_switch)
	{
		sndPlaySound(musicPath, setting);
	}
}

void CMusicCtrl::OffMusic()
{
	if (m_switch)
	{

	}
}


CMusicCtrl::CMusicCtrl()
{
}


CMusicCtrl::~CMusicCtrl()
{
}
