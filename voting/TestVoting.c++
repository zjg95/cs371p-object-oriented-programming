
#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair

#include "gtest/gtest.h"

#include "Voting.h"

using namespace std;

TEST(Voting, solve) { // correct
    istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ("John Doe\n", w.str());
}
TEST(Voting, solve2_tie) { // Correct
    istringstream r("1\n\n3\nJane Smith\nJohn Doe\nSirhan Sirhan\n1 2 3\n2 1 3\n3 1 2\n");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ("Jane Smith\nJohn Doe\nSirhan Sirhan\n", w.str());
}
TEST(Voting, solve_two_elections) { // correct
    istringstream r("2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ("John Doe\n\nJohn Doe\n", w.str());
}
TEST(Voting, solve_three_elections) { // correct
    istringstream r("3\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ("John Doe\n\nJohn Doe\n\nJohn Doe\n", w.str()); // John Doe
}
TEST(Voting, solve_tie) { // correct
    istringstream r("1\n\n2\nJane Smith\nJohn Doe\n1 2\n2 1\n1 2\n2 1\n");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ("Jane Smith\nJohn Doe\n", w.str());
}

TEST(Voting, solve_1_otherstudent) {
    istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ("John Doe\n", w.str());}

TEST(Voting, solve_2_otherstudent) {
    istringstream r("2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ("John Doe\n\nJohn Doe\n", w.str());}

TEST(Voting, solve_3_otherstudent) {
    istringstream r("3\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n2 1 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ("John Doe\n\nJohn Doe\n\nJane Smith\n", w.str());}

TEST(Voting, voting_solve_1_otherstudent){
        istringstream r("1\n\n4\nJim\nJose\nCarter\nMichael\n1 2 3 4\n");
        ostringstream w;
        
    voting_solve(r, w);

        ASSERT_EQ(w.str(), "Jim\n");
}

TEST(Voting, voting_solve_2_otherstudent){
        istringstream r("2\n\n4\nJim\nJose\nCarter\nMichael\n1 2 3 4\n\n4\nJim\nJose\nCarter\nMichael\n1 2 3 4\n");
        ostringstream w;

        voting_solve(r, w);

        ASSERT_EQ(w.str(), "Jim\n\nJim\n");
}

TEST(Voting, voting_solve_3_otherstudent){
        istringstream r("1\n\n4\nJim\nJose\nCarter\nMichael\n1 2 3 4\n2 1 3 4\n");
        ostringstream w;

        voting_solve(r, w);

        ASSERT_EQ(w.str(), "Jim\nJose\n");
}

TEST(Voting, voting_solve_4_otherstudent){
        istringstream r("1\n\n4\nJim\nJose\nCarter\nMichael\n1 2 3 4\n2 1 3 4\n3 1 2 4\n 4 3 1 2");
        ostringstream w;

        voting_solve(r, w);

        ASSERT_EQ(w.str(), "Jim\nJose\nCarter\nMichael\n");
}

TEST(Voting, voting_solve_5_otherstudent){
        istringstream r("1\n\n4\nJim\nJose\nCarter\nMichael\n1 2 3 4\n1 2 3 4\n2 1 3 4\n2 1 3 4\n3 4 1 2");
        ostringstream w;

        voting_solve(r, w);

        ASSERT_EQ(w.str(), "Jim\n");
}

TEST(Voting, voting_solve_6_otherstudent){
        istringstream r("4\n\n1\nJim\n1\n\n1\nJose\n1\n\n1\nCarter\n1\n\n1\nMichael\n1");
        ostringstream w;

        voting_solve(r, w);

        ASSERT_EQ(w.str(), "Jim\n\nJose\n\nCarter\n\nMichael\n");
}

TEST(Voting, voting_solve_7_otherstudent){
        istringstream r("1\n\n0\n");
        ostringstream w;

        voting_solve(r, w);

        ASSERT_EQ(w.str(), "");
}

TEST(Voting, voting_solve_8_otherstudent){
        istringstream r("1\n\n7\nJim\nJose\nCarter\nMichael\nBaylor\nMatt\nB rian\n1 2 3 4 5 6 7\n1 2 3 4 5 6 7\n1 2 3 4 5 6 7\n2 7 3 4 5 6 1\n2 7 3 4 5 6 1\n3 2 7 4 5 6 1\n4 2 7 3 5 6 1\n");
        ostringstream w;

        voting_solve(r, w);

        ASSERT_EQ(w.str(), "Jose\n");
}
TEST(Voting, evalVoting_1_otherstudent) {
    istringstream iss("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
    ostringstream oss;
    voting_solve(iss, oss);
    ASSERT_EQ("John Doe\n", oss.str());
}

TEST(Voting, evalVoting_2_otherstudent) {
    istringstream iss("2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n2\nabc\ndef\n1 2\n1 2\n2 1\n");
    ostringstream oss;
    voting_solve(iss, oss);
    ASSERT_EQ("John Doe\n\nabc\n", oss.str());
}

TEST(Voting, evalVoting_3_otherstudent) {
    istringstream iss("1\n\n2\nA\nB");
    ostringstream oss;
    voting_solve(iss, oss);
    ASSERT_EQ("A\nB\n", oss.str());
}

TEST(Voting, evalVoting_4_otherstudent) {
    istringstream iss("1\n\n2\nA\nB\nC\n1 2 3\n1 2 3");
    ostringstream oss;
    voting_solve(iss, oss);
    ASSERT_EQ("A\n", oss.str());
}
TEST(Voting, solve_1_other){
    istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ("John Doe\n", w.str());
}

TEST(Voting, solve_2_other){
    istringstream r("2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ("John Doe\n\nJohn Doe\n", w.str());
}

TEST(Voting, solve_3_other){
    istringstream r("3\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n2 1 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ("John Doe\n\nJohn Doe\n\nJane Smith\n", w.str());
}

TEST(Voting, voting_solve_1_otherguy) {
    istringstream r("1\n\n2\nDennis Cheng\nChris Zahrah\n");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ("Dennis Cheng\nChris Zahrah\n", w.str());
}

TEST(Voting, voting_solve_2_otherguy) {
    istringstream r("1\n\n2\nDennis Cheng\nChris Zahrah\n1 2\n1 2\n2 1\n2 1");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ("Dennis Cheng\nChris Zahrah\n", w.str());
}

TEST(Voting, voting_solve_3_otherguy) {
    istringstream r("1\n\n1\nDennis Cheng");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ("Dennis Cheng\n", w.str());
}
TEST(Voting, solve_1_dude) {
    istringstream r("1\n\n1\nJohn Doe\n1\n");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ("John Doe\n", w.str());}

/*TEST(Voting, solve_3_dude) {
    istringstream r("1\n\n5\njhXYZVCH\nwYXaGVCD\nyPAIkZkv\nwFocuBKz\nFqsJmuex\n2 4 1 5 3\n5 4 2 1 3\n1 4 3 5 2\n5 3 1 4 2\n4 5 3 2 1\n2 4 5 1 3\n3 1 2 4 5\n2 4 1 5 3\n3 2 1 5 4\n4 1 3 2 5\n");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ("wYXaGVCD\nwFocuBKz\n", w.str());}*/

TEST(Voting, solve_2a_dude) {
    istringstream r("2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n5\nCaNvliuJ\ntznRtFHr\nsPIpiOWk\nQizkdufu\nGhWDeKnB\n3 2 5 1 4\n4 2 3 5 1\n2 3 4 1 5\n2 3 1 4 5\n4 2 5 1 3\n5 1 2 4 3\n5 1 2 3 4\n5 2 4 3 1\n3 5 1 2 4\n5 2 3 4 1\n");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ("John Doe\n\nGhWDeKnB\n", w.str());}

TEST(Voting, solve_2b_dude) {
    istringstream r("1\n\n5\nCalvin\nHarris\nJamie\nKickapoo\nJonathan\n3 2 5 1 4\n4 2 3 5 1\n2 3 4 1 5\n2 3 1 4 5\n4 2 5 1 3\n5 1 2 4 3\n5 1 2 3 4\n5 2 4 3 1\n3 5 1 2 4\n5 2 3 4 1\n");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ("Jonathan\n", w.str());}

TEST(Voting, voting_solveington)
{
  std::istringstream r("1\n\n4\nRed\nGreen\nBlue\nOrange\n1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1\n");
  std::ostringstream w;
  voting_solve(r, w);
  ASSERT_EQ("Red\nGreen\n", w.str());
}
TEST(Voting, voting_solve2ington)
{
  std::istringstream r("1\n\n2\nRed\nGreen\n1 2\n2 1\n2 1\n1 2\n1 2\n2 1\n");
  std::ostringstream w;
  voting_solve(r, w);
  ASSERT_EQ("Red\nGreen\n", w.str());
}


TEST(Voting, voting_solve3ington)
{
  std::istringstream r("1\n\n3\nRed\nGreen\nTaylor\n1 2 3\n3 2 1\n2 3 1\n1 2 3\n3 2 1\n2 1 3\n");
  std::ostringstream w;
  voting_solve(r, w);
  ASSERT_EQ("Red\nGreen\nTaylor\n", w.str());
}



/*
% ls -al /usr/include/gtest/
...
gtest.h
...



% locate libgtest.a
/usr/lib/libgtest.a
...



% locate libpthread.a
...
/usr/lib32/libpthread.a



% locate libgtest_main.a
/usr/lib/libgtest_main.a
...



% g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Voting.c++ TestVoting.c++ -o TestVoting -lgtest -lgtest_main -lpthread



% valgrind TestVoting        >  TestVoting.out 2>&1
% gcov-4.7 -b Voting.c++     >> TestVoting.out
% gcov-4.7 -b TestVoting.c++ >> TestVoting.out



% cat TestVoting.out
==14225== Memcheck, a memory error detector
==14225== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
==14225== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
==14225== Command: TestVoting
==14225==
Running main() from gtest_main.cc
[==========] Running 7 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 7 tests from Voting
[ RUN      ] Voting.read
[       OK ] Voting.read (31 ms)
[ RUN      ] Voting.eval_1
[       OK ] Voting.eval_1 (5 ms)
[ RUN      ] Voting.eval_2
[       OK ] Voting.eval_2 (3 ms)
[ RUN      ] Voting.eval_3
[       OK ] Voting.eval_3 (3 ms)
[ RUN      ] Voting.eval_4
[       OK ] Voting.eval_4 (3 ms)
[ RUN      ] Voting.print
[       OK ] Voting.print (17 ms)
[ RUN      ] Voting.solve
[       OK ] Voting.solve (10 ms)
[----------] 7 tests from Voting (88 ms total)

[----------] Global test environment tear-down
[==========] 7 tests from 1 test case ran. (132 ms total)
[  PASSED  ] 7 tests.
==14225==
==14225== HEAP SUMMARY:
==14225==     in use at exit: 0 bytes in 0 blocks
==14225==   total heap usage: 495 allocs, 495 frees, 70,302 bytes allocated
==14225==
==14225== All heap blocks were freed -- no leaks are possible
==14225==
==14225== For counts of detected and suppressed errors, rerun with: -v
==14225== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 2 from 2)
File 'Voting.c++'
Lines executed:100.00% of 17
Branches executed:100.00% of 18
Taken at least once:61.11% of 18
Calls executed:89.47% of 19
Creating 'Voting.c++.gcov'
...
File 'TestVoting.c++'
Lines executed:100.00% of 26
Branches executed:57.14% of 224
Taken at least once:28.57% of 224
Calls executed:54.07% of 209
Creating 'TestVoting.c++.gcov'
...
*/