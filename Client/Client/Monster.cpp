#include "Monster.h"
#include "CSVFile.h"
#include "Audio.h"
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

CMonster::CMonster()
{
	//m_nType = 0;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

CMonster::~CMonster()
{

}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CMonster::setType(unsigned long uType)
{
	m_uType = uType;
	// ----
	CCsvFile csv(MONSTER_CVS_PATCH);
	// ----
	csv.seek(uType);
	// ----
	const char* szName			= csv.getStr("name","000000");
	const char* szModelFilename	= csv.getStr("model","000000");
	// ----
	float fScale				= csv.getFloat("scale",1.0f);
	// ----
	setRoleName(s2ws(szName).c_str());
	// ----
	load(szModelFilename);
	// ----
	setScale(Vec3D(fScale,fScale,fScale));
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void playMonsterSound(unsigned long uType, const char* szName)
{
	/*for (int i=0; i<10; ++i)
	{
		//CCsvFile csv("Data\\CSV\\MonsterV.csv");
		//csv.seek(uType);
	}*/

	CCsvFile csv(MONSTER_CVS_PATCH);
	// ----
	csv.seek(uType);
	// ----
	GetAudio().playSound(csv.getStr(szName,""));
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CMonster::frameMoveRole(const Matrix& mWorld, double fTime, float fElapsedTime)
{
	float fSoundIdleTime = 10.0f;
	// ----
	if(m_uActionState == WALK||m_uActionState == RUN)
	{
		// ----
		if(fElapsedTime < fSoundIdleTime)
		{
			if(rand() % (int)(fSoundIdleTime / fElapsedTime) == 0)
			{
				playMonsterSound(m_uType,"soundIdle");
			}
		}
	}
	// ----
	CRole::frameMoveRole(mWorld, fTime, fElapsedTime);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CMonster::setActionState(unsigned char uActionState)
{
	m_uActionState=uActionState;
	// ----
	switch(m_uActionState)
	{
		case STAND:
		{
			setAnimByName("0");
		}
		break;

		case WALK:
		case RUN:
		{
			setAnimByName("2");
		}
		break;

		case HIT1:
		{
			playMonsterSound(m_uType,"soundAttack");
			// ----
			setAnimByName("3");
		}
		break;

		case DIE:
		{
			playMonsterSound(m_uType,"soundDie");
			// ----
			setAnimByName("6");
		}
		break;
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------