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

vector<string> testIn = {"tests/test1.in", 
						"tests/test2.in", 
						"tests/test-prob-1.in", 
						"tests/test-prob-2.in", 
						"tests/test_completo_10_1.in", 
						"tests/test_completo_100_4.in", 
						"tests/test_completo_100_8.in", 
						"tests/test_completo_1000_2.in",
						"tests/test_completo_1000_8.in"};

vector<string> testExpected = {"tests/test1.expected", 
							"tests/test2.expected", 
							"tests/test-prob-1.expected", 
							"tests/test-prob-2.expected",
							"tests/test_completo_10_1.expected", 
							"tests/test_completo_100_4.expected", 
							"tests/test_completo_100_8.expected", 
							"tests/test_completo_1000_2.expected",
							"tests/test_completo_1000_8.expected"};
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

	int equiposInicial = 100; int equiposFinal = 10000; 
	int k = 2; int salto = 50;

	cout << "Experimentacion: \"Match AND Team quantity matters?\" "<< endl;
	cout << "Cantidad de equipos inicial : " << equiposInicial << endl;
	cout << "Cantidad de equipos final : " << equiposFinal << endl;
	cout << "Cantidad de partidos por torneo: " << k << " * #equipos^2" << endl;
	cout << "Salto por iteracion: " << salto << endl << endl;

	string output = "match&Team_output.txt";

	cout << "------- Guardando los resultados en " << output << " -------" << endl;

	ofstream File; File.open(output);

	File << "Equipos,Error" << endl;

	for(int i=equiposInicial; i<= equiposFinal; i+=salto) {
		
		double error = getError(i, k*i*i);
		File << i << "," << error << endl;
	
	}

	File.close();	

}

void matchesCountDoesntMatter() {

	/* Experimentacion variando la cantidad de partidos */

	int cantidadDeEquipos = 1000;
	int partidosInicial = 500; int partidosFinal = 5000000;
	int salto = 500;

	cout << "Experimentacion: \"Matches quatity matters?\" "<< endl;
	cout << "Cantidad de partidos inicial : " << partidosInicial << endl;
	cout << "Cantidad de partidos final : " << partidosFinal << endl;
	cout << "Cantidad de equipos por torneo: " << cantidadDeEquipos << endl;
	cout << "Salto por iteracion: " << salto << endl << endl;

	string output = "matchCount_output.txt";

	cout << "------- Guardando los resultados en " << output << " -------" << endl;

	ofstream File; File.open(output);

	File << "Partidos,Error" << endl;

	for(int i=partidosInicial; i<= partidosFinal; i+=salto) {
		
		double error = getError(cantidadDeEquipos, i);
		File << i << "," << error << endl;
	
	}

	File.close();

}

void teamCountDoesntMatter() {

	/* Experimentacion variando la cantidad de equipos */

	int cantidadDePartidos = 10000;
	int equiposInicial = 50; int equiposFinal = 10000;
	int salto = 50;

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

pair<int, int> matchesCount(string file, int player){

	/* Cuenta los partidos jugados y ganados por un jugador */

	ifstream File; File.open(file);

	int T, L; File >> T >> L;
	int matches, wins; matches = wins = 0;

	for(int i=0; i<L; i++) {
		int fecha, local, gol_local, vis, gol_vis;
		File >> fecha >> local >> gol_local >> vis >> gol_vis;

		if(local == player) {

			if(gol_local > gol_vis) wins += 1;
			matches += 1;

		} else if (vis == player) {

			if(gol_vis > gol_local) wins += 1;
			matches += 1;

		}

	}

	File.close();

	return make_pair(matches, wins);

}

void makeTestCases(){

	/* Arma todos los casos de test disponibles */

	fixedAtpCases.clear();

	for(int i=0; i<testAtpCases.size(); i++){
		fixFile(testAtpCases[i]);
	}
}

int fromValueKey(map<int, int>& m, int value){
	for(auto &x: m) {
		if(x.second == value)
			return x.first;
	}
	return 0;
}

bool moreData = true;

void testAtp(int i){

	/* Genera el ranking del torneo y lo imprime por consola */

	/* Guardo el mapeo que se hace durante el fixFile */

	map<int, int> m = fixFile(testAtpCases[i]);

	/*   Realizo el torneo con cada ranking   */

	char* torneo = const_cast<char*>(fixedAtpCases[0].c_str());
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

	/* Voy a armarme un map con los nombres de los jugadores */

	map<int, string> codeToName; codeToName.clear();

	string f = "atp_players.csv";

	ifstream File; File.open(f);

	string code, name, surname, let, number, country;

	while(File.good()) {

		getline(File, code, ',');
		getline(File, name, ',');
		getline(File, surname, ',');
		getline(File, let, ',');
		getline(File, number, ',');
		getline(File, country, '\n');

		name += " "; name += surname;

		if(code != "") 
			codeToName.insert({stoi(code), name});

	}

	File.close();


	cout << "  Rank  |  CMM  |  WP  |  ELO  " << endl;

	for(int j=0; j<equiposAComparar && j < orderCMM.size(); j++){
		cout << "  " << j+1 << "  |";
		cout << "  " << codeToName[fromValueKey(m, orderCMM[orderCMM.size()-1-j].second + 1)] << "  |";
		cout << "  " << codeToName[fromValueKey(m, orderWP[orderCMM.size()-1-j].second + 1)] << "  |";
		cout << "  " << codeToName[fromValueKey(m, orderELO[orderCMM.size()-1-j].second + 1)] << "  " << endl;
	}

	cout << endl << "Peores 10: " << endl;
		for(int j=0; j<10; j++){	
			cout << "  " << j+1 << "  |";
			cout << "  " << codeToName[fromValueKey(m, orderCMM[j].second + 1)] << "  |";
			cout << "  " << codeToName[fromValueKey(m, orderWP[j].second + 1)] << "  |";
			cout << "  " << codeToName[fromValueKey(m, orderELO[j].second + 1)] << "  " << endl;
		}


	if(moreData) {

		cout << endl << "Mostrando datos de CMM:" << endl;

		for(int j=0; j<5; j++) { 
			pair<int, int> data = matchesCount(fixedAtpCases[0], orderCMM[orderCMM.size()-1-j].second + 1);
			cout << j+1 << ": " << data.first << " partidos, " << data.second << " victorias" << endl;
		}


		cout << endl << "Mostrando datos de WP:" << endl;

		for(int j=0; j<5; j++) { 
			pair<int, int> data = matchesCount(fixedAtpCases[0], orderWP[orderCMM.size()-1-j].second + 1);
			cout << j+1 << ": " << data.first << " partidos, " << data.second << " victorias" << endl;
		}

		cout << endl << "Mostrando datos de Elo:" << endl;

		for(int j=0; j<5; j++) { 
			pair<int, int> data = matchesCount(fixedAtpCases[0], orderELO[orderCMM.size()-1-j].second + 1);
			cout << j+1 << ": " << data.first << " partidos, " << data.second << " victorias" << endl;
		}
	}

	cout << endl << "----------------------------------" << endl;
}

void testNBA() {

	/* Arma el ranking de los equipos de la NBA */

	// Primero armamos el diccionario con el nombre de los equipos

	ifstream File; File.open("nba_2016_teams.csv");

	string number; string name;
	map<int, string> m;

	while(File.good()) {

		getline(File, number, ',');
		getline(File, name, '\n');
		
		if (number != "")
			m.insert({stoi(number), name});

	}

	File.close();

	// Ahora hago el torneo con cada metodo y
	// ordeno los resultados

	string f = "nba_2016_scores.dat";

	char* torneo = const_cast<char*>(f.c_str());
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

	cout << "     CMM     |     WP     |     ELO     " << endl;

	for(int j=0; j<orderCMM.size(); j++){
		cout << "   " << m[orderCMM[orderCMM.size()-1-j].second + 1] << "   |";
		cout << "   " << m[orderWP[orderCMM.size()-1-j].second + 1] << "   |";
		cout << "   " << m[orderELO[orderCMM.size()-1-j].second + 1] << "   " << endl;
	}

	cout << endl << "Mostrando datos de CMM:" << endl;

	for(int j=0; j<10; j++) { 
		pair<int, int> data = matchesCount(f, orderCMM[orderCMM.size()-1-j].second + 1);
		cout << j+1 << ": " << data.first << " partidos, " << data.second << " victorias" << endl;
	}


	cout << endl << "Mostrando datos de WP:" << endl;

	for(int j=0; j<10; j++) { 
		pair<int, int> data = matchesCount(f, orderWP[orderCMM.size()-1-j].second + 1);
		cout << j+1 << ": " << data.first << " partidos, " << data.second << " victorias" << endl;
	}

	cout << endl << "Mostrando datos de Elo:" << endl;

	for(int j=0; j<10; j++) { 
		pair<int, int> data = matchesCount(f, orderELO[orderCMM.size()-1-j].second + 1);
		cout << j+1 << ": " << data.first << " partidos, " << data.second << " victorias" << endl;
	}

	cout << endl << "----------------------------------" << endl;

}

bool print = true;

int estrategia() {

	/*  Genera un torneo y sigue el desarrollo de la estrategia */

	int teams = 40; int matches = 2000;
	int iteraciones = 100; int yo = 1;
	int res; string temp = creator;

	createTournament(teams, matches); //El archivo se llama newTournament

	if (print)
		cout << "Iteracion | Mi ranking | Mejor jugador | Mejor ranking" << endl;

	for(int i=0; i<iteraciones; i++) {

		char* torneo = const_cast<char*>(temp.c_str());
		char* output = const_cast<char*>(s.c_str());

		vector<double> rank = CMM(torneo, output);

		int bestPlayer = -1; double maxRank = -1;

		for(int j=0; j<rank.size(); j++) {
			if(rank[j]>maxRank) {
				maxRank = rank[j];
				bestPlayer = j+1;
			}
		}

		if(bestPlayer == yo) {
			if (print)
				cout << endl << "Alcance el liderazgo. Se requirieron "
								<< i+1 << " iteraciones." << endl;
			res = i+1;
			break;
		}

		if (print)
			cout << "    " << i+1 << "    |   " << rank[yo-1] << "   |   " << 
						bestPlayer << "   |  " << maxRank << endl;

		string nuevoTorneo = "nuevoTorneo.txt";
		if(torneo == nuevoTorneo) 
			nuevoTorneo = "nuevoTorneoMirror.txt";

		ifstream Input;
		Input.open(torneo);

		int T; //Cantidad de equipos
		int cantPartidos; //La cantidad de partidos disputados
		Input >> T >> cantPartidos; cantPartidos++;

		ofstream NuevoTorneo; NuevoTorneo.open(nuevoTorneo);

		NuevoTorneo << T << " " << cantPartidos << endl;

		int fecha, A, B, A_p, B_p;

		for (int i = 0; i<cantPartidos; i++){
			Input >> fecha >> A >> A_p >> B >> B_p;
			NuevoTorneo << fecha << " " << A << " " << A_p << " " << B << " " << B_p << endl;
		}
		NuevoTorneo << fecha << " " << yo << " 1 " << bestPlayer << " 0 \n"; 

		Input.close(); NuevoTorneo.close();

		temp = nuevoTorneo;

		if(i == iteraciones-1 && print)
			cout << "No se alcanzo el mejor puesto." << endl;

	}

	return res;

}

void estrategiaPromediada() {

	/* Calcula el promedio de las iteraciones de la estrategia */

	int rep = 1000; print = false;
	cout << "Calculando el promedio de iteraciones necesarias para alcanzar el primer lugar." << endl;
	cout << "Repeticiones a realizar: " << rep << endl;

	double count = 0;
	for(int i=0; i<rep; i++) {
		count += estrategia();
	}

	cout << endl << "Se requirieron " << count/rep << " iteraciones en promedio." << endl;

}

void EloVSCMM() {

	/*  Crea un torneo donde los resultados de Elo son  */
	/*            distintos a los de CMM                */

	string fileName = "CMMvsElo.txt";
	ofstream File; File.open(fileName);
	int teams = 20; int matches = 2000; int Franja = 50;
	int end = 40;

	File << teams << " " << 4*matches << endl;

	for(int i=0; i<4*matches; i++) {
		//Fecha, local, puntos_l, vis, puntos_v
		if(i<2000-Franja)
			File << 1 << " " << (i%5)+1 << " 1 " << (i%15)+6 << " 0 " << endl;
			//Inflamos el ranking de los primeros 5 equipos.
		if(i>=2000-Franja && i<2000+Franja) 
			File << 1 << " " << (i%2)+19 << " 1 " << (i%5)+1 << " 0 " << endl;
			//Damos ranking a los equipos 19 y 20 
		if((i>=2000+Franja))
			File << 1 << " " << (i%13)+6 << " 1 " << (i%5)+1 << " 0 " << endl;
	}

	File.close();

	cout << "Realizando experimento: CMM vs Elo" << endl;
	cout << "Generando torneo..." << endl;
	cout << "#equipos: " << teams << 
			" | #partidos: " << 4*matches << 
			" | Franja de victorias: " << 2*Franja << endl << endl;



	char* torneo = const_cast<char*>(fileName.c_str());
	char* genericOutput = const_cast<char*>(s.c_str());

	vector<double> CMM_res = CMM(torneo, genericOutput);
	vector<double> ELO_res = ELO(torneo, genericOutput);
	vector<pair<double, int>> orderCMM, orderELO;
	orderCMM.clear(); orderELO.clear();

	pair<double, int> elem = make_pair (0, 0);
	for(int i=0; i<CMM_res.size(); i++){ 
		elem.second = i; 
		elem.first = CMM_res[i]; orderCMM.push_back(elem);
		elem.first = ELO_res[i]; orderELO.push_back(elem);
	}

	sort(orderCMM.begin(), orderCMM.end());
	sort(orderELO.begin(), orderELO.end());

	cout << "     Rank     |     CMM     |     ELO     " << endl;

	for(int j=0; j<orderCMM.size(); j++){
		cout << "      " << j+1 << "      |     ";
		cout << orderCMM[orderCMM.size()-1-j].second + 1 << "      |     ";
		cout << orderELO[orderCMM.size()-1-j].second + 1 << endl;
	}


}

int main() {

	/*      Drivers      */

	/* Catedra */
	//testCatedra();

	/* Experimentacion */
	//teamCountDoesntMatter();
	//matchesCountDoesntMatter();
	//matchTeamMatter();

	/* Torneos reales */
	//testAtp(0);  //Se le pasa 0 para 2015, 1 para 2016
	//testNBA();

	/* Torneos de comparacion */
	//EloVSCMM();

	/* Estrategia para CMM */
	//estrategia();
	//estrategiaPromediada();

	return 0;

}


