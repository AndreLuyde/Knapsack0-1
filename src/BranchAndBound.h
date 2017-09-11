/*
 * BranchAndBound.h
 *
 *  Created on: 5 de set de 2017
 *      Author: andre
 */

#ifndef SRC_BRANCHANDBOUND_H_
#define SRC_BRANCHANDBOUND_H_

#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <chrono>
#include <string>

#include "Knapsack.h"
#include "Solution.h"

using namespace std;

class BranchAndBound {

public:
    BranchAndBound(vector<Knapsack> kc, int cap, vector<bool> solSpc, int profit);

    void run(double enTime, Solution &solution);
    vector<bool> solSpace;

private:
    vector<Knapsack> problem;
    vector<bool> best;
    int maxProfit;
    int capacity;

    vector<int> getProfit();
};

#endif /* SRC_BRANCHANDBOUND_H_ */
