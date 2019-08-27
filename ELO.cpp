#include <bits/stdc++.h>

using namespace std;

void actualizarRanking(vector<double> ranking, pair<int, int> partido){
	int K = 40 ; //cambiar la constante para experimentar
	int ganador = partido.first;
	int perdedor = partido.second;
	ranking[ganador-1] = ranking[ganador-1] + K*(1-1/(1+(pow(10,(ranking[perdedor-1]-ranking[ganador-1])/400))));
	ranking[perdedor-1] = ranking[perdedor-1] - K*(1/(1+pow(10,(ranking[ganador-1]-ranking[perdedor-1])/400)));
	};

vector<double> elo (int T, vector<pair<int, int> > partidos){
	vector<double> ranking(T,1/T);
	for(int i=0; i < partidos.size() ; i++){
		actualizarRanking(ranking, partidos[i]);	
	};
	return ranking;
	};

int main(){
	
	
	
	
	return 0;
}
