// --------------------------
// projects/life/Life.h
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------

#ifndef Life_h
#define Life_h

// --------
// includes
// --------

#include <iostream> // istream, ostream
#include <string>   // string
#include <utility>  // pair
#include <stdexcept> // invalid_argument
#include <vector>
#include <list>
#include <algorithm> // swap
#include "gtest/gtest_prod.h"

using namespace std;

template <typename T>
class Handle {
    friend bool operator == (const Handle& lhs, const Handle& rhs) {
        if (!lhs._p && !rhs._p)
            return true;
        if (!lhs._p || !rhs._p)
            return false;
        return (*lhs._p == *rhs._p);}

    friend bool operator != (const Handle& lhs, const Handle& rhs) {
        return !(lhs == rhs);}

    public:
        typedef T                 value_type;

        typedef value_type*       pointer;
        typedef const value_type* const_pointer;

        typedef value_type&       reference;
        typedef const value_type& const_reference;

    private:
        pointer _p;

    protected:
        pointer get () {
            return _p;}

        const_pointer get () const {
            return _p;}

    public:
        Handle (pointer p) {
            _p = p;}

        Handle (bool t) {
        	get()->alive = t;
        }

        Handle (const Handle& that){
            if (!that._p)
                _p = 0;
            else
                _p = that._p->clone();}

        ~Handle () {
            delete _p;}

        Handle& operator = (Handle that){
            swap(that);
            return *this;}

        void swap (Handle& that) {
            std::swap(_p, that._p);}};

class AbstractCell {
	friend ostream& operator << (ostream& w, const AbstractCell& cell){
        return cell.print(w);
    }

public:
	bool alive;
/**
 * Each cell must be able to print itself.
 *   ConwayCell prints '*' for alive or '.' for dead
 *   FredkinCell prints its age if alive or '-' if dead
 * @param ostream an output stream
 * @return ostream the output stream
 */			
	virtual ostream& print(ostream& w) const = 0;

	AbstractCell(){
		alive = false;
	}

	AbstractCell(bool t){
		alive = t;
	}

	virtual ~AbstractCell(){}

	bool& operator*(){
		return alive;
	}

	bool operator*() const{
		return alive;
	}

	virtual void evolve(bool neighbors[]) = 0;

  virtual AbstractCell* clone () const = 0;
};

class Cell : Handle<AbstractCell> {
    friend ostream& operator << (ostream& w, Cell rhs) {
        return rhs.operator>>(w);
    }
private:
	unsigned int age;
public:
	//Cell () : age(0) {}
	Cell (AbstractCell* p) : Handle<AbstractCell> (p) {}
	Cell(bool t) : Handle<AbstractCell> (t) {}


/**
 * From one generation to the next the rules are:
 *   a dead cell becomes a live cell, if exactly 3 neighbors are alive
 *   a live cell becomes a dead cell, if less than 2 or more than 3 neighbors are alive
 * @param neighbors An 8-member bool array indicating which neighbors are alive
 */		
	void evolve(bool neighbors[]) {
		get()->evolve(neighbors);
	}

	ostream& operator>>(ostream& w){
		if (!get())
			return w << "N";
		return w << *get();
	}

	Cell* clone () { 
  	return new Cell(*this);}  	
};

class ConwayCell : public AbstractCell {
public:

	ConwayCell() : AbstractCell() {}
	ConwayCell(bool t) : AbstractCell(t) {}

	virtual ostream& print(ostream& w) const{
		return (alive) ? w << "*" : w << ".";
	}

/**
 * From one generation to the next the rules are:
 *   a dead cell becomes a live cell, if exactly 3 neighbors are alive
 *   a live cell becomes a dead cell, if less than 2 or more than 3 neighbors are alive
 * @param neighbors An 8-member bool array indicating which neighbors are alive
 */		
	void evolve(bool neighbors[]){
		int alive_count = 0;
		for (int i = 0; i < 8; ++i)
			if (neighbors[i])
				++alive_count;
		
		if (alive_count == 3)
			alive = true;
		if (alive_count < 2 || alive_count > 3)
			alive = false;
	}

	virtual ConwayCell* clone () const { 
  	return new ConwayCell(*this);}  	
};

class FredkinCell : public AbstractCell{
private:
	unsigned int age;
public:

	FredkinCell() : AbstractCell(), age(0) {}
	FredkinCell(bool t) : AbstractCell(t), age(0) {}


	virtual ostream& print(ostream& w) const{
		return (alive) ? w << age % 10 : w << "-";
	}

/**
 * From one generation to the next the rules are:
 *   a dead cell becomes a live cell, if 1 or 3 neighbors are alive
 *   a live cell becomes a dead cell, if 0, 2, or 4 neighbors are alive
 * @param neighbors An 8-member bool array indicating which neighbors are alive
 */
	void evolve(bool neighbors[]){
		int alive_count = 0;
		if (neighbors[1])
			++alive_count;
		if (neighbors[3])
			++alive_count;
		if (neighbors[4])
			++alive_count;
		if (neighbors[6])
			++alive_count;

		if (alive_count == 1 || alive_count == 3){
			if (alive)
				age++;
			alive = true;
		}
		if (alive_count == 0 || alive_count == 2 || alive_count == 4)
			alive = false;
	}

	virtual FredkinCell* clone () const { 
  	return new FredkinCell(*this);}  	
};

template <typename T>
class Life {
private:
	FRIEND_TEST(Life, read1);
	FRIEND_TEST(Life, read2);
	FRIEND_TEST(Life, read3);

private:
	int gen;
	int rows;
	int columns;
	vector<vector <T> > array;

public:
	Life() : gen(0), rows(0), columns(0) {}
  Life(int r, int c) : gen(0), rows(r), columns(c) {
		for (int i = 0; i < rows; ++i) {
			vector <T> RowVector(columns, T(false));
			array.push_back(RowVector);
		}
  }
/**
 * Constructor for Life. Sample invocation for 3x4 grid with ConwayCells
 * from the default input stream:
 * 
 * Life<ConwayCell> life(cin, 3, 4);
 * @param s the input stream
 * @param rows the number of rows 
 * @param cols the number of columns
 */
	Life(istream& s, int r, int c){
		gen = 0;
		rows = r;
		columns = c;
		*this << s;
	}

/**
 * Parse input and build the grid.  Pushes a row of dead Cells
 * onto the array, then makes some alive based on the input.
 * @param r an input stream
 * @return the input stream
 */	
	istream& operator<<(istream& r){
		read(r);
		string s;

		for (int row = 0; row < rows; row++){
			r >> s;
			vector <T> RowVector(columns, T(false));
			array.push_back(RowVector);

			for (int col = 0; col < columns; ++col){
				try {
					int value = (int)s.at(col);
					if (value != '0' && value != '.' && value != '-' && value != '*')
	          throw std::invalid_argument( "Value received is not an acceptable input! [0-.*]");
              switch (value) {
              	case('0'):
              	case('*'): array[row][col] = true; 
              		break;
              	case('-'):
              	case('.'): array[row][col] = false; 
              		break;
              	default: cout << "unknown value!" << endl;
              }
        }
      	catch (const std::out_of_range& oor) {
      		cout << "ERROR! Trying to get index " << col << ". expected string size is " << columns << endl;
      		cout << "Bad String = '" << s << "'" << endl;
      	    throw std::invalid_argument("String is too short!");
      	}
			}
		}
		return r;
	}

	ostream& operator>>(ostream& w) const{
		w << endl;
		w << "Generation = " << gen << ", Population = " << count_living() << "." << endl;

		for (int y = 0; y < rows; y++){
			for (int x = 0; x < columns; x++){
				w << array[y][x];
			}
			w << endl;
		}
		return w;
	}

/**
 * Determine which neighbors are alive 
 * @param c the column the cell is in
 * @param r the row the cell is in
 * @param neighbors a bool array indicating which neighbors are alive
 */	
	void get_neighbors(int r, int c, bool neighbors[]) const{
		/*
		0 1 2
		3 X 4
		5 6 7
		*/
		neighbors[0] = (r > 0 && c > 0) ? *array[r-1][c-1] : false;
		neighbors[1] = (r > 0) ? *array[r-1][c] : false;
		neighbors[2] = (c + 1 < columns && r > 0) ? *array[r-1][c+1] : false;
		neighbors[3] = (c > 0) ? *array[r][c-1] : false;
		neighbors[4] = (c + 1 < columns) ? *array[r][c+1] : false;
		neighbors[5] = (c > 0 && r + 1 < rows) ? *array[r+1][c-1] : false;
		neighbors[6] = (r + 1 < rows) ? *array[r+1][c] : false;
		neighbors[7] = (c + 1 < columns && r + 1 < rows) ? *array[r+1][c+1] : false;
	}

/**
 * Have the cell suicide or survive based on the state of the neighbors 
 * @param row the row the cell is in
 * @param col the column the cell is in
 * @param neighbors a bool array indicating which neighbors are alive
 */
	void evolve_cell(int row, int col, bool neighbors[]){
		array[row][col].evolve(neighbors);
	}

/**
 * Count the total number of living cells in the game 
 * @return an int indicating the number of live cells
 */
	int count_living() const{
		int count = 0;
		for (int y = 0; y < rows; y++)
			for (int x = 0; x < columns; x++)
				if (*array[y][x])
					count++;
		return count;
	}

/**
 * Throw away the first line of input and take the other two as dimensions
 * @param r an input stream
 */
	void read(istream& r){
		string s;
		r >> s;
		int x;
		int y;

		r >> x;
		r >> y;
		rows = x;
		columns = y; 
	}

/**
 * Have each cell in the grid decide whether to suicide or survive at once 
 * @param int argument added for overloading purposes
 */
	void simulate() {
		++gen;
		Life<T> copy = *this;
		assert(&copy != this);

		for (int row = 0; row < rows; ++row){
			for (int col = 0; col < columns; ++col){
				bool neighbors[8];
				copy.get_neighbors(row,col,neighbors);
				evolve_cell(row,col,neighbors);

			}
		}
	}  	
};

#endif // Life_h
