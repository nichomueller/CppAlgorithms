#include <bits/stdc++.h>
using namespace std;

vector<int> findTaskPairForSlot(vector<int> taskDurations, int slotLength) {
    std::unordered_map<int, int> tmp;
    vector<int> indices = {-1, -1};
    for(int right = 0; right < (int)taskDurations.size(); ++right){
        if(tmp.count(slotLength - taskDurations[right])){
            indices[0] = tmp.at(slotLength - taskDurations[right]);
            indices[1] = right;
            break;
        }
        tmp.insert({taskDurations[right], right});
    }
    return indices;
}

void printIntervals(vector<vector<int>> a){
    for(auto & ai : a){
        std::cout << "Interval: " << "(" << ai[0] << ", " << ai[1] << ")" << std::endl;
    }
}

vector<vector<int>> mergeHighDefinitionIntervals(vector<vector<int>> intervals) {
    std::priority_queue<
        std::vector<int>,
        std::vector<std::vector<int>>,
        std::greater<std::vector<int>>
    > pq;
    for(auto & intrvl : intervals){
        pq.push(intrvl);
    }
    
    vector<vector<int>> result;
    
    vector<int> intrvl = pq.top();
    pq.pop();
    int left = intrvl[0];
    int right = intrvl[1];
        
    while(!pq.empty()){
        intrvl = pq.top();
        pq.pop();
        
        if (intrvl[0] <= right){
            right = intrvl[1];
        } else{
            result.push_back({left, right});
            left = intrvl[0];
            right = intrvl[1];
        }
    }

    result.push_back({left, right});
    
    return result;
}

int main(){
    // auto inds = findTaskPairForSlot({2, 7, 11, 15}, 9);

    // std::cout << "(" << inds[0] << ", " << inds[1] << ")" << std::endl;
    
    vector<vector<int>> intervals = {{2, 6}, {1, 3}, {8, 10}};
    
    auto mints = mergeHighDefinitionIntervals(intervals);
    printIntervals(mints);
    
    return 0;
}