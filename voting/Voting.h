#ifndef Voting_h
#define Voting_h

#include <iostream> // istream, ostream
#include <string>   // string

using namespace std;

#define MAX_BALLOTS 1001
#define MAX_CANDIDATES 21

int voting_read_int (const string& s);
void voting_eval (struct candidate candidates[], int num_candidates, struct ballot ballots[], int num_ballots);
void voting_solve (istream& r, ostream& w);

#endif // Voting_h
