#pragma once

enum
{
	PLAY = 0,
	LEVEL,
	SETTINGS,
	CREDITS,
	HELP,
	QUIT

};

static bool firstTime = true;
static bool firstUnload = true;

static int currTag;

void GameStateMainMenuLoad(void);
void GameStateMainMenuInit(void);
void GameStateMainMenuUpdate(void);
void GameStateMainMenuDraw(void);
void GameStateMainMenuFree(void);
void GameStateMainMenuUnload(void);

void RenderButton(float f, AEGfxTexture* tex, AEGfxVertexList* mesh);