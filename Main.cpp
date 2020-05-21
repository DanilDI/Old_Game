#include <string>
#include <iostream>
#include < memory >
#include < algorithm >
#include < vector >
#include < set >
#include "Hero.h"
#include "Strike.h"
#include "Battlefield.h"
#include "Utilities.h"
using namespace std;

int main(){
	setlocale(LC_ALL, "Russian");
	
	
	Battlefield::Battle_begin();
	int exp1 = 0, exp2 = 0, winner=0, round_counter=0;
	/*Бой*/
	while (true) {
		round_counter++;
		winner=Battlefield::Win_check();
		if (winner != 0) break;
		std::vector<std::weak_ptr<Hero> > order = Battlefield::Get_turn_order();
		cout << "Начался раунд " << round_counter << endl << endl;
		for (int i = 0; i < order.size(); i++) {
			std::shared_ptr<Hero> h = order[i].lock();
			if (h == nullptr) continue;
			/*Ход одного героя*/
				/*Выбор действия*/{
					cout << "Ходит " << h->Get_name() << " Игрока " << h->Get_team() <<
						" на позиции " << h->Get_position().first << " " << h->Get_position().second <<
						endl<<"Уровень здоровья "<< h->Get_hp() <<"/"<< h->Get_max_hp() <<endl<<
						endl << "Выберите действие:" << endl;

					if (h->Get_strike().lock()->Get_damage() > 0)
						cout << "1)Атакавать!" << endl;
					else
						cout << "1)Исцелять!" << endl;

					cout << "2)Защищаться" << endl;
				}
				std::cout << std::endl;
				int action = get_int(1,2);
				std::cout << std::endl;
				/*Блок*/
				if (action == 2) {
					h->Set_block(true);
					continue;
				}
				/*Атака*/
				h->Set_block(false);
				std::vector<std::weak_ptr<Hero> > targets = Battlefield::Find_target(h->Get_position().first, h->Get_position().second);
				set<int> num_of_targets;
				int nt = std::min((h->Get_strike()).lock()->Get_num_of_targets(),(int) targets.size());
				
				if (nt == 0) {
					winner = Battlefield::Win_check();
					if (winner != 0) {
						cout << "У вас не осталось доступных целей, битва окнчена!" << endl;
						break;
					}
					if (winner == 0) {
						cout << "Враг слишком далеко, вы защищаетесь" << endl;
						h->Set_block(true);
						continue;
					}
				}


				/*Выбор цели для атаки*/
				if (nt == 1) cout << "Выберите цель" << endl;
				else cout << "Выберите "<<nt<< " цели" << endl;
				for (int i = 0; i < targets.size(); i++) {
					cout << i + 1 << ") " << targets[i].lock()->Get_name() <<
						" На позиции " << targets[i].lock()->Get_position().first << " " << targets[i].lock()->Get_position().second
						<< endl << "Уровень здоровья " << targets[i].lock()->Get_hp() << "/" << targets[i].lock()->Get_max_hp() << endl;
				}
				while (nt != num_of_targets.size()) {
					int target = get_int(1, targets.size()+1);
					num_of_targets.insert(target-1);
				}
				for (auto i : num_of_targets) {
					bool dead = false;
					dead = h->Get_strike().lock()->Hit(targets[i]);
					if (dead == true) {
						if (h->Get_team() == 1) exp1 += targets[i].lock()->Get_exp_kill();
						if (h->Get_team() == 2) exp2 += targets[i].lock()->Get_exp_kill();

						Battlefield::Kill(targets[i]);
						
					}

				
			}
			

		}
	}
	
	/*Левелап*/
	{
		int exp;
		cout << "Победил игрок " << winner << "!" << endl << endl;
		if (winner == 1) exp = exp1;
		else exp = exp2;
		exp /= Battlefield::Alive_counter(winner);
		std::vector<std::weak_ptr<Hero> > survivers = Battlefield::Get_team(winner);
		for (auto i : survivers) {
			std::shared_ptr<Hero> h = i.lock();

			
			Battlefield::Set_Hero(h->Get_position().first, h->Get_position().second, h->Level_UP(exp));
		}

	}
}
