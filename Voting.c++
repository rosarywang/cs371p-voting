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
// #include "Candidate.c++"
// #include "Ballot.c++"
#include <list>
using namespace std;

class Ballot {
public:
    list<int> ballot;
    Ballot (list<int>);
};

Ballot::Ballot (list<int> temp_ballot) {
    ballot = temp_ballot;
}

class Candidate {
public:
    string c_name;
    bool is_loser;
    // list<Ballot> c_ballot;
    int current_vote;
    list<list<int>> c_ballot;
    Candidate(string);
    Candidate();
    // void set_bool(bool loser);
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
        // printf("candidate_total_vote = %d\n", candidate_total_votes[i]);
        // if(max < candidate_total_votes[i])
        //     max = candidate_total_votes[i];
        if(max < candidate_list[i].current_vote)
            max = candidate_list[i].current_vote;
    }

    return max;
}

// ---------------
// voting_min_eval
// ---------------

void voting_min_eval(int num_of_candidate) {
    // printf("in min eval.\n");
    int min = 1000;
    for(int i =0; i < num_of_candidate; ++i) {
        if(!candidate_list[i].is_loser && min > candidate_list[i].current_vote)
            min = candidate_list[i].current_vote;
        // if(!candidate_loser[i] && min > candidate_total_votes[i])
        //     min = candidate_total_votes[i];
    }


    //w << "138 min "<< min << endl; 
    for(int i =0; i < num_of_candidate; ++i) {
        if(min == candidate_list[i].current_vote)
            candidate_list[i].is_loser = true;
        // if(min == candidate_total_votes[i])
        //     candidate_loser[i] = true;
    }
    // printf("113 after loser\n");
    for(int i = 0; i < num_of_candidate; ++i){
        Candidate c = candidate_list[i];
        // printf("116 for loop\n");
        // int c = candidate_ballot[i][0]-1;

        while(c.is_loser && min == c.current_vote && !c.c_ballot.empty()) {
            // printf("119:\n");

            list<int> next_ballot = c.c_ballot.front();


            // printf("next_ballot 122.\n");
            int next_vote = next_ballot.front();
            // printf("next_vote: %d\n", next_vote);

            next_ballot.pop_front();
            // int next_vote = c.c_ballot.pop_front();
            while(candidate_list[next_vote-1].is_loser) {
                next_vote = next_ballot.front();
                // printf("while next_vote: %d\n", next_vote);
                next_ballot.pop_front();
            }
            // printf("while\n");
            c.c_ballot.pop_front();
            candidate_list[next_vote-1].current_vote+=1;
        }

        // if(candidate_loser[c] && min == candidate_total_votes[c]){
        //     int j = 1;
        //     c = candidate_ballot[i][j]-1;
        //     while(candidate_loser[c]){
        //         ++j;
        //         c = candidate_ballot[i][j]-1;
        //     }
        //     ++candidate_total_votes[c];
        // }
    }
    // printf("end min_eval\n");
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

    Ballot b(temp);
    // printf("front: %d\t back: %d\n", temp.front(), temp.back());
    candidate_list[c].c_ballot.push_back(temp);
    // printf("front= %d\tsize= %d\n", b.ballot.front(), b.ballot.size());
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
        int num_of_candidate = 0;
        num_of_candidate = voting_candidate(s);

        // fill(candidate_total_votes, candidate_total_votes+20, 0);
        // fill( &candidate_ballot[0][0], &candidate_ballot[0][0] + sizeof(candidate_ballot)/sizeof(candidate_ballot[0][0]), 0 );
        // fill(candidate_loser, candidate_loser+20, false);
        // string candidate_names[20] = { "" };
        for (int i = 0; i < num_of_candidate; ++i)
            candidate_list[i] = Candidate();
        // printf("got candidate\n");
        // candidate_list[20]= {Candidate(), Candidate(), Candidate(), Candidate(), Candidate(), 
        //                         Candidate(), Candidate(), Candidate(), Candidate(), Candidate(), 
        //                         Candidate(), Candidate(), Candidate(), Candidate(), Candidate(), 
        //                         Candidate(), Candidate(), Candidate(), Candidate(), Candidate() };
        for (int i = 0; i < num_of_candidate; ++i) {
            getline(r,s);
            // candidate_names[i] = s;
            Candidate c(s);
            candidate_list[i] = c;
        }

        int i = 0;
        while(!s.empty() && !r.eof()){
            getline(r,s);
            if(!s.empty()) {
                voting_parse_ballot(s, i, num_of_candidate);
                ++i;
            }    
        }
        // printf("got ballots 255\n");
        // for (int i = 0; i < num_of_candidate; ++i) {
        //     // list<int> temp = candidate_list[0].c_ballot.front();
        //     // printf("front: %d\n", temp.front());
        //     printf("total votes: %d\n", candidate_list[i].current_vote);
        // }

        int ballot = i;
        int max = voting_max_eval(num_of_candidate);
        int cutoff = ballot/2;
        int winner_vote = 0;
        // printf("266.\n");
        for(int i =0; i < num_of_candidate; ++i) {
            if(max == candidate_list[i].current_vote)
                winner_vote += max;
        }
        while(max <= cutoff && winner_vote<ballot){
            winner_vote = 0;
            voting_min_eval(num_of_candidate);
            // printf("min eval: 270.\n");
            max = voting_max_eval(num_of_candidate);
            // printf("voting_max 272.\n");
            for(int i =0; i < num_of_candidate; ++i) {
                if(max == candidate_list[i].current_vote)
                    winner_vote += max;
            
                // if(max == candidate_total_votes[i])
                //     winner_vote+=max;
            }
            // printf("280.\n");
        }
        // printf("end while.\n");
        for(int i =0; i < num_of_candidate; ++i){
            if(max == candidate_list[i].current_vote)
                w << candidate_list[i].c_name << endl;
            // if(max == candidate_total_votes[i])
            //     w << candidate_names[i] << endl;
        }
        --size;
        if(size>0)
            w << endl;

    }


}
