#pragma once

// ---------------------------------------------------------------------------
// includes

#include "AEEngine.h"
#include "Math.h"

#include "GameStates.h"
#include "GameStateMgr.h"
#include "GameStateMainMenu.h"
#include <iostream>
#include <fstream>
#include "Map.h"

//------------------------------------
// Macros

#define WIN_HEIGHT 900
#define WIN_WIDTH 1600

//------------------------------------
// Globals

extern float	g_dt;
extern double	g_appTime;

extern s8 font;

typedef struct
{
	int x;
	int y;
} mPos;

extern mPos mousePos;

void MainFreeUnload();

