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

using namespace std;

// ----------------
// voting_candidate
// ----------------

int voting_candidate(const string& s) {
    int num_of_candidate;
    istringstream sin1(s);
    sin1 >> num_of_candidate;
    assert(num_of_candidate > 0 && num_of_candidate < 21);
    return num_of_candidate;
}

// -------------------
// voting_parse_ballot
// -------------------

vector<int> voting_parse_ballot(string& s, int num_of_candidate) {
    stringstream s_ballot;
    s_ballot << s;
    vector<int> ballot(num_of_candidate);
    for (int i = 0; i < num_of_candidate; ++i) {
        s_ballot >> ballot[i];
        ballot[i] = ballot[i]-1;
    }
    return ballot;
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
        assert(num_of_candidate > 0 && num_of_candidate < 21);

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

        assert(total_ballots < 1001);

        vector<int> index_ballot(total_ballots, 0);
        int winner = -1;
        bool is_winner = false;

        int current_max = *max_element(count.begin(), count.end());
        int current_min = 1000;

        if (current_max > total_ballots/2) {
            is_winner = true;
            winner = current_max;
        }

        while (!is_winner) {
            current_max = 0;
            current_min = 1000;

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
        assert((current_max == current_min) || (current_max > (total_ballots/2)));

        for (int i = 0; i < num_of_candidate; ++i)
            if (!losers_list[i] && winner == count[i])            
                w << names[i] << endl;

        if(r.eof())
            break;
        w << endl;
    }
}
int main () {
    using namespace std;
    voting_solve(cin, cout);
    return 0;}