#include <string>
#include < memory >
#include "Hero.h"
#include "Utilities.h"

void Hero::Set_hp(const int x) {
	qhp = x;
}
void Hero::Set_block(const bool x) {
	qblock = x;
}
void Hero::Set_exp(int x) {
    qexp = x;
}
 int Hero::Get_hp() const{
	return qhp;
}
 int Hero::Get_max_hp() const {
     return qmaxhp;
 }

 bool Hero::Get_block() const {
	 return qblock;
 }
 int Hero::Get_exp() const {
     return qexp;
 }
 int Hero::Get_exp_max() const {
     return qexp_max;
 }
 int Hero::Get_exp_kill() const {
     return qexp_kill;
 }
 std::weak_ptr<Strike> Hero::Get_strike() const {
	 return qstrike;
 }

 int Hero::Get_type() const {
     return qtype;
 }

 Hero::Hero(int health, int exp_max, int exp_kill, int armour, int init, std::string name, int type,int team, std::pair<int, int> position)
     : qmaxhp(health),qhp(health),qblock(false), qexp_max(exp_max), qexp(0), qexp_kill(exp_kill), qarmour(armour), qinit(init),qname(name), qtype(type),qteam(team), qposition(position)
 {
    

 }

 int Hero::Get_init() const {
	 return qinit;
 }


 std::pair<int, int> Hero::Get_position() const {
     return qposition;
 }

 int Hero::Get_team() const {
     return qteam;
 }

std::string Hero::Get_name() const {
     return qname;
 }

 int Hero::Get_armour() const {
     return qarmour;
 }

 bool Hero::Is_alive() const {
     if (qhp > 0) return true;
     else return false;
 }



std::shared_ptr<Hero> Hero::Make(type hero_type, int team, int x, int y) {
     std::shared_ptr<Hero> result = nullptr;
     switch (hero_type)
     {
     case Hero::type::Peasant:
         
         result = std::make_shared<Hero>(25, 30, 10, 0, 10, "Peasant",1, team, std::make_pair(x,y));
         result->qstrike = std::make_shared<Strike>(10,Strike::attack_type::melee,1);
         break;

     case Hero::type::Archer:
         result = std::make_shared<Hero>(50, 100, 40, 0, 70, "Archer", 2, team, std::make_pair(x, y));
         result->qstrike = std::make_shared<Strike>(25, Strike::attack_type::ranged, 1);
         break;
        
     
     case Hero::type::Swordsman:

         result = std::make_shared<Hero>(100, 100, 40, 0, 50, "Swordsman", 3, team, std::make_pair(x, y));
         result->qstrike = std::make_shared<Strike>(25, Strike::attack_type::melee, 1);
         break;


     case Hero::type::Young_Mage:

         result = std::make_shared<Hero>(35, 100, 40, 0, 30,"Young_Mage",4, team, std::make_pair(x, y));
         result->qstrike = std::make_shared<Strike>(15, Strike::attack_type::ranged, 4);
         break;

     case Hero::type::Monk:

         result = std::make_shared<Hero>(30, 100, 40, 0, 0, "Monk", team,5, std::make_pair(x, y));
         result->qstrike = std::make_shared<Strike>(-20, Strike::attack_type::ranged, 1);
         break;
        

     case Hero::type::Bowman:

         result = std::make_shared<Hero>(75, 300, 100, 0, 80, "Bowman", 6, team, std::make_pair(x, y));
         result->qstrike = std::make_shared<Strike>(25, Strike::attack_type::ranged, 2);
         break;

     case Hero::type::Sniper:

         result = std::make_shared<Hero>(65, 300, 100, 0, 80, "Sniper", 7, team, std::make_pair(x, y));
         result->qstrike = std::make_shared<Strike>(65, Strike::attack_type::ranged, 1);
         break;

     case Hero::type::Knight:

         result = std::make_shared<Hero>(150, 300, 100, 10, 55, "Knight", 8, team, std::make_pair(x, y));
         result->qstrike = std::make_shared<Strike>(40, Strike::attack_type::melee, 1);
         break;

     case Hero::type::Berserk:

         result = std::make_shared<Hero>(100, 300, 100, 0, 65, "Berserk", 9, team, std::make_pair(x, y));
         result->qstrike = std::make_shared<Strike>(30, Strike::attack_type::melee, 2);
         break;

     case Hero::type::Inquisitor:

         result = std::make_shared<Hero>(150, 300, 100, 5, 60, "Inquisitor", 10, team, std::make_pair(x, y));
         result->qstrike = std::make_shared<Strike>(50, Strike::attack_type::melee, 1);
         break;

     case Hero::type::Sorcerer:

         result = std::make_shared<Hero>(45, 300, 100, 0, 40, "Sorcerer", 11, team, std::make_pair(x, y));
         result->qstrike = std::make_shared<Strike>(25, Strike::attack_type::ranged, 4);
         break;


     case Hero::type::Wizard:

         result = std::make_shared<Hero>(45, 300, 100, 0, 40, "Wizard", 12, team, std::make_pair(x, y));
         result->qstrike = std::make_shared<Strike>(80, Strike::attack_type::ranged, 1);
         break;

     case Hero::type::Temple_keeper:

         result = std::make_shared<Hero>(40, 300, 100, 0, 0, "Temple_keeper",13, team, std::make_pair(x, y));
         result->qstrike = std::make_shared<Strike>(-40, Strike::attack_type::ranged, 1);
         break;


     case Hero::type::Priest:

         result = std::make_shared<Hero>(50, 300, 100, 0, 0, "Priest",14, team, std::make_pair(x, y));
         result->qstrike = std::make_shared<Strike>(-20, Strike::attack_type::ranged, 4);
         break;
     }

     

     return result;
 }



std::shared_ptr<Hero> Hero::Level_UP(int exp){
   
    std::shared_ptr<Hero> result;
    result = std::make_shared<Hero>(*this); 
    result->Set_exp(result->Get_exp() + exp);
    std::cout << result->Get_name() <<
    " На позиции " << result->Get_position().first << " " << result->Get_position().second
    << " получил "<<exp <<" опыта" << std::endl << std::endl;
    if (result->Get_exp() < result->Get_exp_max()) return result;

    std::cout << result->Get_name() <<
    " Повысил уровень" <<std::endl << std::endl;

    int new_type;
    switch (result->Get_type())
    {
    case 1:
        std::cout << "Выберте путь развития " << std::endl << "1)Archer" << std::endl << "2)Swordsman" << std::endl << "3)Young_Mage" << std::endl << "4)Monk" << std::endl;
        new_type = get_int(1, 4);
        new_type += 1;
        break;

    case 2:
        std::cout << "Выберте путь развития " << std::endl << "1)Bowman" << std::endl << "2)Sniper" << std::endl ;
        new_type = get_int(1, 2);
        new_type += 5;
        break;

    case 3:
        std::cout << "Выберте путь развития " << std::endl << "1)Knight" << std::endl << "2)Berserk" << std::endl << "3)Inquisitor"<< std::endl;
        new_type = get_int(1, 3);
        new_type += 7;
        break;

    case 4:
        std::cout << "Выберте путь развития " << std::endl << "1)Sorcerer" << std::endl << "2)Wiizard" << std::endl;
        new_type = get_int(1, 2);
        new_type += 10;
        break;


    case 5:
        std::cout << "Выберте путь развития " << std::endl << "1)Temple_keeper" << std::endl << "2)Priest" << std::endl;
        new_type = get_int(1, 2);
        new_type += 12;
        break;
    default:
        std::cout << "Достигнут максимальный уровень!" << std::endl;
        new_type =0;
        break;
    }
    if(new_type==0) return result;
    result = Hero::Make(static_cast<Hero::type>(new_type), result->Get_team(), result->Get_position().first, result->Get_position().second);
    return result;
}