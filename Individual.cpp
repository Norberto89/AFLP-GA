#include "Individual.h"



Individual::Individual(AFLP_Data *aflp)
{
	_aflp = aflp;
	
	_I = 0;
	_Ncov = 0;
	cov_zones = new unordered_set<int>[_aflp->get_NLoc()];
	
	_demandI.resize(_aflp->get_NLoc());
	fill(_demandI.begin(), _demandI.end(), 0);
	_pC.resize(_aflp->get_NLoc());
	_w.resize(_aflp->get_ZonesJ());
	_CobBy.resize(_aflp->get_ZonesJ());
	fill(_w.begin(), _w.end(), 0.0);
	counter = 0;



	

	_alpha1 = 1000.0;
	_alpha2 = 250.0;
	_alpha3 = 100.0;
	_alpha4 = -1.0;
	_alpha5 = 0.01;
	_alpha6 = 1.0;
}


Individual::~Individual()
{
}

void Individual::add_openFacilituy(int id) {
	open_facilities.insert(id);
	_index[id] = counter;
	counter++;
}

void Individual::print_OpenFacilities() {
	for (auto el : open_facilities) {
		cout << el << endl;
	}
}

void Individual::completeSol() {


	for (int j = 0; j < _aflp->get_ZonesJ(); j++) {
		double distmin = (double)INT_MAX;
		int ind = -1;
		for (auto el : open_facilities) {
			if ((_aflp->is_IMobJ(el, j) || _aflp->is_JCovI(el, j)) && _aflp->get_distance(el, _aflp->get_ZonesI()+j) < distmin) {
				distmin = _aflp->get_distance(el, _aflp->get_ZonesI()+j);
				ind = el;
			}
		}
		if (ind != -1) {
			if (_aflp->is_IMobJ(ind, j) && !_aflp->is_JCovI(ind,j)) {
				_J2.insert(j);
			}
			cov_zones[_index[ind]].insert(j);
			_demandI[_index[ind]] += _aflp->get_Demand(j);
			_Ncov++;
			_CobBy[j] = ind;
		}
		else {
			Ncov_zones.insert(j);
		}
	}
	vector<Pot_zone> LR;
	vector<Pot_zone>::iterator it;
	for (int ele : open_facilities) {
		int c = 0;
		double percentage = (double)_aflp->get_Capacity(ele) / _demandI[_index[ele]];
		_pC[_index[ele]] = (percentage>=1.0) ? 1.0:percentage;
		for (int j : cov_zones[_index[ele]]) {
			if (_pC[_index[ele]] < 1) {
				_w[j] = (int)floor(_pC[_index[ele]] * _aflp->get_Demand(j));
				//_w[j] = _pC[_index[ele]] *(double) _aflp->get_Demand(j);
				Pot_zone pot1(j, (double)_w[j]/_aflp->get_Demand(j));
				it = upper_bound(LR.begin(), LR.end(), pot1);
				LR.insert(it, pot1);
			}else{
				_w[j] = _aflp->get_Demand(j);
			}
			if (_aflp->is_JCovI(ele, j)) {
				_I++;
			}
			c += _w[j];
		}



		if (_pC[_index[ele]] < 1) {
			
			
			int cap = _aflp->get_Capacity(ele);
			while (c < cap ) {
				Pot_zone tmp = LR.front();
				int eleJ = tmp.get_id();
				LR.erase(LR.begin());
				_w[eleJ]++;
				c++;
				tmp.set_Ninfo(eleJ, (double)_w[eleJ] / _aflp->get_Demand(eleJ));
				it = upper_bound(LR.begin(), LR.end(), tmp);
				LR.insert(it, tmp);
			}
			Pot_zone tmp2 = LR.front();
			_pC[_index[ele]] = LR.front().get_eval();
			LR.clear();
		}
		//cout << c << "\t" << _aflp->get_Capacity(ele) << endl;
		/*if (c-0.00001 > _aflp->get_Capacity(ele)) {
			cout << c << "\t" <<_aflp->get_Capacity(ele) << endl;
			cout << "no cumple" << endl;
		}*/
		
	}

	/*for (int j = 0; j < _aflp->get_ZonesJ(); j++) {
		cout << j << "\t" << _w[j] << endl;
	}*/
	make_eval();
}

void Individual::make_eval() {
	double as = 0.0, at = (double)_I, an = 0.0,ae=0.0;
	for (int el1 : Ncov_zones) {
		for (int el2 : Ncov_zones) {
			as += _aflp->get_distance(_aflp->get_ZonesI()+el1, _aflp->get_ZonesI()+el2);
		}
	}
	
	for (int j : _J2) {
		
		if (_aflp->get_distance(_CobBy[j], _aflp->get_ZonesI() + j) != 0) {
			double tmp = 1.0 / _aflp->get_distance(_CobBy[j], _aflp->get_ZonesI() + j);
			//an += _aflp->get_distance(_CobBy[j], _aflp->get_ZonesI()+j);
			double mint = (double)INT_MAX;
			for (int i : _aflp->get_mobJ(j)) {
				double dista = _aflp->get_distance(i, _aflp->get_ZonesI() + j);
				if (dista < mint) {
					mint = dista;
				}
			}
			at += tmp * mint;
		}
		else {
			at++;
		}
	}

	
	for (int j :Ncov_zones) {
		double mint = (double)INT_MAX;
		for (int i : open_facilities) {
			double dista = _aflp->get_distance(i, _aflp->get_ZonesI()+j);
			if (dista < mint) {
				mint = dista;
			}
		}
		an += mint;
	}

	for (int j : _J2) {
		an += _aflp->get_distance(_CobBy[j],_aflp->get_ZonesI()+j);
	}

	

	for (int i : open_facilities) {
		ae += 100*_pC[_index[i]];
	}
	_eval = _alpha1 * _Ncov + _alpha2 * _I + _alpha3 * at + _alpha4 * an + _alpha5 * as + _alpha6 * ae;
	//cout << as << endl;
	//cout << _alpha5*as << endl;
	//cout << _alpha1 * _Ncov << "\t" << _alpha2 * _I << "\t" << _alpha3 * at << "\t" << _alpha4 * an << "\t" << _alpha5 * as << "\t" << _alpha6 * ae<< endl;
	//cout << _Ncov << "\t" <<  _I << "\t" <<  at << "\t" <<  an << "\t" <<  as << "\t" <<  ae << endl;
}