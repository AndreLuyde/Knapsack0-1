//============================================================================
// Name        : Knapsack.cpp
// Author      : André Luyde
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "Knapsack.h"
#include "AG.h"
#include "BranchAndBound.h"

using namespace std;

//funções
int getValue(vector<Knapsack> items);
int getWeight(vector<Knapsack> items);
void createProblem(vector<Knapsack> * kc, vector<string> fileslist);

int main(int argc, char* argv[]) {
	vector<Knapsack> kc;
	vector<string> fileslist;
	int capacity;
	string arq = argv[1];
	double totalTime = stod(argv[2]);
//	double totalTime = 60.0;
//	string arq = "/home/andre/Documentos/knpconf/kc50.txt";
	ifstream readlist;
	string lineRead;

//	leitura do arquivo com o problema
	readlist.open(arq);

	while (getline(readlist, lineRead)) {
		stringstream ss;
		ss << lineRead << endl;
		fileslist.push_back(ss.str());
	}

	readlist.close();

	capacity = stoi(fileslist[1]);
	createProblem(&kc, fileslist);

	//Algoritmo Genetico
	clock_t start = clock();
	Solution solution;

	AG ag(kc, 100, start, totalTime * 2/3, capacity);
	ag.run(solution);

	clock_t end = clock();
	double finalTime = ((double) end - start) / ((double) CLOCKS_PER_SEC);
	cout << finalTime << "s solution improved to:" << solution.getFitness() << " by heuristic" << endl;

	//branch and bound
	BranchAndBound bnb(kc, capacity, solution.getSolution(), solution.getFitness());
	bnb.run(totalTime * 1/3, solution);

	end = clock();
	finalTime = ((double) end - start) / ((double) CLOCKS_PER_SEC);
	cout << "search concluded. best: " << solution.getFitness() << " time: " << finalTime << "s complete search" << endl;

	//contar itens solução
	int countItens = 0;
	for (int i = 0; i < solution.getSolution().size(); i++) {
		if (solution.getSolution()[i]) {
			countItens++;
		}
	}

	//escrever arquivo de saida
	ofstream outfile;
	outfile.open("sol.txt");

	outfile << solution.getFitness() << endl;
	outfile << countItens << endl;
	for (int i = 0; i < solution.getSolution().size(); i++) {
		if (solution.getSolution()[i]) {
			outfile << i << endl;
		}
	}
	outfile.close();
	return 0;
}
//cria lista com os dados lidos do arquivo
void createProblem(vector<Knapsack> * kc, vector<string> fileslist) {
	Knapsack item;

	//armazenamento na lista
	int size = stoi(fileslist[0]);

	int count = 2;
	int i = 0;

	//armazena valores
	while (i < size) {
		item.profit = stoi(fileslist[count]);
		count++;
		i++;
		kc->push_back(item);
	}

	//armazena pesos
	i = 0;
	while (i < size) {
		kc->at(i).weight = stoi(fileslist[count]);
		count++;
		i++;
	}

	//armazena conflitos
	for (int j = 0; j < kc->size(); j++) {
		i = 0;
		int numConflits = stoi(fileslist[count]);
		count++;
		while (i < numConflits) {
			kc->at(j).conflits.push_back(stoi(fileslist[count]));
			count++;
			i++;
		}
	}
}
