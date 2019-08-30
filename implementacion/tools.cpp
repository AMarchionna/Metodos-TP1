#ifndef TOOLS
#define TOOLS

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

void printVector(const vector<double>& v){
	
	cout << "(";

	for (int i = 0; i < v.size(); ++i){
		cout << v[i] << " ";
	}

	cout << ") \n";
} 

void imprimirMatriz(vector<vector<double> > A, vector<double> b){
	int n = (int)b.size();
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cout << A[i][j] << " ";
		}
		cout << "    " << b[i] << endl << endl;
	}
}


#endif //TOOLS