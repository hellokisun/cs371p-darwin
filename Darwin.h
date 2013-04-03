#ifndef Darwin_h
#define Darwin_h

#include <vector>
#include <unordered_map>
#include <iostream>
#include <string>

using namespace std;

// --------------
// InstructionSet
// --------------
/**
 * A container that has the types of instruction within. Uses the 
 * unordered_map with the string value of the instruction for the key
 * and integer representation of the instruction for the value.
 */
class InstructionSet {
	public:
		static unordered_map<string,int> mymap;
};

// -------
// Species
// -------
class Species {
	private:
		static int id_count;
	public:
		vector<pair<int, int> > i;
		int id;
		char avatar; //'f' for food, 'h' for hopper, etc..
		/**
		 * Default constructor.
		 */
		Species();
		
		/**
		 * Constructor.
		 * @param	a	avatar for the Species object.
		 */
		Species(char a);
		
		/**
		 * Adds an instruction to this Specie's instruction list. Stores
		 * the instructions inside a vector in forms of a pair of ints,
		 * where the 	first element 	is the instruction code, and
		 * 				second element 	is the argument for control flow
		 * 								instructions.
		 * Vector index is equivalent to the line number of instructions
		 * @param	ins		string representation of the instruction to 
		 * 					be added
		 * @param	arg		argument for the instruction (optional).
		 * @return	bool	returns	true if a valid instruction was passed.
		 * 							false if the string argument is not
		 * 							a key in the InstructionSet.
		 */
		bool add_instruction(string ins, int arg = 0);
		
		/**
		 * << operator for printing. Sends the avatar to ostream.
		 * @param &s	the Species to print the avatar of.
		 */
		ostream& operator<<(const Species &s);
};

// --------
// Creature
// --------
class Creature {
	public:
		int pc;
		int _dir;		//0 for west, 1 for north, 2 for east, 3 for south
		Species _sp;
		bool done;
		bool empty;
		/**
		 * Default constructor.
		 */
		Creature();
		
		/**
		 * Constructor.
		 * @param	sp	Species for this Creature.
		 * @param	dir	Direction for this Creature.	
		 * 				0 = west	1 = north
		 * 				2 = south	3 = west
		 */
		Creature(Species sp, int dir);
		
		/**
		 * Gets the instruction pair corresponding to this Creature's pc
		 * @return	pair<int, int>	pair of integers (code, argument)
		 */
		pair<int, int> run();
};

// ----
// Game
// ----
class Game {
	private:
		vector<Creature> _creatures;
		int _xsize;		//horizontal size of the board
		int _ysize;		//vertical size of the board
	
	public:
		int turn;
		/**
		 * Constructor. Creates a game board with given size.
		 * @param	ysize	number of rows for the game.
		 * @param	xsize	number of columns for the game.
		 */
		Game(int ysize, int xsize);
		
		/**
		 * Attempt to add a creature to a board.
		 * @param	c		Creature to be added to the board
		 * @param	y		y-coordinates for the Creature
		 * @param	x		x-coordinates for the Creature
		 * @return	bool	returns true if the creature is successfully 
		 * 					added to the board (no overlap).
		 * 					returns false if coordinates are invalid or
		 * 					if something already occupies the space.
		 */
		bool add_creature(Creature c, int y, int x);
		
		/**
		 * Simulates a turn for the game.
		 */
		void step();
		
		/**
		 * Performs the action for a Creature on the board.
		 * @param	pos		location of the Creature
		 * @param	i		instruction pair (code, arg)
		 * @return	bool	returns false if a control flow operation
		 * 					returns true if an action operation
		 */
		bool perform(int pos, pair<int, int> i);
		
		/**
		 * Prints the game board to cout.
		 */
		void print();
};

#endif
