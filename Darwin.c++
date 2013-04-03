#include <cassert>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <cstdlib>
#include "Darwin.h"

using namespace std;

unordered_map<string, int> InstructionSet::map;
int Species::id_count = 0;

InstructionSet::InstructionSet() {}

Species::Species() {
	id = id_count++;
	avatar = '.';
}
		
Species::Species(char a) {
	id = id_count++;
	avatar = a;
}

void Species::add_instruction(string ins, int arg) {
	i.push_back(pair<int, int>(InstructionSet::map[ins], arg));
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
	done = false;
	empty = false;
}

pair<int, int> Creature::run() {
	return _sp.i[pc];
}

Game::Game(int ysize, int xsize) {
	turn = 0;
	_creatures.resize(xsize*ysize);
	_xsize = xsize;
	_ysize = ysize;
}

bool Game::add_creature(Creature c, int y, int x) {
	//adds creature to the game at (x,y). returns false if fails
	if(!_creatures[x + y*_xsize].empty)
		return false;
	else {
		//add creature
		_creatures[x + y*_xsize] = c;
		return true;
	}
}

void Game::step() {
	//simulates a turn.
	pair<int, int> temp;
	++turn;
	for(int i = 0; i < _xsize*_ysize; ++i) {
		if(!_creatures[i].empty && !_creatures[i].done) {
			//retrieve instruction for the creature
			temp = _creatures[i].run();
			//execute command (or try to) for creature at position i
			while(!perform(i, temp)) {
				temp = _creatures[i].run();
			}
			//print();
		}
	}
	
	//undone everyone;
	for(int i = 0; i < _xsize*_ysize; ++i) {
		if(!_creatures[i].empty)
			_creatures[i].done = false;
	}
}

//returns true if an action is performed, false otherwise
bool Game::perform(int pos, pair<int, int> i) {
	//take an instruction and attempt to do it for the creature at position pos
	int arg = get<1>(i);
	int dir = _creatures[pos]._dir;
	int xpos = pos % _xsize;
	int ypos = pos / _xsize;
			
	//cout << _creatures[pos]._sp << " - " << get<0>(i) <<  endl;
	
	
	switch(get<0>(i)) {
		case 1:		//hop
			++_creatures[pos].pc;
			_creatures[pos].done = true;
			if(dir == 1) { //north
				if(ypos != 0) {			//if not at the north wall
					if(_creatures[pos - _xsize].empty) {	//if spot above is empty
						swap(_creatures[pos], _creatures[pos - _xsize]);
					}
				}
			}
			else if(dir == 2) {	//east
				if(xpos != _xsize-1) {	//if not at east wall
					if(_creatures[pos + 1].empty) {			//if spot to the right is empty
						swap(_creatures[pos], _creatures[pos+1]);
					}
				}
			}
			else if(dir == 3) {	//south		
				if(ypos != _ysize-1) {	//if not at south wall
					if(_creatures[pos + _xsize].empty) {	//if spot below is empty
						swap(_creatures[pos], _creatures[pos+_xsize]);
					}
				}
			}
			else if(dir == 0) {	//west
				if(xpos != 0) {			//if not at west wall
					if(_creatures[pos - 1].empty) {			//if spot to the left is empty
						swap(_creatures[pos], _creatures[pos-1]);
					}
				}				
			}
			return true;
		case 2:		//left
			++_creatures[pos].pc;
			_creatures[pos].done = true;
			if(dir == 0)
				_creatures[pos]._dir = 3;
			else
				_creatures[pos]._dir = dir - 1;
			return true;
		case 3:		//right
			++_creatures[pos].pc;
			_creatures[pos].done = true;
			_creatures[pos]._dir = (dir + 1) % 4;
			return true;
		case 4:		//infect
			//do stuff
			++_creatures[pos].pc;
			_creatures[pos].done = true;
			if(dir == 1) { //north
				if(ypos != 0) {			//if not at the north wall
					if(!_creatures[pos - _xsize].empty) {	//if spot above is not empty
						if(_creatures[pos - _xsize]._sp.id != _creatures[pos]._sp.id){
							_creatures[pos - _xsize]._sp = _creatures[pos]._sp;
							_creatures[pos - _xsize].pc = 0;
						}
					}
				}
			}
			else if(dir == 2) {	//east
				if(xpos != _xsize-1) {	//if not at east wall
					if(!_creatures[pos + 1].empty) {			//if spot to the right is not empty
						if(_creatures[pos + 1]._sp.id != _creatures[pos]._sp.id) {
							_creatures[pos + 1]._sp = _creatures[pos]._sp;
							_creatures[pos + 1].pc = 0;
						}
					}
				}
			}
			else if(dir == 3) {	//south		
				if(ypos != _ysize-1) {	//if not at south wall
					if(!_creatures[pos + _xsize].empty) {	//if spot below is not empty
						if(_creatures[pos + _xsize]._sp.id != _creatures[pos]._sp.id) {
							_creatures[pos + _xsize]._sp = _creatures[pos]._sp;
							_creatures[pos + _xsize].pc = 0;
						}
					}
				}
			}
			else if(dir == 0) {	//west
				if(xpos != 0) {			//if not at west wall
					if(!_creatures[pos - 1].empty) {			//if spot to the left is not empty
						if(_creatures[pos - 1]._sp.id != _creatures[pos]._sp.id) {
							_creatures[pos - 1]._sp = _creatures[pos]._sp;
							_creatures[pos - 1].pc = 0;
						}
					}
				}				
			}
			return true;
		case 5:		//if_empty
			if(dir == 1) { //north
				if(ypos != 0) {			//if not at the north wall
					if(_creatures[pos - _xsize].empty) {	//if spot above is empty
						_creatures[pos].pc = arg;
						return false;
					}
				}
			}
			else if(dir == 2) {	//east
				if(xpos != _xsize-1) {	//if not at east wall
					if(_creatures[pos + 1].empty) {			//if spot to the right is empty
						_creatures[pos].pc = arg;
						return false;
					}
				}
			}
			else if(dir == 3) {	//south		
				if(ypos != _ysize-1) {	//if not at south wall
					if(_creatures[pos + _xsize].empty) {	//if spot below is empty
						_creatures[pos].pc = arg;
						return false;
					}
				}
			}
			else if(dir == 0) {	//west
				if(xpos != 0) {			//if not at west wall
					if(_creatures[pos - 1].empty) {			//if spot to the left is empty
						_creatures[pos].pc = arg;
						return false;
					}
				}				
			}
			++_creatures[pos].pc;
			return false;
		case 6:		//if_wall
			if(dir == 1) { //north
				if(ypos == 0) {			//if at the north wall
					_creatures[pos].pc = arg;
					return false;
				}
			}
			else if(dir == 2) {	//east
				if(xpos != _xsize-1) {	//if at east wall
					_creatures[pos].pc = arg;
					return false;
				}
			}
			else if(dir == 3) {	//south		
				if(ypos != _ysize-1) {	//if at south wall
					_creatures[pos].pc = arg;
					return false;
				}
			}
			else if(dir == 0) {	//west
				if(xpos != 0) {			//if at west wall
					_creatures[pos].pc = arg;
					return false;
				}
			}
			++_creatures[pos].pc;
			return false;
		case 7:		//if_random
			if(rand() % 2 == 1)
				_creatures[pos].pc = arg;
			else
				++_creatures[pos].pc;
			return false;
		case 8:		//if_enemy
			//cout << "if_enemy lv.1" << endl;
			if(dir == 1) { //north
				if(ypos != 0) {			//if not at the north wall
					if(!_creatures[pos - _xsize].empty) {	//if spot above is not empty		
						if(_creatures[pos - _xsize]._sp.id != _creatures[pos]._sp.id) {	
							_creatures[pos].pc = arg;
							return false;
						}
					}
				}
			}
			else if(dir == 2) {	//east
				if(xpos != _xsize-1) {	//if not at east wall
					if(!_creatures[pos + 1].empty) {			//if spot to the right is not empty
						if(_creatures[pos + 1]._sp.id != _creatures[pos]._sp.id) {
							_creatures[pos].pc = arg;
							return false;
						}
					}
				}
			}
			else if(dir == 3) {	//south		
				if(ypos != _ysize-1) {	//if not at south wall
					if(!_creatures[pos + _xsize].empty) {	//if spot below is not empty
						if(_creatures[pos + _xsize]._sp.id != _creatures[pos]._sp.id) {
							_creatures[pos].pc = arg;
							return false;
						}
					}
				}
			}
			else if(dir == 0) {	//west
				if(xpos != 0) {			//if not at west wall
					if(!_creatures[pos - 1].empty) {			//if spot to the left is not empty
						if(_creatures[pos - 1]._sp.id != _creatures[pos]._sp.id) {
							_creatures[pos].pc = arg;
							return false;
						}
					}
				}				
			}
			++_creatures[pos].pc;
			return false;
		case 9:		//go
			_creatures[pos].pc = arg;
			return false;
		default:
			cout << "you shouldn't be here." << endl;
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


