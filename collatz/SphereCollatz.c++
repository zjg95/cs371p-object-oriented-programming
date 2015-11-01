// -------------------------------
// projects/collatz/RunCollatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// -------------------------------

// -------
// defines
// -------

#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif

// --------
// includes
// --------

#include <iostream> // cin, cout

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair

using namespace std;

// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// ----------------------------

// ------------
// collatz_read
// ------------

pair<int, int> collatz_read (const string& s) {
    istringstream sin(s);
    int i;
    int j;
    sin >> i >> j;
    return make_pair(i, j);}

// ------------
// collatz_eval
// ------------
#define cache_length 100000
int cache[cache_length];

int cycle_recurse_cache (int n){
    assert (n>0);
    if (n==1)
        return 1;
    if (n < cache_length && cache[n]>0) // cache entry is already defined
        return cache[n];
    int next_num = (n%2==0) ? n/2 : (n*3)+1; // the next number in the cycle
    int result = 1 + cycle_recurse_cache(next_num); // recurse, defining cache entries as we go
    assert(result>0);
    if (n < cache_length) // if a slot exists in the cache, define the entry
        cache[n] = result;
    return result;
}
int collatz_eval (int i, int j) {
    assert (i>0 && j > 0);
    if (i>j){ // switch i and j so that j is bigger
        int temp = i;
        i = j;
        j = temp;
    }
    int max_cycle = 1;
    for (; i<=j; i++){
        int current_cycle = cycle_recurse_cache(i);
        if (current_cycle > max_cycle) // if this cycle is higher than the max, make it the new max
            max_cycle = current_cycle;
    }
    assert(max_cycle > 0);
    return max_cycle;}

// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
    string s;
    while (getline(r, s)) {
        const pair<int, int> p = collatz_read(s);
        const int            i = p.first;
        const int            j = p.second;
        const int            v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}

// ----
// main
// ----

int main () {
    using namespace std;
    collatz_solve(cin, cout);
    return 0;}