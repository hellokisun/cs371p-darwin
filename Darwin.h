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
		static void add(string, int);
};

class Species {
	private:
		vector<pair<int, int> > i;
	public:
		char avatar; //'f' for food, 'h' for hopper, etc..
		Species();		
		Species(char);		
		bool execute(int);		
		void add_instruction(int, int);
		ostream& operator<<(const Species&);
};

class Creature {
	private:
		int _dir;		//0 for north, 1 for east, 2 for south, 3 for west
		int pc;
	public:
		Species _sp;
		bool empty;
		Creature();
		Creature(Species, int);
		void run();
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
		void print();
};

#endif
