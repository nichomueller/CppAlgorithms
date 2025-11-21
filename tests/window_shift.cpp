#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>

#include "../include/timers.hpp"

using namespace std;

class Solution
{
private:
    void printIndex(int i, int j, int k){
        std::cout << "(" << i << ", " << j << ", " << k << ")" << std::endl;
    }

    void printSet(const std::set<vector<int>> & triplets){
        for (auto & t : triplets){
            std::cout << "(" << t[0] << ", " << t[1] << ", " << t[2] << ")" << std::endl;
        }
    }
public:

    void slideNaive(const vector<int> & readings, int windowSize) {
        int n = readings.size();
        std::set<vector<int>> triplets;
        
        if(windowSize < 3) {return printSet(triplets);}
        
        for(int i = 0; i < n - windowSize + 1; ++i){
            for(int j = i+1; j < i + windowSize - 1; ++j){
                int pij = readings[i] + readings[j];
                for(int k = j+1; k < i + windowSize; ++k){
                    if (readings[k] == -pij){
                        triplets.insert({readings[i], readings[j], readings[k]});
                    }
                }
            }
        }
        
        return printSet(triplets);
    }

    void slideOpt(const vector<int> & readings, int windowSize) {
        int n = readings.size();
        std::set<vector<int>> triplets;
        
        if(windowSize < 3) {return printSet(triplets);}
        
        for(int i = 0; i < n - windowSize + 1; ++i){
            std::unordered_set<int> touched;
            for(int j = i+1; j < i + windowSize; ++j){
                int pij = readings[i] + readings[j];
                
                if(touched.count(-pij)){
                    triplets.insert({readings[i], -pij, readings[j]});
                }

                touched.insert(readings[j]);
            }
        }
        
        return printSet(triplets);
    }

};

int main(){
    
    Solution sol;

    vector<int> readings = {1, -1, 0, 0, -1, 1};
    int windowSize = 5;

    Timer clock; 

    clock.tick();
    sol.slideNaive(readings, windowSize);
    clock.tock();

    cout << "Run time = " << clock.duration().count() << " mu s\n";

    std::cout << "------------------------" << std::endl;

    clock.tick();
    sol.slideOpt(readings, windowSize);
    clock.tock();

    cout << "Run time = " << clock.duration().count() << " mu s\n";

    return 0;
}