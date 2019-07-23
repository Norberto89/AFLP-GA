#pragma once
#include "AFLP_Data.h"
#include"Individual.h"
#include <algorithm>
#include<iterator>

class GenAlg
{
	AFLP_Data *_aflp;
	vector<Pot_zone> _LRC_I1;
	vector<Pot_zone> _LRC_IJ;
	vector<Pot_zone> _LRC_cap;
	vector<Pot_zone> _LRC_CD;
	double _LRC_PerC;
	double _PCCO;
	

	set<Individual> _Pop;
	int _Npop;
	int _Ngens;

	void Constr_Method1();
	void Constr_Method2();
	void Constr_Method3();
	void Constr_Method4();
	void Constr_Method5();

	void generate_population();
	void cross_over();
	void cross_ind(Individual dad, Individual mom);
	
public:
	GenAlg(AFLP_Data *aflp,int Npop);
	~GenAlg();

	void solve();
};

