/*
 * AG.cpp
 *
 *  Created on: 31 de ago de 2017
 *      Author: andre
 */

#include "AG.h"

AG::AG(vector<Knapsack> kc, int sizePopulation, clock_t beginTime, double endTime, int capacity) {
	setKc(kc);
	setSizePopulation(sizePopulation);
	setCrossingProbability(0.9);
	setMutationProbability(1 / sizePopulation);
	setBeginTime(beginTime);
	setEndTime(endTime);
	setKnapsackCapacity(capacity);
}

void AG::run(Solution &solution) {
	//inicializa a população de forma randomica
	vector<bool> items;
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
	solution = getBest();
}
//ciclo evolucionario do algoritmo
void AG::evolucionaryClicle(vector<Solution> population, int sizePopulation) {
	double elapsedTime = 0;

	//vetor para armazenar os filhos
	vector<Solution> newSolutions;

	//calcula o fitness da população
	for (int i = 0; i < population.size(); i++) {
		fitness(population[i]);
	}
	do {
		newSolutions.clear();
		while (newSolutions.size() < (sizePopulation / 3)) {
			int seed = std::chrono::system_clock::now().time_since_epoch().count();
			static default_random_engine gen(seed);
			normal_distribution<double> dist(0.0, 1.0);
			double probability = dist(gen);

			//verifica a probabilidade de cruzamento
			if (probability < getCrossingProbability()) {
				int rand1 = rand() % (population.size());
				int rand2 = rand() % (population.size());
				newSolutions.push_back(crossing1Cut(population[rand1], population[rand2]));
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

		//Armazena e mostra melhor solução da geração
		Solution best = getBestSolution(population);
		if (getGeneration() == 1) {
			setBest(best);
		} else {
			if (best.getFitness() > getBest().getFitness()) {
				setBest(best);
				//Mostra a solução
//				for (int i = 0; i < getBest().getSolution().size(); i++) {
//					cout << best.getSolution()[i];
//				}
//				cout << " " << endl;
//				cout << "Fitness: " << best.getFitness() << endl;
			}
		}

		//atualiza critério de parada
		clock_t clockEnd = clock();
		elapsedTime = ((double) clockEnd - getBeginTime())/ ((double) CLOCKS_PER_SEC);
	} while (elapsedTime < getEndTime()); //condição de tempo
}
//cruzamento de 1 corte
Solution AG::crossing1Cut(Solution solution1, Solution solution2) {
	int randNum = rand() % (solution1.getSolution().size());
	vector<bool> newSolution;
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
//cruzamento de 2 cortes
Solution AG::crossing2Cut(Solution solution1, Solution solution2) {
	int rand1 = rand() % (solution1.getSolution().size());
	int rand2 = rand() % (solution2.getSolution().size());
	vector<bool> newSolution;
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
//mutação do indivíduo alterando cromossomo
Solution AG::mutation(Solution solution) {
	int randNum = rand() % (solution.getSolution().size());
	vector<bool> sol = solution.getSolution();
	if (!sol[randNum]) {
		sol[randNum] = true;
	} else {
		sol[randNum] = false;
	}
	solution.setSolution(sol);
	solution.setChecked(false);
	solution.setFitness(0);
	return solution;
}
//torneio para decidir quais individuos vão para a prócima geração
vector<Solution> AG::tournament(vector<Solution> population, vector<Solution> newSolutions, int sizePopulation) {
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
			finalPopulation.push_back(competition(population[rand1], population[rand2]));
			countPopularion++;
		}
	}
	return finalPopulation;
}
//verifica qual solução é melhor
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
//calcula o valor fitness(lucro) da solução
int AG::fitness(Solution &solution) {
	if (checkConflits(solution)) {
		repairSolution(solution);
	}
	int fitness = 0;
	int totalWeight = 0;
	vector<bool> sol = solution.getSolution();
	for (int i = 0; i < sol.size(); i++) {
		if (sol[i]) {
			fitness += getKc()[i].profit;
			totalWeight += getKc()[i].weight;
		}
	}

	//verificar viabilidade
	if (totalWeight > getKnapsackCapacity()) {
		solution.setFitness(fitness - 10000000);
	} else if (checkConflits(solution)) {
		solution.setFitness(fitness - 10000000);
	} else {
		solution.setFitness(fitness);
	}
	return fitness;
}
//repara a solução removendo os conflitos
void AG::repairSolution(Solution &solution) {
	vector<bool> sol = solution.getSolution();
	int repair = rand() % (2);
	if (repair) {
		for (int i = 0; i < sol.size(); i++) {
			if (sol[i]) {
				for (int j = 0; j < getKc()[i].conflits.size(); j++) {
					sol[getKc()[i].conflits[j]] = 0;
				}
			}
		}
	} else {
		for (int i = sol.size() - 1; i > 1; i--) {
			if (sol[i]) {
				for (int j = 0; j < getKc()[i].conflits.size(); j++) {
					sol[getKc()[i].conflits[j]] = 0;
				}
			}
		}
	}
	solution.setSolution(sol);
}
//verifica se a solução possui conflitos
bool AG::checkConflits(Solution &solution) {
	bool avaliable = false;
	vector<bool> sol = solution.getSolution();

	for (int i = 0; i < sol.size(); i++) {
		if (sol[i]) {
			for (int j = 0; j < getKc()[i].conflits.size(); j++) {
				if (sol[getKc()[i].conflits[j]]) {
					avaliable = true;
					return true;
				}
			}
		}
	}
	return avaliable;
}
//retorna a melhor solução
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

