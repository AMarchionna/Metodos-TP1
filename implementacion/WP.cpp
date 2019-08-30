#include "tools.cpp"

using namespace std;

void WP(char* input, char* output){

	ifstream Input;
	Input.open(input);

	int T, P;
	Input >> T >> P;

	vector<double> wins(T, 0); vector<double> matches(T, 0);

	for(int k=0; k<P; k++){
		int fecha, i, p_i, j, p_j;
		Input >> fecha >> i >> p_i >> j >> p_j;

		if(p_i>p_j){
			wins[i-1] += 1;
		} else {
			wins[j-1] += 1;
		}

		matches[i-1] += 1; matches[j-1] += 1;

	}

	Input.close();

	vector<double> result(T); 

	for(int i=0; i<T; i++){
		result[i] = wins[i]/matches[i];
	}

	ofstream Output;
	Output.open(output);
	for (int i = 0; i < result.size(); i++){
		Output << result[i] << "\n";
	}
	Output.close();

}


