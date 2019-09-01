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
#include "testCreator.cpp"

using namespace std;

vector<string> testIn = {"tests/test1.in", "tests/test2.in", "tests/test-prob-1.in", "tests/test-prob-2.in"};
vector<string> testExpected = {"tests/test1.expected", "tests/test2.expected", "tests/test-prob-1.expected", "tests/test-prob-2.expected"};
vector<string> testAtpCases = {"atp_matches_2015.dat", "atp_matches_2016.dat"};
vector<string> fixedAtpCases;
string s = "output.txt"; //Lo uso para pasar archivos basura a las funciones
string creator = "newTournament.txt";
int equiposAComparar = 20;


double getError(int teams, int matches){

	/* Genera un torneo con los parametros de entrada */
	/* y devuelve el error de la solucion con norma 1 */

	createTournament(teams, matches);
	//El archivo se llama "newTournament.txt"

	char* torneo = const_cast<char*>(creator.c_str());
	char* output = const_cast<char*>(s.c_str());

	vector<double> x = CMM(torneo, output);

	ifstream Input;
	Input.open(torneo);

	//Armo la matriz C y al vector b
	//Esto deberia estar modularizado pero bueno

	int T; //Cantidad de equipos
	int cantPartidos; //La cantidad de partidos disputados
	Input >> T >> cantPartidos;
	vector<vector<double> > C; //La matriz de Colley
	for(int i = 0; i < T; i++){//Inicializamos C
		vector<double> fila;
		for(int j = 0; j < T; j++){
			fila.push_back(i == j ? 2 : 0);
		}
		C.push_back(fila);
	}
	vector<double> b; //El vector b del metodo CMM
	for(int i = 0; i < T; i++){//Inicializo el vector b
		b.push_back(1);
	} 
	//Leo los partidos disputados
	for(int partido = 0; partido < cantPartidos; partido++){
		int fecha, equipoLocal, equipoVisitante, golesLocal, golesVisitante;
		Input >> fecha >> equipoLocal >> golesLocal >> equipoVisitante >> golesVisitante;
		if (golesLocal < golesVisitante){
			//Si gano el visitante, los cambio para asumir que gano el local
			swap(equipoLocal, equipoVisitante);
		}
		//Pongo en rango a los equipos
		equipoLocal -= 1;
		equipoVisitante -= 1;
		//Actualizo la matriz C acorde al partido
		C[equipoLocal][equipoLocal] += 1;
		C[equipoVisitante][equipoVisitante] += 1;
		C[equipoLocal][equipoVisitante] -= 1;
		C[equipoVisitante][equipoLocal] -= 1;
		//Actualizo el vector b
		b[equipoLocal] += 0.5;
		b[equipoVisitante] -= 0.5;
	}

	Input.close();

	vector<double> errorVector = checkResults(C, x, b);

	double error = 0;
	for(int i=0; i<errorVector.size(); i++) error += abs(errorVector[i]);
	return error;
}

void matchTeamMatter(){

	/* Experimentacion variando ambos a la vez */

	int equiposInicial = 100; int equiposFinal = 5000; 
	int k = 20; int salto = 20;

	cout << "Experimentacion: \"Match AND Team quantity matters?\" "<< endl;
	cout << "Cantidad de partidos inicial : " << equiposInicial << endl;
	cout << "Cantidad de partidos final : " << equiposFinal << endl;
	cout << "Cantidad de equipos por torneo: " << k << " * #equipos" << endl;
	cout << "Salto por iteracion: " << salto << endl << endl;

	string output = "match&Team_output.txt";

	cout << "------- Guardando los resultados en " << output << " -------" << endl;

	ofstream File; File.open(output);

	File << "Equipos,Error" << endl;

	for(int i=equiposInicial; i<= equiposFinal; i+=salto) {
		
		double error = getError(i, k*i);
		File << i << "," << error << endl;
	
	}

	File.close();	

}

void matchesCountDoesntMatter() {

	/* Experimentacion variando la cantidad de partidos */

	int cantidadDeEquipos = 5000;
	int partidosInicial = 10; int partidosFinal = 100000;
	int salto = 20;

	cout << "Experimentacion: \"Matches quatity matters?\" "<< endl;
	cout << "Cantidad de partidos inicial : " << partidosInicial << endl;
	cout << "Cantidad de partidos final : " << partidosFinal << endl;
	cout << "Cantidad de equipos por torneo: " << cantidadDeEquipos << endl;
	cout << "Salto por iteracion: " << salto << endl << endl;

	string output = "matchCount_output.txt";

	cout << "------- Guardando los resultados en " << output << " -------" << endl;

	ofstream File; File.open(output);

	File << "Equipos,Error" << endl;

	for(int i=partidosInicial; i<= partidosFinal; i+=salto) {
		
		double error = getError(i, cantidadDeEquipos);
		File << i << "," << error << endl;
	
	}

	File.close();

}

void teamCountDoesntMatter() {

	/* Experimentacion variando la cantidad de equipos */

	int cantidadDePartidos = 10000;
	int equiposInicial = 10; int equiposFinal = 5000;
	int salto = 10;

	cout << "Experimentacion: \"Team quantity matters?\" "<< endl;
	cout << "Cantidad de equipos inicial : " << equiposInicial << endl;
	cout << "Cantidad de equipos final : " << equiposFinal << endl;
	cout << "Cantidad de partidos por torneo: " << cantidadDePartidos << endl;
	cout << "Salto por iteracion: " << salto << endl << endl;

	string output = "teamCount_output.txt";

	cout << "------- Guardando los resultados en " << output << " -------" << endl;

	ofstream File; File.open(output);

	File << "Equipos,Error" << endl;

	for(int i=equiposInicial; i<=equiposFinal; i+=salto){

		double error = getError(i, cantidadDePartidos);
		File << i << "," << error << endl;

	}

	File.close();	

}


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


int countTeams(string file){

	/* Cuenta los equipo en un archivo de entrada */

	// Sirve porque los archivos pasados por la catedra
	// estan mal

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

map<int, int> fixFile(string input){

	/* Arregla los datos de entrada */

	// Renumera los equipos para asignarla a cada uno
	// un valor entre 1 y la cantidad de equipos

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

	return m;

}

void makeTestCases(){

	/* Arma todos los casos de test disponibles */

	fixedAtpCases.clear();

	for(int i=0; i<testAtpCases.size(); i++){
		fixFile(testAtpCases[i]);
	}
}

void comparePlayersResult(string file){

	/* Arma un torneo sin perder los ID de los jugadores */

	char* torneo = const_cast<char*>(file.c_str());
	char* genericOutput = const_cast<char*>(s.c_str());

	map<int, int> m = fixFile(file);
}


void testAtp() {

	/* Compara resultados de torneos con cada metodo */

	//Imprime por consola a los mejores del torneo

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

	/* Drivers */

	//testCatedra();
	//testAtp();
	//teamCountDoesntMatter();
	//matchesCountDoesntMatter();
	matchTeamMatter();

	return 0;

}


