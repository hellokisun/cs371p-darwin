// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2013
// Glenn P. Downing
// -----------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall RunDarwin.c++ -o RunDarwin
    % valgrind RunDarwin > RunDarwin.out

To configure Doxygen:
    doxygen -g
That creates the file Doxyfile.
Make the following edits:
    EXTRACT_ALL            = YES
    EXTRACT_PRIVATE        = YES
    EXTRACT_STATIC         = YES
    GENERATE_LATEX         = NO

To document the program:
    doxygen Doxyfile
*/

// --------
// includes
// --------

#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include <string>
#include "Darwin.h"

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    
    //building dictionary of instructions
    //Type		Code	Instruction	Description
	//Action	1		hop			If the space ahead is empty, move forward, otherwise, do nothing.
	//			2		left		Turn to face left.
	//			3		right		Turn to face right.
	//			4		infect		If the space ahead contains a creature of a different species, change that creature to be of your species, reset the program counter, but leave the direction unchanged, otherwise, do nothing.
	//Control	5		if_empty n	If the space ahead is empty, go to line n, otherwise, go to the next line.
	//			6		if_wall n	If the space ahead is a wall, go to line n, otherwise, go to the next line.
	//			7		if_random n	Randomly choose between going to line n or the next line. If rand() from <cstdlib> returns an odd number, go to line n. Call srand(0) at the start of every test case that uses rand().
	//			8		if_enemy n	If the space ahead contains a creature of a different species, go to line n, otherwise, go to the next line.
	//			9		go n		Go to line n.
	
	InstructionSet::mymap["hop"] = 1;
	InstructionSet::mymap["left"] = 2;
	InstructionSet::mymap["right"] = 3;
	InstructionSet::mymap["infect"] = 4;
	InstructionSet::mymap["if_empty"] = 5;
	InstructionSet::mymap["if_wall"] = 6;
	InstructionSet::mymap["if_random"] = 7;
	InstructionSet::mymap["if_enemy"] = 8;
	InstructionSet::mymap["go"] = 9;
	
	Species food('f');
	Species hopper('h');
	Species rover('r');
	Species trap('t');
	Species best('b');
	
	food.add_instruction("left");
	food.add_instruction("go", 0);
	
	hopper.add_instruction("hop");
	hopper.add_instruction("go", 0);
	
	rover.add_instruction("if_enemy", 9);
	rover.add_instruction("if_empty", 7);
	rover.add_instruction("if_random", 5);
	rover.add_instruction("left");
	rover.add_instruction("go", 0);
	rover.add_instruction("right");
	rover.add_instruction("go", 0);
	rover.add_instruction("hop");
	rover.add_instruction("go", 0);
	rover.add_instruction("infect");
	rover.add_instruction("go", 0);
	
	trap.add_instruction("if_enemy", 3);
	trap.add_instruction("left");
	trap.add_instruction("go", 0);
	trap.add_instruction("infect");
	trap.add_instruction("go", 0);
	
	best.add_instruction("if_enemy", 9);
	best.add_instruction("if_empty", 7);
	best.add_instruction("if_random", 5);
	best.add_instruction("left");
	best.add_instruction("go", 0);
	best.add_instruction("right");
	best.add_instruction("go", 0);
	best.add_instruction("hop");
	best.add_instruction("go", 0);
	best.add_instruction("infect");
	best.add_instruction("if_random", 5);
	best.add_instruction("if_empty", 7);
	best.add_instruction("if_random", 3);
	best.add_instruction("if_wall", 3);
	best.add_instruction("if_random", 5);
	best.add_instruction("if_wall", 5);
	best.add_instruction("if_random", 0);
	best.add_instruction("if_random", 2);
	best.add_instruction("if_random", 1);
	best.add_instruction("if_random", 5);
	best.add_instruction("if_random", 3);
	best.add_instruction("if_random", 4);
	best.add_instruction("go", 0);
	//~ 
	//~ best.add_instruction("if_enemy", 14);
	//~ best.add_instruction("if_empty", 13);
	//~ best.add_instruction("left");
	//~ best.add_instruction("go", 6);
	//~ best.add_instruction("hop");
	//~ best.add_instruction("if_enemy", 14);
	//~ best.add_instruction("if_wall", 20);
	//~ best.add_instruction("go", 0);
	//~ best.add_instruction("left");
	//~ best.add_instruction("infect");
	//~ best.add_instruction("left");
	//~ best.add_instruction("if_empty", 9);
	//~ best.add_instruction("infect");
	//~ best.add_instruction("hop");
	//~ best.add_instruction("if_empty", 12);
	//~ best.add_instruction("infect");
	//~ best.add_instruction("hop");
	//~ best.add_instruction("right");
	//~ best.add_instruction("if_empty", 16);
	//~ best.add_instruction("go", 0);
	//~ best.add_instruction("hop");
	//~ best.add_instruction("go", 0);
	//~ 
    // ----------
    // darwin 8x8
    // ----------

    try {
        cout << "*** Darwin 8x8 ***" << endl;
        /*
        8x8 Darwin
        Food,   facing east,  at (0, 0)
        Hopper, facing north, at (3, 3)
        Hopper, facing east,  at (3, 4)
        Hopper, facing south, at (4, 4)
        Hopper, facing west,  at (4, 3)
        Food,   facing north, at (7, 7)
        Simulate 5 moves.
        Print every grid.
        */
        
        Game game(8,8);
        Creature f1(food, 2);
        Creature h1(hopper, 1);
        Creature h2(hopper, 2);
        Creature h3(hopper, 3);
        Creature h4(hopper, 0);
        Creature f2(food, 1);
        game.add_creature(f1, 0, 0);
        game.add_creature(h1, 3, 3);
        game.add_creature(h2, 3, 4);
        game.add_creature(h3, 4, 4);
        game.add_creature(h4, 4, 3);
        game.add_creature(f2, 7, 7);
        game.print();
        for(int i = 0; i < 5; ++i) {
			game.step();
			game.print();
		}
	}
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 7x9
    // ----------

    try {
        cout << "*** Darwin 7x9 ***" << endl;
        srand(0);
        /*
        7x9 Darwin
        Trap,   facing south, at (0, 0)
        Hopper, facing east,  at (3, 2)
        Rover,  facing north, at (5, 4)
        Trap,   facing west,  at (6, 8)
        Simulate 5 moves.
        Print every grid.
        */
        
        Game game(7,9);
        Creature t1(trap, 3);
        Creature h1(hopper, 2);
        Creature r1(rover, 1);
        Creature t2(trap, 0);
        game.add_creature(t1, 0, 0);
        game.add_creature(h1, 3, 2);
        game.add_creature(r1, 5, 4);
        game.add_creature(t2, 6, 8);
        game.print();
        for(int i = 0; i < 5; ++i) {
			game.step();
			game.print();
		}
	}
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 72x72
    // without best
    // ------------

    try {
        cout << "*** Darwin 72x72 without Best ***" << endl;
        srand(0);
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 5184 (72x72), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature.
        10 Food
        10 Hopper
        10 Rover
        10 Trap
        Simulate 1000 moves.
        Print every 100th grid.
        */
        Game game(72,72);
        for(int i = 0; i < 10; ++i) {
			int pos = rand() % 5184;
			int dir = rand() % 4;
			Creature f(food, dir);
			while(!game.add_creature(f, pos/72, pos%72)){};		
		}
		for(int i = 0; i < 10; ++i) {
			int pos = rand() % 5184;
			int dir = rand() % 4;
			Creature h(hopper, dir);
			while(!game.add_creature(h, pos/72, pos%72)){};		
		}
		for(int i = 0; i < 10; ++i) {
			int pos = rand() % 5184;
			int dir = rand() % 4;
			Creature r(rover, dir);
			while(!game.add_creature(r, pos/72, pos%72)){};		
		}
		for(int i = 0; i < 10; ++i) {
			int pos = rand() % 5184;
			int dir = rand() % 4;
			Creature t(trap, dir);
			while(!game.add_creature(t, pos/72, pos%72)){};		
		}
		
        game.print();
        for(int j = 0; j < 10; ++j) {
			for(int i = 0; i < 100; ++i) {
				game.step();
			}
			game.print();
		}
	}
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 72x72
    // with best
    // ------------

    try {
        cout << "*** Darwin 72x72 with Best ***" << endl;
        srand(0);
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 5184 (72x72), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: 0:west, 1:north, 2:east, 3:south.
        Do that for each kind of creature.
        10 Food
        10 Hopper
        10 Rover
        10 Trap
        10 Best
        Simulate 1000 moves.
        Best MUST outnumber ALL other species for the bonus pts.
        Print every 100th grid.
        */
        Game game(72,72);
        for(int i = 0; i < 10; ++i) {
			int pos = rand() % 5184;
			int dir = rand() % 4;
			Creature f(food, dir);
			while(!game.add_creature(f, pos/72, pos%72)){};		
		}
		for(int i = 0; i < 10; ++i) {
			int pos = rand() % 5184;
			int dir = rand() % 4;
			Creature h(hopper, dir);
			while(!game.add_creature(h, pos/72, pos%72)){};		
		}
		for(int i = 0; i < 10; ++i) {
			int pos = rand() % 5184;
			int dir = rand() % 4;
			Creature r(rover, dir);
			while(!game.add_creature(r, pos/72, pos%72)){};		
		}
		for(int i = 0; i < 10; ++i) {
			int pos = rand() % 5184;
			int dir = rand() % 4;
			Creature t(trap, dir);
			while(!game.add_creature(t, pos/72, pos%72)){};		
		}
		for(int i = 0; i < 10; ++i) {
			int pos = rand() % 5184;
			int dir = rand() % 4;
			Creature b(best, dir);
			while(!game.add_creature(b, pos/72, pos%72)){};		
		}
		
        game.print();
        for(int j = 0; j < 10; ++j) {
			for(int i = 0; i < 100; ++i) {
				game.step();
			}
			game.print();
		}
	}
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}
