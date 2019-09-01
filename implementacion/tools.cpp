#ifndef TOOLS
#define TOOLS

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

double errorTolerable = 1e-4;

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

bool compareResults(const vector<double>& x, const vector<double>& y){

	bool diferenciasGrandes = false; 
	
	cout << "(";

	for(int i=0; i<x.size()-1; i++){

		cout << abs(x[i]-y[i]) << ", ";
		if(abs(x[i]-y[i])>=1e-4) diferenciasGrandes = true;

	}

	cout << abs(x[x.size()-1]-y[y.size()-1]) << ") \n";
	return diferenciasGrandes;
}

vector<double> checkResults(const vector<vector<double> >& A,const vector<double>& x,const vector<double>& b){

	vector<double> diferencias (x.size(), 0);
	
	for(int i=0; i<diferencias.size(); i++){
		double acum = 0;
		for(int j=0; j<A.size(); j++){
			acum += A[i][j] * x[j];
		}
		diferencias[i] = abs(b[i]-acum);
	}
	
	return diferencias;

}

#endif //TOOLS