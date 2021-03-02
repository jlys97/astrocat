#pragma once

enum TYPE_TOWER
{
	TYPE_TOWER_SHORTRANGE_SINGLE,    //0
	TYPE_TOWER_LONGRANGE_SINGLE,     //1
	TYPE_TOWER_AOE                   //2
};

struct ShortRangeTower
{
	int TowerHealth;
	int TowerDamage;
	float TowerAttackSpeed;
	float TowerShootingRange;
};

struct LongRangeTower
{
	int TowerHealth;
	int TowerDamage;
	float TowerAttackSpeed;
	float TowerShootingRange;
};

struct AOETower
{
	int TowerHealth;
	int TowerDamage;
	float TowerAttackSpeed;
	float TowerShootingRange;
};