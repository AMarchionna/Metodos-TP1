#include "implementacion/CMM.cpp"
#include "implementacion/ELO.cpp"
#include "implementacion/WP.cpp"

int main(int argc, char* argv[]){
	if (argc != 4){
		printf("Parametros incorrectos\n");
		return 1;
	} else {
		int modo = atoi(argv[1]);
		char* input = argv[2];
		char* output = argv[3];

		switch (modo){
			case 0: CMM(input, output);
				break;
			case 1: WP(input, output);
				break;
			case 2: ELO(input, output);
				break;
			default: printf("ERROR\n");
		}
	}
	return 0;
}