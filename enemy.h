//Final project
//Enemy.h

#include <iostream>
using namespace std;

class Enemy: public entity{
	public:
		Enemy();	//constructor
		~Enemy();	//deconstructor
		virtual void render();	//implementation of pure virtual
	private:
		stat_type stats;	//creates structure for stats (health, mana,stamina)
		skill_type skills;	//structure for skills (atk, def, power)
		
};
