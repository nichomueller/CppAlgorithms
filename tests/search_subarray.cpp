// Given an integer array nums and integers k and M, count the number of contiguous subarrays whose sum equals k and whose maximum element is at most M.

#include <bits/stdc++.h>
using namespace std;

long countSubarraysWithSumAndMaxAtMost(vector<int> nums, long k, long M) {
    int alln = 0;
    for(int left = 0; left < (int)nums.size(); ++left){
        if (nums[left] > M){ continue; }
        int psum = 0;
        for(int right = left; right < (int)nums.size(); ++right){
            if (nums[right] > M){ break; }
            psum += nums[right];
            if (psum == k){ 
                // std::cout << "Found subarray starting at " << left << " and terminating at " << right << std::endl;
                alln++; 
            }
        }
    } 
    return alln;
}