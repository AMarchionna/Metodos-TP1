#include <bits/stdc++.h>

using namespace std;

void imprimirMatriz(vector<vector<double> > A, vector<double> b){
	int n = (int)b.size();
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cout << A[i][j] << " ";
		}
		cout << "    " << b[i] << endl << endl;
	}
}

vector<double> eliminacionGaussiana(vector<vector<double> > A, vector<double> b){ 
	//Resuelve el sistema Ax = b
	//Asume que A es de nxn y que b tiene n elementos
	int n = (int)b.size();
	for(int i = 0; i < n-1; i++){//Triangulo la matriz
		for(int j = i+1; j < n; j++){
			double m = A[j][i]/A[i][i];
			for (int k = i; k < n; k++){
				A[j][k] -= m*A[i][k];
			}
			b[j] -= m * b[i]; 
		}
	}
	
	vector<double> resultado;
	for(int i = 0; i < n; i++) resultado.push_back(-1);
	
	for(int i = n-1; i >= 0; i--){//Despejo las incognitas
		double res = b[i];
		for(int j = i+1; j < n; j++){
			res -= A[i][j]*resultado[j];
		}
		res /= A[i][i];
		resultado[i] = res;
	}
	
	return resultado;
	
}

int main(){
	freopen("in.txt", "r", stdin);
	int T; //Cantidad de equipos
	int cantPartidos; //La cantidad de partidos disputados
	cin >> T >> cantPartidos;
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
		cin >> fecha >> equipoLocal >> golesLocal >> equipoVisitante >> golesVisitante;
		if (golesLocal < golesVisitante){
			//Si gano el visitante, los cambio para asumir que gano el local;
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
	
	vector<double> resultado = eliminacionGaussiana(C,b); //Resolvemos el sistema
	
	for(int i = 0; i < T; i++){//Imprimo el resultado
		cout << resultado[i] << endl;
	}
	return 0;
}
