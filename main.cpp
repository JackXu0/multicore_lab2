//
//  main.cpp
//  parallel_programming
//
//  Created by Zhuocheng Xu on 4/22/21.
//

#include "main.hpp"
#include <iostream>
#include <fstream>
#include <omp.h>
#include <chrono>
#include<set>
#include<string>
#include<vector>
#include<cmath>
using namespace std;

pair<int, string> travel(int city, vector<vector<int>> map, set<int> set, int x){
    // if all cities have been visited
    if (x == set.size()){
        pair<int, string> result(0, to_string(city));
        return result;
    }

    int cost = pow (2, 31) - 1;
    string s = "a";
    // # pragma omp for 
    for(int i=0; i<x; i++){
        if(i != city && set.find(i) == set.end()){
            set.insert(i);
            pair<int, string> ans = travel(i, map, set, x);
            if (ans.first + map.at(city).at(i) < cost){
                cost = ans.first + map.at(city).at(i);
                s = to_string(city)+" "+ans.second;
            }
            set.erase(i);
        }
    }

    pair<int, string> result(cost, s);

    return result;
}

int main (int argc, char *argv[])
{

    chrono::time_point<std::chrono::high_resolution_clock> start = chrono::high_resolution_clock::now();

    int x, t;
    string filename;
    x = atoi(argv[1]);
    t = atoi(argv[2]);
    filename = argv[3];

    // init the map
    ifstream infile;
    infile.open(filename);

    vector<vector<int>> map;
    for(int i=0; i<x; i++){
        vector<int> line;
        for(int j=0; j<x; j++){
            int current;
            infile >> current;
            line.push_back(current);
        }
        map.push_back(line);
    }

    // chrono::time_point<std::chrono::high_resolution_clock> t1 = chrono::high_resolution_clock::now();
    // cout<<"d1: " <<chrono::duration_cast<chrono::nanoseconds>(t1-start).count() << endl;

    int cost = pow (2, 31) - 1;
    string s;
    # pragma omp parallel num_threads(t)
    {
        # pragma omp for
        for(int i=1; i<x; i++){
            set<int> set;
            set.insert(0);
            set.insert(i);

            pair<int, string> ans = travel(i, map, set, x);
            int curr_cost = map.at(0).at(i) + ans.first;
            # pragma omp critical
            {
                if (curr_cost < cost){
                    cost = curr_cost;
                    s = "0 "+ans.second;
                }
            }
        }

    }

    printf("Best path: %s \n", s.c_str());
    printf("Distance: %i \n", cost);

    // chrono::time_point<std::chrono::high_resolution_clock> t2 = chrono::high_resolution_clock::now();
    // cout<<"d2: " <<chrono::duration_cast<chrono::nanoseconds>(t2-t1).count() << endl;
    
    return 0;
}

 