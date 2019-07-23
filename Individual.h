#pragma once
#include "AFLP_Data.h"
#include <algorithm>
#include <unordered_set>
#include <map>

class Pot_zone {
private:
	int _id;
	double _eval;
public:
	Pot_zone(int id, double eval) {
		_id = id;
		_eval = eval;
	}
	~Pot_zone() {};
	int get_id() { return _id; };
	double get_eval() const { return _eval; };

	void set_Ninfo(int id, double eval) {
		_id = id;
		_eval = eval;
	};

	bool operator<(const Pot_zone& rhs) const {
		//return _k<rhs.getk();
		return _eval < rhs.get_eval();

	}

	bool operator==(const Pot_zone& rhs) const {
		return _eval == rhs.get_eval();
	}
};

class Individual
{
private: 
	AFLP_Data *_aflp;
	unordered_set<int> open_facilities;
	unordered_set<int> *cov_zones;
	unordered_set<int> Ncov_zones;
	unordered_set<int> _J2;
	vector<int> _demandI;
	vector <int> _CobBy;
	vector <double> _pC;		//Porcentaje asignado 
	vector<int> _w;

	int _I;
	int _Ncov;

	double _eval;

	double _alpha1;
	double _alpha2;
	double _alpha3;
	double _alpha4;
	double _alpha5;
	double _alpha6;

	int counter;
	map<int, int> _index;

	void make_eval();

public:
	Individual(AFLP_Data *aflp);
	~Individual();
	void add_openFacilituy(int id);
	int get_NopenFac() { return (int)open_facilities.size(); };

	void completeSol();

	void print_OpenFacilities();

	unordered_set<int> get_openFacilities() { return open_facilities; };

	double get_eval() const{ return _eval; };


	bool operator<(const Individual& rhs) const {
		//return _k<rhs.getk();
		return _eval > rhs.get_eval();

	}

	bool operator==(const Individual& rhs) const {
		return _eval == rhs.get_eval();
	}
};

