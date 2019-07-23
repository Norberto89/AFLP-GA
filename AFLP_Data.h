#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <set>
using namespace std;

class AFLP_Data
{

	int NumZonesI;							// Entero que representa la candidad de puntos en el conjunto I de puntos de demanda
	int NumZonesJ;							// Entero que representa la candidad de puntos en el conjunto J de ubicaciones potenciales de fabricas
	int NumLocations;						// Entero que representa el parametro n del problema (cantidad de fabricas por abrir)
	vector < vector <double> > Distance;	// Matriz cuadrada de distancias de dimension NumZonesI X NumZonesJ
	vector < vector <int> > NofZoneI;       // Vector de vectores que representa las zonas que cubre cada facility i. Por ejemplo
											// NofZoneI[5] es un vector que contiene a todos los puntos j que cubre la fabrica en la ubicacion 5
											// y NofZoneI[5][0] es el primer elemento de ese vector, similarmente NofZone[5][NofZone[5].size()-1] es el último
	vector < unordered_set <int> > InvNofZoneI;    // Vector de vectores que contiene las ubicaciones que cubren a cada punto de demanda. Por ejemplo,
											// InvNofZoneI[8] es un vector que contiene a todos los puntos i que cubren al punto de demanda j=8.
	vector < unordered_set <int> > AofZoneJ;// Vector de vectores que representa los puntos i alcanzables por la mobilidad del punto j. Por ejemplo,
											// AofZone[5] es el conjunto de puntos i que estan en el radio de movilidad del punto j = 5.
	vector < vector <int> > InvAofZoneJ;    // Vector de vectores que representa los puntos j que pueden accesar mediante su movilidad al punto i. Por ejemplo,
											// InvAofZoneJ[4] contiene a todos los puntos j que pueden llegar a la ubicación i = 4.
	vector <int> DemandofJ;					// Vector de demandas
	vector <int> CapacityofI;				// Vector de capacidades

	vector <int> maxDem;					//Obtiene la máxima demanda de los j's cubiertos por la instalación i
	


public:
	AFLP_Data(string pth);
	~AFLP_Data();

	int get_ZonesI() { return NumZonesI; };
	int get_ZonesJ() { return NumZonesJ; };
	int get_NLoc() { return NumLocations; };
	int get_sizeNofZ(int id) { return (int) NofZoneI[id].size(); };
	int get_sizeIAofZ(int id) { return (int) InvAofZoneJ[id].size(); };
	int get_maxDemand(int id) { return maxDem[id]; };
	int get_Capacity(int id) { return CapacityofI[id]; };
	double get_distance(int i, int j) { return Distance[i][j]; };
	vector<int> get_coveredZones(int id) { return NofZoneI[id]; };
	unordered_set<int> get_mobJ(int j) { return AofZoneJ[j]; };
	int get_Demand(int j) { return DemandofJ[j]; };
	bool is_IMobJ(int i, int j);					//Deterina si i está dentro del radio de mobilidad de j.
	bool is_JCovI(int i, int j);					
};

