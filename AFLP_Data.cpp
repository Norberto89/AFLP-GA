#include "AFLP_Data.h"



AFLP_Data::AFLP_Data(string pth)
{
	ifstream ifile(pth.c_str(), ios::in);
	if (!ifile.good()) {
		cout << "File not found" << endl;
		system("pause");
		exit(0);
	}


	cout << "Reading Instance ..." << endl;
	//Definiendo instancia con nombre A
	cout << pth << endl;

	
	ifile >> NumZonesI;
	ifile >> NumZonesJ;
	ifile >> NumLocations;

	int NumZones = NumZonesI + NumZonesJ;
	vector<double> CordX;
	vector<double> CordY;
	CordX.resize(NumZones);
	CordY.resize(NumZones);
	for (int i = 0; i < NumZones; i++) {
		ifile >> CordX[i];
		ifile >> CordY[i];
	}

	Distance.resize(NumZones);
	for (int i = 0; i < NumZones; i++) {
		Distance[i].resize(NumZones);
		for (int j = 0; j < NumZones; j++)
			ifile >> Distance[i][j];
	}

	NofZoneI.resize(NumZonesI);
	InvNofZoneI.resize(NumZonesJ);

	for (int i = 0; i < NumZonesI; i++) {
		int SizeOfN;
		ifile >> SizeOfN;
		for (int n = 0; n < SizeOfN; n++) {
			int number;
			ifile >> number;
			NofZoneI[i].push_back(number);
			InvNofZoneI[number].push_back(i);
		}
	}
	cout << endl;

	AofZoneJ.resize(NumZonesJ);
	InvAofZoneJ.resize(NumZonesI);
	for (int j = 0; j < NumZonesJ; j++) {
		int SizeOfA;
		ifile >> SizeOfA;
		for (int n = 0; n < SizeOfA; n++) {
			int number;
			ifile >> number;
			AofZoneJ[j].insert(number);
			InvAofZoneJ[number].push_back(j);
		}
	}
	

	DemandofJ.resize(NumZonesJ);
	for (int j = 0; j < NumZonesJ; j++) {
		ifile >> DemandofJ[j];
	}

	CapacityofI.resize(NumZonesI);
	maxDem.resize(NumZonesI);
	for (int i = 0; i < NumZonesI; i++) {
		ifile >> CapacityofI[i];
		int demax = INT_MIN;
		for (auto el : NofZoneI[i]) {
			if (DemandofJ[el] > demax) {
				demax = DemandofJ[el];
			}
		}
		maxDem[i]= demax;
	}

	cout << "Done" << endl;
	ifile.close();
}


AFLP_Data::~AFLP_Data()
{
	Distance.clear();
	NofZoneI.clear();
	InvNofZoneI.clear();
	AofZoneJ.clear();
	InvAofZoneJ.clear();
	DemandofJ.clear();
	CapacityofI.clear();
}

bool AFLP_Data::is_IMobJ(int i, int j) {
	if (AofZoneJ[i].find(j) != AofZoneJ[i].end()) {
		return true;
	}
	return false;
}