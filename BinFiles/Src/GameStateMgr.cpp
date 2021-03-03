#include "../Header/Main.h"

// ---------------------------------------------------------------------------
// globals

// variables to keep track the current, previous and next game state
unsigned int	gGameStateInit;
unsigned int	gGameStateCurr;
unsigned int	gGameStatePrev;
unsigned int	gGameStateNext;

// pointer to functions for game state life cycles functions
void (*GameStateLoad)() = 0;
void (*GameStateInit)() = 0;
void (*GameStateUpdate)() = 0;
void (*GameStateDraw)() = 0;
void (*GameStateFree)() = 0;
void (*GameStateUnload)() = 0;

/******************************************************************************/
/*!

*/
/******************************************************************************/
void GameStateMgrInit(unsigned int gameStateInit)
{
	// set the initial game state
	gGameStateInit = gameStateInit;

	// reset the current, previoud and next game
	gGameStateCurr =
		gGameStatePrev =
		gGameStateNext = gGameStateInit;

	// call the update to set the function pointers
	GameStateMgrUpdate();
}

/******************************************************************************/
/*!

*/
/******************************************************************************/
void GameStateMgrUpdate()
{
	if ((gGameStateCurr == GS_RESTART) || (gGameStateCurr == GS_QUIT))
		return;

	switch (gGameStateCurr)
	{
	case GS_MAINMENU:
		GameStateInit = GameStateMainMenuInit;
		GameStateDraw = GameStateMainMenuDraw;
		GameStateFree = GameStateMainMenuFree;
		GameStateLoad = GameStateMainMenuLoad;
		GameStateUnload = GameStateMainMenuUnload;
		GameStateUpdate = GameStateMainMenuUpdate;
		break;
	case GS_LEVELSELECT:
		GameStateInit = GameStateLevelSelectInit;
		GameStateDraw = GameStateLevelSelectDraw;
		GameStateFree = GameStateLevelSelectFree;
		GameStateLoad = GameStateLevelSelectLoad;
		GameStateUnload = GameStateLevelSelectUnload;
		GameStateUpdate = GameStateLevelSelectUpdate;
		break;
	case GS_LEVEL1:
		GameStateInit = GameStateLevel1Init;
		GameStateDraw = GameStateLevel1Draw;
		GameStateFree = GameStateLevel1Free;
		GameStateLoad = GameStateLevel1Load;
		GameStateUnload = GameStateLevel1Unload;
		GameStateUpdate = GameStateLevel1Update;
		break;
	case GS_SETTINGS:
		GameStateInit = GameStateSettingsInit;
		GameStateDraw = GameStateSettingsDraw;
		GameStateFree = GameStateSettingsFree;
		GameStateLoad = GameStateSettingsLoad;
		GameStateUnload = GameStateSettingsUnload;
		GameStateUpdate = GameStateSettingsUpdate;
		break;
	case GS_CREDITS:
		GameStateInit = GameStateCreditsInit;
		GameStateDraw = GameStateCreditsDraw;
		GameStateFree = GameStateCreditsFree;
		GameStateLoad = GameStateCreditsLoad;
		GameStateUnload = GameStateCreditsUnload;
		GameStateUpdate = GameStateCreditsUpdate;
		break;
	default:
		AE_FATAL_ERROR("invalid state!!");
	}
}
