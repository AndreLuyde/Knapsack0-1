/*
 * AG.cpp
 *
 *  Created on: 31 de ago de 2017
 *      Author: andre
 */

#include "AG.h"

AG::AG(vector<Knapsack> kc) {
	setKc(kc);
}

AG::~AG() {
	// TODO Auto-generated destructor stub
}

Solution AG::crossing1Cut(Solution solution1, Solution solution2) {
	int randNum = rand() % (solution1.getSolution().size());
	vector<int> newSolution;
	Solution solutionGenerated;
	for (int i = 0; i < randNum; i++) {
		newSolution.push_back(solution1.getSolution()[i]);
	}
	for (int i = randNum; i < solution1.getSolution().size(); i++) {
		newSolution.push_back(solution2.getSolution()[i]);
	}
	solutionGenerated.setSolution(newSolution);
	return solutionGenerated;
}

Solution AG::crossing2Cut(Solution solution1, Solution solution2) {
	int rand1 = rand() % (solution1.getSolution().size());
	int rand2 = rand() % (solution2.getSolution().size());
	vector<int> newSolution;
	Solution solutionGenerated;
	if (rand1 < rand2) {
		for (int i = 0; i < rand1; i++) {
			newSolution.push_back(solution1.getSolution()[i]);
		}
		for (int i = rand1; i < rand2; i++) {
			newSolution.push_back(solution2.getSolution()[i]);
		}
		for (int i = rand2; i < solution1.getSolution().size(); i++) {
			newSolution.push_back(solution1.getSolution()[i]);
		}
	} else {
		for (int i = 0; i < rand2; i++) {
			newSolution.push_back(solution1.getSolution()[i]);
		}
		for (int i = rand2; i < rand1; i++) {
			newSolution.push_back(solution2.getSolution()[i]);
		}
		for (int i = rand1; i < solution1.getSolution().size(); i++) {
			newSolution.push_back(solution1.getSolution()[i]);
		}
	}
	solutionGenerated.setSolution(newSolution);
	return solutionGenerated;
}

vector<Solution> tournament(vector<Solution> population,
		vector<Solution> newSolutions, int sizePopulation) {
	vector<Solution> finalPopulation;
	for (int i = 0; i < newSolutions.size(); i++) {
		population.push_back(newSolutions[i]);
	}
	return finalPopulation;
}

int AG::fitness(Solution &solution) {
	int fitness = 0;
	int totalWeight = 0;
	vector<int> sol = solution.getSolution();
	for (int i = 0; i < sol.size(); i++) {
		if (sol[i] == 1) {
			fitness += getKc()[i].value;
			totalWeight += getKc()[i].weight;
		}
	}

	//verificar viabilidade
	if (totalWeight > getKnapsackCapacity()) {
		solution.setFitness(fitness - 100000);
	} else if (checkConflits(solution)) {
		solution.setFitness(fitness - 100000);
	} else {
		solution.setFitness(fitness);
	}
	return fitness;
}

bool AG::checkConflits(Solution &solution) {
	bool avaliable = true;

	for (int i = 0; i < solution.getSolution().size(); i++) {
		for (int j = 0; j < getKc()[i].conflits.size(); j++) {
			if (solution.getSolution()[i] == 1) {
				if (i == getKc()[i].conflits[j]) {
					avaliable = false;
				}
			}
		}
	}
	return avaliable;
}



