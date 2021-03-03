#include "../Header/Main.h"

/******************************************************************************/
/*!
\brief
	This function serves as the "Load" function of this state
*/
/******************************************************************************/
void GameStateCreditsLoad()
{
}

/******************************************************************************/
/*!
\brief
	This function serves as the "Initialize" function of this state
*/
/******************************************************************************/
void GameStateCreditsInit()
{
	currTag = 0;
}

/******************************************************************************/
/*!
\brief
	This function serves as the "Update" function of this state
*/
/******************************************************************************/
void GameStateCreditsUpdate()
{

}

/******************************************************************************/
/*!
\brief
	This function serves as the "Draw" function of this state
*/
/******************************************************************************/
void GameStateCreditsDraw()
{
	char buffer[1024];
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	sprintf_s(buffer, "CREDITS");
	AEGfxPrint(font, buffer, -0.1f, 0, 1.25f, 255, 255, 255);


	AEGfxSetBlendMode(AE_GFX_BM_NONE);

}

/******************************************************************************/
/*!
\brief
	This function serves as the "Free" function of this state
*/
/******************************************************************************/
void GameStateCreditsFree()
{

}

/******************************************************************************/
/*!
\brief
	This function serves as the "Unload" function of this state
*/
/******************************************************************************/
void GameStateCreditsUnload()
{

}