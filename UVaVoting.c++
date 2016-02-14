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
#include <utility>  // make_pair, pair
#include <algorithm>

// #include "Collatz.h"

using namespace std;

//array<list<int>, 20> candidate_ballot;
int candidate_ballot[1000][20];
int candidate_total_votes[20];
bool candidate_loser[20];

// ----------------
// voting_candidate
// ----------------

int voting_candidate(const string& s){
    int num_of_candidate;
    istringstream sin(s);
    sin >> num_of_candidate;
    return num_of_candidate;
}

// ---------------
// voting_max_eval
// ---------------

int voting_max_eval(int num_of_candidate) {
    int max = 0;
    for(int i = 0; i < num_of_candidate; ++i) {
        // printf("candidate_total_vote = %d\n", candidate_total_votes[i]);
        if(max < candidate_total_votes[i])
            max = candidate_total_votes[i];
    }

    return max;
}

// ---------------
// voting_min_eval
// ---------------

void voting_min_eval(int num_of_candidate, int ballot) {
    int min = 1000;
    for(int i =0; i < num_of_candidate; ++i)
        if(!candidate_loser[i] && min > candidate_total_votes[i])
            min = candidate_total_votes[i];
    //w << "138 min "<< min << endl; 
    for(int i =0; i < num_of_candidate; ++i)
        if(min == candidate_total_votes[i])
            candidate_loser[i] = true;

    for(int i = 0; i < ballot; ++i){
        int c = candidate_ballot[i][0]-1;
        if(candidate_loser[c] && min == candidate_total_votes[c]){
            int j = 1;
            c = candidate_ballot[i][j]-1;
            while(candidate_loser[c]){
                ++j;
                c = candidate_ballot[i][j]-1;
            }
            ++candidate_total_votes[c];
        }
    }
}

// -------------------
// voting_parse_ballot
// -------------------

void voting_parse_ballot(const string& s, int i, int num_of_candidate){

    stringstream stream(s);
    int j = 0;

    while(num_of_candidate > 0){
        int n;
        stream >> n;

        if(j == 0)
            ++candidate_total_votes[n-1];
        candidate_ballot[i][j] = n;

        ++j;
        --num_of_candidate;
    }
}

// void voting_candidate_name(int num_of_candidate, istream& r, ostream& w, string candidate_names[]) {

//     string s;
//     for (int i = 0; i < num_of_candidate; ++i) {
//         getline(r,s);
//         // w << s << endl;
//         candidate_names[i] = s;

//     }
// }


// ------------
// collatz_read
// ------------

// pair<int, int> collatz_read (const string& s) {
//     istringstream sin(s);
//     int i;
//     int j;
//     sin >> i >> j;
//     return make_pair(i, j);}

// // ------------
// // collatz_eval
// // ------------

// int collatz_eval (int i, int j) {
//     // <your code>
//     return 1;}

// // -------------
// // collatz_print
// // -------------

// void collatz_print (ostream& w, int i, int j, int v) {
//     w << i << " " << j << " " << v << endl;}

// -------------
// voting_solve
// -------------

void voting_solve (istream& r, ostream& w) {
    string s;
    //voting_sample_size
    //read the first line, where the number of samples in the test
    int size;
    getline(r, s);
    istringstream sin1(s);
    sin1 >> size;
    
    //get the number of candidate in each sample
    getline(r,s);
    while (getline(r, s) && !r.eof()) {
        int num_of_candidate = voting_candidate(s);
        fill(candidate_total_votes, candidate_total_votes+20, 0);
        fill( &candidate_ballot[0][0], &candidate_ballot[0][0] + sizeof(candidate_ballot)/sizeof(candidate_ballot[0][0]), 0 );
        fill(candidate_loser, candidate_loser+20, false);
        string candidate_names[20] = { "" };

        for (int i = 0; i < num_of_candidate; ++i) {
            getline(r,s);
            candidate_names[i] = s;
        }

        int i = 0;
        while(!s.empty() && !r.eof()){
            getline(r,s);
            if(!s.empty()) {
                voting_parse_ballot(s, i, num_of_candidate);
                ++i;
            }    
        }
        int ballot = i;
        int max = voting_max_eval(num_of_candidate);
        int cutoff = ballot/2;
        int winner_vote = 0;
        
        while(max <= cutoff && winner_vote<ballot){
            winner_vote = 0;
            voting_min_eval(num_of_candidate, ballot);
            max = voting_max_eval(num_of_candidate);
            for(int i =0; i < num_of_candidate; ++i)
                if(max == candidate_total_votes[i])
                    winner_vote+=max;
        }
        for(int i =0; i < num_of_candidate; ++i){
            if(max == candidate_total_votes[i])
                w << candidate_names[i] << endl;
        }
        --size;
        if(size>0)
            w << endl;

    }
}

int main () {
    using namespace std;
    voting_solve(cin, cout);
    return 0;}