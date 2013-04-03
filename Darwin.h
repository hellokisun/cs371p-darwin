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
		static int id_count;
		int _dir;
		int pc, _x, _y;
	public:
		Species _sp;
		bool on;
		int _id;
		Creature();
		Creature(Species, int, int, int);
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
