// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string

#include "gtest/gtest.h"

#include "Voting.h"

using namespace std;

// ----------
// TestVoting
// ----------

// ---------
// candidate
// ---------

TEST(VotingFixture, candidate_1) {
    string s("1\n");
    const int p = voting_candidate(s);
    ASSERT_EQ(1, p);
}

TEST(VotingFixture, candidate_2) {
    string s("10\n");
    const int p = voting_candidate(s);
    ASSERT_EQ(10, p);
}

TEST(VotingFixture, candidate_3) {
    string s("20\n");
    const int p = voting_candidate(s);
    ASSERT_EQ(20, p);
}

// ------------
// parse_ballot
// ------------

TEST(VotingFixture, parse_1) {
    const vector<int> result = {0, 1, 1, 3, 2};
    string s("1 2 2 4 3\n");
    vector<int> test = voting_parse_ballot(s, 5);
    ASSERT_EQ(result, test);
}

TEST(VotingFixture, parse_2) {
    const vector<int> result = {1, 1, 1};
    string s("2 2 2\n");
    vector<int> test = voting_parse_ballot(s, 3);
    ASSERT_EQ(result, test);
}

TEST(VotingFixture, parse_3) {
    const vector<int> result = {0};
    string s("1\n");
    vector<int> test = voting_parse_ballot(s, 1);
    ASSERT_EQ(result, test);
}

// -----
// solve
// -----

TEST(VotingFixture, solve_1) {
    istringstream r("2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n2\nA\nB\n1 2\n2 1");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ("John Doe\n\nA\nB\n", w.str());
}

TEST(VotingFixture, solve_2) {
    istringstream r("1\n\n4\nA\nB\nC\nD\n1 2 3 4\n2 3 4 1\n3 4 1 2\n 4 1 2 3");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ("A\nB\nC\nD\n", w.str());
}

TEST(VotingFixture, solve_3) {
    istringstream r("1\n\n3\nA\n1\n1\n1\n1\n1");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ("A\n", w.str());
}

/*
% g++ -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Voting.c++ TestVoting.c++ -o TestVoting -lgtest -lgtest_main -lpthread



% valgrind TestVoting                                         >  TestVoting.out 2>&1
% gcov -b Voting.c++     | grep -A 5 "File 'Voting.c++'"     >> TestVoting.out
% gcov -b TestVoting.c++ | grep -A 5 "File 'TestVoting.c++'" >> TestVoting.out



% cat TestVoting.out
==14225== Memcheck, a memory error detector
==14225== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
==14225== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
==14225== Command: TestVoting
==14225==
Running main() from gtest_main.cc
[==========] Running 7 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 7 tests from Voting
[ RUN      ] Voting.read
[       OK ] Voting.read (31 ms)
[ RUN      ] Voting.eval_1
[       OK ] Voting.eval_1 (5 ms)
[ RUN      ] Voting.eval_2
[       OK ] Voting.eval_2 (3 ms)
[ RUN      ] Voting.eval_3
[       OK ] Voting.eval_3 (3 ms)
[ RUN      ] Voting.eval_4
[       OK ] Voting.eval_4 (3 ms)
[ RUN      ] Voting.print
[       OK ] Voting.print (17 ms)
[ RUN      ] Voting.solve
[       OK ] Voting.solve (10 ms)
[----------] 7 tests from Voting (88 ms total)

[----------] Global test environment tear-down
[==========] 7 tests from 1 test case ran. (132 ms total)
[  PASSED  ] 7 tests.
==14225==
==14225== HEAP SUMMARY:
==14225==     in use at exit: 0 bytes in 0 blocks
==14225==   total heap usage: 495 allocs, 495 frees, 70,302 bytes allocated
==14225==
==14225== All heap blocks were freed -- no leaks are possible
==14225==
==14225== For counts of detected and suppressed errors, rerun with: -v
==14225== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 2 from 2)
File 'Voting.c++'
Lines executed:100.00% of 17
Branches executed:100.00% of 18
Taken at least once:61.11% of 18
Calls executed:89.47% of 19
Creating 'Voting.c++.gcov'
File 'TestVoting.c++'
Lines executed:100.00% of 26
Branches executed:57.14% of 224
Taken at least once:28.57% of 224
Calls executed:54.07% of 209
Creating 'TestVoting.c++.gcov'
*/
