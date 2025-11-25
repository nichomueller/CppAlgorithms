#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

template<typename S, typename T>
class Printers
{
private:
    bool verbose = true;
    bool indent = true;
    std::ostream& out = std::cout;
    std::ostream& endout = indent ? std::endl : std::flush;

    void printMessage(const vector<T> & v){
        if (!verbose)
            return;
        int n = v.size();
        out << n << " - dimensional vector with entries:" << endout;
    }

    void printMessage(const vector<vector<T>> & m){
        if (!verbose)
            return;
        int n1 = m.size();
        int n2 = m[0].size();
        std::cout << "(" << n1 << "x" <<  n2 << ")" << " - dimensional matrix with entries:" << endout;
    }

    void printMessage(const std::set<T> & s){
        if (!verbose)
            return;
        int n = s.size();
        std::cout << "Set with " << n << " values:" << endout;
    }

    void printMessage(const std::stack<T> & s){
        if (!verbose)
            return;
        int n = s.size();
        std::cout << "Stack with " << n << " values:" << endout;
    }

    void printMessage(const std::deque<T> & s){
        if (!verbose)
            return;
        int n = s.size();
        std::cout << "Double-ended queue with " << n << " values:" << endout;
    }

    void printMessage(const std::priority_queue<T> & s){
        if (!verbose)
            return;
        int n = s.size();
        std::cout << "Max-heap with " << n << " values:" << endout;
    }

    void printMessage(const std::unordered_map<S, T> & m){
        if (!verbose)
            return;
        int n = m.size();
        std::cout << "Unordered map with " << n << " key-value pairs:" << endout;
    }

    void printMessage(const std::unordered_set<T> & m){
        if (!verbose)
            return;
        int n = m.size();
        std::cout << "Unordered set with " << n << " key-value pairs:" << endout;
    }

    void quickPrint(T v){
        out << v << '\n';
    }

    void quickPrint(const vector<T> & v){
        for (auto & i : v){
            out << i << ", " << std::flush;
        }
        out << '\n';
    }

public:

    void print(const vector<T>& v){
        printMessage(v);
        out << "[ " << endout; 
        for (auto & i : v){
            out << i << ", " << endout;
        }
        out << "]" << '\n\n';
    }

    void print(const vector<vector<T>>& m){
        printMessage(m);
        out << "[ " << endout; 
        for (auto & mi : m){
            quickPrint(mi);
        }
        out << "]" << '\n\n';
    }

    void print(std::unordered_set<T>& s){
        printMessage(m);
        for (auto & mi : m){
            out << "(" << quickPrint(mi.first) << "," << quickPrint(mi.second) << ")" << endout;
        }
        out << '\n\n';
    }

    void print(const std::unordered_map<S, T>& m){
        printMessage(m);
        for (auto & mi : m){
            out << "(" << quickPrint(mi.first) << "," << quickPrint(mi.second) << ")" << endout;
        }
        out << '\n\n';
    }

};

namespace printers{

    template<typename T>
    void print(vector<T> v, bool verbose = true){
        int n = v.size();
        std::cout << n << " - dimensional vector with entries: [" << std::flush;
        for (auto & i : v){
            std::cout << i << ", " << std::flush;
        }
        std::cout << "]" << std::flush;
    }

    void print(std::unordered_map<int, vector<int>> m1){
        for (auto & i : m1){
            std::cout << "(Key, value) pair: " << "(" << i.first << "," << std::flush;
            print(i.second);
            std::cout << ")" << std::endl;
        }
        std::cout << "------------" << std::endl;
    }
}
