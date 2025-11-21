// Given a sorted array of unique integers that has been rotated at an unknown pivot, find the index of a target value or return -1 if not found.

#include <bits/stdc++.h>
using namespace std;

int searchRotatedTimestamps(vector<int> nums, int target) {
    if (nums.size() == 0) { return -1; }
    if (nums.size() == 1) { 
        return nums[0] == target ? 0 : -1; 
    }
    
    int left = 0;
    int right = nums.size() - 1;
    
    while (left <= right){
        int mid = (left + right) / 2;
        
        if (nums[mid] == target){ return mid; }
        
        if (nums[left] <= nums[mid]){ // left half is sorted
            if (nums[left] <= target && target < nums[mid]){
                right = mid - 1;
            } else{
                left = mid + 1;
            }
        } else{ // right half is sorted
            if (nums[mid] < target && target <= nums[right]){
                left = mid + 1;
            } else{
                right = mid - 1;
            }
        }
    }
    
    return -1;
}