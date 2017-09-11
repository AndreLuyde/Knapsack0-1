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

	int getFitness() const {
		return fitness;
	}

	void setFitness(int fitness) {
		this->fitness = fitness;
	}

	const vector<bool>& getSolution() const {
		return solution;
	}

	void setSolution(const vector<bool>& solution) {
		this->solution = solution;
	}

	bool isChecked() const {
		return checked;
	}

	void setChecked(bool checked) {
		this->checked = checked;
	}

private:
	vector<bool> solution;
	int fitness;
	bool checked;
};

#endif /* SOLUTION_H_ */
