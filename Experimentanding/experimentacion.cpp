#include <bits/stdc++.h>

using namespace std;

vector<string> testIn = {"tests/test1.in", "tests/test2.in", "tests/test-prob-1.in", "tests/test-prob-2.in"};

vector<string> testExpected = {"tests/test1.expected", "tests/test2.expected", "tests/test-prob-1.expected", "tests/test-prob-2.expected"};

vector<vector<double> > a_restar_kohan;

void printVector(const vector<double>& v){
	
	cout << "(";

	for (int i = 0; i < v.size(); ++i){
		cout << v[i] << " ";
	}

	cout << ") \n";
} 

void imprimirMatriz(vector<vector<double> >& A, vector<double> b){
	int n = (int)b.size();
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cout << A[i][j] << " ";
		}
		cout << "    " << b[i] << endl << endl;
	}
}

void compareResults(const vector<double>& x, const vector<double>& y){
	
	cout << "(";

	for(int i=0; i<x.size()-1; i++){

		cout << abs(x[i]-y[i]) << ", ";

	}

	cout << abs(x[x.size()-1]-y[y.size()-1]) << ") \n";
}

void checkResults(const vector<vector<double> >& A,const vector<double>& x,const vector<double>& b){
	
	cout << endl;

	vector<double> diferencias (x.size(), 0);
	
	for(int i=0; i<diferencias.size(); i++){
		double acum = 0;
		for(int j=0; j<A.size(); j++){
			acum += A[i][j] * x[j];
		}
		diferencias[i] = abs(b[i]-acum);
	}
	
	for(int i=0; i<diferencias.size(); i++) cout << diferencias[i] << " ";

	cout << "\n";

}

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

//Armar bien PLS los .h

vector<double> solve(string input){

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
	
	return resultado;
}

void testCatedra(){

	/* Script para los tests de la cátedra */

	for(int i=0; i < testIn.size(); i++){
		
		vector<double> x = solve(testIn[i]);

		ifstream Expected;

		Expected.open(testExpected[i]);

		vector<double> true_x (0);

		double r;
		while (Expected >> r) {
			true_x.push_back(r);
		}

		Expected.close();

		compareResults(x, true_x);

	}

}

int main() {

	cout << endl;

	testCatedra();

	return 0;

}


