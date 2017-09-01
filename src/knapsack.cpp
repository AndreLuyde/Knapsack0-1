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

using namespace std;

struct Knapsack {
	int label;
	int value;
	int weight;
	vector<int> conflits;
};

//funções
int getValue(vector<Knapsack> items);
int getWeight(vector<Knapsack> items);
void createProblem(vector<Knapsack> &kc, vector<string> fileslist);

int main() {
	vector<Knapsack> kc;
	int capacity;
	char* arq = "/home/andre/Documentos/knpconf/kc20.txt";
	ifstream readlist;
	ofstream resultList;
	vector<string> fileslist;
	string lineRead;

	readlist.open(arq);

	while (getline(readlist, lineRead)) {
		stringstream ss;
		ss << lineRead;
		fileslist.push_back(ss.str());
	}

	readlist.close();
	capacity = stoi(fileslist[1]);
	createProblem(kc, fileslist);

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}

int getWeight(vector<Knapsack> items) {
	int totalWeight = 0;
	for (int i = 0; i < items.size(); i++) {
		totalWeight += items[i].weight;
	}
	return totalWeight;
}

int getValue(vector<Knapsack> items) {
	int totalValue = 0;
	for (int i = 0; i < items.size(); i++) {
		totalValue += items[i].value;
	}
	return totalValue;
}

void createProblem(vector<Knapsack> &kc, vector<string> fileslist) {
	Knapsack item;

	//armazenamento na lista
	int size = stoi(fileslist[0]);

	int count = 2;
	int i = 0;

	//armazena valores
	while (i < size) {
		item.value = stoi(fileslist[count]);
		count++;
		i++;
		kc.push_back(item);
	}

	//armazena pesos
	i = 0;
	while (i < size) {
		kc[i].weight = stoi(fileslist[count]);
		count++;
		i++;
	}

	//armazena conflitos
	for (int j = 0; j < kc.size(); j++) {
		i = 0;
		int numConflits = stoi(fileslist[count]);
		count++;
		while (i < numConflits) {
			kc[j].conflits.push_back(stoi(fileslist[count]));
			count++;
			i++;
		}
	}
}
