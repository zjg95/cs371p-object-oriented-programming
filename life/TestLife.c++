// --------------------------------
// projects/life/TestLife.c++
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

#include "Life.h"

using namespace std;

// -----------
// TestLife
// -----------

TEST(Life, print_conway) {
  Life<ConwayCell> life(3,3);
  ostringstream w;
  life >> w;
  ASSERT_EQ("\nGeneration = 0, Population = 0.\n...\n...\n...\n",w.str());
}
TEST(Life, print_fredkin) {
  Life<FredkinCell> life(3,3);
  ostringstream w;
  life >> w;
  ASSERT_EQ("\nGeneration = 0, Population = 0.\n---\n---\n---\n",w.str());
}

TEST(Cell, constructors) {
  ostringstream w;
  Cell cell(new ConwayCell());
  w << cell;
  cell = new FredkinCell();
  w << cell;
  cell = new FredkinCell(true);
  w << cell;
  cell = new ConwayCell(true);
  w << cell;
  ASSERT_EQ(".-0*",w.str());
}

// TEST(Life, cell) {
//   Life<Cell> life(3,3);
//   ostringstream w;
//   life >> w;
//   ASSERT_EQ("\nGeneration = 0, Population = 0.\n---\n---\n---\n",w.str());
// }

TEST(Life, read_file){
  istringstream file ("ConwayCell\n"
    "21\n"
    "13\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    "....*****....\n"
    ".......*.....\n"
    "......*......\n"
    ".....*.......\n"
    "....*****....\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    "\n");
  Life<ConwayCell> life(file,21,13);

  ostringstream w;
  life >> w;
  ASSERT_EQ("\nGeneration = 0, Population = 13.\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    "....*****....\n"
    ".......*.....\n"
    "......*......\n"
    ".....*.......\n"
    "....*****....\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    "",w.str());
}

TEST(Life, read_file_multi){
  istringstream file ("ConwayCell\n"
    "21\n"
    "13\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    "....*****....\n"
    ".......*.....\n"
    "......*......\n"
    ".....*.......\n"
    "....*****....\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    "\n"
    "ConwayCell\n"
    "20\n"
    "29\n"
    ".............................\n"
    ".............................\n"
    ".............................\n"
    "...**........................\n"
    "...*.......***......****.....\n"
    ".............................\n"
    ".............................\n"
    ".............................\n"
    ".............................\n"
    ".............................\n"
    ".............................\n"
    "....*......*.........*.......\n"
    "....**.....***......***......\n"
    ".....*.......................\n"
    ".............................\n"
    ".............................\n"
    ".............................\n"
    ".............................\n"
    ".............................\n"
    ".............................\n"
    "");
  Life<ConwayCell> life1(file,21,13);
  Life<ConwayCell> life2(file,20,29);

  ostringstream w;
  life1 >> w;
  life2 >> w;
  ASSERT_EQ("\nGeneration = 0, Population = 13.\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n....*****....\n.......*.....\n......*......\n.....*.......\n....*****....\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n\nGeneration = 0, Population = 22.\n.............................\n.............................\n.............................\n...**........................\n...*.......***......****.....\n.............................\n.............................\n.............................\n.............................\n.............................\n.............................\n....*......*.........*.......\n....**.....***......***......\n.....*.......................\n.............................\n.............................\n.............................\n.............................\n.............................\n.............................\n",w.str());
}
TEST(Life, read_file_multi2){
  istringstream file ("ConwayCell\n"
    "21\n"
    "13\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    "....*****....\n"
    ".......*.....\n"
    "......*......\n"
    ".....*.......\n"
    "....*****....\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    ".............\n"
    "\n"
    "FredkinCell\n"
    "20\n"
    "20\n"
    "--------------------\n"
    "--------------------\n"
    "--------------------\n"
    "--------------------\n"
    "--------------------\n"
    "--------------------\n"
    "--------------------\n"
    "--------------------\n"
    "--------------------\n"
    "---------00---------\n"
    "---------00---------\n"
    "--------------------\n"
    "--------------------\n"
    "--------------------\n"
    "--------------------\n"
    "--------------------\n"
    "--------------------\n"
    "--------------------\n"
    "--------------------\n"
    "--------------------\n"
    "");
  Life<ConwayCell> life1(file,21,13);
  Life<FredkinCell> life2(file,20,20);

  ostringstream w;
  life1 >> w;
  life2 >> w;
  ASSERT_EQ("\nGeneration = 0, Population = 13.\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n....*****....\n.......*.....\n......*......\n.....*.......\n....*****....\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n\nGeneration = 0, Population = 4.\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n---------00---------\n---------00---------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n",w.str());
}

TEST(Life, read_conway){
  istringstream file ("ConwayCell\n3\n3\n.*.\n.*.\n.*.");
  Life<ConwayCell> life(file,3,3);
 // life << i;
 // life >> cout;
  ostringstream w;
  life >> w;
  ASSERT_EQ("\nGeneration = 0, Population = 3.\n.*.\n.*.\n.*.\n",w.str());
}
TEST(Life, read_fredkin){
  istringstream i ("FredkinCell\n3\n3\n-0-\n-0-\n-0-");
  Life<FredkinCell> life(i,3,3);
//  life << i;

  ostringstream w;
  life >> w;
  ASSERT_EQ("\nGeneration = 0, Population = 3.\n-0-\n-0-\n-0-\n",w.str());
}


TEST(Life, read1){
  istringstream file ("ConwayCell\n11\n12\n");
  Life<ConwayCell> life;
  ostringstream w;
  life.read(file);
  ASSERT_EQ(11,life.rows);
  ASSERT_EQ(12,life.columns);
}

TEST(Life, read2){
  istringstream file ("FredkinCell\n5\n13\n");
  Life<FredkinCell> life;
  ostringstream w;
  life.read(file);
  ASSERT_EQ(5,life.rows);
  ASSERT_EQ(13,life.columns);  
}

TEST(Life, read3){
  istringstream file ("Cell\n6\n1\n");
  Life<Cell> life;
  ostringstream w;
  life.read(file);
  ASSERT_EQ(6,life.rows);
  ASSERT_EQ(1,life.columns);  
}

TEST(Life, count1){
  istringstream i ("ConwayCell\n3\n3\n*..\n...\n...");
  Life<ConwayCell> life(i,3,3);
  int x = life.count_living();
  ASSERT_EQ(1,x);
}
TEST(Life, count2){
  istringstream i ("ConwayCell\n3\n3\n***\n***\n***");
  Life<ConwayCell> life(i,3,3);
  int x = life.count_living();
  ASSERT_EQ(9,x);
}
TEST(Life, count3){
  istringstream i ("ConwayCell\n3\n3\n...\n...\n...");
  Life<ConwayCell> life(i,3,3);
  int x = life.count_living();
  ASSERT_EQ(0,x);
}
TEST(Life, count4){
  istringstream i ("FredkinCell\n3\n3\n0--\n---\n---");
  Life<FredkinCell> life(i,3,3);
  int x = life.count_living();
  ASSERT_EQ(1,x);
}
TEST(Life, count5){
  istringstream i ("FredkinCell\n3\n3\n000\n000\n000");
  Life<FredkinCell> life(i,3,3);
  int x = life.count_living();
  ASSERT_EQ(9,x);
}
TEST(Life, count6){
  istringstream i ("FredkinCell\n3\n3\n---\n---\n---");
  Life<FredkinCell> life(i,3,3);
  int x = life.count_living();
  ASSERT_EQ(0,x);
}

TEST(Life, get_neighbors1){
  istringstream i ("ConwayCell\n3\n3\n.*.\n***\n.*.");
  Life<ConwayCell> life(i,3,3);
 // grid << i;

  /*
  
    .*.
    ***
    .*.

  */

  ostringstream w;
  life >> w;
  ASSERT_EQ("\nGeneration = 0, Population = 5.\n.*.\n***\n.*.\n",w.str());

  bool neighbors[8];

  for (int y = 0; y < 3; y++){
    for (int x = 0; x < 3; x++){
      life.get_neighbors(x,y,neighbors);
      int alive_count = 0;
      for (int i = 0; i < 8; ++i)
        if (neighbors[i])
          ++alive_count;
      if (x == 1 && y == 1)
        ASSERT_EQ(4,alive_count);
      else
        ASSERT_EQ(3,alive_count);
    }
  }
}
TEST(Life, get_neighbors2){
  istringstream i ("ConwayCell\n3\n3\n.*.\n.*.\n.*.");
  Life<ConwayCell> life(i,3,3);
 // grid << i;

  /*
  
    .*.
    .*.
    .*.

  */

  ostringstream w;
  life >> w;
  ASSERT_EQ("\nGeneration = 0, Population = 3.\n.*.\n.*.\n.*.\n",w.str());

  bool neighbors[8];

  life.get_neighbors(0,0,neighbors);
  int alive_count = 0;
  for (int i = 0; i < 8; ++i)
    if (neighbors[i])
      ++alive_count;
  ASSERT_EQ(2,alive_count);

  life.get_neighbors(1,0,neighbors);
  alive_count = 0;
  for (int i = 0; i < 8; ++i)
    if (neighbors[i])
      ++alive_count;
  ASSERT_EQ(3,alive_count);

  life.get_neighbors(2,0,neighbors);
  alive_count = 0;
  for (int i = 0; i < 8; ++i)
    if (neighbors[i])
      ++alive_count;
  ASSERT_EQ(2,alive_count);

  life.get_neighbors(0,1,neighbors);
  alive_count = 0;
  for (int i = 0; i < 8; ++i)
    if (neighbors[i])
      ++alive_count;
  ASSERT_EQ(1,alive_count);

  life.get_neighbors(1,1,neighbors);
  alive_count = 0;
  for (int i = 0; i < 8; ++i)
    if (neighbors[i])
      ++alive_count;
  ASSERT_EQ(2,alive_count);

  life.get_neighbors(2,1,neighbors);
  alive_count = 0;
  for (int i = 0; i < 8; ++i)
    if (neighbors[i])
      ++alive_count;
  ASSERT_EQ(1,alive_count);

  life.get_neighbors(0,2,neighbors);
  alive_count = 0;
  for (int i = 0; i < 8; ++i)
    if (neighbors[i])
      ++alive_count;
  ASSERT_EQ(2,alive_count);

  life.get_neighbors(1,2,neighbors);
  alive_count = 0;
  for (int i = 0; i < 8; ++i)
    if (neighbors[i])
      ++alive_count;
  ASSERT_EQ(3,alive_count);

  life.get_neighbors(2,2,neighbors);
  alive_count = 0;
  for (int i = 0; i < 8; ++i)
    if (neighbors[i])
      ++alive_count;
  ASSERT_EQ(2,alive_count);
}


// ------------
// TestAbstract
// ------------

TEST(AbstractCell, create) {
  ConwayCell c;
  ASSERT_FALSE(c.alive);
}

TEST(AbstractCell, create2) {
  ConwayCell c(true);
  ASSERT_TRUE(c.alive);
}

TEST(AbstractCell, create3) {
  ConwayCell c(false);
  ASSERT_FALSE(c.alive);
}

TEST(AbstractCell, create4) {
  FredkinCell c;
  ASSERT_FALSE(c.alive);
}

TEST(AbstractCell, create5) {
  FredkinCell c(true);
  ASSERT_TRUE(c.alive);
}

TEST(AbstractCell, create6) {
  FredkinCell c(false);
  ASSERT_FALSE(c.alive);
}

TEST(AbstractCell, deref1) {
  ConwayCell c(false);
  ASSERT_FALSE((*c));
}

TEST(AbstractCell, deref2) {
  ConwayCell c(true);
  ASSERT_TRUE((*c));
}

TEST(AbstractCell, deref3) {
  FredkinCell c(false);
  ASSERT_FALSE((*c));
}

TEST(AbstractCell, deref4) {
  FredkinCell c(true);
  ASSERT_TRUE((*c));
}

// TEST(AbstractCell, print1) {
//   ConwayCell c(true);
//   ostringstream w;
//   c.print(w);
//   ASSERT_EQ('*', w.str());
// }

// TEST(AbstractCell, print2) {
//   ConwayCell c(false);
//   ostringstream w;
//   c.print(w);
//   ASSERT_EQ('.', w.str());
// }

// TEST(Cell, create) {
//   Cell c;
//   ASSERT_FALSE(c.alive);
// }

TEST(ConwayCell, evolve1){
  istringstream i ("ConwayCell\n3\n3\n.*.\n***\n.*.");
  Life<ConwayCell> life(i,3,3);

  /*
  
    .*.
    ***
    .*.

  */

  ostringstream w;
  life >> w;
  ASSERT_EQ("\nGeneration = 0, Population = 5.\n.*.\n***\n.*.\n",w.str());

  ConwayCell cell;

  ASSERT_FALSE(*cell);

  bool neighbors[8];

  life.get_neighbors(0,0,neighbors);

  cell.evolve(neighbors);

  ASSERT_TRUE(*cell);
}

TEST(ConwayCell, evolve_left){
  istringstream i ("ConwayCell\n3\n3\n*..\n*..\n*..");
  Life<ConwayCell> life(i,3,3);
 // grid << i;

  /*
  
    *..
    *..
    *..

  */

  ostringstream w;
  life >> w;
  ASSERT_EQ("\nGeneration = 0, Population = 3.\n*..\n*..\n*..\n",w.str());

  ConwayCell cell;

  ASSERT_FALSE(*cell);

  bool neighbors[8];

  life.get_neighbors(1,1,neighbors);

  cell.evolve(neighbors);

  ASSERT_TRUE(*cell);
}

TEST(ConwayCell, simulate){
  istringstream i ("ConwayCell\n3\n3\n.*.\n***\n.*.");
  Life<ConwayCell> life(i,3,3);
 // life << i;

  /*
  
    .*.
    ***
    .*.

  */

  life.simulate();
  life.simulate();

  ostringstream w;
  life >> w;
  ASSERT_EQ("\nGeneration = 2, Population = 4.\n*.*\n...\n*.*\n",w.str());
}

TEST(ConwayCell, simulate_left){
  istringstream i ("ConwayCell\n3\n3\n*..\n*..\n*..");
  Life<ConwayCell> life(i,3,3);

  life.simulate();
  life.simulate();

  ostringstream w;
  life >> w;
  ASSERT_EQ("\nGeneration = 2, Population = 0.\n...\n...\n...\n",w.str());
}

TEST(ConwayCell, simulate_top){
  istringstream i ("ConwayCell\n3\n3\n***\n...\n...");
  Life<ConwayCell> life(i,3,3);

  life.simulate();
  life.simulate();

  ostringstream w;
  life >> w;
  ASSERT_EQ("\nGeneration = 2, Population = 0.\n...\n...\n...\n",w.str());
}

TEST(ConwayCell, simulate_bottom){
  istringstream i ("ConwayCell\n3\n3\n...\n...\n***");
  Life<ConwayCell> life(i,3,3);

  life.simulate();
  life.simulate();

  ostringstream w;
  life >> w;
  ASSERT_EQ("\nGeneration = 2, Population = 0.\n...\n...\n...\n",w.str());
}

TEST(ConwayCell, simulate_right){
  istringstream i ("ConwayCell\n3\n3\n..*\n..*\n..*");
  Life<ConwayCell> life(i,3,3);

  life.simulate();
  life.simulate();

  ostringstream w;
  life >> w;
  ASSERT_EQ("\nGeneration = 2, Population = 0.\n...\n...\n...\n",w.str());
}


TEST(ConwayCell, simulate_full){
  istringstream i ("ConwayCell\n3\n3\n***\n***\n***");
  Life<ConwayCell> life(i,3,3);

  life.simulate();
  life.simulate();

  ostringstream w;
  life >> w;
  ASSERT_EQ("\nGeneration = 2, Population = 0.\n...\n...\n...\n",w.str());
}

TEST(ConwayCell, evolve_quiz32){
  istringstream i("ConwayCell\n5\n8\n........\n"
    "........\n"
    "***.****\n"
    "........\n"
    "........\n");

  Life<ConwayCell> life(i,5,8);

  life.simulate();

  ostringstream w;
  life >> w;
  ASSERT_EQ(""
  "\nGeneration = 1, Population = 9.\n........\n"
  ".*...**.\n"
  ".*...**.\n"
  ".*...**.\n"
  "........\n",w.str());
}


TEST(FredkinCell, evolve1){
  istringstream i ("FredkinCell\n3\n3\n-0-\n000\n-0-");
  Life<FredkinCell> life(i,3,3);

  /*
  
    -0-
    000
    -0-

  */

  ostringstream w;
  life >> w;
  ASSERT_EQ("\nGeneration = 0, Population = 5.\n-0-\n000\n-0-\n",w.str());

  ConwayCell cell;

  ASSERT_FALSE(*cell);

  bool neighbors[8];

  life.get_neighbors(0,0,neighbors);

  cell.evolve(neighbors);

  ASSERT_TRUE(*cell);
}

TEST(FredkinCell, simulate){
  istringstream i ("FredkinCell\n3\n3\n-0-\n000\n-0-");
  Life<FredkinCell> life(i,3,3);
//  life << i;

  /*
  
    -0-
    000
    -0-

  */

  life.simulate();
  life.simulate();

  ostringstream w;
  life >> w;
  ASSERT_EQ("\nGeneration = 2, Population = 0.\n---\n---\n---\n",w.str());
}

TEST(FredkinCell, simulate_left){
  istringstream i ("FredkinCell\n3\n3\n0--\n0--\n0--");
  Life<FredkinCell> life(i,3,3);

  life.simulate();
  life.simulate();
  life.simulate();
  life.simulate();

  ostringstream w;
  life >> w;
  ASSERT_EQ("\nGeneration = 4, Population = 0.\n---\n---\n---\n",w.str());
}

TEST(FredkinCell, simulate_right){
  istringstream i ("FredkinCell\n3\n3\n--0\n--0\n--0");
  Life<FredkinCell> life(i,3,3);

  life.simulate();
  life.simulate();
  life.simulate();
  life.simulate();

  ostringstream w;
  life >> w;
  ASSERT_EQ("\nGeneration = 4, Population = 0.\n---\n---\n---\n",w.str());
}

TEST(FredkinCell, simulate_top){
  istringstream i ("FredkinCell\n3\n3\n000\n---\n---");
  Life<FredkinCell> life(i,3,3);

  life.simulate();
  life.simulate();
  life.simulate();
  life.simulate();

  ostringstream w;
  life >> w;
  ASSERT_EQ("\nGeneration = 4, Population = 0.\n---\n---\n---\n",w.str());
}

TEST(FredkinCell, simulate_bottom){
  istringstream i ("FredkinCell\n3\n3\n---\n---\n000");
  Life<FredkinCell> life(i,3,3);

  life.simulate();
  life.simulate();
  life.simulate();
  life.simulate();

  ostringstream w;
  life >> w;
  ASSERT_EQ("\nGeneration = 4, Population = 0.\n---\n---\n---\n",w.str());
}

TEST(FredkinCell, simulate_full){
  istringstream i ("FredkinCell\n3\n3\n000\n000\n000");
  Life<FredkinCell> life(i,3,3);

  life.simulate();
  life.simulate();
  life.simulate();
  life.simulate();

  ostringstream w;
  life >> w;
  ASSERT_EQ("\nGeneration = 4, Population = 0.\n---\n---\n---\n",w.str());
}

  // Life<ConwayCell> life(3,3);
  // ostringstream w;
  // life >> w;
  // ASSERT_EQ("\n...\n...\n...\n",w.str());