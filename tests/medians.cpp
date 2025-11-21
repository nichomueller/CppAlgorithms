#include <bits/stdc++.h>
using namespace std;

class Solution
{
private:
    
    void printIntervals(int aleft, int aright, int bleft, int bright){
        std::cout << "[" << aleft << ", " << aright << "]" << " x " << "[" << bleft << ", " << bright << "]" << std::endl;
    }

public:

    int findPivot(const vector<int>& a){
        int n = a.size();
        if (n <= 1 || a[0] <= a[n - 1]) { return 0; }

        int left = 0;
        int right = n - 1;

        while (left <= right){
            int mid = (left + right) / 2;

            if (mid < n - 1 && a[mid] > a[mid + 1]) { return mid + 1; }

            if (a[left] <= a[mid]){
                right = mid - 1;
            } else{
                left = mid + 1;
            }
        }

        return 0;
    }

    int getindex(const vector<int>& a, int p, int i){
        if (a.size() == 0) return 0;
        return a[(p + i) % a.size()];
    }

    int getindex(const vector<int>& a, int i){
        int p = findPivot(a);
        return getindex(a, p, i);
    }

    int findMedian(const vector<int>& a){
        int n = a.size();
        return getindex(a, n / 2);
    }

    int findMedian(const vector<int>& a, const vector<int>& b){
        int m = a.size();
        int n = b.size();
        if (m > n) return findMedian(a, b);

        if (m == 0 && n == 0) return 0;
        if (m == 0) return findMedian(b);
        if (n == 0) return findMedian(a);

        int pa = findPivot(a);
        int pb = findPivot(b);

        int tot = m + n;

        int left = 0;
        int right = m;

        while (left <= right){
            int i = (left + right) / 2; // Binary Search
            int j = (tot + 1) / 2 - i;

            int aleft = i == 0 ? -1e5 : getindex(a, pa, i - 1);
            int aright = i == m ? 1e5 : getindex(a, pa, i);
            int bleft = j == 0 ? -1e5 : getindex(b, pb, j - 1);
            int bright = j == n ? 1e5 : getindex(b, pb, j);

            printIntervals(aleft, aright, bleft, bright);

            if (aleft <= bright && bleft <= aright){
                if (tot % 2 != 0){ return max(aleft, bleft); }
                else { return (max(aleft, bleft) + min(aright, bright)) / 2;}
            } 
            if (aleft > bright){
                right = i - 1;
            } else{
                left = i + 1;
            }
        }

        return -1;
    }

};

int main(){
    Solution sol;

    // vector<int> a = {10, 11, 17, 3, 5};
    // vector<int> b = {21, 23, 27, 9, 13, 20};
    vector<int> a = {5, 8, 2, 3};
    vector<int> b = {16, 18, 20, 10, 12, 14};

    std::cout << sol.findMedian(a, b) << std::endl;
    // std::cout << sol.findMedian(b) << std::endl;

    return 0;
}