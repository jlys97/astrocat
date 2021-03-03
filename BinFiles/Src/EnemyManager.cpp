#include "../Header/EnemyManager.h"

enemyStats& enemyInit(int h, int a, int ms, int d, int as, bool alive)
{
	// init enemy stats 
	enemyStats enemy;

	enemy.health = h;
	enemy.attack = a;
	enemy.movement_speed = ms;
	enemy.defense = d;
	enemy.attack_speed = as;
	enemy.alive = alive;

	return enemy;
}

void RemoveEnemy()
{
	// to-do: remove enemy from the map
}

int& reduceHealth(enemyStats& enemy, int amount)
{
	enemy.health -= amount;
	return enemy.health;
}

int& reduceDefense(enemyStats& enemy, int amount)
{
	enemy.defense -= amount;
	return enemy.defense;
}

int& ChangeSpeed(enemyStats& enemy, int amount)
{
	enemy.movement_speed += amount;
	return enemy.movement_speed;
}