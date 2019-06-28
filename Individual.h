#pragma once
#include "AFLP_Data.h"

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

	bool operator<(const Pot_zone& rhs) const {
		//return _k<rhs.getk();
		return _eval < rhs.get_eval();

	}

	bool operator==(const Pot_zone& rhs) const {
		return _eval == rhs.get_eval();
	}
};

class J_zone {
private:
	int _id;
	int _w;
public:
	J_zone(int id,  int w) {
		_id = id;
		_w = w;
	}
	~J_zone() {};
	int get_id() const { return _id; };
	
	int get_w() { return _w; };

	bool operator<(const J_zone& rhs) const {
		//return _k<rhs.getk();
		return _id < rhs.get_id();

	}

	bool operator==(const J_zone& rhs) const {
		return _id == rhs.get_id();
	}
};

class Individual
{
private:

	AFLP_Data *_aflp;
	unordered_set<int> open_facilities;
	unordered_set<int> cob_zons;
	vector<vector<Pot_zone>> _LRC_cob;
	double _perc;
	int counter;
	map<int, int> _index;

	void get_mobilityNodes();
public:
	Individual(AFLP_Data *aflp);
	~Individual();
	void add_openFacilituy(int id);
	int get_NopenFac() { return (int)open_facilities.size(); };

	

	void completeSol_max();
	void completeSol_min();

	void print_OpenFacilities();
};

