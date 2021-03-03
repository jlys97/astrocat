#pragma once

void GameStateLevel1Load(void);
void GameStateLevel1Init(void);
void GameStateLevel1Update(void);
void GameStateLevel1Draw(void);
void GameStateLevel1Free(void);
void GameStateLevel1Unload(void);

enum : int
{
	wave1Enemies = 10,
	wave2Enemies = 20

};