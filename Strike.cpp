#include <string>
#include < memory >
#include < vector >
#include <iostream>
#include "Hero.h"
#include "Strike.h"


int Strike::Get_damage() const {
	return qdamage;
}

Strike::attack_type Strike::Get_type() const {
	return qtype;
}
int Strike::Get_num_of_targets() const {
	return qnum_of_targets;
}

bool Strike::Hit(std::weak_ptr<Hero> x) {
	int dam = this->Get_damage() ;
	std::shared_ptr<Hero>xx = x.lock();
	if (dam > 0) {
		if (xx->Get_block() == true) dam /= 2;
		dam -= (dam * xx->Get_armour() ) / 100;
		xx->Set_hp((xx->Get_hp() ) - dam);
		std::cout << "Нанесено " << dam << " урона вражескому "<<xx->Get_name()<<
			" на позиции " <<xx->Get_position().first << " " << xx->Get_position().second << std::endl<< std::endl;
		if (xx->Get_hp() <= 0) {
			std::cout << "Противник убит! " <<std::endl << std::endl;
			return true;
		}
	}
	else {
		xx->Set_hp((xx->Get_hp() ) - dam);
		std::cout<< xx->Get_name() <<" на позиции " << xx->Get_position().first << " " << xx->Get_position().second <<
			" исцелён на " << -dam << " очков здоровья" << std::endl << std::endl;
		if ((xx->Get_hp() ) >= (xx->Get_max_hp() )) {
			xx->Set_hp(xx->Get_max_hp() );
		}
	}
	return false;
}



Strike::Strike(int damage, attack_type type, int num_of_targets)
	:qdamage(damage), qtype(type), qnum_of_targets(num_of_targets)
{}
