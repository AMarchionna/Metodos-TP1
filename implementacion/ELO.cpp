#include "tools.cpp"

using namespace std;

void actualizarRanking(vector<double>& ranking, pair<int, int> partido){
	double K = 40 ;
	int ganador = partido.first;
	int perdedor = partido.second;
	int temp = ranking[ganador-1];
	ranking[ganador-1] += K-(K/(1+(pow(10,(ranking[perdedor-1]-ranking[ganador-1])/400))));
	ranking[perdedor-1] -= K*(1/(1+pow(10,(temp-ranking[perdedor-1])/400)));	
}

vector<double> elo (double T, vector<pair<int, int> > partidos){
	vector<double> ranking(T,1);
	for(int i=0; i < partidos.size() ; i++){
		actualizarRanking(ranking, partidos[i]);	
	}
	return ranking;
}

vector<double> ELO(char* input, char* output){
	ifstream Input;
	Input.open(input);

	double T; int P;
	Input >> T >> P;

	vector<pair<int, int>> partidos;

	pair<int, int> game;

	for(int k=0; k<P; k++){
		int fecha, i, p_i, j, p_j;
		Input >> fecha >> i >> p_i >> j >> p_j;

		if(p_i>p_j){
			game = {i,j};
		} else {
			game = {j,i};
		}
		
		partidos.push_back(game);
	}

	vector<double> result = elo(T, partidos);

	ofstream Output;
	Output.open(output);
	for (int i = 0; i < result.size(); i++){
		Output << result[i] << "\n";
	}
	Output.close();

	return result;
}

