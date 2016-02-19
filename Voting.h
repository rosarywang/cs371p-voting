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
#include <list>

using namespace std;

// ----------------
// voting_candidate
// ----------------

/**
 * read one int
 * @param s a string
 * @return a int, representing the number of candidate in this test case
 */
int voting_candidate(const string& s);

// -------------------
// voting_parse_ballot
// -------------------

/**
 * parse through all the ballot and assign votes to canidate
 * @param s as string, i as int, num_of_candidate as int
 * @retuen a vetor<int>, containing each line of the ballot
 */
vector<int> voting_parse_ballot(string& s, int num_of_candidate);

// ------------
// voting_solve
// ------------

/**
 * @param r an istream
 * @param w an ostream
 */
void voting_solve (istream& r, ostream& w);

#endif // Voting_h
