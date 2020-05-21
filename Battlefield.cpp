
#include < memory >
#include < vector >
#include <iostream>
#include < algorithm >
#include "Hero.h"

#include "Battlefield.h"
#include "Utilities.h"
std::shared_ptr<Hero> Battlefield::map[2][4];
Battlefield* Battlefield::qBattlefield;
Battlefield* Battlefield::Get_battlefield() {
	if (qBattlefield == nullptr) {
		qBattlefield = new Battlefield();
	}
	return  qBattlefield;
}






 std::vector<std::weak_ptr<Hero> > Battlefield::Find_target(int x, int y)  {
	std::vector<std::weak_ptr<Hero> > result;
	std::shared_ptr<Hero> h=Battlefield::map[x][y];
	if ((h->Get_strike()).lock()->Get_type() == Strike::attack_type::ranged) {
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 4; j++) {
				if (map[i][j] != nullptr) {
					if ((h->Get_strike().lock()->Get_damage() > 0) && (h->Get_team() != map[i][j]->Get_team())) {
						result.push_back(map[i][j]);
					}
					if ((h->Get_strike().lock()->Get_damage() < 0) && (h->Get_team() == map[i][j]->Get_team())) {
						result.push_back(map[i][j]);
					}
				}

			}
	}

	if ((h->Get_strike()).lock()->Get_type() == Strike::attack_type::melee) {
		int xx = h->Get_position().first;
		int yy = h->Get_position().second;
		switch (yy) {
		case 0:
			if (map[0][1] == nullptr && map[1][1] == nullptr) {
				if(map[0][2]!=nullptr) result.push_back(map[0][2]);
				if (map[1][2] != nullptr) result.push_back(map[1][2]);
				if (result.size() == 0) {
					if (map[0][3] != nullptr) result.push_back(map[0][3]);
					if (map[1][3] != nullptr) result.push_back(map[1][3]);
				}
			}
			
			break;

		case 1:
			
				if (map[0][2] != nullptr) result.push_back(map[0][2]);
				if (map[1][2] != nullptr) result.push_back(map[1][2]);
				if (result.size() == 0) {
					if (map[0][3] != nullptr) result.push_back(map[0][3]);
					if (map[1][3] != nullptr) result.push_back(map[1][3]);
				
			}

			break;


		case 2:
			if (map[0][1] != nullptr) result.push_back(map[0][1]);
			if (map[1][1] != nullptr) result.push_back(map[1][1]);
			if (result.size() == 0) {
				if (map[0][0] != nullptr) result.push_back(map[0][0]);
				if (map[1][0] != nullptr) result.push_back(map[1][0]);
			}
			break;


		case 3:
			if (map[0][2] == nullptr && map[1][2] == nullptr) {
				if (map[0][1] != nullptr) result.push_back(map[0][1]);
				if (map[1][1] != nullptr) result.push_back(map[1][1]);
				if (result.size() == 0) {
					if (map[0][0] != nullptr) result.push_back(map[0][0]);
					if (map[1][0] != nullptr) result.push_back(map[1][0]);
				}
			}

			break;
		}
		
		

	}


	return result;

}

 bool comp(const std::weak_ptr<Hero> a, const std::weak_ptr<Hero> b) {
	 std::shared_ptr<Hero> aa = a.lock();
	 std::shared_ptr<Hero> bb = b.lock();
	 return(aa->Get_init() < bb->Get_init());
 }

 std::vector<std::weak_ptr<Hero>> Battlefield::Get_turn_order()
 {
	 std::vector<std::weak_ptr<Hero>> order;
	 for (int i = 0; i < 2; i++)
		 for (int j = 0; j < 4; j++)
			 if(map[i][j]!=nullptr) order.push_back(map[i][j]);
	
	 std::sort(order.begin(), order.end(), comp);
	 return order;
 }

 void Battlefield::Battle_begin() {
	setlocale(LC_ALL, "Russian");
	Get_battlefield();
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 4; j++)
			map[i][j] = nullptr;
	std::cout << "Фараза размещения игрока 1" << std::endl << std::endl;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			std::cout << "Разместите героя на позиции " << i << " " << j << std::endl;
			
			std::cout << "1)Peasan" << std::endl << "2)Swordsman" << std::endl << "3)Archer" << std::endl << "4)Young_mage" << std::endl <<
				"5)Monk" << std::endl << "6)Bowman" << std::endl << "7)Sniper" << std::endl << "8)Knight" << std::endl <<
				"9)Berserk" << std::endl << "10)Inquisitor" << std::endl << "11)Sorcerer" << std::endl << "12)Wizard" << std::endl
				<< "13)Temple_keeper" << std::endl << "14)Priest" << std::endl;
			
			std::cout << std::endl;
			int type = get_int(1, NUM_OF_TYPES);
			std::cout << std::endl;
			map[i][j] = Hero::Make(static_cast< Hero::type>(type), 1, i, j);
			
		}
	}
	std::cout << "Фараза размещения игрока 2" << std::endl << std::endl;
	for (int i = 0; i < 2; i++) {
		for (int j = 2; j < 4; j++) {
			std::cout << "Разместите героя на позиции " << i << " " << j << std::endl;
			std::cout << "1)Peasan" << std::endl << "2)Swordsman" << std::endl << "3)Archer" << std::endl << "4)Young_mage" << std::endl <<
				"5)Monk" << std::endl << "6)Bowman" << std::endl << "7)Sniper" << std::endl << "8)Knight" << std::endl <<
				"9)Berserk" << std::endl << "10)Inquisitor" << std::endl << "11)Sorcerer" << std::endl << "12)Wizard" << std::endl
				<< "13)Temple_keeper" << std::endl << "14)Priest" << std::endl;
			std::cout << std::endl;
			int type = get_int(1, NUM_OF_TYPES);
			std::cout << std::endl;
			
			map[i][j] = Hero::Make(static_cast<Hero::type>(type), 2, i, j);
			
		}
	}
}

 void Battlefield::Kill(std::weak_ptr<Hero> h){
	 map[h.lock()->Get_position().first][h.lock()->Get_position().second] = nullptr;

 }


 int Battlefield::Win_check(){
	 if (Alive_counter(1) == 0) return 2;
	 if (Alive_counter(2) == 0) return 1;
	 return 0;
 }

 int Battlefield::Alive_counter(int team) {
	 int result = 0;
	 for (int i = 0; i < 2; i++)
		 for (int j = 0; j < 4; j++) 
			 if (map[i][j] != nullptr)
				 if (map[i][j]->Get_team() == team) result++;
	 return result;

 }

 std::vector<std::weak_ptr<Hero>> Battlefield::Get_team(int team){
	 std::vector<std::weak_ptr<Hero>> result;
	 for (int i = 0; i < 2; i++)
		 for (int j = 0; j < 4; j++)
			 if (map[i][j] != nullptr)
				 if (map[i][j]->Get_team() == team)
					 result.push_back(map[i][j]);

	 return result;
 }

 void Battlefield::Set_Hero(int x, int y, std::shared_ptr<Hero> h) {
	 map[x][y] = h;
 }