/*
 * AG.h
 *
 *  Created on: 31 de ago de 2017
 *      Author: andre
 */

#ifndef AG_H_
#define AG_H_

#include "Solution.h"
#include "Knapsack.h"

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>


using namespace std;

class AG{

public:
	AG(vector<Knapsack> kc, int sizePopulation, clock_t timeBegin, double timeEnd, int capacity);

	Solution crossing1Cut(Solution solution1, Solution solution2);
	Solution crossing2Cut(Solution solution1, Solution solution2);
	Solution mutation(Solution solution);
	Solution competition(Solution solution1, Solution solution2);
	Solution getBestSolution(vector<Solution> population);
	vector<Solution> tournament(vector<Solution> population, vector<Solution> newSolutions, int sizePopulation);
	int fitness(Solution &solution);
	bool checkConflits(Solution &solution);
	void evolucionaryClicle(vector<Solution> population, int sizePopulation);
	void repairSolution(Solution &solution);
	void run(Solution &solution);


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

	int getGeneration() const {
		return generation;
	}

	void setGeneration(int generation) {
		this->generation = generation;
	}

	double getEndTime() const {
		return endTime;
	}

	void setEndTime(double endTime) {
		this->endTime = endTime;
	}

	clock_t getBeginTime() const {
		return beginTime;
	}

	void setBeginTime(clock_t beginTime) {
		this->beginTime = beginTime;
	}

	double getCrossingProbability() const {
		return crossingProbability;
	}

	void setCrossingProbability(double crossingProbability) {
		this->crossingProbability = crossingProbability;
	}

	double getMutationProbability() const {
		return mutationProbability;
	}

	void setMutationProbability(double mutationProbability) {
		this->mutationProbability = mutationProbability;
	}

	const Solution& getBest() const {
		return best;
	}

	void setBest(const Solution& best) {
		this->best = best;
	}

private:
	int sizePopulation;
	double crossingProbability;
	double mutationProbability;
	int knapsackCapacity;
	int generation = 0;
	clock_t beginTime;
	double endTime;
	vector<Knapsack> kc;
	Solution best;

};

#endif /* AG_H_ */
