#include "../Header/Main.h"
#include"../Header/EnemyManager.h"

/******************************************************************************/
/*!
\brief
	This function serves as the "Load" function of this state
*/
/******************************************************************************/
void GameStateLevel1Load()
{

}

/******************************************************************************/
/*!
\brief
	This function serves as the "Initialize" function of this state
*/
/******************************************************************************/
void GameStateLevel1Init()
{
	// tentative enemy initialisation
	enemyStats enemies[wave1Enemies];

	for (int i = 0; i < wave1Enemies; ++i)
	{
		enemies[i] = enemyInit();
	}
}

/******************************************************************************/
/*!
\brief
	This function serves as the "Update" function of this state
*/
/******************************************************************************/
void GameStateLevel1Update()
{

}

/******************************************************************************/
/*!
\brief
	This function serves as the "Draw" function of this state
*/
/******************************************************************************/
void GameStateLevel1Draw()
{
	char buffer[1024];
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	sprintf_s(buffer, "LEVEL 1");
	AEGfxPrint(font, buffer, -0.1f, 0, 1.25f, 255, 255, 255);


	AEGfxSetBlendMode(AE_GFX_BM_NONE);

}

/******************************************************************************/
/*!
\brief
	This function serves as the "Free" function of this state
*/
/******************************************************************************/
void GameStateLevel1Free()
{

}

/******************************************************************************/
/*!
\brief
	This function serves as the "Unload" function of this state
*/
/******************************************************************************/
void GameStateLevel1Unload()
{

}