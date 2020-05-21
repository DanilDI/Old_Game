#pragma once

#include < memory >

#include <vector>
class Hero;

class Strike {
public:
	
	enum class attack_type { melee = 1, ranged = 2 };

	
	int Get_damage() const;
	attack_type Get_type() const;
	int Get_num_of_targets() const;
	bool Hit(std::weak_ptr<Hero> x);

	
	Strike(int damage, attack_type type, int num__of_targets);
	~Strike() = default;

private:
	
	const int qdamage;
	const attack_type qtype;
	const int qnum_of_targets;
	

};