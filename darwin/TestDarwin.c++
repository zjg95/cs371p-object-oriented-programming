// --------------------------------
// projects/darwin/TestDarwin.c++
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair

#include "gtest/gtest.h"

#include "Darwin.h"

using namespace std;

// -----------
// TestDarwin
// -----------

// -----
// print
// -----

TEST(Darwin, print) {
	Darwin<8,8> darwin;
    ostringstream w;
    darwin.print(w);
    ASSERT_EQ("  01234567\n0 ........\n1 ........\n2 ........\n3 ........\n4 ........\n5 ........\n6 ........\n7 ........\n\n", w.str());
}

TEST(Darwin, print_8x8){
	ostringstream w;

    Species food('f');

    Species hopper('h');
    
    // 8x8 Darwin
    Darwin<8,8> darwin;
    // Food,   facing east,  at (0, 0)
    darwin.add_creature(Creature(food,'e'),0,0);
    // Hopper, facing north, at (3, 3)
    darwin.add_creature(Creature(hopper,'n'),3,3);
    // Hopper, facing east,  at (3, 4)
    darwin.add_creature(Creature(hopper,'e'),3,4);
    // Hopper, facing south, at (4, 4)
    darwin.add_creature(Creature(hopper,'s'),4,4);
    // Hopper, facing west,  at (4, 3)
    darwin.add_creature(Creature(hopper,'w'),4,3);
    // Food,   facing north, at (7, 7)
    darwin.add_creature(Creature(food,'n'),7,7);
    // Print every grid.
    darwin.print(w);
    ASSERT_EQ("  01234567\n0 f.......\n1 ........\n2 ........\n3 ...hh...\n4 ...hh...\n5 ........\n6 ........\n7 .......f\n\n", w.str());    
}

TEST(Species, add_get_instruction){

	Species food('f');
	food.add_instruction("left");
	food.add_instruction("go", 0);
	ASSERT_EQ(2,food.code_size);
	instruction instr = food.get_instruction(0);
	ASSERT_EQ("left",instr.operation);
	instr = food.get_instruction(1);
	ASSERT_EQ("go",instr.operation);
	ASSERT_EQ(0,instr.argument);

    Species hopper('h');
    hopper.add_instruction("hop");
    hopper.add_instruction("go",0);
	ASSERT_EQ(2,hopper.code_size);
	instr = hopper.get_instruction(0);
	ASSERT_EQ("hop",instr.operation);

    Species rover('r');
    rover.add_instruction("if_enemy",9);
    rover.add_instruction("if_empty",7);
    rover.add_instruction("if_random",5);
    rover.add_instruction("left");
    rover.add_instruction("go",0);
    rover.add_instruction("right");
    rover.add_instruction("go",0);
    rover.add_instruction("hop");
    rover.add_instruction("go",0);
    rover.add_instruction("infect");
    rover.add_instruction("go",0);
	ASSERT_EQ(11,rover.code_size);

    Species trap('t');
    trap.add_instruction("if_enemy",3);
    trap.add_instruction("left");
    trap.add_instruction("go",0);
    trap.add_instruction("infect");
    trap.add_instruction("go",0);
	ASSERT_EQ(5,trap.code_size);

	instr = trap.get_instruction(0);
	ASSERT_EQ("if_enemy",instr.operation);
	ASSERT_EQ(3,instr.argument);
	instr = trap.get_instruction(1);
	ASSERT_EQ("left",instr.operation);
	instr = trap.get_instruction(2);
	ASSERT_EQ("go",instr.operation);
	ASSERT_EQ(0,instr.argument);
	instr = trap.get_instruction(3);
	ASSERT_EQ("infect",instr.operation);
	instr = trap.get_instruction(4);
	ASSERT_EQ("go",instr.operation);
	ASSERT_EQ(0,instr.argument);
}


TEST(Darwin, simulate_simple_af){
    ostringstream w;

    Species a('a');
    a.add_instruction("hop");
    a.add_instruction("go",0);
    
    // 3x3 Darwin
    Darwin<2,1> darwin;
    darwin.add_creature(Creature(a,'e'),0,0);
    darwin.print(w);
    ASSERT_EQ("  01\n0 a.\n\n", w.str());
    w.str("");
    w.clear();
    darwin.simulate(1);
    darwin.print(w);
    ASSERT_EQ("  01\n0 .a\n\n", w.str());
}
TEST(Darwin, simulate_simple_af2){
    ostringstream w;

    Species a('a');
    a.add_instruction("hop");
    a.add_instruction("go",0);
    
    // 3x3 Darwin
    Darwin<3,1> darwin;
    darwin.add_creature(Creature(a,'e'),0,0);
    darwin.print(w);
    ASSERT_EQ("  012\n0 a..\n\n", w.str());
    w.str("");
    w.clear();
    darwin.simulate(1);
    darwin.print(w);
    ASSERT_EQ("  012\n0 .a.\n\n", w.str());
    w.str("");
    w.clear();
    darwin.simulate(1);
    darwin.print(w);
    ASSERT_EQ("  012\n0 ..a\n\n", w.str());
}
TEST(Darwin, simulate_basic){
    ostringstream w;

    Species a('a');
    a.add_instruction("left");
    a.add_instruction("go",0);
    Species b('b');
    b.add_instruction("left");
    b.add_instruction("go",0);
    Species c('c');
    c.add_instruction("left");
    c.add_instruction("go",0);
    
    // 3x3 Darwin
    Darwin<3,3> darwin;
    darwin.add_creature(Creature(a,'n'),0,0);
    darwin.add_creature(Creature(b,'n'),1,1);
    darwin.add_creature(Creature(c,'n'),2,2);
    darwin.print(w);
    ASSERT_EQ("  012\n0 a..\n1 .b.\n2 ..c\n\n", w.str());
    w.str("");
    w.clear();
    darwin.simulate(1);
    darwin.print(w);
    ASSERT_EQ("  012\n0 a..\n1 .b.\n2 ..c\n\n", w.str());
}

TEST(Darwin, simulate_basic_hopper){
    ostringstream w;

    Species hopper('h');
    hopper.add_instruction("hop");
    hopper.add_instruction("go",0);
    
    // 3x3 Darwin
    Darwin<3,3> darwin;
    darwin.add_creature(Creature(hopper,'w'),2,0);
    darwin.add_creature(Creature(hopper,'w'),2,1);
    darwin.add_creature(Creature(hopper,'w'),2,2);
    darwin.print(w);
    ASSERT_EQ("  012\n0 ..h\n1 ..h\n2 ..h\n\n", w.str());
    w.str("");
    w.clear();
    darwin.simulate(1);
    darwin.print(w);
    ASSERT_EQ("  012\n0 .h.\n1 .h.\n2 .h.\n\n", w.str());
    w.str("");
    w.clear();
    darwin.simulate(1);
    darwin.print(w);
    ASSERT_EQ("  012\n0 h..\n1 h..\n2 h..\n\n", w.str());
}

TEST(Darwin, simulate_custom_simple_creature){
    ostringstream w;

    Species a('a');
    a.add_instruction("hop");
    a.add_instruction("right");
    a.add_instruction("hop");
    a.add_instruction("left");
    a.add_instruction("infect");
    a.add_instruction("go",0);

    Species food('f');
    food.add_instruction("left");
    food.add_instruction("go",0);
    
    // 3x3 Darwin
    Darwin<3,3> darwin;
    darwin.add_creature(Creature(a,'e'),0,0);
    darwin.add_creature(Creature(food,'e'),2,1);
    darwin.print(w);
    ASSERT_EQ("  012\n0 a..\n1 ..f\n2 ...\n\n", w.str());
    w.str("");
    w.clear();
    darwin.simulate(5);
    darwin.print(w);
    ASSERT_EQ("  012\n0 ...\n1 .aa\n2 ...\n\n", w.str());
}
TEST(Darwin, simulate_infect_creature){
    ostringstream w;

    Species a('a');
    a.add_instruction("if_enemy",2);
    a.add_instruction("hop");
    a.add_instruction("infect");
    a.add_instruction("go",0);

    Species food('f');
    food.add_instruction("left");
    food.add_instruction("go",0);
    
    // 3x3 Darwin
    Darwin<5,1> darwin;
    darwin.add_creature(Creature(a,'e'),0,0);
    darwin.add_creature(Creature(food,'e'),1,0);
    darwin.print(w);
    ASSERT_EQ("  01234\n0 af...\n\n", w.str());
    w.str("");
    w.clear();
    darwin.simulate(3);
    darwin.print(w);
    ASSERT_EQ("  01234\n0 .a.a.\n\n", w.str());
}

TEST(Darwin, simulate_border_creature){
    ostringstream w;

    Species a('a');
    a.add_instruction("if_wall",3);
    a.add_instruction("hop");
    a.add_instruction("go",0);
    a.add_instruction("left");
    a.add_instruction("go",0);
    
    // 3x3 Darwin
    Darwin<3,3> darwin;
    darwin.add_creature(Creature(a,'s'),0,0);
    darwin.print(w);
    ASSERT_EQ("  012\n0 a..\n1 ...\n2 ...\n\n", w.str());
    w.str("");
    w.clear();
    darwin.simulate(11);
    darwin.print(w);
    ASSERT_EQ("  012\n0 a..\n1 ...\n2 ...\n\n", w.str());
}

TEST(Darwin, darwin_8x8){
    /*
        Turn = 0.
          01234567
        0 f.......
        1 ........
        2 ........
        3 ...hh...
        4 ...hh...
        5 ........
        6 ........
        7 .......f

        Turn = 5.
          01234567
        0 f..h....
        1 ........
        2 ........
        3 .......h
        4 h.......
        5 ........
        6 ........
        7 ....h..f
    */
    Species food('f');
    food.add_instruction("left");
    food.add_instruction("go", 0);

    Species hopper('h');
    hopper.add_instruction("hop");
    hopper.add_instruction("go",0);

    // 8x8 Darwin
    Darwin<8,8> d1;
    // Food,   facing east,  at (0, 0)
    d1.add_creature(Creature(food,'e'),0,0);
    // Hopper, facing north, at (3, 3)
    d1.add_creature(Creature(hopper,'n'),3,3);
    // Hopper, facing east,  at (3, 4)
    d1.add_creature(Creature(hopper,'e'),4,3);
    // Hopper, facing south, at (4, 4)
    d1.add_creature(Creature(hopper,'s'),4,4);
    // Hopper, facing west,  at (4, 3)
    d1.add_creature(Creature(hopper,'w'),3,4);
    // Food,   facing north, at (7, 7)
    d1.add_creature(Creature(food,'n'),7,7);
    // Simulate 5 moves; Print every grid.

    ostringstream w;
    d1.print(w);
    ASSERT_EQ("  01234567\n0 f.......\n1 ........\n2 ........\n3 ...hh...\n4 ...hh...\n5 ........\n6 ........\n7 .......f\n\n", w.str());
    w.str("");
    w.clear();
    d1.simulate(5);
    d1.print(w);
    ASSERT_EQ("  01234567\n0 f..h....\n1 ........\n2 ........\n3 .......h\n4 h.......\n5 ........\n6 ........\n7 ....h..f\n\n", w.str());
}

TEST(Darwin, darwin_7x9){
    /*
        Turn = 0.
          012345678
        0 t........
        1 .........
        2 .........
        3 ..h......
        4 .........
        5 ....r....
        6 ........t

        Turn = 5.
          012345678
        0 t........
        1 ....r....
        2 .........
        3 .......r.
        4 .........
        5 .........
        6 ........t
    */

    Species rover('r');
    rover.add_instruction("if_enemy",9);
    rover.add_instruction("if_empty",7);
    rover.add_instruction("if_random",5);
    rover.add_instruction("left");
    rover.add_instruction("go",0);
    rover.add_instruction("right");
    rover.add_instruction("go",0);
    rover.add_instruction("hop");
    rover.add_instruction("go",0);
    rover.add_instruction("infect");
    rover.add_instruction("go",0);

    Species hopper('h');
    hopper.add_instruction("hop");
    hopper.add_instruction("go",0);

    Species trap('t');
    trap.add_instruction("if_enemy",3);
    trap.add_instruction("left");
    trap.add_instruction("go",0);
    trap.add_instruction("infect");
    trap.add_instruction("go",0);

    // 7x9 Darwin
    Darwin<9,7> d2;
    // Trap,   facing south, at (0, 0)
    d2.add_creature(Creature(trap,'s'),0,0);
    // Hopper, facing east,  at (3, 2)
    d2.add_creature(Creature(hopper,'e'),2,3);
    // Rover,  facing north, at (5, 4)
    d2.add_creature(Creature(rover,'n'),4,5);
    // Trap,   facing west,  at (6, 8)
    d2.add_creature(Creature(trap,'w'),8,6);
    // Simulate 5 moves.
    // Print every grid.

    ostringstream w;
    d2.print(w);
    ASSERT_EQ("  012345678\n0 t........\n1 .........\n2 .........\n3 ..h......\n4 .........\n5 ....r....\n6 ........t\n\n", w.str());
    w.str("");
    w.clear();
    d2.simulate(5);
    d2.print(w);
    ASSERT_EQ("  012345678\n0 t........\n1 ....r....\n2 .........\n3 .......r.\n4 .........\n5 .........\n6 ........t\n\n", w.str());
}
