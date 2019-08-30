#include "tools.cpp"

using namespace std;

void printVectores(const vector<double>& v){
	
	cout << "(";

	for (int i = 0; i < v.size(); ++i){
		cout << v[i] << " ";
	}

	cout << ") \n";
} 

void actualizarRanking(vector<double> ranking, pair<int, int> partido){
	int K = 40 ; //cambiar la constante para experimentar
	int ganador = partido.first;
	int perdedor = partido.second;
	ranking[ganador-1] = ranking[ganador-1] + K*(1-1/(1+(pow(10,(ranking[perdedor-1]-ranking[ganador-1])/400))));
	ranking[perdedor-1] = ranking[perdedor-1] - K*(1/(1+pow(10,(ranking[ganador-1]-ranking[perdedor-1])/400)));
	}

vector<double> elo (int T, vector<pair<int, int> > partidos){
	vector<double> ranking(T,1/T);
	for(int i=0; i < partidos.size() ; i++){
		actualizarRanking(ranking, partidos[i]);	
	}
	return ranking;
	}

void ELO(char* input, char* output){
	ifstream Input;
	Input.open(input);

	int T, P;
	Input >> T >> P;

	vector<pair<int, int>> partidos;

	pair<int, int> game;

	for(int k=0; k<P; k++){
		int fecha, i, p_i, j, p_j;
		Input >> fecha >> i >> p_i >> j >> p_j;

		if(p_i>p_j){
			game = {i,j};
		} else {
			game = {j, i};
		}
		
		partidos.push_back(game);
	}

	vector<double> result = elo(T, partidos);

	printVectores(result);
}
