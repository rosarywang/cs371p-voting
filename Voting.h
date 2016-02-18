// --------------------------
// projects/Voting/Voting.h
// Copyright (C) 2016
// Glenn P. Downing
// --------------------------

#ifndef Voting_h
#define Voting_h

// --------
// includes
// --------

#include <iostream> // istream, ostream
#include <string>   // string
#include <vector>   // vector

using namespace std;

// ---------
// Candidate
// ---------

/**
 * Constructors: Candidate()
 * Function: reset()
 * Attributes:
 *	string c_name
 *	bool is_loser
 *	int current_vote
 *	vector<vector<int>> c_ballt
 */

class Candidate {
public:
    string c_name;
    bool is_loser;
    int current_vote;
    vector<vector<int>> c_ballot;
    Candidate();
    void reset();
};

// --------------
// candidate_list
// --------------

extern Candidate candidate_list[];

// ---------------------
// candidate_total_votes
// ---------------------

extern vector<int> candidate_total_votes;

// ----------------
// voting_candidate
// ----------------

/**
 * read one int
 * @param s a string
 * @return a int, representing the number of candidate in this test case
 */
int voting_candidate(const string& s);

// ---------------
// voting_min_eval
// ---------------

/**
 * find min value in the list
 * determine the loser using min value
 * reassign loser's vote to remaining winner
 * @param num_of_candidate as int
 */
void voting_min_eval(int num_of_candidate);

// -------------------
// voting_parse_ballot
// -------------------

/**
 * parse through all the ballot and assign votes to canidate
 * @param s as string, i as int, num_of_candidate as int
 */
void voting_parse_ballot(const string& s, int num_of_candidate);

// ------------
// voting_solve
// ------------

/**
 * @param r an istream
 * @param w an ostream
 */
void voting_solve (istream& r, ostream& w);

#endif // Collatz_h
