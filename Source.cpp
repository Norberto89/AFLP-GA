#include "AFLP_Data.h"
#include "GenAlg.h"
#include <ctime>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout << "Argument not valid" << endl;
		system("pause");
		exit(0);
	}
	srand(time(NULL));
	string pth = argv[1];
	AFLP_Data *_AfData = new AFLP_Data(pth);
	
	GenAlg *_gen = new GenAlg(_AfData,100);

	_gen->solve();

	delete _AfData;
	system("pause");
	return 0;
}
