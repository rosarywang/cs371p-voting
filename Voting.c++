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
#include <list>
#include "Voting.h"
#include <ctime>
#include <iostream>


using namespace std;

Candidate:: Candidate() {
    is_loser = false;
    current_vote = 0;
}

void Candidate:: reset() {
    c_name = "";
    is_loser = false;
    current_vote = 0;
    c_ballot.clear();
}
Candidate candidate_list[] = {Candidate(), Candidate(), Candidate(), Candidate(), Candidate(), 
                              Candidate(), Candidate(), Candidate(), Candidate(), Candidate(), 
                              Candidate(), Candidate(), Candidate(), Candidate(), Candidate(), 
                              Candidate(), Candidate(), Candidate(), Candidate(), Candidate()};

vector<int> candidate_total_votes;
list<int> eliminated;
int ballot_count;
// ----------------
// voting_candidate
// ----------------

int voting_candidate(const string& s){
    int num_of_candidate;
    istringstream sin(s);
    sin >> num_of_candidate;
    return num_of_candidate;
}

// // ---------------
// // voting_max_eval
// // ---------------

// int voting_max_eval(int num_of_candidate) {
//     int max = 0;
//     for(int i = 0; i < num_of_candidate; ++i) {
//         if(max < candidate_list[i].current_vote)
//             max = candidate_list[i].current_vote;
//     }

//     return max;
// }

// ---------------
// voting_min_eval
// ---------------

void voting_min_eval(int num_of_candidate) {

    int min = 1000;
    for(int i =0; i < num_of_candidate; ++i) {
        if(!candidate_list[i].is_loser && min > candidate_total_votes.at(i))
            min = candidate_total_votes.at(i);
    }

    for(int i =0; i < num_of_candidate; ++i) {
        if(min == candidate_total_votes.at(i)){
            candidate_list[i].is_loser = true;
            eliminated.push_back(i);
        }
    }

    while(!eliminated.empty()) {
        int i = eliminated.front();
        eliminated.pop_front();
        Candidate c = candidate_list[i];
        
        while(c.is_loser && min == candidate_total_votes.at(i) && !c.c_ballot.empty()){
            vector<int> next_ballot = c.c_ballot.front();
            int next_vote = next_ballot.front();

            next_ballot.erase(next_ballot.begin());
            
            while(candidate_list[next_vote-1].is_loser && !next_ballot.empty()) {
                next_vote = next_ballot.front();
                next_ballot.erase(next_ballot.begin());
            }
            c.c_ballot.erase(c.c_ballot.begin());
            candidate_total_votes[next_vote-1]++;
        }   
    }
}

// -------------------
// voting_parse_ballot
// -------------------

void voting_parse_ballot(const string& s, int num_of_candidate){
    stringstream stream(s);
    int j = 0;
    int c = 0;
    vector<int> values;
    int n;
    while(stream >> n){
        if(j == 0) {
            c = n-1;
            ++candidate_total_votes[c];
        } else {
            values.push_back(n);
        }
        ++j;
    }
    candidate_list[c].c_ballot.push_back(values);
    
}

// ------------
// voting_solve
// ------------

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

    while (size--) {
        ballot_count = 0;
        getline(r,s);
        istringstream sin2(s);
        int num_of_candidate = 0;
        sin2 >> num_of_candidate;
        candidate_total_votes.assign(20, 0);

        for (int i = 0; i < num_of_candidate; ++i) {
            getline(r, s);
            candidate_list[i].c_name = s;
        }

        int i = 0;
        while(getline(r, s) && s != "") {
            voting_parse_ballot(s, num_of_candidate);
            ++i;
            ++ballot_count;
        }

        int ballot = i;
        auto val = max_element(begin(candidate_total_votes), end(candidate_total_votes));
        int max = *val;
        int cutoff = ballot/2;
        int winner_vote = 0;
        winner_vote = max*count(candidate_total_votes.begin(), candidate_total_votes.end(), max);

        while(max <= cutoff && winner_vote < ballot) {
            winner_vote = 0;
            voting_min_eval(num_of_candidate);
            val = max_element(begin(candidate_total_votes), end(candidate_total_votes));
            max = *val;
            winner_vote += max*count(candidate_total_votes.begin(), candidate_total_votes.end(), max);
        }

        for(int i =0; i < num_of_candidate; ++i){
            if(max == candidate_total_votes.at(i))
                w << candidate_list[i].c_name << endl;
            candidate_list[i].reset();
        }

        if(r.eof())
            break;

        w << endl;

    }

}