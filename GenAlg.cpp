#include "GenAlg.h"



GenAlg::GenAlg(AFLP_Data *aflp,int Npop)
{
	_aflp = aflp;
	_LRC_PerC = 0.4;
	_PCCO = 1;
	_Npop = Npop;
	_Ngens = 100000;
	
	for (int i = 0; i < _aflp->get_ZonesI(); i++) {
		Pot_zone pot1(i, _aflp->get_sizeNofZ(i)+_aflp->get_sizeIAofZ(i));
		Pot_zone pot2(i, _aflp->get_sizeNofZ(i));
		Pot_zone pot3(i, _aflp->get_Capacity(i));
		Pot_zone pot4(i, (double)_aflp->get_Capacity(i) / _aflp->get_maxDemand(i));
		_LRC_I1.push_back(pot2);
		_LRC_IJ.push_back(pot1);
		_LRC_cap.push_back(pot3);
		_LRC_CD.push_back(pot4);
	}
	sort(_LRC_I1.begin(),_LRC_I1.end());
	sort(_LRC_IJ.begin(), _LRC_IJ.end());
	sort(_LRC_cap.begin(), _LRC_cap.end());
	sort(_LRC_CD.begin(), _LRC_CD.end());

	//vector<Pot_zone>::iterator it= upper_bound(LRCI1.begin(), LRCI1.end(), Pot_zone(-1,3));
	
	//int pos1 = it - LRCI1.begin();
	//cout << pos1 << endl;
	//for (int i = 0; i < _aflp->get_ZonesI(); i++) {
		//cout <<LRCI1[i].get_id() << "\t" <<LRCI1[i].get_eval() << endl;
	//}
}


GenAlg::~GenAlg()
{
}


void GenAlg::Constr_Method1() {
	//Constructive method for aaj for the maximization of the covered points by open facilities.
	vector<Pot_zone> LCR_temp = _LRC_I1; 
	Individual *new_individual = new Individual(_aflp);
	
	while (new_individual->get_NopenFac() < _aflp->get_NLoc()) {
		double LB = LCR_temp.back().get_eval() - _LRC_PerC * (LCR_temp.back().get_eval() - LCR_temp.front().get_eval());
		vector<Pot_zone>::iterator it = upper_bound(LCR_temp.begin(), LCR_temp.end(), Pot_zone(-1, LB));
		int pos =(int) (it - LCR_temp.begin());
		int nPos = rand() % (LCR_temp.size() - pos) + pos;
		new_individual->add_openFacilituy(LCR_temp[nPos].get_id());
		LCR_temp.erase(LCR_temp.begin()+nPos);
	}
	LCR_temp.clear();
	//Añadir clientes y Evaluar
	//Generar función en Clase individual
	//Generar conjunto de la población 
	new_individual->completeSol();
	_Pop.insert(*new_individual);
	cout << "sol1 = " << new_individual->get_eval() << endl;
}

void GenAlg::Constr_Method2() {
	vector<Pot_zone> LCR_temp = _LRC_IJ;
	Individual *new_individual = new Individual(_aflp);

	while (new_individual->get_NopenFac() < _aflp->get_NLoc()) {
		double LB = LCR_temp.back().get_eval() - _LRC_PerC * (LCR_temp.back().get_eval() - LCR_temp.front().get_eval());
		vector<Pot_zone>::iterator it = upper_bound(LCR_temp.begin(), LCR_temp.end(), Pot_zone(-1, LB));
		int pos = (int) (it - LCR_temp.begin());
		int nPos = rand() % (LCR_temp.size() - pos) + pos;
		new_individual->add_openFacilituy(LCR_temp[nPos].get_id());
		LCR_temp.erase(LCR_temp.begin() + nPos);
	}
	new_individual->completeSol();
	_Pop.insert(*new_individual);
	cout << "sol2 = " << new_individual->get_eval() << endl;
}

void GenAlg::Constr_Method3() {
	vector<Pot_zone> LCR_temp = _LRC_cap;
	Individual *new_individual = new Individual(_aflp);

	while (new_individual->get_NopenFac() < _aflp->get_NLoc()) {
		double LB = LCR_temp.back().get_eval() - _LRC_PerC * (LCR_temp.back().get_eval() - LCR_temp.front().get_eval());
		vector<Pot_zone>::iterator it = upper_bound(LCR_temp.begin(), LCR_temp.end(), Pot_zone(-1, LB));
		int pos =(int) (it - LCR_temp.begin());
		int nPos = rand() % (LCR_temp.size() - pos) + pos;
		new_individual->add_openFacilituy(LCR_temp[nPos].get_id());
		LCR_temp.erase(LCR_temp.begin() + nPos);
	}
	new_individual->completeSol();
	_Pop.insert(*new_individual);
	cout << "sol3 = " << new_individual->get_eval() << endl;
}

void GenAlg::Constr_Method4() {
	vector<Pot_zone> LCR_temp = _LRC_CD;
	Individual *new_individual = new Individual(_aflp);

	while (new_individual->get_NopenFac() < _aflp->get_NLoc()) {
		double LB = LCR_temp.back().get_eval() - _LRC_PerC * (LCR_temp.back().get_eval() - LCR_temp.front().get_eval());
		vector<Pot_zone>::iterator it = upper_bound(LCR_temp.begin(), LCR_temp.end(), Pot_zone(-1, LB));
		int pos =(int) (it - LCR_temp.begin());
		int nPos = rand() % (LCR_temp.size() - pos) + pos;
		new_individual->add_openFacilituy(LCR_temp[nPos].get_id());
		LCR_temp.erase(LCR_temp.begin() + nPos);
	}
	new_individual->completeSol();
	_Pop.insert(*new_individual);
	cout << "sol4 = " << new_individual->get_eval() << endl;
}

void GenAlg::Constr_Method5() {
	
	Individual *new_individual = new Individual(_aflp);
	set <int> posi,posa;
	for(int i=0; i<_aflp->get_ZonesI();i++){
		posi.insert(i);
	}
	int loc = rand() % posi.size();
	set<int>::iterator it= posi.begin();
	
	advance(it,loc);

	new_individual->add_openFacilituy(*it);
	posa.insert(*it);
	posi.erase(it);
	


	while (new_individual->get_NopenFac() < _aflp->get_NLoc()){
		
		vector<Pot_zone> LCR_temp;
		
		for (auto el1 : posa) {
			for (auto el : posi) {
				double d = _aflp->get_distance(el1, el);
				Pot_zone pot(el, d);
				vector<Pot_zone>::iterator it = upper_bound(LCR_temp.begin(), LCR_temp.end(), pot);
				LCR_temp.insert(it, pot);
			}
		}

		/*for (auto el : LCR_temp) {
			cout << el.get_id() << "\t" << el.get_eval() << endl;
		}*/
		
		double LB = LCR_temp.back().get_eval() - _LRC_PerC * (LCR_temp.back().get_eval() - LCR_temp.front().get_eval());
		vector<Pot_zone>::iterator it = upper_bound(LCR_temp.begin(), LCR_temp.end(), Pot_zone(-1, LB));
		int pos = (int) (it - LCR_temp.begin());
		int nPos = rand() % (LCR_temp.size() - pos) + pos;
		//cout << "Elegido: " << endl;
		//cout << LCR_temp[nPos].get_id() << "\t" << LCR_temp[nPos].get_eval() << endl;
		new_individual->add_openFacilituy(LCR_temp[nPos].get_id());
		posi.erase(LCR_temp[nPos].get_id());
		posa.insert(LCR_temp[nPos].get_id());
		LCR_temp.erase(LCR_temp.begin() + nPos);
		LCR_temp.clear();
	}
	//new_individual->print_OpenFacilities();
	new_individual->completeSol();
	_Pop.insert(*new_individual);
	cout << "sol5 = " << new_individual->get_eval() << endl;
}


void GenAlg::generate_population() {
	int SolPer = (int)floor(_Npop / 5.0);
	while ((int)_Pop.size() < _Npop) {
		int indic = (int)_Pop.size();

		if (indic < SolPer) {
			Constr_Method1();
		}
		else if (indic < 2 * SolPer) {
			Constr_Method2();
		}
		else if (indic < 3 * SolPer) {
			Constr_Method3();
		}
		else if (indic < 4 * SolPer) {
			Constr_Method4();
		}
		else {
			Constr_Method5();
		}
	}
}

void GenAlg::cross_over() {
	int nCop =(int) floor(_Npop * _PCCO);

	vector <Individual> CO_pop;
	set<Individual>::iterator ItInd;
	unordered_set<int> used_ind;
	int index;
	cout << "----------------------------" << endl;
	cout << _Pop.begin()->get_eval() << endl;
	while (used_ind.size() < nCop) {
		index = rand() % _Npop;
		if (used_ind.find(index) == used_ind.end()) {
			ItInd = _Pop.begin();
			advance(ItInd, index);
			CO_pop.push_back(*ItInd);
			used_ind.insert(index);
		}
	}
	
	while (CO_pop.size() > 1) {
		int rnd = rand() % CO_pop.size();
		Individual par1 = CO_pop[rnd];
		CO_pop.erase(CO_pop.begin()+rnd);
		rnd = rand() % CO_pop.size();
		Individual par2 = CO_pop[rnd];
		CO_pop.erase(CO_pop.begin() + rnd);
		cross_ind(par1, par2);
	}
	
	cout << _Pop.begin()->get_eval() << endl;
	cout << "----------------------------" << endl;
}


void GenAlg::cross_ind(Individual dad, Individual mom) {
	
	unordered_set<int> gened = dad.get_openFacilities(), genem = mom.get_openFacilities(),_NI;
	int nPos;
	bool indic = true;
	double rnd;
	
	for (int gd : gened) {
		rnd = (double)rand() / RAND_MAX;
		if (rnd < 0.5) {
			_NI.insert(gd);
		}
	}
	for (int gm : genem) {
		rnd = (double)rand() / RAND_MAX;
		if (rnd < 0.5) {
			_NI.insert(gm);
		}
	}

	while (_NI.size() < _aflp->get_NLoc()) {
		nPos = rand() % _aflp->get_NLoc();
		_NI.insert(nPos);
	}

	while (_NI.size() > _aflp->get_NLoc()) {
		unordered_set<int>::iterator it = _NI.begin();
		nPos = rand() % _NI.size();
		advance(it, nPos);
		_NI.erase(it);
	}

	// Mutación.
	rnd = (double)rand() / RAND_MAX;
	indic = true;
	if (rnd < 0.4) {
		while (indic) {
			nPos = rand() % _aflp->get_NLoc();
			if (_NI.find(nPos) == _NI.end()) {
				
				indic = false;
			}
		}
		unordered_set<int>::iterator it = _NI.begin();
		int nPos2 = rand() % _NI.size();
		advance(it, nPos2);
		_NI.erase(it);
		_NI.insert(nPos);
		
	}

	Individual newIndividual(_aflp);
	for (int elem : _NI) {
		newIndividual.add_openFacilituy(elem);
	}
	newIndividual.completeSol();
	_Pop.insert(newIndividual);
	_NI.clear();
	gened.clear();
	genem.clear();
}
 
void GenAlg::solve(){
	generate_population();

	for (int i = 0; i < _Ngens; i++) {
		cross_over();
	}

}