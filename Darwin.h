#ifndef Darwin_h
#define Darwin_h

#include <vector>
#include <unordered_map>
#include <iostream>
#include <string>

using namespace std;


class InstructionSet {
	public:
		static unordered_map<string,int> map;
		InstructionSet();
};

class Species {
	private:
		static int id_count;
	public:
		vector<pair<int, int> > i;
		int id;
		char avatar; //'f' for food, 'h' for hopper, etc..
		Species();		
		Species(char);
		void add_instruction(string, int = 0);
		ostream& operator<<(const Species&);
};

class Creature {
	public:
		int pc;
		int _dir;		//0 for west, 1 for north, 2 for east, 3 for south
		Species _sp;
		bool done;
		bool empty;
		Creature();
		Creature(Species, int);
		pair<int, int> run();
};

class Game {
	private:
		vector<Creature> _creatures;
		int turn;
		int _xsize;		//horizontal size of the board
		int _ysize;		//vertical size of the board
	
	public:
		Game(int, int);
		bool add_creature(Creature, int, int);
		void step();
		bool perform(int, pair<int, int>);
		void print();
};

#endif
