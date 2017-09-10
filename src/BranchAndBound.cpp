/*
 * BranchAndBound.cpp
 *
 *  Created on: 5 de set de 2017
 *      Author: andre
 */

#include "BranchAndBound.h"

using namespace std;

BranchAndBound::BranchAndBound(vector<Knapsack> kc, int cap, vector<bool> solSpc, int profit){
	problem = kc;
	solSpace = solSpc;
	best = solSpace;
	capacity = cap;
	maxProfit = profit;
}

//Branch and bound
void BranchAndBound::run(double endtTime, Solution &solution) {
	double elapsedTime = 0.0;

	while (elapsedTime < endtTime) {
		clock_t start, end;
		start = clock();

		//verifica a qualidade da solução
		vector<int> prof = getProfit();
		if (prof[0] > maxProfit) {
			maxProfit = prof[0];
			best = solSpace;

			//mostra a solução
//			cout << "Solução: ";
//			for (int i = 0; i < solSpace.size(); i++) {
//				cout << solSpace[i];
//			}
//			cout << ", Profit: " << prof[0];
//			cout << ", Best: " << maxProfit;
//			cout << endl;
		}

		//atualiza elemento para a pesquisa
		int pos = prof[1];

		for (int i = pos + 1; i < solSpace.size(); i++) {
			solSpace[i] = false;
		}

		//atualiza espaço de busca
		while (true && solSpace[pos] && pos > 0) {
			solSpace[pos] = false;
			pos--;
		}
		if (pos > 0) {
			solSpace[pos] = true;
		} else {
			if (solSpace[pos] == true)
				break;
			else
				solSpace[pos] = (solSpace[pos] | true);
		}
		//calcula o tempo decorrido e atualiza
		end = clock();
		double dif = ((double) end - start) / ((double) CLOCKS_PER_SEC);
		elapsedTime += dif;
	}
	cout << elapsedTime << "s solution improved to: " << maxProfit << " by branch-and-bound"<< endl;
	solution.setSolution(solSpace);
	solution.setFitness(maxProfit);
}
//verifica o lucro da solução e se ela é valida
vector<int> BranchAndBound::getProfit() {
	int ans = 0, weight = 0;
		for (int i = solSpace.size() -1; i >= 0; i--) {
			if (solSpace[i]) {
				ans += problem[i].profit;
				weight += problem[i].weight;
				if (weight > capacity)
					return {-100, i};
				for (int j = problem[i].conflits.size() - 1; j >= 0; j--) {
					if (solSpace[problem[i].conflits[j]]) {
						return {-100, (int)(solSpace.size()-1)};
					}
				}
			}
		}
		return {ans, (int)(solSpace.size()-1)};
}
