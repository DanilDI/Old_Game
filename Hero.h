#pragma once
#include <string>
#include < memory >
#include <iostream>
#include "Strike.h"


#define NUM_OF_TYPES 14
class Hero {
public:
	enum class type { Peasant = 1,  Archer = 2 ,Swordsman = 3
		, Young_Mage = 4, Monk = 5 ,Bowman=6,
		Sniper=7, Knight = 8, Berserk=9,
		Inquisitor=10, Sorcerer=11, Wizard=12,
		Temple_keeper= 13, Priest= 14 };
	void Set_hp(int x) ;
	void Set_block(bool x);
	void Set_exp(int x);


	int Get_hp() const;
	int Get_max_hp() const;

	bool Get_block() const;

	int Get_exp() const;
	int Get_exp_max() const;
	int Get_exp_kill() const;
	
	int Get_armour() const;

	int Get_init() const;
	
	std::string Get_name() const;
	int Get_type() const;
	
	int Get_team() const;

	std::pair<int, int> Get_position() const;
	bool Is_alive() const;
	std::weak_ptr<Strike> Get_strike() const;
	Hero(int health, int exp_max, int exp_kill, int armor, int init, std::string name, int type, int team, std::pair<int,int> position);
	~Hero() = default;

	static std::shared_ptr<Hero> Make(type hero_type, int team, int x, int y);
	std::shared_ptr<Hero> Level_UP(int exp);


	
private:
	

	int qhp;
	const int qmaxhp;
	
	bool qblock;

	int qexp;
	const int qexp_max;
	const int qexp_kill;

	const int qarmour;

	const int qinit;

	const std::string qname;
	const int qtype;
	const int qteam;
	std::pair<int, int> qposition;
	std::shared_ptr<Strike> qstrike;
};
/*
std::string Type_List[NUM_OF_TYPES]  = {
	   "Peasant" ,  "Archer" ,"Swordsman"
	   , "Young_Mage" , "Monk"  ,"Bowman",
	   "Sniper" , "Knight" , "Berserk" ,
	   "Inquisitor" , "Sorcerer" , "Wizard" ,
	   "Temple_keeper" , "Priest"
};
*/