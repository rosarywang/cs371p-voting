// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2016
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <vector>   // vector
#include <algorithm>// max_element, min_element
#include <utility>   // make_pair, pair
#include <ctime>
#include <iostream>


using namespace std;

// ----------------
// voting_candidate
// ----------------

int voting_candidate(const string& s){
    int num_of_candidate;
    istringstream sin1(s);
    sin1 >> num_of_candidate;
    return num_of_candidate;
}

// -------------------
// voting_parse_ballot
// -------------------

vector<int> voting_parse_ballot(string& s, int num_of_candidate){
    stringstream s_ballot;
    s_ballot << s;
    vector<int> ballot(num_of_candidate);
    for (int i = 0; i < num_of_candidate; ++i)
    {
        s_ballot >> ballot[i];
        ballot[i] = ballot[i]-1;
    }
    return ballot;
    
}

// ------------------------
// voting_loser_count_votes
// ------------------------

void voting_loser_count_votes(int total_ballots, vector<bool> &losers_list, vector<vector<int>> &votings, vector<int> &index_ballot, vector<int> &count) {
    // loop through the whole ballots to find loser
    for (int i = 0; i < total_ballots; ++i) {
        // if the next vote in the ballot is still loser, keep incrementing
        while (losers_list[votings[i][index_ballot[i]]] == true) {
            ++index_ballot[i];
            ++count[votings[i][index_ballot[i]]];
        }
    }
}

void voting_max_min_eval(int num_of_candidate, vector<bool> &losers_list, vector<int> &count, int &current_max, int &current_min) {

}
// ------------
// voting_solve
// ------------

void voting_solve (istream& r, ostream& w) {
    string s;
    int size;
    getline(r, s);
    istringstream sin1(s);
    sin1 >> size;
    getline(r,s);

    while (size--) {
        getline(r,s);
        int num_of_candidate = voting_candidate(s);

        vector<string> names(num_of_candidate);
        vector<bool> losers_list(num_of_candidate, false);

        for (int i = 0; i < num_of_candidate; ++i) {
            getline(r,s);
            names[i] = s;
        }

        vector<vector<int>> votings;
        vector<int> count(num_of_candidate, 0);

        int total_ballots = 0;
        while(getline(r, s) && s != "") {
            vector<int> ballot = voting_parse_ballot(s, num_of_candidate);
            int candidate = ballot.front();
            ++count[candidate];
            votings.push_back(ballot);
            
            if (r.eof())
                break;
            ++total_ballots;
        }


        vector<int> index_ballot(total_ballots, 0);
        int winner = -1;
        bool is_winner = false;
        int max_ele = *max_element(count.begin(), count.end());

        if (max_ele > total_ballots/2) {
            is_winner = true;
            winner = max_ele;
        }

        while (!is_winner) {
            int current_max = 0;
            int current_min = 1000;

            // loop through the whole ballots to find loser
            for (int i = 0; i < total_ballots; ++i) {
                // if the next vote in the ballot is still loser, keep incrementing
                while (losers_list[votings[i][index_ballot[i]]] == true) {
                    ++index_ballot[i];
                    ++count[votings[i][index_ballot[i]]];
                }
            }

            for (int i = 0; i < num_of_candidate; ++i) {
                if (!losers_list[i]) {
                    current_max = max(count[i], current_max);
                    current_min = min(count[i], current_min);
                }
            }
            
            bool is_tie = (current_max == current_min);
            bool pass_cutoff = (current_max > (total_ballots/2));
            if (is_tie || pass_cutoff) {
                winner = current_max;
                is_winner = true;
            } else {
                for (int i = 0; i < num_of_candidate; ++i)
                    if (current_min == count[i])
                        losers_list[i] = true;
            }
        }

        for (int i = 0; i < num_of_candidate; ++i)
            if (!losers_list[i] && winner == count[i])            
                cout << names[i] << endl;

        if(r.eof())
            break;
        w << endl;
    }
}

int main () {
    using namespace std;
    voting_solve(cin, cout);
    return 0;}