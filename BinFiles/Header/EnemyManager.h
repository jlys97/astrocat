#pragma once

#include "AEEngine.h"
#include "Math.h"

typedef struct
{
	int health;
	int attack;
	int movement_speed;
	int defense;
	int attack_speed;
	bool alive; // used to check if the enemy is alive or dead
} enemyStats;

enemyStats& enemyInit(int h = 100, int a = 50, int d = 100, int ms = 50, int as = 10, bool alive = true);
void RemoveEnemy();
int& reduceHealth(enemyStats& enemy, int amount);
int& reduceDefense(enemyStats& enemy, int amount);
int& ChangeSpeed(enemyStats& enemy, int amount);