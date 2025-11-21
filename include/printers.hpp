#pragma once
#include <stdlib.h>
#include <vector>

bool verifySameMultisetDifferentStructure(vector<int> root1, vector<int> root2) {

    int n1 = root1.size();
    int n2 = root2.size();
    std::unordered_map<int, vector<int>> m1, m2;
    for (int i = 0; i < max(n1, n2); ++i){
        if (i < n1)
            if (root1[i] != 100001)
                m1[root1[i]].push_back(i);
        if (i < n2)
            if (root2[i] != 100001)
                m2[root2[i]].push_back(i);
    }

    // print(m1);
    // print(m2);
    if (m2.size() != m1.size()) { return false; }
    
    bool structure = false;
    for (auto & i : m1){
        if (!m2.count(i.first))
            return false;
        if (i.second != m2[i.first])
            structure = true;
    }
    
    return structure;
}