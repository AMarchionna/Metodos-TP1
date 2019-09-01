#include "tools.cpp"

using namespace std;

vector<vector<double> > a_restar_kohan;

vector<double> eliminacionGaussiana(vector<vector<double> > A, vector<double> b){ 
	//Resuelve el sistema Ax = b
	//Asume que A es de nxn y que b tiene n elementos	
	int n = (int)b.size();
	vector<vector<double> > costos_A;
	vector<double> costos_b;
	for(int i = 0; i < n; i++){
		vector<double> fila;
		for(int j = 0; j < n; j++){
			fila.push_back(0);
		}
		costos_A.push_back(fila);
		costos_b.push_back(0);
	}
	for(int i = 0; i < n-1; i++){//Triangulo la matriz
		for(int j = i+1; j < n; j++){
			double m = A[j][i]/A[i][i];
			for (int k = i; k < n; k++){
				double y = -m * A[i][k];
				double t = A[j][k] + y;
				costos_A[j][k] = (t - A[j][k]) - y;
				A[j][k] = t;
			}
			double y = -m * b[i];
			double t = b[j] + y;
			costos_b[j] = (t - b[j]) - y;
			b[j] = t;
		}
	}
	
	vector<double> resultado;
	for(int i = 0; i < n; i++) resultado.push_back(-1);
	
	for(int i = n-1; i >= 0; i--){//Despejo las incognitas
		double res = b[i];
		double c = 0;
		for(int j = i+1; j < n; j++){
			double y = -A[i][j]*resultado[j];
			double t = res + y;
			c = (t - res) - y;
			res = t;
		}
		res /= A[i][i];
		resultado[i] = res;
	}
	
	return resultado;
	
}

vector<double> CMM(char* input, char* output){

	ifstream Input;
	Input.open(input);

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
	
	vector<double> resultado = eliminacionGaussiana(C,b); //Resolvemos el sistema
	double suma = 0;
	for(int i = 0; i < T; i++){
		suma += b[i];
	}
	
	ofstream Output;
	Output.open(output);
	for (int i = 0; i < T; i++){
		Output << resultado[i] << "\n";
	}
	Output.close();

	return resultado;
}
