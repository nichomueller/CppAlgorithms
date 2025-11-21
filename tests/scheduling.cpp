/*
Task Scheduler with Cooldown and Multiple Machines:

Given an array tasks and m machines, find the minimum time to complete all tasks. Each time unit can process up to m tasks in parallel. A machine cannot process the same task type again for k time units.
*/

#include <bits/stdc++.h>
using namespace std;

class NaiveSolution
{
private:
    /* data */
public:
    bool isIdle(
        const vector<int> & taskScheduler,
        const vector<int> & timeScheduler,
        int k, int task, int time, int i){
        // machine empty
        if (taskScheduler[i] == -1) return true;

        // allowed if different task OR same task but cooldown passed
        return (taskScheduler[i] != task ||
            (time - timeScheduler[i] >= k));
    }

    int calculateMinimumTimeUnits(vector<int> tasks, int m, int k){

        if (tasks.empty()) return 0;

        int ntasks = tasks.size();

        // Count frequencies of each task type
        int maxTask = *max_element(tasks.begin(), tasks.end());
        vector<int> boxes(maxTask + 1, 0);
        for (int t : tasks) boxes[t]++;

        // machine scheduling state
        vector<int> taskScheduler(m, -1);
        vector<int> timeScheduler(m, -1);

        int time = 0;
        while (ntasks > 0) {
            ++time;

            // for every machine: try assign ONE task
            for (int i = 0; i < m; ++i) {

                // find a task type that fits rules
                for (int b = 0; b <= maxTask; ++b) {
                    if (boxes[b] == 0) continue;

                    if (isIdle(taskScheduler, timeScheduler, k, b, time, i)) {
                        // assign
                        taskScheduler[i] = b;
                        timeScheduler[i] = time;
                        boxes[b]--;
                        ntasks--;
                        break;  // machine assigned, go to next machine
                    }
                }
            }
        }

        return time;
    }
};

/* The problem with this solution is that it computes a locally optimal solution, not a globally optimal one. For example, given the inputs:

tasks = [1, 1, 1, 2]
m = 1
k = 2

The naive solution's procedure would be to run the tasks in order, which means
1) run 1 
2) idle 
3) run 1
4) idle 
5) run 1
6) idle
7) run 2

On the other hand, the optimal solution is 6 time steps, as shown here:
1) run 1 
2) idle 
3) run 2
4) run 1
5) idle
6) run 1

Additionally, the code is inefficient: O(m * ntasks).

The solution is to use priority queues. 

*/

class Solution
{
private:

    struct Machine {
        int lastTask = -1;
        long long lastTime = -1;
    };

    void printQueue(priority_queue<pair<int,int>> pq, int time = 0){
        while (!pq.empty()){
            auto top = pq.top();
            pq.pop();
            std::cout << "(Key, value) pair at time " << time << ": (" <<  top.first << ", " << top.second << ")" << std::endl;
        }
    }

    void printMachineStatus(const vector<Machine> & machines){
        for(size_t i = 0; i < machines.size(); ++i){
            std::cout << "(Task, time) of machine " << i << " is : (" << machines[i].lastTask << ", " << machines[i].lastTime << ")" << std::endl;
        }
    }

public:

    int calculateMinimumTimeUnits(vector<int> tasks, int m, int k) {
        if (tasks.empty()) return 0;

        // Count frequency of each task type
        unordered_map<int,int> boxes;
        for (int t : tasks) boxes[t]++;

        // Max heap of (remaining_count, task_id)
        priority_queue<pair<int,int>> pq;
        for (auto &p : boxes) pq.push({p.second, p.first});

        // machines
        vector<Machine> machines(m);

        int time = 0;
        int ntasks = tasks.size();

        while (ntasks > 0) {
            ++time;
            printQueue(pq, time);

            // try to assign tasks to each machine this time unit
            for (int i = 0; i < m; ++i) {
                // to store tasks that were popped but not assigned this round
                vector<pair<int,int>> tmp;

                if (pq.empty()) break;

                bool assigned = false;

                // Try until either machine gets a valid task or pq becomes empty
                while (!pq.empty() && !assigned) {
                    auto top = pq.top();
                    int count = top.first;
                    int task = top.second;

                    pq.pop();

                    // Check cooldown rule
                    if (machines[i].lastTask != task 
                        || 
                        time - machines[i].lastTime >= k) {
                        // Assign task
                        machines[i].lastTask = task;
                        machines[i].lastTime = time;
                        ntasks--;
                        assigned = true;

                        // push back to heap if still ntasks
                        if (count > 1)
                            tmp.push_back({count - 1, task});
                    } else {
                        // can't assign now, put aside
                        tmp.push_back({count, task});
                    }
                }

                // push back all unused tasks into heap
                for (auto &p : tmp) pq.push(p);
            }
        }

        return time;
    }

};

int main(){
    Solution sol;

    vector<int> tasks = {1, 1, 1, 2};
    int k = 2;
    int m = 2;

    int time = sol.calculateMinimumTimeUnits(tasks, m, k);

    return 0;
}