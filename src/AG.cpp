/*
 * AG.cpp
 *
 *  Created on: 31 de ago de 2017
 *      Author: andre
 */

#include "AG.h"

AG::AG(vector<Knapsack> kc, int sizePopulation, clock_t beginTime,
		double endTime, int capacity) {
	setKc(kc);
	setSizePopulation(sizePopulation);
	setCrossingProbability(0.9);
	setMutationProbability(1 / sizePopulation);
	setBeginTime(beginTime);
	setEndTime(endTime);
	setKnapsackCapacity(capacity);
}

void AG::run() {
	//inicializa a população de forma randomica
	vector<int> items;
	Solution solution;
	vector<Solution> population;
	for (int i = 0; i < getSizePopulation(); i++) {
		items.clear();
		for (int j = 0; j < getKc().size(); j++) {
			items.push_back(rand() % (2));
		}
		solution.setSolution(items);
		solution.setFitness(0);
		solution.setChecked(false);
		population.push_back(solution);
	}

	evolucionaryClicle(population, getSizePopulation());
}

void AG::evolucionaryClicle(vector<Solution> population, int sizePopulation) {
	double currentTime = 0;

	//vetor para armazenar os filhos
	vector<Solution> newSolutions;

	//calcula o fitness da população
	for (int i = 0; i < population.size(); i++) {
		fitness(population[i]);
	}
	do {
		newSolutions.clear();
		while (newSolutions.size() < (sizePopulation / 3)) {
			int seed =
					std::chrono::system_clock::now().time_since_epoch().count();
			static default_random_engine gen(seed);
			normal_distribution<double> dist(0.0, 1.0);
			double probability = dist(gen);

			//verifica a probabilidade de cruzamento
			if (probability < getCrossingProbability()) {
				int rand1 = rand() % (population.size());
				int rand2 = rand() % (population.size());
				newSolutions.push_back(
						crossing2Cut(population[rand1], population[rand2]));
			}

			//verifica a probabilidade de mutação
			if (probability < getMutationProbability()) {
				int rand1 = rand() % (population.size());
				newSolutions.push_back(mutation(population[rand1]));
			}
		}

		//calcula o fitness dos novos individuos
		for (int i = 0; i < newSolutions.size(); i++) {
			fitness(newSolutions[i]);
		}

		//seleção para próxima geração
		population = tournament(population, newSolutions, sizePopulation);
		setGeneration(getGeneration() + 1);

		//Mostra melhor solução da geração
		Solution best = getBestSolution(population);
		for (int i = 0; i < best.getSolution().size(); i++) {
			cout << best.getSolution()[i];
		}
		cout << " " << endl;
		cout << "Fitness: " << best.getFitness() << endl;

		//atualiza critério de parada
		clock_t clockEnd = clock();
		currentTime = ((double) clockEnd - getBeginTime())
				/ ((double) CLOCKS_PER_SEC);
	} while (currentTime < getEndTime()); //condição de tempo
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
	solutionGenerated.setChecked(false);
	solutionGenerated.setFitness(0);
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
	solutionGenerated.setChecked(false);
	solutionGenerated.setFitness(0);
	return solutionGenerated;
}

Solution AG::mutation(Solution solution) {
	int randNum = rand() % (solution.getSolution().size());
	vector<int> sol = solution.getSolution();
	if (sol[randNum] == 0) {
		sol[randNum] = 1;
	} else {
		sol[randNum] = 0;
	}
	solution.setSolution(sol);
	solution.setChecked(false);
	solution.setFitness(0);
	return solution;
}

vector<Solution> AG::tournament(vector<Solution> population,
		vector<Solution> newSolutions, int sizePopulation) {
	vector<Solution> finalPopulation;
	int rand1;
	int rand2;
	int countPopularion = 0;

	for (int i = 0; i < newSolutions.size(); i++) {
		population.push_back(newSolutions[i]);
	}
	while (countPopularion < sizePopulation) {
		rand1 = rand() % (population.size());
		rand2 = rand() % (population.size());
		if (!population[rand1].isChecked() && !population[rand2].isChecked()) {
			finalPopulation.push_back(
					competition(population[rand1], population[rand2]));
			countPopularion++;
		}
	}
	return finalPopulation;
}

Solution AG::competition(Solution solution1, Solution solution2) {
	if (solution1.getFitness() != 0) {
		if (solution2.getFitness() != 0) {
			if (solution1.getFitness() > solution2.getFitness()) {
				solution1.setChecked(true);
				return solution1;
			} else {
				solution2.setChecked(true);
				return solution2;
			}
		} else {
			fitness(solution2);
		}
	} else {
		fitness(solution1);
		if (solution2.getFitness() != 0) {
			fitness(solution2);
		}
	}

	if (solution1.getFitness() > solution2.getFitness()) {
		solution1.setChecked(true);
		return solution1;
	} else {
		solution2.setChecked(true);
		return solution2;
	}
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
		solution.setFitness(fitness - 100000000);
	} else if (checkConflits(solution)) {
		solution.setFitness(fitness - 100000000);
	} else {
		solution.setFitness(fitness);
	}
	return fitness;
}

bool AG::checkConflits(Solution &solution) {
	bool avaliable = false;
	for (int i = 0; i < solution.getSolution().size(); i++) {
		if (solution.getSolution()[i] == 1) {
			for (int j = 0; j < getKc()[i].conflits.size(); j++) {
				for (int k = 0; k < solution.getSolution().size(); k++) {
					if (solution.getSolution()[k] == 1) {
						if (k == getKc()[i].conflits[j]) {
							avaliable = true;
							return true;
						}
					}
				}
			}
		}
	}
	return avaliable;
}

Solution AG::getBestSolution(vector<Solution> population) {
	Solution best = population[0];
	int fitness = population[0].getFitness();
	for (int i = 1; i < population.size(); i++) {
		if (population[i].getFitness() > fitness) {
			best = population[i];
		}
	}
	return best;
}

