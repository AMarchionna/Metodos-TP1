#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

void createTournament(int T, int P){
	int fecha = 1;

	ofstream outfile ("newTournament.txt");

	outfile << T << " " << P << endl;

	int A, B, A_p, B_p;

	for (int i=0; i<P; i++){
		A = rand() % T +1;
		B = rand() % T +1;
		while (B == A){
			B = rand() % T +1; 
		}
		A_p = rand() % 2;
		B_p = 1 - A_p;
		
		outfile << fecha << " " << A << " " << A_p << " " << B << " " << B_p << endl;
	}

	outfile.close();
}

/*int main(int argc, char* argv[]){
	int T = atoi(argv[1]);
	int P = atoi(argv[2]);

	createTournament(T, P);
}*/
