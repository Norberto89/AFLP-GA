#include "GenAlg.h"



GenAlg::GenAlg(AFLP_Data *aflp)
{
	_aflp = aflp;
	_LRC_PerC = 0.3;
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
	Constr_Method1();
	Constr_Method2();
	Constr_Method3();
	Constr_Method4();
	Constr_Method5();
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
	new_individual->completeSol_max();
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
}

