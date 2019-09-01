#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include <fstream>
#include <utility>
#include <algorithm>

#include "../implementacion/tools.cpp"
#include "../implementacion/CMM.cpp"
#include "../implementacion/ELO.cpp"
#include "../implementacion/WP.cpp"


using namespace std;

vector<string> testIn = {"tests/test1.in", "tests/test2.in", "tests/test-prob-1.in", "tests/test-prob-2.in"};
vector<string> testExpected = {"tests/test1.expected", "tests/test2.expected", "tests/test-prob-1.expected", "tests/test-prob-2.expected"};
vector<string> testAtpCases = {"atp_matches_2015.dat", "atp_matches_2016.dat"};
vector<string> fixedAtpCases;
int equiposAComparar = 20;

string s = "output.txt";

void testCatedra(){

	/* Script para los tests de la cátedra */

	cout << "Comparando con resultados de la catedra..." << endl;
	cout << "Error considerado: " << errorTolerable << endl << endl;;

	for(int i=0; i < testIn.size(); i++){

		cout << "Diferencias con test " << i << ":" << endl << "    ";

		
		char* testChar = const_cast<char*>(testIn[i].c_str());
		char* testOutput = const_cast<char*>(s.c_str());

		vector<double> x = CMM(testChar, testOutput);

		ifstream Expected;

		Expected.open(testExpected[i]);

		vector<double> true_x (0);

		double r;
		while (Expected >> r) {
			true_x.push_back(r);
		}

		Expected.close();

		bool control = compareResults(x, true_x);
		if(control) cout << "Hay diferencias mayores a " << errorTolerable << endl;
		else cout << "No hay diferencias relevantes." << endl;

		cout << endl;

	}

}


bool imprimirResultados = false;
bool imprimirComparacion = true;

int countTeams(string file){

	ifstream File; File.open(file);

	map<int, int> m; m.clear();

	int T, L; File >> T >> L;
	int count = 0;
	for(int i=0; i<L; i++){
		int fecha, local, gol_local, vis, gol_vis;
		File >> fecha >> local >> gol_local >> vis >> gol_vis;

		if(m.count(local)==0){
			m.insert({local, count}); count ++;
		}
		if(m.count(vis)==0){
			m.insert({vis, count}); count ++;
		}

	}

	File.close();
	return count;

}

void fixFile(string input){

	int teams = countTeams(input);

	ifstream Old_File; ofstream Proper_File;
	string name = "test_cases/test_case_"; name += input;
	Old_File.open(input); Proper_File.open(name);

	map<int, int> m; m.clear();
	int nextPlayer = 1;

	int T, L; Old_File >> T >> L;
	Proper_File << teams << " " << L << endl;
	for(int i=0; i<L; i++){

		int fecha, local, gol_local, vis, gol_vis;
		Old_File >> fecha >> local >> gol_local >> vis >> gol_vis;
		Proper_File << fecha << " ";

		if(m.count(local)==0){ //Verifico si el equipo es nuevo
			m.insert({local, nextPlayer}); nextPlayer += 1;
		}
		Proper_File << m[local] << " " << gol_local << " ";

		if(m.count(vis)==0){ 
			m.insert({vis, nextPlayer}); nextPlayer += 1;
		}
		Proper_File << m[vis] << " " << gol_vis << endl;

	}

	fixedAtpCases.push_back(name);

	Old_File.close(); Proper_File.close();

}

void makeTestCases(){

	fixedAtpCases.clear();

	for(int i=0; i<testAtpCases.size(); i++){
		fixFile(testAtpCases[i]);
	}
}

/*
void testAtpFile(string input){

	vector<double> CMM_res = CMM(input);
	vector<double> WP_res = WP(input);
	vector<double> ELO_res = ELO(input);
	vector<int> orderCMM, orderWP, orderELO;
	orderCMM.clear(); orderWP.clear(); orderELO.clear();

	for(int i=1; i<CMM_res.size(); i++){
		orderCMM.push_back(i); orderWP.push_back(i); orderELO.push_back(i);
	}

}*/

void testAtp() {

	makeTestCases();

	for(int i=0; i<fixedAtpCases.size(); i++){

		cout << "Resultados de " << fixedAtpCases[i] << ":" << endl;
		cout << "(Solo los mejores " << equiposAComparar << ")" << endl << endl;

		char* torneo = const_cast<char*>(fixedAtpCases[i].c_str());
		char* genericOutput = const_cast<char*>(s.c_str());

		vector<double> CMM_res = CMM(torneo, genericOutput);
		vector<double> WP_res = WP(torneo, genericOutput);
		vector<double> ELO_res = ELO(torneo, genericOutput);
		vector<pair<double, int>> orderCMM, orderWP, orderELO;
		orderCMM.clear(); orderWP.clear(); orderELO.clear();

		pair<double, int> elem = make_pair (0, 0);
		for(int i=0; i<CMM_res.size(); i++){ 
			elem.second = i; 
			elem.first = CMM_res[i]; orderCMM.push_back(elem);
			elem.first = WP_res[i]; orderWP.push_back(elem);
			elem.first = ELO_res[i]; orderELO.push_back(elem);
		}

		sort(orderCMM.begin(), orderCMM.end());
		sort(orderWP.begin(), orderWP.end());
		sort(orderELO.begin(), orderELO.end());

		cout << "  CMM  |  WP  |  ELO  " << endl;

		for(int j=0; j<equiposAComparar; j++){
			cout << "  " << orderCMM[orderCMM.size()-1-j].second << "  |";
			cout << "  " << orderWP[orderCMM.size()-1-j].second << "  |";
			cout << "  " << orderELO[orderCMM.size()-1-j].second << "  " << endl;
		}

		cout << endl << "----------------------------------" << endl;
	}
}

int main() {

	testAtp();

	return 0;

}


