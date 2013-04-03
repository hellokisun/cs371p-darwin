// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Darwin.h"

// -----------
// TestDarwin
// -----------

struct TestDarwin : CppUnit::TestFixture {
	
	void test_set_1() {
		InstructionSet::mymap["a"] = 1;
        CPPUNIT_ASSERT(InstructionSet::mymap["a"] == 1);
	}
	void test_set_2() {
		InstructionSet::mymap["a"] = 2;
        CPPUNIT_ASSERT(InstructionSet::mymap["a"] == 2);
	}
	void test_set_3() {
		InstructionSet::mymap["aa"] = 1;
		InstructionSet::mymap["b"] = 2;
		InstructionSet::mymap["c"] = 3;
		CPPUNIT_ASSERT(InstructionSet::mymap["a"] == 2);
		CPPUNIT_ASSERT(InstructionSet::mymap["aa"] == 1);
		CPPUNIT_ASSERT(InstructionSet::mymap["b"] == 2);
		CPPUNIT_ASSERT(InstructionSet::mymap["c"] == 3);
	}
	
	void test_species_1() {
		Species s1('k');
		Species s2('k');
		CPPUNIT_ASSERT(s1.id == 0);
		CPPUNIT_ASSERT(s2.id == 1);
		CPPUNIT_ASSERT(s1.avatar == 'k');
		CPPUNIT_ASSERT(s2.avatar == 'k');
	}
	void test_species_2() {
		Species s1(' ');
		Species s2('k');
		CPPUNIT_ASSERT(s1.id == 2);
		CPPUNIT_ASSERT(s2.id == 3);
		CPPUNIT_ASSERT(s1.avatar == ' ');
		CPPUNIT_ASSERT(s2.avatar == 'k');
	}
	void test_species_3() {
		Species s1('[');
		Species s2('\\');
		CPPUNIT_ASSERT(s1.id == 4);
		CPPUNIT_ASSERT(s2.id == 5);
		CPPUNIT_ASSERT(s1.avatar == '[');
		CPPUNIT_ASSERT(s2.avatar == '\\');
	}
	
	void test_add_ins_1() {
		Species s1('t');
		bool b1 = s1.add_instruction("");
		bool b2 = s1.add_instruction("test");
		CPPUNIT_ASSERT(b1 == false);
		CPPUNIT_ASSERT(b2 == false);
		CPPUNIT_ASSERT(s1.i.size() == 0);
	}
	void test_add_ins_2() {
		Species s1('t');
		bool b1 = s1.add_instruction("hop");
		InstructionSet::mymap["hop"] = 1;
		bool b2 = s1.add_instruction("hop");
		CPPUNIT_ASSERT(b1 == false);
		CPPUNIT_ASSERT(b2 == true);
		CPPUNIT_ASSERT(s1.i.size() == 1);
	}
	void test_add_ins_3() {
		InstructionSet::mymap["hop"] = 1;
		InstructionSet::mymap["left"] = 2;
		InstructionSet::mymap["right"] = 3;
		InstructionSet::mymap["infect"] = 4;
		InstructionSet::mymap["if_empty"] = 5;
		InstructionSet::mymap["if_wall"] = 6;
		InstructionSet::mymap["if_random"] = 7;
		InstructionSet::mymap["if_enemy"] = 8;
		InstructionSet::mymap["go"] = 9;
		Species s1('t');
		bool b1 = s1.add_instruction("hop", 9);
		bool b2 = s1.add_instruction("left");
		bool b3 = s1.add_instruction("right");
		bool b4 = s1.add_instruction("infect");
		bool b5 = s1.add_instruction("if_wall");
		bool b6 = s1.add_instruction("if_empty", 4);
		bool b7 = s1.add_instruction("if_enemy", 900);
		bool b8 = s1.add_instruction("if_random", 0);
		bool b9 = s1.add_instruction("go");
		CPPUNIT_ASSERT(b1 == true);
		CPPUNIT_ASSERT(b2 == true);
		CPPUNIT_ASSERT(b3 == true);
		CPPUNIT_ASSERT(b4 == true);
		CPPUNIT_ASSERT(b5 == true);
		CPPUNIT_ASSERT(b6 == true);
		CPPUNIT_ASSERT(b7 == true);
		CPPUNIT_ASSERT(b8 == true);
		CPPUNIT_ASSERT(b9 == true);
		CPPUNIT_ASSERT(s1.i.size() == 9);
	}
	
	void test_creature_1() {
		Species s1('t');
		Creature c1(s1, 0);
		CPPUNIT_ASSERT(c1._dir == 0);
		CPPUNIT_ASSERT(c1._sp.avatar == 't');
	}
	void test_creature_2() {
		Species s1(' ');
		Creature c1(s1, 3);
		CPPUNIT_ASSERT(c1._dir == 3);
		CPPUNIT_ASSERT(c1._sp.avatar == ' ');
		CPPUNIT_ASSERT(c1.empty == false);
		CPPUNIT_ASSERT(c1.pc == 0);
	}
	void test_creature_3() {
		Species s1('.');
		Creature c1(s1, 0);
		CPPUNIT_ASSERT(c1._sp.avatar == '.');
		CPPUNIT_ASSERT(c1.pc == 0);
	}
	
	void test_run_1() {
		Species s1(' ');
		s1.add_instruction("hop");
		Creature c1(s1, 0);
		pair<int, int> t1 = c1.run();
		pair<int, int> t2(1, 0);
		pair<int, int> t3(1, 1);
		CPPUNIT_ASSERT(t1 == t2);
		CPPUNIT_ASSERT(t1 != t3);
	}
	
	void test_run_2() {
		Species s1('1');
		Species s2('2');
		s1.add_instruction("go",1);
		s2.add_instruction("left",1);
		Creature c1(s1, 0);
		Creature c2(s1, 3);
		pair<int, int> t1 = c1.run();
		pair<int, int> t2 = c2.run();
		pair<int, int> t3(9, 1);
		pair<int, int> t4(2, 1);
		CPPUNIT_ASSERT(t1 == t2);
		CPPUNIT_ASSERT(t1 == t3);
		CPPUNIT_ASSERT(t1 != t4);
		CPPUNIT_ASSERT(t2 == t3);
		CPPUNIT_ASSERT(t2 != t4);
		CPPUNIT_ASSERT(t3 != t4);
		c2 = Creature(s2, 0);
		t2 = c2.run();
		CPPUNIT_ASSERT(t1 != t2);
	}
	
	void test_run_3	() {
		Species s1(' ');
		s1.add_instruction("left");
		s1.add_instruction("right", 1);
		s1.add_instruction("go", 0);
		Creature c1(s1, 0);
		pair<int, int> t1 = c1.run();
		++c1.pc;
		pair<int, int> t2 = c1.run();
		++c1.pc;
		pair<int, int> t3 = c1.run();
		c1.pc = 0;
		pair<int, int> t4 = c1.run();
		CPPUNIT_ASSERT(get<0>(t1) == 2);
		CPPUNIT_ASSERT(get<1>(t1) == 0);
		CPPUNIT_ASSERT(get<0>(t2) == 3);
		CPPUNIT_ASSERT(get<1>(t2) == 1);
		CPPUNIT_ASSERT(get<0>(t3) == 9);
		CPPUNIT_ASSERT(get<1>(t3) == 0);
		CPPUNIT_ASSERT(t1 == t4);
		CPPUNIT_ASSERT(get<0>(t4) == 2);
		CPPUNIT_ASSERT(get<1>(t4) == 0);
	}
	
	void test_add_creature_1() {
		Game game(0,0);
		Species s1(' ');
		Creature c1(s1, 0);
		bool b1 = game.add_creature(c1, 0, 0);
		CPPUNIT_ASSERT(!b1);
	}
	void test_add_creature_2() {
		Game game(1,1);
		Species s1(' ');
		Creature c1(s1, 0);
		bool b1 = game.add_creature(c1, 0, 0);
		CPPUNIT_ASSERT(b1);
	}
	void test_add_creature_3() {
		Game game(2,2);
		Species s1(' ');
		Creature c1(s1, 0);
		bool b1 = game.add_creature(c1, 0, 0);
		bool b2 = game.add_creature(c1, 0, 1);
		bool b3 = game.add_creature(c1, 1, 0);
		bool b4 = game.add_creature(c1, 1, 1);
		bool b5 = game.add_creature(c1, 0, 0);
		CPPUNIT_ASSERT(b1);
		CPPUNIT_ASSERT(b2);
		CPPUNIT_ASSERT(b3);
		CPPUNIT_ASSERT(b4);
		CPPUNIT_ASSERT(!b5);
	}
	
	void test_step_1() {
		Game game(1,1);
		Species s1(' ');
		s1.add_instruction("hop");
		s1.add_instruction("go", 0);
		Creature c1(s1, 0);
		c1.done = true;
		game.add_creature(c1, 0, 0);
		game.step();
		CPPUNIT_ASSERT(c1.done == true);	
		CPPUNIT_ASSERT(c1.pc == 0);	
		CPPUNIT_ASSERT(game.turn == 1);
	}
	void test_step_2() {
		Game game(0, 0);
		game.step();
		CPPUNIT_ASSERT(game.turn == 1);
		game.step();
		CPPUNIT_ASSERT(game.turn == 2);
	}
	void test_step_3() {
		Game game(500, 500);
		for(int i = 0; i < 25; ++i)
			game.step();
		CPPUNIT_ASSERT(game.turn == 25);
	}
	
	void test_perform_1() {
		Game game(1,1);
		Species s1(' ');
		Creature c1(s1, 0);
		game.add_creature(c1, 0, 0);
		pair<int, int> i1(1, 0);
		bool b1 = game.perform(0, i1);
		CPPUNIT_ASSERT(b1 == true);
	}
	void test_perform_2() {
		Game game(1,1);
		Species s1(' ');
		Creature c1(s1, 0);
		game.add_creature(c1, 0, 0);
		pair<int, int> i1(2, 0);
		pair<int, int> i2(9, 0);
		bool b1 = game.perform(0, i1);
		bool b2 = game.perform(0, i2);
		CPPUNIT_ASSERT(b1 == true);
		CPPUNIT_ASSERT(b2 == false);
	}
	void test_perform_3() {
		Game game(50,50);
		Species s1(' ');
		Creature c1(s1, 1250);
		game.add_creature(c1, 0, 0);
		pair<int, int> i1(1, 0);
		pair<int, int> i2(2, 0);
		pair<int, int> i3(3, 0);
		pair<int, int> i4(4, 0);
		pair<int, int> i5(5, 0);
		pair<int, int> i6(6, 0);
		pair<int, int> i7(7, 0);
		pair<int, int> i8(8, 0);
		pair<int, int> i9(9, 0);
		bool b1 = game.perform(0, i1);
		bool b2 = game.perform(0, i2);
		bool b3 = game.perform(0, i3);
		bool b4 = game.perform(0, i4);
		bool b5 = game.perform(0, i5);
		bool b6 = game.perform(0, i6);
		bool b7 = game.perform(0, i7);
		bool b8 = game.perform(0, i8);
		bool b9 = game.perform(0, i9);
		CPPUNIT_ASSERT(b1 == true);
		CPPUNIT_ASSERT(b2 == true);
		CPPUNIT_ASSERT(b3 == true);
		CPPUNIT_ASSERT(b4 == true);
		CPPUNIT_ASSERT(b5 == false);
		CPPUNIT_ASSERT(b6 == false);
		CPPUNIT_ASSERT(b7 == false);
		CPPUNIT_ASSERT(b8 == false);
		CPPUNIT_ASSERT(b9 == false);
	}
	     
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestDarwin);
    CPPUNIT_TEST(test_set_1);
    CPPUNIT_TEST(test_set_2);
    CPPUNIT_TEST(test_set_3);
    CPPUNIT_TEST(test_species_1);
    CPPUNIT_TEST(test_species_2);
    CPPUNIT_TEST(test_species_3);
    CPPUNIT_TEST(test_add_ins_1);
    CPPUNIT_TEST(test_add_ins_2);
    CPPUNIT_TEST(test_add_ins_3);
    CPPUNIT_TEST(test_creature_1);
    CPPUNIT_TEST(test_creature_2);
    CPPUNIT_TEST(test_creature_3);
    CPPUNIT_TEST(test_run_1);
    CPPUNIT_TEST(test_run_2);
    CPPUNIT_TEST(test_run_3);
    CPPUNIT_TEST(test_add_creature_1);
    CPPUNIT_TEST(test_add_creature_2);
    CPPUNIT_TEST(test_add_creature_3);
    CPPUNIT_TEST(test_step_1);
    CPPUNIT_TEST(test_step_2);
    CPPUNIT_TEST(test_step_3);
    CPPUNIT_TEST(test_perform_1);
    CPPUNIT_TEST(test_perform_2);
    CPPUNIT_TEST(test_perform_3);
    CPPUNIT_TEST_SUITE_END();};    

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestDarwin.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestDarwin::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
