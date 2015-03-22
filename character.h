//final project		character.h	3/3/15	Author: Kurt Davis

#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>

class character: public entity{
	public:
		virtual void render();

	private:
		int level;
};
