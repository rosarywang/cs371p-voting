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
#include <utility>   // make_pair, pair
#include "Voting.h"
#include <ctime>
#include <iostream>


using namespace std;

Candidate:: Candidate() {
}

Candidate:: Candidate(string name) {
    c_name = name;
}

// <<<<<<< HEAD

// =======
// vector<int> candidate_total_votes;
// list<int> eliminated;
// int ballot_count;
// >>>>>>> acde1c22966775c2c12cff7ba57de66656c5bd26
// ----------------
// voting_candidate
// ----------------

int voting_candidate(const string& s){
    int num_of_candidate;
    istringstream sin1(s);
    sin1 >> num_of_candidate;
    return num_of_candidate;
}

//<<<<<<< HEAD
void voting_min_eval(int num_of_candidate, vector<pair<int,int>> &candidate_total_votes, Candidate (&candidate_list)[20]) {

    list<int> min_candidate;
    auto index = candidate_total_votes.end()-1;
    int min = (*index).second;
    while(index >= candidate_total_votes.begin() && min == (*index).second){
        int i = (*index).first;
        candidate_total_votes.erase(index);
        min_candidate.push_back(i);
        --index;
    }
    while(!min_candidate.empty()) {
        
        int i = min_candidate.front();
        min_candidate.pop_front();
        Candidate c = candidate_list[i];

        while(!c.c_ballot.empty()){
            list<int> next_ballot = c.c_ballot.back();
            int next_vote = next_ballot.front();

            next_ballot.pop_front();
            auto it = find_if( candidate_total_votes.begin(), candidate_total_votes.end(), [next_vote](const pair<int, int>& element){ return element.first == (next_vote-1);} );
            while(it==candidate_total_votes.end() && !next_ballot.empty()) {
                next_vote = next_ballot.front();
                next_ballot.pop_front();
                it = find_if( candidate_total_votes.begin(), candidate_total_votes.end(), [next_vote](const pair<int, int>& element){ return element.first == (next_vote-1);} );
            }
            if(it!=candidate_total_votes.end())
                (*it).second+=1;
            c.c_ballot.pop_back();
            
        }
//=======
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

// void voting_min_eval(int num_of_candidate) {

//     int min = 1000;
//     for(int i =0; i < num_of_candidate; ++i) {
//         if(!candidate_list[i].is_loser && min > candidate_total_votes.at(i))
//             min = candidate_total_votes.at(i);
//     }

//     for(int i =0; i < num_of_candidate; ++i) {
//         if(min == candidate_total_votes.at(i)){
//             candidate_list[i].is_loser = true;
//             eliminated.push_back(i);
//         }
//     }

//     while(!eliminated.empty()) {
//         int i = eliminated.front();
//         eliminated.pop_front();
//         Candidate c = candidate_list[i];
        
//         while(c.is_loser && min == candidate_total_votes.at(i) && !c.c_ballot.empty()){
//             vector<int> next_ballot = c.c_ballot.front();
//             int next_vote = next_ballot.front();

//             next_ballot.erase(next_ballot.begin());
            
//            while(candidate_list[next_vote-1].is_loser && !next_ballot.empty()) {
//                 next_vote = next_ballot.front();
//                 next_ballot.erase(next_ballot.begin());
//             }
//             c.c_ballot.erase(c.c_ballot.begin());
//             candidate_total_votes[next_vote-1]++;
//         }   
// >>>>>>> acde1c22966775c2c12cff7ba57de66656c5bd26
    }
}

list<int> string_split(string &s, char delimiter){
    size_t start=0;
    size_t end=s.find_first_of(delimiter);
    list<int> output;
    while (end <= string::npos){
        output.emplace_back(atoi(s.substr(start, end-start).c_str()));
        if (end == string::npos)
            break;
        start=end+1;
        end = s.find_first_of(delimiter, start);
    }
    return output;
}


// -------------------
// voting_parse_ballot
// -------------------

//<<<<<<< HEAD
void voting_parse_ballot(string& s, int num_of_candidate, vector<pair<int,int>> &candidate_total_votes, Candidate (&candidate_list)[20]){

    int c;
    list<int> temp = string_split(s, ' ');
    c = temp.front()-1;
    temp.pop_front();
    auto it = find_if( candidate_total_votes.begin(), candidate_total_votes.end(), [c](const pair<int, int>& element){ return element.first == c;} );
    if(it!=candidate_total_votes.end())
        (*it).second+=1;
    else
        candidate_total_votes.push_back(make_pair(c, 1));
    candidate_list[c].c_ballot.push_back(temp);


// =======
// void voting_parse_ballot(const string& s, int num_of_candidate){
//     stringstream stream(s);
//     int j = 0;
//     int c = 0;
//     vector<int> values;
//     int n;
//     while(stream >> n){
//         if(j == 0) {
//             c = n-1;
//             ++candidate_total_votes[c];
//         } else {
//             values.push_back(n);
//         }
//         ++j;
//     }
//     candidate_list[c].c_ballot.push_back(values);
    
// >>>>>>> acde1c22966775c2c12cff7ba57de66656c5bd26
}

// ------------
// voting_solve
// ------------

void voting_solve (istream& r, ostream& w) {
    string s;
    int size;
    getline(r, s);
    istringstream sin1(s);
    sin1 >> size;
    getline(r,s);

    while (size--) {
        ballot_count = 0;
        getline(r,s);
        istringstream sin2(s);
        int num_of_candidate = 0;
// <<<<<<< HEAD
        num_of_candidate = voting_candidate(s);
        vector<pair<int,int>> candidate_total_votes;
        Candidate candidate_list[20];

        for (int i = 0; i < num_of_candidate; ++i) {
            getline(r,s);
            candidate_list[i]= Candidate(s);
        }

        int i = 0;
        while(!s.empty() && !r.eof()){
            getline(r,s);
            if(!s.empty()) {
                voting_parse_ballot(s, num_of_candidate, candidate_total_votes, candidate_list);
                ++i;
            }    
        }
        for(auto i = candidate_total_votes.begin(); i != candidate_total_votes.end(); ++i){
            w << (*i).first << " " << (*i).second << endl;
        }
// =======
//         sin2 >> num_of_candidate;
//         candidate_total_votes.assign(20, 0);

//         for (int i = 0; i < num_of_candidate; ++i) {
//             getline(r, s);
//             candidate_list[i].c_name = s;
//         }

//         int i = 0;
//         while(getline(r, s) && s != "") {
//             voting_parse_ballot(s, num_of_candidate);
//             ++i;
//             ++ballot_count;
//         }

// >>>>>>> acde1c22966775c2c12cff7ba57de66656c5bd26
        int ballot = i;
        
        
        // auto val = max_element(begin(candidate_total_votes), end(candidate_total_votes));
        // int max = *val;
        
        int winner_vote = 0;
//<<<<<<< HEAD
        auto cmp = [](pair<int,int> const & a, pair<int,int> const & b) 
        { 
            return a.second != b.second?  a.second > b.second : a.first < b.first;
        };
        sort(candidate_total_votes.begin(), candidate_total_votes.end(), cmp);
        
        auto index1 = candidate_total_votes.begin();
        int max = (*index1).second;

        auto index2 = candidate_total_votes.end()-1;
        int min = (*index2).second;

        // for(auto i = candidate_total_votes.begin(); i != candidate_total_votes.end(); ++i){
        //     w << (*i).first << " " << (*i).second << endl;
        // }
        // w << "\n" <<endl;

        while(max != min && winner_vote < ballot) {
            // printf("entering 211\n");
            winner_vote = 0;
            voting_min_eval(num_of_candidate, candidate_total_votes, candidate_list);
            sort(candidate_total_votes.begin(), candidate_total_votes.end(), cmp);
            // for(auto i = candidate_total_votes.begin(); i != candidate_total_votes.end(); ++i){
            //     w << (*i).first << " " << (*i).second << "\n"<< endl;
            // }
            //  w << "\n" <<endl;
            index1 = candidate_total_votes.begin();
            max = (*index1).second;
            index2 = candidate_total_votes.end()-1;
            min = (*index2).second;
//=======
//         winner_vote = max*count(candidate_total_votes.begin(), candidate_total_votes.end(), max);

//         while(max <= cutoff && winner_vote < ballot) {
//             winner_vote = 0;
//             voting_min_eval(num_of_candidate);
//             val = max_element(begin(candidate_total_votes), end(candidate_total_votes));
//             max = *val;
//             winner_vote += max*count(candidate_total_votes.begin(), candidate_total_votes.end(), max);
// >>>>>>> acde1c22966775c2c12cff7ba57de66656c5bd26
        }
        // for(auto i = candidate_total_votes.begin(); i != candidate_total_votes.end(); ++i){
        //     w << (*i).first << " " << (*i).second << endl;
        // }
        //  w << "\n" <<endl;
        sort(candidate_total_votes.begin(), candidate_total_votes.end(), cmp);
        auto index = candidate_total_votes.begin();
        max = (*index).second;
        while(index != candidate_total_votes.end() && (*index).second == max){
            w << candidate_list[(*index).first].c_name << "\n" << endl;
            ++index;
        }
// <<<<<<< HEAD
        //candidate_total_votes.clear();
        --size;
        if(size>0)
           w << endl;
// =======

//         if(r.eof())
//             break;

//         w << endl;

// >>>>>>> acde1c22966775c2c12cff7ba57de66656c5bd26
    }

}