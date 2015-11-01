// --------------------------
// projects/darwin/Darwin.h
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------

#ifndef Darwin_h
#define Darwin_h

// --------
// includes
// --------

#include <iostream> // istream, ostream
#include <string>   // string
#include <utility>  // pair
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

class instruction {
	public:
		string operation;
		int argument;
		bool action;

		instruction(const string& op, int arg){
			operation = op;
			argument = arg;
			if (operation.compare("hop") == 0 || operation.compare("left") == 0 || operation.compare("right") == 0 || operation.compare("infect") == 0)
				action = true;
			else
				action = false;
		}
		instruction& operator=(const instruction& rhs){
			operation = rhs.operation;
			argument = rhs.argument;
			action = rhs.action;
			return *this;
		}
};

class Species {
	private:
		char name;
		vector<instruction> code;
	public:
		unsigned int code_size;

	public:
		Species(char n){
			name = n;
			code_size = 0;
		}
		Species(const Species& copy){
			name = copy.name;
			code = copy.code;
			code_size = copy.code_size;
		}
		Species& operator=(const Species& copy){ // used when infected
			name = copy.name;
			code = copy.code;
			code_size = copy.code_size;
			return *this;
		}
		const instruction& get_instruction(int pc) const { // fetches next instruction
			return code[pc];
		}
		bool operator==(const Species& rhs) const {
			return (name == rhs.name);
		}
		void add_instruction(const string& op, int arg){
			code.push_back(instruction(op,arg));
			code_size++;
		}
		void add_instruction(const string& op){
			add_instruction(op, -1);
		}
		void print_name(ostream& w){
			w << name;
		}
};

class Creature {
	private:
		Species type;
		int pc;
	public:
		char direction;

		Creature(const Species& t, char d) : type(t), direction(d){
			pc = 0;
		}
		Creature(const Species& t, int d) : type(t){
			pc = 0;
			switch (d){
				case(0): 
					direction = 'w';
					break;
				case(1): 
					direction = 'n';
					break;
				case(2): 
					direction = 'e';
					break;
				case(3): 
					direction = 's';
					break;
				default: cout << "you ended up with number " << d << endl;
			}
		}
		Creature(const Creature& c) : type(c.type){
			pc = 0;
			direction = c.direction;
		}
		const instruction * next_instruction() { // fetches next instruction
			return &type.get_instruction(pc++);
		}
		Creature& operator=(const Creature& rhs){
			pc = 0;
			type = rhs.type;
			return *this;
		}
		bool operator==(const Creature& rhs) const {
			return (type == rhs.type);
		}
		void act(){
			/* TODO: make creature perform an action */
			instruction instr = type.get_instruction(pc);
		}
		void go(int n){
			pc = n;
		}
		void change_direction(char d){
			if (d == 'l'){
				if (direction == 'n')
					direction = 'w';
				else if (direction == 'w')
					direction = 's';
				else if (direction == 's')
					direction = 'e';
				else if (direction == 'e')
					direction = 'n';
			}
			else{
				if (direction == 'n')
					direction = 'e';
				else if (direction == 'e')
					direction = 's';
				else if (direction == 's')
					direction = 'w';
				else if (direction == 'w')
					direction = 'n';
			}
		}
		void print_name(ostream& w){
			type.print_name(w);
		}
};

template <typename T, int size_x, int size_y>
class Grid {
	private:
		T * array[size_y][size_x];

		pair<int,int> find(T* crea){
			int y;
			int x;
			for (y = 0; y < size_y; y++)
				for (x = 0; x < size_x; ++x)
					if (array[y][x] == crea)
						return make_pair(x,y);
			return make_pair(-1,-1);
		}
		bool equals(const Creature& lhs, const Creature& rhs) const{
			return (lhs == rhs);
		}

	public:
		Grid(){
			for (int y = 0; y < size_y; y++)
				for (int x = 0; x < size_x; ++x)
					array[y][x] = NULL;
		}
		void hop(Creature * crea){
			/*TODO add code*/
			pair<int,int> coords = find(crea);
			int x = coords.first;
			int y = coords.second;
			array[y][x] = NULL;
			if (crea->direction == 'w'){
				x = coords.first - 1;
			}
			else if (crea->direction == 'e'){
				x = coords.first + 1;
			}
			else if (crea->direction == 's'){
				y = coords.second + 1;
			}
			else { // north
				y = coords.second - 1;
			}
			array[y][x] = crea;
		}
		char inquire(Creature * crea){
			pair<int,int> coords = find(crea);
			int x;
			int y;
			if (crea->direction == 'w'){
				x = coords.first - 1;
				y = coords.second;
				if (x < 0)
					return 'w';
			}
			else if (crea->direction == 'e'){
				x = coords.first + 1;
				y = coords.second;
				if (x >= size_x)
					return 'w';
			}
			else if (crea->direction == 's'){
				x = coords.first;
				y = coords.second + 1;
				if (y >= size_y)
					return 'w';
			}
			else { // north
				x = coords.first;
				y = coords.second - 1;
				if (y < 0)
					return 'w';
			}
			if (array[y][x] == NULL)
				return 'n';
			return (equals(*crea,(Creature)*array[y][x])) ? 's' : 'e';
		}
		void infect(Creature * crea){
			/*TODO add code*/
			pair<int,int> coords = find(crea);
			int x = coords.first;
			int y = coords.second;
			if (crea->direction == 'w'){
				x = coords.first - 1;
			}
			else if (crea->direction == 'e'){
				x = coords.first + 1;
			}
			else if (crea->direction == 's'){
				y = coords.second + 1;
			}
			else { // north
				y = coords.second - 1;
			}
			*array[y][x] = *crea;
		}
		void print(ostream& w){
			w<< "  ";
			for (int x = 0; x<size_x; x++)
					w << x%10;
			w<< endl;
			for (int y = 0; y< size_y; y++){
				w<< y%10 << " ";
				for (int x = 0; x< size_x; x++){
					T * ptr = array[y][x];
					if (ptr != NULL){
						ptr->print_name(w);
					}
					else
						w<< '.';
				}
				w<< endl;
			}
		}
		T * get_next_creature(int it){
			// cout << "searching" << endl;
			static int iteration = it;
			static int iterator_x = 0;
			static int iterator_y = 0;
			static list<T*> visited;
			if (iteration != it){
				iteration = it;
				iterator_x = 0;
				iterator_y = 0;
				visited.clear();
			}
			while (iterator_y < size_y){
				while (iterator_x < size_x){
					if (array[iterator_y][iterator_x] != NULL){
						bool found = false;
						for (T * ptr : visited)
							if (ptr == array[iterator_y][iterator_x]){
								found = true;
								// cout << "visited" << endl;
								break;
							}
						if (!found){
							visited.push_back(array[iterator_y][iterator_x]);
							return array[iterator_y][iterator_x++];
						}
					}
					++iterator_x;
				}
				iterator_x = 0;
				++iterator_y;
			}
			// cout << "returning null" << endl;
			return NULL;
		}
		void add_creature(Creature * c, int x, int y){
			array[y][x] = c;
		}
};

template <int size_x, int size_y>
class Darwin{
	private:
		Grid<Creature, size_x,size_y> grid;
		list<Creature> creature_list;

		void simulate(int current, int goal){
			if (current > goal)
				return;
			cout << "Turn = " << current << "." << endl;
			Creature * creature;
			int session = rand();
			while ((creature = grid.get_next_creature(session)) != NULL){
				// cout << " inside while loop" << endl;
				const instruction * instr;
				do {
					// cout << "  inside do loop" << endl;
					instr = creature->next_instruction();
					interpret(creature,instr);
				} while (!instr->action);
			}
			print(cout);
			simulate(++current, goal);
		}
		void simulate_big(int current, int goal){
			if (current > goal)
				return;
			if (current < 10 || (current >= 100 && current % 100 == 0))
				cout << "Turn = " << current << "." << endl;
			Creature * creature;
			int session = rand();
			while ((creature = grid.get_next_creature(session)) != NULL){
				// cout << " inside while loop" << endl;
				const instruction * instr;
				do {
					// cout << "  inside do loop" << endl;
					instr = creature->next_instruction();
					interpret(creature,instr);
				} while (!instr->action);
			}
			
			if (current < 10 || (current >=100 && current % 100 == 0))
				print(cout);
			simulate_big(++current, goal);
		}
	public:
		void add_creature(const Creature& c, int pos_x, int pos_y){
			creature_list.push_back(Creature(c));
			grid.add_creature(&creature_list.back(), pos_x, pos_y);
		}
		void print(ostream& w){
			grid.print(w);
			w << endl;
		}
		void interpret(Creature * crea, const instruction * inst){
			// cout << "   interpreting" << endl;
			if (inst->operation.compare("hop") == 0){
				// cout << "    hop" << endl;
				char response = grid.inquire(crea);
				// cout << "     space ahead = " << response << endl;
				if (response == 'n'){
					// cout << "     hopping " << endl;
					grid.hop(crea);
				}
			}
			else if (inst->operation.compare("left") == 0){
				// cout << "    left" << endl;
				crea->change_direction('l');
			}
			else if (inst->operation.compare("right") == 0){
				// cout << "    right" << endl;
				crea->change_direction('r');
			}
			else if (inst->operation.compare("infect") == 0){
				// cout << "    infect" << endl;
				char response = grid.inquire(crea);
				// cout << "     space ahead = " << response << endl;
				if (response == 'e'){
					// cout << "     infecting " << endl;
					grid.infect(crea);
				}
			}
			else if (inst->operation.compare("if_empty") == 0){
				// cout << "    if_empty" << endl;
				char response = grid.inquire(crea);
				// cout << "    space ahead = " << response << endl;
				if (response == 'n'){
					// cout << "     going " << inst->argument << endl;
					crea->go(inst->argument);
				}
			}
			else if (inst->operation.compare("if_wall") == 0){
				// cout << "    if_wall" << endl;
				char response = grid.inquire(crea);
				// cout << "     space ahead = " << response << endl;
				if (response == 'w'){
					// cout << "     going " << inst->argument << endl;
					crea->go(inst->argument);
				}
			}
			else if (inst->operation.compare("if_random") == 0){
				srand(0);
				// cout << "    if_random" << endl;
				int response = rand() % 2;
				// cout << "    random = " << response << endl;
				if (response != 0){
					// cout << "     going " << inst->argument << endl;
					crea->go(inst->argument);
				}
			}
			else if (inst->operation.compare("if_enemy") == 0){
				// cout << "    if_enemy" << endl;
				char response = grid.inquire(crea);
				// cout << "     space ahead = " << response << endl;
				if (response == 'e'){
					// cout << "     going " << inst->argument << endl;
					crea->go(inst->argument);
				}
			}
			else /*if (inst->operation.compare("go") == 0)*/{
				// cout << "    go " << inst->argument << endl;
				// cout << "     going " << inst->argument << endl;
				crea->go(inst->argument);
			}
		}
		void simulate(int goal){
			cout << "Turn = 0." << endl;
			print(cout);
			simulate(1,goal);
		}
		void simulate_big(int goal){
			cout << "Turn = 0." << endl;
			print(cout);
			simulate_big(1,goal);
		}
};

#endif // Darwin_h