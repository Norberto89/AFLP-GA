#include "Individual.h"



Individual::Individual(AFLP_Data *aflp)
{
	_aflp = aflp;
	_perc = 0.3;
	
	_LRC_cob.resize(_aflp->get_NLoc());
	
	counter = 0;
}


Individual::~Individual()
{
}

void Individual::add_openFacilituy(int id) {
	open_facilities.insert(id);
	_index[id] = counter;

	for(auto el:_aflp->get_coveredZones(id)) {
		Pot_zone pot(el, _aflp->get_Demand(el));
		_LRC_cob[counter].push_back(pot);
	}

	sort(_LRC_cob[counter].begin(), _LRC_cob[counter].end());
	counter++;
}

void Individual::print_OpenFacilities() {
	for (auto el : open_facilities) {
		cout << el << endl;
	}
}

void Individual::get_mobilityNodes() {
	for (int j = 0; j < _aflp->get_ZonesJ(); j++) {
		double distmin = (double)INT_MAX;
		int ind = -1;
		for (auto el : open_facilities) {
			if (_aflp->is_IMobJ(el, j) && _aflp->get_distance(el, j) < distmin) {
				distmin = _aflp->get_distance(el, j);
				ind = el;
			}
		}
		if (ind != -1) {
			Pot_zone pot(j, _aflp->get_Demand(j));
			vector<Pot_zone>::iterator it = upper_bound(_LRC_cob[_index[ind]].begin(), _LRC_cob[_index[ind]].end(), pot);
			_LRC_cob[_index[ind]].insert(it, pot);
		}
	}
}

void Individual::completeSol_max() {

	get_mobilityNodes();

	int cap, acumCap;
	
	for (auto el : open_facilities) {
		cap = _aflp->get_Capacity(el);
		acumCap = 0;
		int i_ind = _index[el];
		vector<Pot_zone> tmp = _LRC_cob[i_ind];
		while (acumCap + tmp.front().get_eval()<cap) {
			vector<Pot_zone>::iterator it = upper_bound(tmp.begin(), tmp.end(), Pot_zone(-1, cap - acumCap));
			vector<Pot_zone> tmp2(tmp.begin(), it);
			Pot_zone pot(-1,  tmp2.back().get_eval() - _perc *(tmp2.back().get_eval()-tmp2.front().get_eval()));
			it = upper_bound(tmp2.begin(),tmp2.end(), pot);
			int pos, nPos;
			if (tmp2.size() == 1) {
				pos = 0;
				nPos = 0;
			}
			else {
				pos = (int)(it - tmp2.begin());
				nPos = rand() % (tmp2.size() - pos) + pos;
			}

			for (auto el2 : tmp) {
				cout <<el2.get_id() << ","<<  el2.get_eval() << "\t";
			}
			cout << endl;
			if (cob_zons.find(tmp2[nPos].get_id()) == cob_zons.end()) {
				acumCap +=(int) tmp2[nPos].get_eval();
				tmp.erase(tmp.begin() + nPos);
				cob_zons.insert(tmp2[nPos].get_id());
				cout << tmp2[nPos].get_id() << "\t" << tmp2[nPos].get_eval() << endl;
			}
			else {
				tmp.erase(tmp.begin() + nPos);
			}
			
			
			cout << endl;
			getchar();
		}

	}


	
}

void Individual::completeSol_min() {
	get_mobilityNodes();
}