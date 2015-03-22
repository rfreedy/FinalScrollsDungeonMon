//final project		entity.h	3/3/15	Author: Kurt Davis

#ifndef ENTITY_H
#define ENTITY_H

#include<iostream>
using namespace std;

class entity{
	public:
		entity();
		~entity();
		virtual void render() = 0;

	private:
		int isVisible;
};
