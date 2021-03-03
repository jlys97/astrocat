#pragma once

enum
{
	// list of all game states 
	GS_LEVEL1 = 0,
	GS_LEVEL2,
	GS_LEVEL3,

	// special game state. Do not change
	GS_RESTART,
	GS_QUIT,
	GS_NONE,

	// menu states
	GS_MAINMENU, 
	GS_LEVELSELECT,
	GS_SETTINGS,
	GS_CREDITS,
	GS_HELP,
};