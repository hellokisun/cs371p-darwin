#include <cassert>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include "Darwin.h"

using namespace std;

unordered_map<string, int> InstructionSet::map;

InstructionSet::InstructionSet() {}

void InstructionSet::add(string ins, int code) {
	map[ins] = code;
}

Species::Species() {
	avatar = '.';
}
		
Species::Species(char a) {
	avatar = a;
}

bool Species::execute(int n) {
	
	return true;
}

void Species::add_instruction(int ins, int arg = 0) {
	i.push_back(pair<int, int>(ins, arg));
}

ostream& operator<<(ostream &o, const Species &s) {
  return o << s.avatar;
}

Creature::Creature() {
	pc = 0;
	empty = true;
}

Creature::Creature(Species sp, int dir) {
	pc = 0;
	_sp = sp;
	_dir = dir;
	empty = false;
}

void Creature::run() {
	_sp.execute(pc);
}

Game::Game(int xsize, int ysize) {
	turn = 0;
	_creatures.resize(xsize*ysize);
	_xsize = xsize;
	_ysize = ysize;
}

bool Game::add_creature(Creature c, int x, int y) {
	//adds creature to the game at (x,y). returns false if fails
	if(!_creatures[x + y*_xsize].empty)
		return false;
	else {
		//add creature
		_creatures[x + y*_xsize] = c;
		return true;
	}
}

void Game::print() {
	//print turn number
	cout << "Turn = " << turn << "." << endl;
	//print column numbers
	cout << "  ";
	for(int i = 0; i < _xsize; ++i) {
		cout << i%10;
	}
	cout << endl;
	
	for(int i = 0; i < _ysize; ++i) {
		cout << i%10 << " ";
		//print the row
		for(int j = 0; j < _xsize; ++j) {
			cout << _creatures[i*_xsize + j]._sp;
		}
		cout << endl;
	}
	
	cout << endl;
}


