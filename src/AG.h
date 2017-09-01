/*
 * AG.h
 *
 *  Created on: 31 de ago de 2017
 *      Author: andre
 */

#ifndef AG_H_
#define AG_H_

#include "Solution.h"

#include <list>
#include <vector>
#include <algorithm>
using namespace std;

struct Knapsack {
	int label;
	int value;
	int weight;
	vector<int> conflits;
};

class AG{

public:
	AG(vector<Knapsack> kc);

	virtual ~AG();

	Solution crossing1Cut(Solution solution1, Solution solution2);
	Solution crossing2Cut(Solution solution1, Solution solution2);
	vector<Solution> tournament(vector<Solution> population, vector<Solution> newSolutions, int sizePopulation);
	int fitness(Solution &solution);
	void mutationByChange();
	bool checkConflits(Solution &solution);

	int getCrossingProbability() const {
		return crossingProbability;
	}

	void setCrossingProbability(int crossingProbability) {
		this->crossingProbability = crossingProbability;
	}

	int getMutationProbability() const {
		return mutationProbability;
	}

	void setMutationProbability(int mutationProbability) {
		this->mutationProbability = mutationProbability;
	}

	int getSizePopulation() const {
		return sizePopulation;
	}

	void setSizePopulation(int sizePopulation) {
		this->sizePopulation = sizePopulation;
	}

	const vector<Knapsack>& getKc() const {
		return kc;
	}

	void setKc(const vector<Knapsack>& kc) {
		this->kc = kc;
	}

	int getKnapsackCapacity() const {
		return knapsackCapacity;
	}

	void setKnapsackCapacity(int knapsackCapacity) {
		this->knapsackCapacity = knapsackCapacity;
	}

private:
	int sizePopulation;
	int crossingProbability;
	int mutationProbability;
	int knapsackCapacity;
	vector<Knapsack> kc;

};

#endif /* AG_H_ */
