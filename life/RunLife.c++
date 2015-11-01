// -------------------------
// projects/life/RunLife.c++
// Copyright (C) 2015
// Glenn P. Downing
// -------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // cout, endl
#include "Life.h"

// ----
// main
// ----

int main () {
    using namespace std;

    // -----------------
    // Conway Cell 21x13
    // -----------------

    cout << "*** Life<ConwayCell> 21x13 ***" << endl;
    /*
    Simulate 12 evolutions.
    Print every grid (i.e. 0, 1, 2, 3, ... 12)
    */
    {
        Life<ConwayCell> life(cin, 21, 13);
        for (int i = 0; i < 12; ++i) {
            life >> cout;
            life.simulate();
        }
        life >> cout;
        cout << endl;
    }
    // -----------------
    // Conway Cell 20x29
    // -----------------

    cout << "*** Life<ConwayCell> 20x29 ***" << endl;
    /*
    Simulate 28 evolutions.
    Print every 4th grid (i.e. 0, 4, 8, ... 28)
    */
    {
        Life<ConwayCell> life(cin, 20, 29); 
        for (int i = 0; i < 28; ++i) {
            if (i % 4 == 0)
                life >> cout;
            life.simulate();
        }
        life >> cout;
        cout << endl;
    }
    // ------------------
    // Conway Cell 109x69
    // ------------------

    cout << "*** Life<ConwayCell> 109x69 ***" << endl;
    /*
    Simulate 283 evolutions.
    Print the first 10 grids (i.e. 0, 1, 2, ... 9).
    Print the 283rd grid.
    Simulate 40 evolutions.
    Print the 323rd grid.
    Simulate 2177 evolutions.
    Print the 2500th grid.
    */
    {
        Life<ConwayCell> life(cin, 109, 69); 
        for (int i = 0; i < 2500; ++i) {
            if (i < 10 || i == 283 || i == 323)
                life >> cout;
            life.simulate();
        }
        life >> cout;
        cout << endl;
    }
    // ------------------
    // Fredkin Cell 20x20
    // ------------------

    cout << "*** Life<FredkinCell> 20x20 ***" << endl;
    /*
    Simulate 5 evolutions.
    Print every grid (i.e. 0, 1, 2, ... 5)
    */
    {
        Life<FredkinCell> life(cin, 20, 20); 
        for (int i = 0; i < 5; ++i) {
            life >> cout;
            life.simulate();
        }
        life >> cout;
        cout << endl;
    }
    // ----------
    // Cell 20x20
    // ----------

    cout << "*** Life<Cell> 20x20 ***" << endl;
    /*
    Simulate 5 evolutions.
    Print every grid (i.e. 0, 1, 2, ... 5)
    */
    {
        Life<Cell> life(cin, 20, 20);
        // for (int i = 0; i < 5; ++i) {
        //     life >> cout;
        //     life.simulate();
        // }
        // life >> cout;
    }

    return 0;}
