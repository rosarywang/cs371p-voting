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

// #include "Collatz.h"

using namespace std;

//array<list<int>, 20> candidate_ballot;
int candidate_ballot[1000][20];

// ----------------
// voting_candidate
// ----------------

int voting_candidate(const string& s){
    int num_of_candidate;
    istringstream sin(s);
    sin >> num_of_candidate;
    return num_of_candidate;
}

// -------------------
// voting_parse_ballot
// -------------------

void voting_parse_ballot(const string& s, int i){

    stringstream stream(s);

    int j = 0;

    while(1){
        int n;
        stream >> n;
        if(!stream)
            break;
        candidate_ballot[i][j] = n;
        ++j;
    }
}


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
        int candidate_total_votes[20]= {0};
        string candidate_names[20] = { "" };
        bool candidate_loser[20] = { false };
        candidate_ballot[1000][20] ={0};
        int ballot;
        for (int i = 0; i < num_of_candidate; ++i)
        {
            getline(r,s);
            /*function*/
            candidate_names[i] = s;
           // w << candidate_names[i] << endl;
        }
        int i = 0;
        while(!s.empty() && !r.eof()){
            getline(r,s);
            if(!s.empty()) {
                voting_parse_ballot(s, i);
                ++i;
            }    
        }
        ballot = i;
        for(int i = 0; i < ballot; ++i){
            int first_vote = candidate_ballot[i][0]-1;
            ++candidate_total_votes[first_vote];
        }
        int max = -1;
        for(int i =0; i < num_of_candidate; ++i)
            if(max < candidate_total_votes[i])
                max = candidate_total_votes[i];
       // w << "128 max "<< max << endl;        
        int cutoff = ballot/2;
        //w << "13 cutoff "<< cutoff << endl; 
        int winner_vote = 0;
        while(max <= cutoff && winner_vote<ballot){
            int min = 1000;
            winner_vote = 0;
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
            max = -1;
            for(int i =0; i < num_of_candidate; ++i)
                if(max < candidate_total_votes[i])
                    max = candidate_total_votes[i];
           // w << "158 max "<< max << endl;
            for(int i =0; i < num_of_candidate; ++i)
                if(max == candidate_total_votes[i])
                    winner_vote+=max;
            //w << "162 winner_vote "<< winner_vote << endl;
        }
        // for(int i =0; i < num_of_candidate; ++i)
        //    w << candidate_total_votes[i] << endl;
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