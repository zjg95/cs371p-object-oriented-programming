// --------------------------
// projects/life/Life.h
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------

// --------
// includes
// --------

#include <iostream> // istream, ostream
#include <string>   // string
#include <utility>  // pair
#include <vector>
#include <list>
#include <algorithm>

#include "Life.h"

using namespace std;

vector<int> life_read(istream& r){
	vector<int> array;
	string s;
	getline(r,s);
	int type;
	if (s == "ConwayCell")
		type = 1;
	else if (s == "FredkinCell")
		type = 2;
	else
		type = 0;
	array.push_back(type);
	int x, y;

	r >> x;
	r >> y;

	array.push_back(x);
	array.push_back(y);
	return array;
}