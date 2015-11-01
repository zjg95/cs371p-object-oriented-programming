// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2015
// Glenn P. Downing
// -----------------------------

// --------
// includes
// --------

#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range

#include "Darwin.h"

// ----
// main
// ----

int main () {
    using namespace std;

    // ----
    // food
    // ----

    Species food('f');
    food.add_instruction("left");
    food.add_instruction("go", 0);

    // ------
    // hopper
    // ------

    Species hopper('h');
    hopper.add_instruction("hop");
    hopper.add_instruction("go",0);

    // -----
    // rover
    // -----

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

    // ----
    // trap
    // ----

    Species trap('t');
    trap.add_instruction("if_enemy",3);
    trap.add_instruction("left");
    trap.add_instruction("go",0);
    trap.add_instruction("infect");
    trap.add_instruction("go",0);

    // ----------
    // darwin 8x8
    // ----------

    cout << "*** Darwin 8x8 ***" << endl;

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
    d1.simulate(5);

    // ----------
    // darwin 7x9
    // ----------

    cout << "*** Darwin 7x9 ***" << endl;
    srand(0);

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
    d2.simulate(5);
    // Print every grid.

    // ------------
    // darwin 72x72
    // without best
    // ------------

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
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */

    Darwin<72,72> d3;

    for (int i = 0; i < 10; i++){
        int base = rand() % 5184;
        int row = base / 72;
        int col = base % 72;

        int dir = rand() % 4;
        d3.add_creature(Creature(food,dir),col,row);
    }
    for (int i = 0; i < 10; i++){
        int base = rand() % 5184;
        int row = base / 72;
        int col = base % 72;

        int dir = rand() % 4;
        d3.add_creature(Creature(hopper,dir),col,row);
    }
    for (int i = 0; i < 10; i++){
        int base = rand() % 5184;
        int row = base / 72;
        int col = base % 72;

        int dir = rand() % 4;
        d3.add_creature(Creature(rover,dir),col,row);
    }
    for (int i = 0; i < 10; i++){
        int base = rand() % 5184;
        int row = base / 72;
        int col = base % 72;

        int dir = rand() % 4;
        d3.add_creature(Creature(trap,dir),col,row);
    }

    d3.simulate_big(1000);

    // ------------
    // darwin 72x72
    // with best
    // ------------

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
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */

    Species best('b');
    best.add_instruction("if_enemy",6);
    best.add_instruction("if_wall",4);
    best.add_instruction("hop");
    best.add_instruction("go",0);
    best.add_instruction("left");
    best.add_instruction("go",0);
    best.add_instruction("infect");
    best.add_instruction("go",0);

    Darwin<72,72> d4;

    for (int i = 0; i < 10; i++){
        int base = rand() % 5184;
        int row = base / 72;
        int col = base % 72;

        int dir = rand() % 4;
        d4.add_creature(Creature(food,dir),col,row);
    }
    for (int i = 0; i < 10; i++){
        int base = rand() % 5184;
        int row = base / 72;
        int col = base % 72;

        int dir = rand() % 4;
        d4.add_creature(Creature(hopper,dir),col,row);
    }
    for (int i = 0; i < 10; i++){
        int base = rand() % 5184;
        int row = base / 72;
        int col = base % 72;

        int dir = rand() % 4;
        d4.add_creature(Creature(rover,dir),col,row);
    }
    for (int i = 0; i < 10; i++){
        int base = rand() % 5184;
        int row = base / 72;
        int col = base % 72;

        int dir = rand() % 4;
        d4.add_creature(Creature(trap,dir),col,row);
    }
    for (int i = 0; i < 10; i++){
        int base = rand() % 5184;
        int row = base / 72;
        int col = base % 72;

        int dir = rand() % 4;
        d4.add_creature(Creature(best,dir),col,row);
    }

    d4.simulate_big(1000);

    return 0;}