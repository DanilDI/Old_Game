#pragma once
#include < memory >
#include < vector >
#include < exception >
class Hero;
class Strike;
class Battlefield {
protected:
	Battlefield() = default;

	static Battlefield* qBattlefield;
public:
	~Battlefield() = default;
	Battlefield(Battlefield& other) = delete;
	
	void operator=(const Battlefield&) = delete;
	static Battlefield* Get_battlefield();
	static std::vector<std::weak_ptr<Hero> > Find_target(int x, int y) ;
	
	static std::vector<std::weak_ptr<Hero> > Get_turn_order();
	static void Battle_begin();
	static int Win_check();
	static int Alive_counter(int team);
	static std::shared_ptr<Hero> map[2][4];
	static void Kill(std::weak_ptr<Hero> h);
	static std::vector<std::weak_ptr<Hero> > Get_team(int team);

	static void Set_Hero(int x, int y, std::shared_ptr<Hero> h);

};


