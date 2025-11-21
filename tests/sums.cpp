#include <bits/stdc++.h>
using namespace std;

void printQueue(const std::deque<int>& q){
    for(auto qi : q){
        std::cout << qi << std::endl;
    }
    std::cout << "-----------------------------" << std::endl;
}

long countValidSubarraysOpt(const vector<int> & a, int k) {
    int n = a.size();
    int tot = 0;
    
    std::deque<int> minq, maxq;

    int left = 0;
    for (int right = 0; right < n; ++right){

        while(!minq.empty() && a[right] < a[minq.back()])
            minq.pop_back();
        minq.push_back(right);

        while(!maxq.empty() && a[right] > a[maxq.back()])
            maxq.pop_back();
        maxq.push_back(right);

        while (!minq.empty() && !maxq.empty() && a[maxq.front()] - a[minq.front()] > k){
            if (minq.front() == left) minq.pop_front();
            if (maxq.front() == left) maxq.pop_front();
            left++;
        }

        tot += right - left + 1;
    }
    
    return (long)tot;
}

int main(){
    vector<int> a = {31, 1, 2, 30, 20, 30, 2, 1};
    int k = 1;

    std::cout << countValidSubarraysOpt(a, k) << std::endl;
    
    return 0;
}