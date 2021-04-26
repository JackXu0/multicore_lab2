//
//  main.cpp
//  parallel_programming
//
//  Created by Zhuocheng Xu on 4/2/21.
//

#include "main.hpp"
#include <iostream>
#include <fstream>
#include <omp.h>
#include <chrono>
#include<set>
#include<string>
using namespace std;

pair<int, string> travel(int city, int (&map)[4][4], set<int> set){
    // if all cities have been visited
    if (sizeof(**map) == set.size()){
        pair<int, string> result(0, to_string(city));
        return result;
    }

    int cost = pow (2, 31) - 1;
    string s = "a";
    for(int i=0; i<sizeof(**map); i++){
        if(i != city && set.find(i) == set.end()){
            printf("city: %i to city %i \n", city, i);
            set.insert(i);
            pair<int, string> ans = travel(i, map, set);
            if (ans.first < cost){
                cost = ans.first + map[city][i];
                printf("change cost to: %i \n", cost);
                s = to_string(city)+","+ans.second;
            }
            set.erase(i);
        }
    }

    printf("cost returned: %i \n", cost);
    pair<int, string> result(cost, s);

    return result;
}

int main (int argc, char *argv[])
{

    // int **map = new int*[4];
    // map[0] = new int[4]{0, 10, 15, 20};
    
    int map[4][4] = {
        {0, 10, 15, 20},     
        {5, 0, 9, 10},      
        {6, 13, 0, 12},    
        {8, 8, 9, 0}
    };

    set<int> set;
    set.insert(0);
    pair<int, string> ans = travel(0, map, set);
    printf("cost: %i \n", ans.first);
    printf("path: %s \n", ans.second.c_str());

    // chrono::time_point<std::chrono::high_resolution_clock> start = chrono::high_resolution_clock::now();
//     int b = 4, t=4;
//     string filename;
//     if (argc >=2)
//         b = atoi(argv[1]);
    
//     t = atoi(argv[2]);
//     filename = argv[3];
// //    printf("filename %s\n", argv[3]);
// //
//     ifstream infile;
//     infile.open(filename);
// //
//     int count = 0;
//     int size;
//     infile >> size;
//     float array[size];
//     float x;

//     while (count < size && infile >> x)
//         array[count++] = x;

//     // display the values stored in the array
// //    for (int i = 0; i < count; i++)
// //        cout << array[i] <<' ';
    
//     // chrono::time_point<std::chrono::high_resolution_clock> t1 = chrono::high_resolution_clock::now();
//     // cout<<"d1: " <<chrono::duration_cast<chrono::nanoseconds>(t1-start).count() << endl;
    
//     int bins[b];
//     for(int i=0; i<b; i++) bins[i] = 0;
    
//     #pragma omp parallel num_threads(t)
//     {
//         int i, local_bins[b];
//         for(i=0; i<b; i++) local_bins[i] = 0;
//         #pragma omp for nowait
//         for(i = 0; i < size; i++) local_bins[int(array[i] * b /20)]++;
//         #pragma omp critical
//         for(i=0; i<b; i++) bins[i] += local_bins[i];
//     }
    
//     // chrono::time_point<std::chrono::high_resolution_clock> t2 = chrono::high_resolution_clock::now();
//     // cout<<"d2: " <<chrono::duration_cast<chrono::nanoseconds>(t2-t1).count() << endl;
    
//     count = 0;
//     for (int i = 0; i < b; i++){
//         count += bins[i];
//         cout << "bin["<<i<<"] = "<< bins[i] << endl;
        
//     }
    
    // chrono::time_point<std::chrono::high_resolution_clock> t3 = chrono::high_resolution_clock::now();
    // cout<< endl <<"d3: " <<chrono::duration_cast<chrono::nanoseconds>(t3-t2).count() << endl;
    
    // cout << endl << "Sum(bins): " << count << " -- Expected: " << size;
    
    
    
    return 0;
}

 