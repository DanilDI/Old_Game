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
	/*���*/
	while (true) {
		round_counter++;
		winner=Battlefield::Win_check();
		if (winner != 0) break;
		std::vector<std::weak_ptr<Hero> > order = Battlefield::Get_turn_order();
		cout << "������� ����� " << round_counter << endl << endl;
		for (int i = 0; i < order.size(); i++) {
			std::shared_ptr<Hero> h = order[i].lock();
			if (h == nullptr) continue;
			/*��� ������ �����*/
				/*����� ��������*/{
					cout << "����� " << h->Get_name() << " ������ " << h->Get_team() <<
						" �� ������� " << h->Get_position().first << " " << h->Get_position().second <<
						endl<<"������� �������� "<< h->Get_hp() <<"/"<< h->Get_max_hp() <<endl<<
						endl << "�������� ��������:" << endl;

					if (h->Get_strike().lock()->Get_damage() > 0)
						cout << "1)���������!" << endl;
					else
						cout << "1)��������!" << endl;

					cout << "2)����������" << endl;
				}
				std::cout << std::endl;
				int action = get_int(1,2);
				std::cout << std::endl;
				/*����*/
				if (action == 2) {
					h->Set_block(true);
					continue;
				}
				/*�����*/
				h->Set_block(false);
				std::vector<std::weak_ptr<Hero> > targets = Battlefield::Find_target(h->Get_position().first, h->Get_position().second);
				set<int> num_of_targets;
				int nt = std::min((h->Get_strike()).lock()->Get_num_of_targets(),(int) targets.size());
				
				if (nt == 0) {
					winner = Battlefield::Win_check();
					if (winner != 0) {
						cout << "� ��� �� �������� ��������� �����, ����� �������!" << endl;
						break;
					}
					if (winner == 0) {
						cout << "���� ������� ������, �� �����������" << endl;
						h->Set_block(true);
						continue;
					}
				}


				/*����� ���� ��� �����*/
				if (nt == 1) cout << "�������� ����" << endl;
				else cout << "�������� "<<nt<< " ����" << endl;
				for (int i = 0; i < targets.size(); i++) {
					cout << i + 1 << ") " << targets[i].lock()->Get_name() <<
						" �� ������� " << targets[i].lock()->Get_position().first << " " << targets[i].lock()->Get_position().second
						<< endl << "������� �������� " << targets[i].lock()->Get_hp() << "/" << targets[i].lock()->Get_max_hp() << endl;
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
	
	/*�������*/
	{
		int exp;
		cout << "������� ����� " << winner << "!" << endl << endl;
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
