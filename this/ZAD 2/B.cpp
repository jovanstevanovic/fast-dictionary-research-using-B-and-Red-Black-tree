#pragma once
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <Windows.h>
#include "KlasaRed.h"
using namespace std;

class B {
	struct Elem {
		int* kljucevi;
		int* indeksi;
		Elem** podStabla;
		Elem* otac;
		int kap, duz;
		explicit Elem(int k = 4, Elem* ot = nullptr) : otac(ot) {
			kljucevi = new int[k - 1];
			indeksi = new int[k - 1];
			for (int i = 0; i < k - 1; i++) {
				kljucevi[i] = 999;
				indeksi[i] = -1;
			}
			podStabla = new Elem*[kap = k] {0};
			duz = 0;
		}
	};
	struct PomElem {
		int kljuc, ind;
		Elem *desni;
		explicit PomElem(int klj = 999, int i = -1, Elem* l = nullptr, Elem* d = nullptr) : kljuc(klj), ind(i), desni(d) { }
	};
	Elem* koren = nullptr;
public:
	B(int k = 4) {
		koren = new Elem(k);
	}
	bool cvorJeList(Elem* p) const {
		bool Jelist = true;
		for (int i = 0; i < p->kap; i++)
			if (p->podStabla[i] != nullptr)
				Jelist = false;
		return Jelist;
	}
	~B() { brisi(); }
	Elem* dohvKoren() const { return koren; }
	void formirajKoren(int k) { koren = new Elem(k); }
	static bool punCvor(Elem* pok) { return pok->duz == pok->kap - 1; }
	static bool prazanCvor(Elem* pok) { return pok->duz == 0; }
	Elem* nadjiCvor(int k, bool& postoji) const;
	void dodavanjeBezPrenosa(Elem* p, int k, int ind = -1);
	void dodavanjeSaPrenosom(Elem* p, PomElem* pm);
	void unesiUpomNiz(Elem* p, int* pomNiz, int k);
	void isprazniCvor(Elem* p);
	bool umetanje(int kljuc, int indek = -1);
	void pisi() const;
	int visinaStabla() const;
	void brisi();
	int brCvorovaSaPraznim() const;
	bool da_Li_se_Nalazi(Elem* p, PomElem* q);
	void ispisi_stablo(Elem* k, int nivo, int* p, int i);
};

bool B::da_Li_se_Nalazi(Elem* p, PomElem* q) {
	bool nalazi = false;
	for (int i = 0; i < p->kap - 1; i++)
		if (p->kljucevi[i] == q->kljuc)
			nalazi = true;
	return nalazi;
}

B::Elem* B::nadjiCvor(int k, bool& postoji) const {
	int i;
	if (koren == nullptr) return nullptr;
	Elem* pok = koren;
	if (pok->duz == 0) return koren;
	while (pok != nullptr) {
		if (pok->kljucevi[0] == 999) i = 1;
		else i = 0;
		for (; i < pok->kap - 1; i++) {
			if (pok->kljucevi[i] == k) { postoji = true; return pok; }
			if (pok->kljucevi[i] > k && cvorJeList(pok)) return pok;
			if (pok->kljucevi[i] > k) { pok = pok->podStabla[i]; i = -1; break; }
			if (pok->kljucevi[pok->kap - 2] < k && cvorJeList(pok))
				return pok;
			if (pok->kljucevi[pok->kap - 2] < k) {
				pok = pok->podStabla[pok->kap - 1];
				i = -1;
				break;
			}
		}
	}
	return nullptr;
}

void B::dodavanjeBezPrenosa(Elem* p, int k, int ind) {
	if (prazanCvor(p)) { p->indeksi[1] = 1; p->kljucevi[1] = k; p->duz++; return; }
	
	if (k < p->kljucevi[1] && k < p->kljucevi[0] && p->kljucevi[0] != 999) {
		p->kljucevi[2] = p->kljucevi[1];
		p->kljucevi[1] = p->kljucevi[0];
		p->kljucevi[0] = k;
		p->indeksi[2] = 0;
		p->indeksi[1] = 1;
		p->indeksi[0] = 0;
		p->duz++;
		return;
	}
	if (k < p->kljucevi[1] && p->kljucevi[0] == 999) {
		p->kljucevi[0] = k;
		p->indeksi[0] = 0;
		p->duz++;
		return;
	}
	if (k < p->kljucevi[1] && k > p->kljucevi[0] && p->kljucevi[0] != 999) {
		p->kljucevi[2] = p->kljucevi[1];
		p->kljucevi[1] = k;
		p->indeksi[2] = 0;
		p->indeksi[1] = 1;
		p->indeksi[0] = 0;
		p->duz++;
		return;
	}
	if (k > p->kljucevi[1] && k > p->kljucevi[2] && p->kljucevi[2] != 999) {
		p->kljucevi[0] = p->kljucevi[1];
		p->kljucevi[1] = p->kljucevi[2];
		p->kljucevi[2] = k;
		p->indeksi[2] = 0;
		p->indeksi[1] = 1;
		p->indeksi[0] = 0;
		p->duz++;
		return;
	}
	if (k > p->kljucevi[1] && p->kljucevi[2] == 999) {
		p->kljucevi[2] = k;
		p->indeksi[2] = 0;
		p->duz++;
		return;
	}
	if (k > p->kljucevi[1] && k < p->kljucevi[2] && p->kljucevi[2] != 999) {
		p->kljucevi[0] = p->kljucevi[1];
		p->kljucevi[1] = k;
		p->indeksi[2] = 0;
		p->indeksi[1] = 1;
		p->indeksi[0] = 0;
		p->duz++;
		return;
	}

}

void B::unesiUpomNiz(Elem* p, int* pomNiz, int k) {
	for (int i = 0; i < p->kap - 1; i++) pomNiz[i] = p->kljucevi[i];
	pomNiz[p->kap - 1] = k;
	for (int i = 0; i < p->kap; i++) {
		for (int j = i + 1; j < p->kap; j++) {
			if (pomNiz[i] > pomNiz[j]) {
				int privr = pomNiz[i];
				pomNiz[i] = pomNiz[j];
				pomNiz[j] = privr;
			}
		}
	}
}

void B::isprazniCvor(Elem* p) {
	for (int i = 0; i < p->kap - 1; i++) { p->kljucevi[i] = 999; p->indeksi[i] = -1; }
	p->duz = 0;
}

void B::dodavanjeSaPrenosom(Elem* p, PomElem* pm) {
	int k = pm->kljuc;
	if (k < p->kljucevi[1] && k < p->kljucevi[0] && p->kljucevi[0] != 999) {
		p->kljucevi[2] = p->kljucevi[1];
		p->kljucevi[1] = p->kljucevi[0];
		p->kljucevi[0] = k;
		p->podStabla[3] = p->podStabla[2];
		p->podStabla[2] = p->podStabla[1];
		p->podStabla[1] = pm->desni;
		pm->desni->otac = p;
		p->indeksi[2] = 0;
		p->indeksi[1] = 1;
		p->indeksi[0] = 0;
		p->duz++;
		return;
	}
	if (k < p->kljucevi[1] && p->kljucevi[0] == 999) {
		p->kljucevi[0] = k;
		p->podStabla[0] = p->podStabla[1];
		p->podStabla[1] = pm->desni;
		pm->desni->otac = p;
		p->indeksi[0] = 0;
		p->duz++;
		return;
	}
	if (k < p->kljucevi[1] && k > p->kljucevi[0] && p->kljucevi[0] != 999) {
		p->kljucevi[2] = p->kljucevi[1];
		p->kljucevi[1] = k;
		p->podStabla[3] = p->podStabla[2];
		p->podStabla[2] = pm->desni;
		pm->desni->otac = p;
		p->indeksi[2] = 0;
		p->indeksi[1] = 1;
		p->indeksi[0] = 0;
		p->duz++;
		return;
	}
	if (k > p->kljucevi[1] && k > p->kljucevi[2] && p->kljucevi[2] != 999) {
		p->kljucevi[0] = p->kljucevi[1];
		p->kljucevi[1] = p->kljucevi[2];
		p->kljucevi[2] = k;
		p->podStabla[0] = p->podStabla[1];
		p->podStabla[1] = p->podStabla[2];
		p->podStabla[2] = p->podStabla[3];
		p->podStabla[3] = pm->desni;
		pm->desni->otac = p;
		p->indeksi[2] = 0;
		p->indeksi[1] = 1;
		p->indeksi[0] = 0;
		p->duz++;
		return;
	}
	if (k > p->kljucevi[1] && p->kljucevi[2] == 999) {
		p->kljucevi[2] = k;
		p->podStabla[3] = pm->desni;
		pm->desni->otac = p;
		p->indeksi[2] = 0;
		p->duz++;
		return;
	}
	if (k > p->kljucevi[1] && k < p->kljucevi[2] && p->kljucevi[2] != 999) {
		p->kljucevi[0] = p->kljucevi[1];
		p->kljucevi[1] = k;
		p->podStabla[0] = p->podStabla[1];
		p->podStabla[1] = p->podStabla[2];
		p->podStabla[2] = pm->desni;
		pm->desni->otac = p;
		p->indeksi[2] = 0;
		p->indeksi[1] = 1;
		p->indeksi[0] = 0;
		p->duz++;
		return;
	}
}

bool B::umetanje(int kljuc, int indek) {
	bool postoji = false;
	Elem* p = nadjiCvor(kljuc, postoji);
	if (postoji == true || koren == nullptr) return false;
	bool prenos = false;
	PomElem* pm = new PomElem;

	while (p != nullptr) {
		if (prenos == false) {
			if (!punCvor(p)) {
				dodavanjeBezPrenosa(p, kljuc, indek);
				p = nullptr;
			}
			else
				if (p == koren) {
					koren = new Elem(p->kap);
					int* pomNiz = new int[p->kap];
					unesiUpomNiz(p, pomNiz, kljuc);
					isprazniCvor(p);
					dodavanjeBezPrenosa(p, pomNiz[0]);
					dodavanjeBezPrenosa(p, pomNiz[1]);
					Elem* q = new Elem(p->kap);
					dodavanjeBezPrenosa(q, pomNiz[3]);
					dodavanjeBezPrenosa(koren, pomNiz[2]);
					koren->podStabla[1] = p;
					koren->podStabla[2] = q;
					p->otac = q->otac = koren;
					p = nullptr;
					delete[] pomNiz;
				}
				else {
					int* pomNiz = new int[p->kap];
					unesiUpomNiz(p, pomNiz, kljuc);
					isprazniCvor(p);
					dodavanjeBezPrenosa(p, pomNiz[0]);
					dodavanjeBezPrenosa(p, pomNiz[1]);	
					Elem* q = new Elem(p->kap);
					dodavanjeBezPrenosa(q, pomNiz[3]);
					pm->ind = 0;
					pm->kljuc = pomNiz[2];
					pm->desni = q;
					prenos = true;
					p = p->otac;
					delete[] pomNiz;
				}
		}
		else {
			if (!punCvor(p)) {
				dodavanjeSaPrenosom(p, pm);
				delete pm;
				p = nullptr;
			}
			else {
				if (p == koren) {
					koren = new Elem(p->kap);
					int* pomNiz = new int[p->kap];
					unesiUpomNiz(p, pomNiz, pm->kljuc);
					isprazniCvor(p);
					dodavanjeBezPrenosa(p, pomNiz[0]);
					dodavanjeBezPrenosa(p, pomNiz[1]);
					Elem* q = new Elem(p->kap);
					if (pomNiz[2] == pm->kljuc) {
						q->podStabla[1] = pm->desni; 
						pm->desni->otac = q;
						dodavanjeBezPrenosa(q, pomNiz[3]);
						q->podStabla[2] = p->podStabla[3];
						if (p->podStabla[3] != nullptr)
							p->podStabla[3]->otac = q;
						p->podStabla[3] = p->podStabla[2];
						p->podStabla[2] = p->podStabla[1];
						p->podStabla[1] = p->podStabla[0];
						p->podStabla[0] = nullptr;
					}
					else {
						dodavanjeBezPrenosa(q, pomNiz[3]);
						if (da_Li_se_Nalazi(p, pm)) {
							q->podStabla[1] = p->podStabla[2];
							if (p->podStabla[2] != nullptr)
								p->podStabla[2]->otac = q;
							q->podStabla[2] = p->podStabla[3];
							if (p->podStabla[3] != nullptr)
								p->podStabla[3]->otac = q;
							if (p->kljucevi[1] == pm->kljuc) {
								p->podStabla[3] = p->podStabla[1]; 
								p->podStabla[2] = pm->desni;
								p->podStabla[1] = p->podStabla[0];
								p->podStabla[0] = nullptr;
								pm->desni->otac = p;
							}
							else {
								p->podStabla[3] = pm->desni;
								p->podStabla[2] = p->podStabla[1];
								p->podStabla[1] = p->podStabla[0];
								p->podStabla[0] = nullptr;
								pm->desni->otac = p;
							}
						}
						else {
							q->podStabla[2] = pm->desni;
							q->podStabla[1] = p->podStabla[3];
							if (p->podStabla[3] != nullptr)
								p->podStabla[3]->otac = q;
							p->podStabla[3] = p->podStabla[2];
							p->podStabla[2] = p->podStabla[1];
							p->podStabla[1] = p->podStabla[0];
							p->podStabla[0] = nullptr;
							pm->desni->otac = q;
						}
					}
					koren->indeksi[1] = 1;
					koren->kljucevi[1] = pomNiz[2];
					koren->podStabla[1] = p;
					koren->podStabla[2] = q;
					koren->duz++;
					p->otac = q->otac = koren;
					p = nullptr;
					delete[] pomNiz;
					delete pm;
				}
				else {
					int* pomNiz = new int[p->kap];
					unesiUpomNiz(p, pomNiz, pm->kljuc);
					isprazniCvor(p);
					dodavanjeBezPrenosa(p, pomNiz[0]);
					dodavanjeBezPrenosa(p, pomNiz[1]);
					Elem* q = new Elem(p->kap);
					if (pomNiz[2] == pm->kljuc) {
						q->podStabla[1] = pm->desni;
						pm->desni->otac = q;
						dodavanjeBezPrenosa(q, pomNiz[3]);
						q->podStabla[2] = p->podStabla[3];
						if (p->podStabla[3] != nullptr)
							p->podStabla[3]->otac = q;
						p->podStabla[3] = p->podStabla[2];
						p->podStabla[2] = p->podStabla[1];
						p->podStabla[1] = p->podStabla[0];
						p->podStabla[0] = nullptr;
					}
					else {
						dodavanjeBezPrenosa(q, pomNiz[3]);
						if (da_Li_se_Nalazi(p, pm)) {
							q->podStabla[1] = p->podStabla[2];
							if (p->podStabla[2] != nullptr)
								p->podStabla[2]->otac = q;
							q->podStabla[2] = p->podStabla[3];
							if (p->podStabla[3] != nullptr)
								p->podStabla[3]->otac = q;
							if (p->kljucevi[1] == pm->kljuc) {
								p->podStabla[3] = p->podStabla[1]; 
								p->podStabla[2] = pm->desni;
								p->podStabla[1] = p->podStabla[0];
								p->podStabla[0] = nullptr;
								pm->desni->otac = p;
							}
							else {
								p->podStabla[3] = pm->desni;
								p->podStabla[2] = p->podStabla[1];
								p->podStabla[1] = p->podStabla[0];
								p->podStabla[0] = nullptr;
								pm->desni->otac = p;
							}
						}
						else {
							q->podStabla[2] = pm->desni;
							q->podStabla[1] = p->podStabla[3];
							if (p->podStabla[3] != nullptr)
								p->podStabla[3]->otac = q;
							p->podStabla[3] = p->podStabla[2];
							p->podStabla[2] = p->podStabla[1];
							p->podStabla[1] = p->podStabla[0];
							p->podStabla[0] = nullptr;
							pm->desni->otac = q;
						}
						pm->ind = 0;
						pm->kljuc = pomNiz[2];
						pm->desni = q;
						prenos = true;
						p = p->otac;
						delete[] pomNiz;
					}
				}
			}
		}
	}
	return true;
}

void B::pisi() const {
	if (koren == nullptr) return;
	Elem* p = koren;
	bool pom = true;
	int visina = visinaStabla();
	int privr1 = 1;
	int privr2 = 0;
	Red r;
	r += p->kljucevi[1];
	system("color 00");
	while (+r != 0) {
		p = nadjiCvor(--r, pom);
		if (privr1-- == 0) {
			privr1 = privr2 - 1;
			privr2 = 0;
			visina--; cout << endl;
		}
		cout << '|';
		cout << "\033[97;101m" << p->kljucevi[0] << "\033[0m" << '|';
		cout << p->kljucevi[1] << '|';
		cout << "\033[97;101m" << p->kljucevi[2] << "\033[0m" << '|';
		if (privr1 != 0)
			cout << setw(5 * visina) << setfill('*');
		for (int i = 0; i < p->kap; i++) {
			if (p->podStabla[i] != nullptr) {
				r += p->podStabla[i]->kljucevi[1];
				privr2++;
			}
		}
	}
}

int B::visinaStabla() const {
	int visina = 0;
	if (koren == nullptr) return visina;
	Elem* p = koren;
	while (p->podStabla[1] != nullptr) {
		visina++; p = p->podStabla[1];
	}
	return visina + 1;
}

void B::brisi() {
	if (koren == nullptr) return;
	Elem* p = koren;
	int* pomNiz = new int[brCvorovaSaPraznim()];
	int duz = 0;
	bool pom = true;
	int privr1 = 1;
	int privr2 = 0;
	Red r;
	bool prazan;
	r += p->kljucevi[1];
	while (+r != 0) {
		p = nadjiCvor(--r, pom);
		if (privr1-- == 0) {
			privr1 = privr2 - 1;
			privr2 = 0;
		}
		for (int i = 0; i < p->kap - 1; i++) pomNiz[duz++] = p->kljucevi[i];
		for (int i = 0; i < p->kap; i++) {
			if (p->podStabla[i] != nullptr) {
				r += p->podStabla[i]->kljucevi[1];
				privr2++;
			}
		}
	}
	for (int i = duz - 1; i >= 0; i--) {
		if (pomNiz[i] != 999) {
			p = nadjiCvor(pomNiz[i], pom);
			for (int j = 0; j < p->kap - 1; j++) {
				if (pomNiz[i] == p->kljucevi[j])
					p->kljucevi[j] = 999;
			}
			prazan = true;
			for (int j = 0; j < p->kap - 1; j++) {
				if (p->kljucevi[j] != 999)
					prazan = false;
			}
			if (prazan == true)  delete p;
		}
	}
	koren = nullptr;
}

int B::brCvorovaSaPraznim() const {
	int brKljuceva = 0;
	if (koren == nullptr) return 0;
	Elem* p = koren;
	bool pom = true;
	int privr1 = 1;
	int privr2 = 0;
	Red r;
	r += p->kljucevi[1];
	while (+r != 0) {
		p = nadjiCvor(--r, pom);
		if (privr1-- == 0) {
			privr1 = privr2 - 1;
			privr2 = 0;
		}
		for (int i = 0; i < p->kap - 1; i++) {
			brKljuceva++;
		}
		for (int i = 0; i < p->kap; i++) {
			if (p->podStabla[i] != nullptr) {
				r += p->podStabla[i]->kljucevi[1];
				privr2++;
			}
		}
	}
	return brKljuceva;
}

void B::ispisi_stablo(Elem* k, int nivo, int* p, int i) {
	if (k != nullptr) {
		if (*p == k->kljucevi[1])
			ispisi_stablo(k, nivo + 1, &(k->kljucevi[2]), i + 1);
		else
			if (k->podStabla[i + 1] != nullptr)
				ispisi_stablo(k->podStabla[i + 1], nivo + 1, &(k->podStabla[i + 1]->kljucevi[1]), 1);
			else
			    ispisi_stablo(k->podStabla[i + 1], nivo + 1, &(k->kljucevi[1]), 1);
		system("color 00");
		if (k->indeksi[i] == 0 || k->indeksi[i] == -1)
			cout << setw(4 * nivo) << "" << '|' << "\033[97;101m" << k->kljucevi[i] << "\033[0m" << '|' << endl;
		else
			cout << setw(4 * nivo) << "" << '|' << k->kljucevi[i] << '|' << endl;

		if (*p == k->kljucevi[1]) 
			ispisi_stablo(k, nivo + 1, &(k->kljucevi[0]), i - 1);
		else 
			if (k->podStabla[i] != nullptr)
			   ispisi_stablo(k->podStabla[i], nivo + 1, &(k->podStabla[i]->kljucevi[1]), 1);
			else
			   ispisi_stablo(k->podStabla[i], nivo + 1, &(k->kljucevi[1]), 1);
		}
}