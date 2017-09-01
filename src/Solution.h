/*
 * Solution.h
 *
 *  Created on: 31 de ago de 2017
 *      Author: andre
 */

#ifndef SOLUTION_H_
#define SOLUTION_H_

#include <list>
#include <vector>
#include <algorithm>
using namespace std;

class Solution{

public:
	Solution();

	virtual ~Solution();

	int getFitness() const {
		return fitness;
	}

	void setFitness(int fitness) {
		this->fitness = fitness;
	}

	const vector<int>& getSolution() const {
		return solution;
	}

	void setSolution(const vector<int>& solution) {
		this->solution = solution;
	}

private:
	vector<int> solution;
	int fitness;
};

#endif /* SOLUTION_H_ */
