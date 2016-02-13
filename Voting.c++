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

// ----------------
// voting_candidate
// ----------------

int voting_candidate(const string& s){
    int num_of_candidate;
    istringstream sin(s);
    sin >> num_of_candidate;
    return num_of_candidate;
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
    //getline(r,s);
    while (getline(r, s) && !r.eof()) {
        int num_of_candidate = voting_candidate(s);
        string name[20];
        for (int i = 0; i < num_of_candidate; ++i)
        {
            getline(r,s);
            /*function*/
            name[i] = s;
            w << name[i] << endl;
        }
        string ballot[1000];
        int i = 0;
        while(!s.empty() && !r.eof()){
            getline(r,s);
            if(!s.empty()) {
                /*function*/
                ballot[i] = s;
                w << ballot[i] << endl;
                ++i;
            }
            
        }
        //eval_loser loser boolean
        //eval_tie break tie 
        // collatz_print(w, i, j, v);
    }
}
