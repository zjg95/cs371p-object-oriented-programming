#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream

#include <string>   // getline, string
#include <list>

#include "Voting.h"

#include <string.h>
#include <stdexcept>

using namespace std;

struct ballot {

    int votes[MAX_CANDIDATES];
    int vote_pointer;
    int first_vote;
    int current_vote;
    int num_votes;
    bool valid;

    void construct(const string& s, int vote_num){
        vote_pointer = 0;
        valid = true;
        num_votes = vote_num;
        votes[num_votes] = -2; // set end of votes

        // fill ballot votes
        istringstream sin(s);
        for (int i = 0; i < num_votes; ++i){
            sin >> votes[i];
            votes[i]--;
        }
        current_vote = votes[vote_pointer];
        first_vote = current_vote;
    }
    bool has_next_vote(){
        return (vote_pointer<num_votes);
    }
    int next_vote(){
        current_vote = votes[vote_pointer++];
        return current_vote;
    }
};

struct candidate {

    string name;
    int vote_count;
    bool valid;

    void construct(istream& r){
        getline(r, name);
        valid = true;
        vote_count = 0;
    }
};

int voting_read_int (const string& s) { // given a string, returns an int
    istringstream sin(s);
    int i;
    sin >> i;
    return i;
}

void print_results(candidate candidates[], int num_candidates){
    cout << "results: ";
    for (int i = 0; i < num_candidates; ++i){
        cout << candidates[i].vote_count << " ";
    }
    cout << endl;
}

bool count_votes (candidate candidates[], int num_candidates, ballot ballots[], int num_ballots){
    cout << "counting votes\n";
    int vote_count = 0;
    for (int ballot_index = 0; ballot_index < num_ballots; ++ballot_index){
        cout << " checking ballot " << ballot_index << endl;
        if (!ballots[ballot_index].valid){
            cout << " invalid ballot\n";
            continue;
        }
        if (!ballots[ballot_index].has_next_vote()){
            cout << " no more votes for this ballot\n";
            ballots[ballot_index].valid = false;
            continue;
        }
        int vote = ballots[ballot_index].next_vote();
        if (!candidates[vote].valid){
            cout << " cannot vote for " << candidates[vote].name << endl;
            //ballots[ballot_index].valid = false; 
            --ballot_index; // causes a run time error
            continue;
        }
        cout << " voting for: " << candidates[vote].name << endl;
        candidates[vote].vote_count++;
        vote_count++;
    }
    return vote_count > 0;
}

void voting_eval (candidate candidates[], int num_candidates, ballot ballots[], int num_ballots) {
    //cout << "evaluating votes\n";

    int half = num_ballots / 2;

    // count the votes
    while (count_votes(candidates, num_candidates, ballots, num_ballots)){
        print_results(candidates,num_candidates);
        int highest_vote = 0;
        int lowest_vote = num_ballots;
        // does someone have more than half the votes?
        for (int i = 0; i < num_candidates; ++i){
            if (!candidates[i].valid)
                continue;
            int vote = candidates[i].vote_count;
            if (vote > half){
                cout << " candidate " << i << " has more than half the votes.\n";
                return;
            }
            if (vote > highest_vote)
                highest_vote = vote;
            if (vote > 0 && vote < lowest_vote)
                lowest_vote = vote;
        }
        cout << "nobody has more than half the votes\n";

        cout << "highest vote: " << highest_vote << endl;
        cout << "lowest_vote: " << lowest_vote << endl;

        if (highest_vote==lowest_vote){
            cout << "there is a tie\n";
            break;
        }

        // invalidate the ballots that voted for a winner
        for (int i = 0; i < num_ballots; ++i){
            // if (!ballots[i].valid)
            //     continue;
            int vote = ballots[i].current_vote;
            if (!candidates[vote].valid)
                continue;
            if (candidates[vote].vote_count > lowest_vote){
                cout << " ballot " << i << " voted for a non-loser (" << vote << ") and will not be considered\n";
                ballots[i].valid = false;
            }
            // invalidate the losers
            else if (candidates[vote].vote_count == lowest_vote){
                cout << " candidate " << vote << " has been eliminated\n";
                cout << " ballot " << i << " will be considered\n";
                candidates[vote].valid = false;
                ballots[i].valid = true;//
            }
        }
    }
    cout << "done evaluating\n";
}

void voting_print (ostream& w, string * word) {
    w << *word << endl;
}

void print_winner(ostream& w, candidate candidates[], int num_candidates){
    int highest_vote = 0;
    for (int i = 0; i < num_candidates; ++i){
        int vote = candidates[i].vote_count;
        if (vote>highest_vote)
            highest_vote = vote;
    }
    for (int i = 0; i < num_candidates; ++i){
        int vote = candidates[i].vote_count;
        if (vote==highest_vote)
            voting_print(w, &candidates[i].name);
    }
}

void print_ballot (ballot b, int num_ballots, int num_candidates){
    cout << " ballot " << num_ballots << ": ";
    for (int ballot_vote_index = 0; ballot_vote_index < num_candidates; ++ballot_vote_index)
        cout << b.votes[ballot_vote_index] << " ";
    cout << endl;
}

void voting_solve (istream& r, ostream& w) {
    string s;
    getline(r, s);
    int num_elections = voting_read_int(s);
    //cout << "number of elections: " << num_elections << endl;
    getline(r,s); // move down an extra line

    for (int election_index = 0; election_index < num_elections; ++election_index){
        getline(r,s); // candidate number
        int num_candidates = voting_read_int(s);
        //cout << " number of candidates: " << num_candidates << endl;

        candidate candidates[MAX_CANDIDATES]; // array of candidates

        // parse the candidates
        for (int candidate_index = 0; candidate_index < num_candidates; ++candidate_index){
            candidates[candidate_index].construct(r);
            //cout << "  candidate " << candidate_index << ": " << candidates[candidate_index].name << endl;
        }

        int num_ballots = 0;
        ballot ballots[MAX_BALLOTS]; // array of ballots

        // parse the ballots
        while (getline(r,s)){
            try {
                int first_char = (int)s.at(0);
                if (first_char < 49 || first_char > 57)
                    break;
            }
            catch (const std::out_of_range& oor) {
                break;
            }
            ballots[num_ballots].construct(s, num_candidates);

            // print_ballot(ballots[num_ballots],num_ballots);

            num_ballots++;
        }

        voting_eval(candidates, num_candidates, ballots, num_ballots);

        cout << "final ";
        print_results(candidates,num_candidates);

        print_winner(w, candidates, num_candidates);

        if (election_index+1 < num_elections)
            w << endl;
    }
}