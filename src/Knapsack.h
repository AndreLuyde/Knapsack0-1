/*
 * Knapsack.h
 *
 *  Created on: 1 de set de 2017
 *      Author: andre
 */

#ifndef SRC_KNAPSACK_H_
#define SRC_KNAPSACK_H_

using namespace std;

class Knapsack {
public:
	int label;
	int profit;
	int weight;
	vector<int> conflits;
};

#endif /* SRC_KNAPSACK_H_ */
