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
using namespace std;

class Candidate {
public:
    string c_name;
    bool is_loser;
    int current_vote;
    list<list<int>> c_ballot;
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


//array<list<int>, 20> candidate_ballot;
// int candidate_ballot[1000][20];
// int candidate_total_votes[20];
// bool candidate_loser[20];
Candidate candidate_list[20] =   {Candidate(), Candidate(), Candidate(), Candidate(), Candidate(), 
                                Candidate(), Candidate(), Candidate(), Candidate(), Candidate(), 
                                Candidate(), Candidate(), Candidate(), Candidate(), Candidate(), 
                                Candidate(), Candidate(), Candidate(), Candidate(), Candidate()};

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
        if(!candidate_list[i].is_loser && min > candidate_list[i].current_vote)
            min = candidate_list[i].current_vote;
    }

    for(int i =0; i < num_of_candidate; ++i) {
        if(min == candidate_list[i].current_vote)
            candidate_list[i].is_loser = true;
    }
    for(int i = 0; i < num_of_candidate; ++i){
        Candidate c = candidate_list[i];

        while(c.is_loser && min == c.current_vote && !c.c_ballot.empty()) {
            list<int> next_ballot = c.c_ballot.front();
            int next_vote = next_ballot.front();

            next_ballot.pop_front();
            while(candidate_list[next_vote-1].is_loser && !next_ballot.empty()) {
                next_vote = next_ballot.front();
                next_ballot.pop_front();
            }
            c.c_ballot.pop_front();
            candidate_list[next_vote-1].current_vote+=1;
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
    list<int> temp;
    while(num_of_candidate > 0){
        int n;
        stream >> n;
        
        if(j == 0) {
            c = n-1;
            ++candidate_list[c].current_vote;
            // ++candidate_total_votes[n-1];
        } 
        else 
            temp.push_back(n);

        // candidate_ballot[i][j] = n;

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

        // w << "================before each cases:===================" << endl;
        
        // for(int i =0; i < num_of_candidate; ++i){    
        //     w << candidate_list[i].c_name << endl;
        //     w << candidate_list[i].c_ballot.size() << endl;
        //     w << candidate_list[i].current_vote << endl;
        //     w << candidate_list[i].is_loser << endl;
        // }
        // w << "================end each cases:=====================" << endl;
        // fill(candidate_total_votes, candidate_total_votes+20, 0);
        // fill( &candidate_ballot[0][0], &candidate_ballot[0][0] + sizeof(candidate_ballot)/sizeof(candidate_ballot[0][0]), 0 );
        // fill(candidate_loser, candidate_loser+20, false);
        // string candidate_names[20] = { "" };

        // for (int i = 0; i < num_of_candidate; ++i) {
        //     candidate_list[i] = Candidate();
        //     // candidate_list[i].reset()
        // }

        for (int i = 0; i < num_of_candidate; ++i) {
            getline(r,s);
            // candidate_names[i] = s;
            // Candidate c(s);
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
        int max = voting_max_eval(num_of_candidate);
        int cutoff = ballot/2;
        int winner_vote = 0;
        for(int i =0; i < num_of_candidate; ++i) {
            if(max == candidate_list[i].current_vote)
                winner_vote += max;
        }
        while(max <= cutoff && winner_vote<ballot){
            winner_vote = 0;
            voting_min_eval(num_of_candidate);
            max = voting_max_eval(num_of_candidate);
            for(int i =0; i < num_of_candidate; ++i) {
                if(max == candidate_list[i].current_vote)
                    winner_vote += max;
            }
        }

        for(int i =0; i < num_of_candidate; ++i){
            if(max == candidate_list[i].current_vote) {
                w << candidate_list[i].c_name << endl;
            }
            // while (!candidate_list[i].c_ballot.empty()) {
            //     while(!candidate_list[i].c_ballot.front().empty()) {
            //         candidate_list[i].c_ballot.front().clear();
            //     }
            //     candidate_list[i].c_ballot.clear();
            // }
            candidate_list[i].reset();
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