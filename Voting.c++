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
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

class Candidate {
public:
    string c_name;
    bool is_loser;
    int current_vote;
    vector<vector<int>> c_ballot;
    Candidate(string);
    Candidate();
    void reset() {
        c_name = "";
        is_loser = false;
        current_vote = 0;
        c_ballot.clear();
    }
};

Candidate:: Candidate(string name) {
    c_name = name;
    is_loser = false;
    current_vote = 0;
}

Candidate:: Candidate() {
    is_loser = false;
    current_vote = 0;
}


Candidate candidate_list[20] =   {Candidate(), Candidate(), Candidate(), Candidate(), Candidate(), 
                                Candidate(), Candidate(), Candidate(), Candidate(), Candidate(), 
                                Candidate(), Candidate(), Candidate(), Candidate(), Candidate(), 
                                Candidate(), Candidate(), Candidate(), Candidate(), Candidate()};
vector<int> candidate_total_votes;

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
        if(max < candidate_list[i].current_vote)
            max = candidate_list[i].current_vote;
    }

    return max;
}

// ---------------
// voting_min_eval
// ---------------

void voting_min_eval(int num_of_candidate) {
    int min = 1000;
    for(int i =0; i < num_of_candidate; ++i) {
        if(!candidate_list[i].is_loser && min > candidate_total_votes.at(i))
            min = candidate_total_votes.at(i);
    }

    // auto val = min_element(begin(candidate_total_votes), end(candidate_total_votes));
    // int min = *val;

    for(int i =0; i < num_of_candidate; ++i) {
        // if(min == candidate_list[i].current_vote)
        //     candidate_list[i].is_loser = true;
        if(min == candidate_total_votes.at(i))
            candidate_list[i].is_loser = true;
    }
    // printf("min val: %d\n", min);
    for(int i = 0; i < num_of_candidate; ++i){
        Candidate c = candidate_list[i];
        // printf("candidate vote: %d\n", candidate_total_votes.at(i));
        // while(c.is_loser && min == c.current_vote && !c.c_ballot.empty()) {
        while(c.is_loser && min == candidate_total_votes.at(i) && !c.c_ballot.empty()){
            vector<int> next_ballot = c.c_ballot.front();
            int next_vote = next_ballot.front();

            // next_ballot.pop_front();
            next_ballot.erase(next_ballot.begin());
            while(candidate_list[next_vote-1].is_loser && !next_ballot.empty()) {
                next_vote = next_ballot.front();
                // next_ballot.pop_front();
                next_ballot.erase(next_ballot.begin());
            }
            // c.c_ballot.pop_front();
            c.c_ballot.erase(c.c_ballot.begin());
            // candidate_list[next_vote-1].current_vote+=1;
            candidate_total_votes[next_vote-1]++;
            // printf("next vote: %d\n", candidate_total_votes[next_vote-1]);
        }
    }
}

// -------------------
// voting_parse_ballot
// -------------------

void voting_parse_ballot(const string& s, int i, int num_of_candidate){

    stringstream stream(s);
    int j = 0;
    int c = 0;
    vector<int> temp;
    while(num_of_candidate > 0){
        int n;
        stream >> n;
        
        if(j == 0) {
            c = n-1;
            ++candidate_total_votes[n-1];
        } 
        else 
            temp.push_back(n);

        ++j;
        --num_of_candidate;
    }

    candidate_list[c].c_ballot.push_back(temp);

}

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
        int num_of_candidate = 0;
        num_of_candidate = voting_candidate(s);
        candidate_total_votes.assign(20, 0);

        for (int i = 0; i < num_of_candidate; ++i) {
            getline(r,s);
            candidate_list[i].c_name = s;
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
        auto val = max_element(begin(candidate_total_votes), end(candidate_total_votes));
        int max = *val;
        int cutoff = ballot/2;
        int winner_vote = 0;

        for(int i =0; i < num_of_candidate; ++i) {
            if (max == candidate_total_votes.at(i))
                winner_vote += max;
        }

        while(max <= cutoff && winner_vote<ballot){
            // printf("entering 211\n");
            winner_vote = 0;
            voting_min_eval(num_of_candidate);
            val = max_element(begin(candidate_total_votes), end(candidate_total_votes));
            max = *val;
            for(int i =0; i < num_of_candidate; ++i) {
                if (max == candidate_total_votes.at(i))
                    winner_vote += max;
            }
        }

        for(int i =0; i < num_of_candidate; ++i){
            if(max == candidate_total_votes.at(i)) {
                w << candidate_list[i].c_name << endl;
            }
            candidate_list[i].reset();
        }
        --size;
        if(size>0)
            w << endl;

    }
}