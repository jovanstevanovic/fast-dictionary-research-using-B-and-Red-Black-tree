#pragma once
#include <iostream>
#include <cmath>
#include "Klasa1.h"
using namespace std;

class B {
	struct Elem {
		int* kljucevi;
		int* indeksi;
		Elem** podStabla;
		Elem* otac;
		int kap, duz;
		explicit Elem(int k = 3, Elem* ot = nullptr) : otac(ot) {
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
	B (int k = 3) {
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
	void formirajKoren(int k) { koren = new Elem(k); }
	bool praznoStablo() const { return koren == nullptr; }
	static bool punCvor(Elem* pok) { return pok->duz == pok->kap - 1; }
	static bool prazanCvor(Elem* pok) { return pok->duz == 0; }
	static bool imaMin(Elem* pok) { return pok->duz - 1 >= ceil(((double)pok->kap) / 2) - 1; }
	static bool Min(Elem* pok) { return pok->duz >= ceil(((double)pok->kap) / 2) - 1; }
	Elem* nadjiCvor(int k, bool& postoji) const;
	void dodavanjeBezPrenosa(Elem* p, int k, int ind = -1);
	void dodavanjeSaPrenosom(Elem* p, PomElem* pm);
	void unesiUpomNiz(Elem* p, int* pomNiz, int k);
	void isprazniCvor(Elem* p);
	void unesiUCvor(Elem* p, int* pomNiz, int d, int g);
	void azuritajPok(Elem* p, Elem* q, int ind);
	bool umetanje(int kljuc, int indek = -1);
	void pisi() const;
	void azurirajInd(int ind, int pomeraj);
	int visinaStabla() const;
	void brisi();
	int brCvorova() const;
	int brCvorovaSaPraznim() const;
	void unesiUpomNizInd(Elem* p, int* pomNiz, int k);
	void unesiUCvorInd(Elem* p, int* pomNiz, int d, int g);
	bool brisanje(int kljuc);
	void izbrisiKljuc(Elem* p, int kljuc);
	Elem* nadjiLBrata(Elem* p, Elem* q) const;
	Elem* nadjiDBrata(Elem* p, Elem* q) const;
	int razdvojniKljucL(Elem* p, Elem* q, Elem* z) const;
	int razdvojniKljucD(Elem* p, Elem* q, Elem* z) const;
	bool da_Li_se_Nalazi(Elem* p, PomElem* q);
	Elem* sledbenik(Elem* p) const;
};

B::Elem* B::sledbenik(Elem* p) const {
	
	while (p->podStabla[0] != nullptr) p = p->podStabla[0];
	return p;

}

bool B::da_Li_se_Nalazi(Elem* p, PomElem* q) {
	bool nalazi = false;
	for (int i = 0; i < p->kap - 1; i++)
		if (p->kljucevi[i] == q->kljuc)
			nalazi = true;
	return nalazi;
}

B::Elem* B::nadjiCvor(int k, bool& postoji) const {
	Elem* pok = koren;
	while (pok != nullptr) {
		for (int i = 0; i < pok->kap - 1; i++)
			if (pok->kljucevi[i] == k) {
				postoji = true;
				return pok;
			}
			else {
				if (pok->kljucevi[0] > k && cvorJeList(pok))
					return pok;
				if (pok->kljucevi[0] > k) {
					pok = pok->podStabla[0];
					i = -1;
					continue;
				}
				if (pok->kljucevi[pok->kap - 2] < k && cvorJeList(pok))
					return pok;
				if (pok->kljucevi[pok->kap - 2] < k) {
					pok = pok->podStabla[pok->kap - 1];
					i = -1;
					continue;
				}
				if (pok->kljucevi[i] > k && cvorJeList(pok))
					return pok;
				if (pok->kljucevi[i] > k) {
					pok = pok->podStabla[i];
					i = -1;
				}
			}

	}
	return nullptr;
}

void B::dodavanjeBezPrenosa(Elem* p, int k, int ind) {
	p->indeksi[p->duz] = ind;
	p->kljucevi[p->duz++] = k;
	for (int i = 0; i < p->kap - 1; i++)
		for (int j = i + 1; j < p->kap - 1; j++)
			if (p->kljucevi[i] > p->kljucevi[j]) {
				int privr = p->kljucevi[i];
				p->kljucevi[i] = p->kljucevi[j];
				p->kljucevi[j] = privr;
				int privr1 = p->indeksi[i];
				p->indeksi[i] = p->indeksi[j];
				p->indeksi[j] = privr1;
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

void B::unesiUpomNizInd(Elem* p, int* pomNiz, int k) {
	for (int i = 0; i < p->kap - 1; i++) pomNiz[i] = p->indeksi[i];
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

void B::unesiUCvor(Elem* p, int* pomNiz, int d, int g) {
	for (int i = d; i < g; i++) p->kljucevi[p->duz++] = pomNiz[i]; 
	
}

void B::unesiUCvorInd(Elem* p, int* pomNiz, int d, int g) {
	for (int i = d; i < g; i++) p->indeksi[p->duz++] = pomNiz[i];
}

void B::dodavanjeSaPrenosom(Elem* p, PomElem* pm) {
	int i;
	bool nadjen = false;
	for (int j = 0; j < p->kap - 1; j++) {
		if (pm->kljuc == p->kljucevi[j]) nadjen = true;
	}
	for (i = 0; i < p->kap - 1; ) {
		if (pm->kljuc > p->kljucevi[i]) i++;
		else break;
	}
	for (int j = p->kap - 1; j > i + 1; j--) p->podStabla[j] = p->podStabla[j - 1];
	if (!nadjen) {
		for (int j = p->kap - 2; j > i; j--) p->kljucevi[j] = p->kljucevi[j - 1];
		for (int j = p->kap - 2; j > i; j--) p->indeksi[j] = p->indeksi[j - 1];
	}
	p->kljucevi[i] = pm->kljuc;
	p->indeksi[i] = pm->ind;
	p->podStabla[i + 1] = pm->desni;
	pm->desni->otac = p;
	if (!nadjen)
		p->duz++;
}

void B::azuritajPok(Elem* p, Elem* q, int ind) {
	for (int i = 0; i < p->kap; i++)
		if (p->kljucevi[i] == 999 && p->podStabla[i + 1] != nullptr) {
			p->podStabla[i + 1]->otac = q;
			q->podStabla[ind++] = p->podStabla[i + 1];
			p->podStabla[i + 1] = nullptr;
		}
}

bool B::umetanje(int kljuc, int indek) {
	bool postoji = false;
	Elem* p = nadjiCvor(kljuc, postoji);
	if (postoji == true) return false;
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
					int* pomNizInd = new int[p->kap];
					unesiUpomNiz(p, pomNiz, kljuc);
					unesiUpomNizInd(p, pomNizInd, indek);
					isprazniCvor(p);
					unesiUCvor(p, pomNiz, 0, p->kap / 2);
					p->duz = 0;
					unesiUCvorInd(p, pomNizInd, 0, p->kap / 2);
					Elem* q = new Elem(p->kap);
					unesiUCvor(q, pomNiz, p->kap / 2 + 1, p->kap);
					q->duz = 0;
					unesiUCvorInd(q, pomNizInd, p->kap / 2 + 1, p->kap);
					int ind = p->kap / 2;
					koren->kljucevi[koren->duz] = pomNiz[ind];
					koren->indeksi[koren->duz++] = pomNizInd[ind];
					koren->podStabla[0] = p;
					koren->podStabla[1] = q;
					p->otac = q->otac = koren;
					p = nullptr;
					delete[] pomNiz;
					delete[] pomNizInd;
					delete pm;
				}
				else {
					int* pomNiz = new int[p->kap];
					int* pomNizInd = new int[p->kap];
					unesiUpomNiz(p, pomNiz, kljuc);
					unesiUpomNizInd(p, pomNizInd, indek);
					isprazniCvor(p);
					unesiUCvor(p, pomNiz, 0, p->kap / 2);
					p->duz = 0;
					unesiUCvorInd(p, pomNizInd, 0, p->kap / 2);
					Elem* q = new Elem(p->kap);
					unesiUCvorInd(q, pomNizInd, p->kap / 2 + 1, p->kap);
					q->duz = 0;
					unesiUCvor(q, pomNiz, p->kap / 2 + 1, p->kap);
					int ind = p->kap / 2;
					pm->ind = pomNizInd[ind];
					pm->kljuc = pomNiz[ind];
					pm->desni = q;
					prenos = true;
					p = p->otac;
					delete[] pomNiz;
					delete[] pomNizInd;
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
					int* pomNizInd = new int[p->kap];
					unesiUpomNiz(p, pomNiz, pm->kljuc);
					unesiUpomNizInd(p, pomNizInd, pm->ind);
					isprazniCvor(p);
					unesiUCvor(p, pomNiz, 0, p->kap / 2);
					p->duz = 0;
					unesiUCvorInd(p, pomNizInd, 0, p->kap / 2);
					Elem* q = new Elem(p->kap);
					int ind = p->kap / 2;
					if (pomNiz[ind] == pm->kljuc) {
						q->podStabla[0] = pm->desni;
						pm->desni->otac = q;
						unesiUCvor(q, pomNiz, p->kap / 2 + 1, p->kap);
						q->duz = 0;
						unesiUCvorInd(q, pomNizInd, p->kap / 2 + 1, p->kap);
						azuritajPok(p, q, 1);
					}
					else {
						unesiUCvor(q, pomNiz, p->kap / 2 + 1, p->kap);
						q->duz = 0;
						unesiUCvorInd(q, pomNizInd, p->kap / 2 + 1, p->kap);
						int j = 0;
						if (da_Li_se_Nalazi(p, pm)) {
							for (int i = 0; i < p->kap; i++) {
								if (p->kljucevi[i] == 999 && p->podStabla[i + 1] != nullptr || p->kljucevi[i] == p->kljucevi[p->duz - 1] && p->podStabla[i + 1] != nullptr) {
									p->podStabla[i + 1]->otac = q;
									q->podStabla[j++] = p->podStabla[i + 1];
									p->podStabla[i + 1] = nullptr;
								}
							}
							dodavanjeSaPrenosom(p, pm);
						}
						else {
							azuritajPok(p, q, 0);
							dodavanjeSaPrenosom(q, pm);
						}
					}
					koren->indeksi[koren->duz] = pomNizInd[ind];
					koren->kljucevi[koren->duz++] = pomNiz[ind];
					koren->podStabla[0] = p;
					koren->podStabla[1] = q;
					p->otac = q->otac = koren;
					p = nullptr;
					delete[] pomNiz;
					delete pm;
				}
				else {
					int* pomNiz = new int[p->kap];
					int* pomNizInd = new int[p->kap];
					unesiUpomNiz(p, pomNiz, pm->kljuc);
					unesiUpomNizInd(p, pomNizInd, pm->ind);
					isprazniCvor(p);
					unesiUCvor(p, pomNiz, 0, p->kap / 2);
					p->duz = 0;
					unesiUCvorInd(p, pomNizInd, 0, p->kap / 2);
					Elem* q = new Elem(p->kap);
					int ind = p->kap / 2;
					if (pomNiz[ind] == pm->kljuc) {
						q->podStabla[0] = pm->desni;
						pm->desni->otac = q;
						unesiUCvor(q, pomNiz, p->kap / 2 + 1, p->kap);
						q->duz = 0;
						unesiUCvorInd(q, pomNizInd, p->kap / 2 + 1, p->kap);
						azuritajPok(p, q, 1);
					}
					else {
						int j = 0;
						unesiUCvor(q, pomNiz, p->kap / 2 + 1, p->kap);
						q->duz = 0;
						unesiUCvorInd(q, pomNizInd, p->kap / 2 + 1, p->kap);
						if (da_Li_se_Nalazi(p, pm)) {
							for (int i = 0; i < p->kap; i++) {
								if (p->kljucevi[i] == 999 && p->podStabla[i + 1] != nullptr || p->kljucevi[i] == p->kljucevi[p->duz - 1] && p->podStabla[i + 1] != nullptr) {
									p->podStabla[i + 1]->otac = q;
									q->podStabla[j++] = p->podStabla[i + 1];
									p->podStabla[i + 1] = nullptr;
								}
							}
							dodavanjeSaPrenosom(p, pm);
						}
						else {
							azuritajPok(p, q, 0);
							dodavanjeSaPrenosom(q, pm);
						}
						pm->ind = pomNizInd[ind];
						pm->kljuc = pomNiz[ind];
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
	r += p->kljucevi[0];
	while (+r != 0) {
		p = nadjiCvor(--r, pom);
		if (privr1-- == 0) {
			privr1 = privr2 - 1;
			privr2 = 0;
			visina--; cout << endl;
		}
		cout << '|';
		for (int i = 0; i < p->kap - 1; i++) cout << p->kljucevi[i] << '|';
		if (privr1 != 0)
		   cout << setw(5 * visina) << setfill('*');
		for (int i = 0; i < p->kap; i++) {
			if (p->podStabla[i] != nullptr) {
				r += p->podStabla[i]->kljucevi[0];
				privr2++;
			}
		}
	}
}

void B::azurirajInd(int ind, int pomeraj) {
	if (koren == nullptr) return;
	Elem* p = koren;
	bool pom = true;
	int privr1 = 1;
	int privr2 = 0;
	Red r;
	r += p->kljucevi[0];
	while (+r != 0) {
		p = nadjiCvor(--r, pom);
		if (privr1-- == 0) {
			privr1 = privr2 - 1;
			privr2 = 0;
		}
		for (int i = 0; i < p->kap - 1; i++)
			if (p->kljucevi[i] > ind && p->kljucevi[i] != 999)
				p->indeksi[i] += pomeraj;
		for (int i = 0; i < p->kap; i++) {
			if (p->podStabla[i] != nullptr) {
				r += p->podStabla[i]->kljucevi[0];
				privr2++;
			}
		}
	}
}

int B::visinaStabla() const {
	int visina = 0;
	if (koren == nullptr) return visina;
	Elem* p = koren;
	while (p->podStabla[0] != nullptr) {
		visina++; p = p->podStabla[0];
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
	r += p->kljucevi[0];
	while (+r != 0) {
		p = nadjiCvor(--r, pom);
		if (privr1-- == 0) {
			privr1 = privr2 - 1;
			privr2 = 0;
		}
		for (int i = 0; i < p->kap - 1; i++) pomNiz[duz++] = p->kljucevi[i];
		for (int i = 0; i < p->kap; i++) {
			if (p->podStabla[i] != nullptr) {
				r += p->podStabla[i]->kljucevi[0];
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

int B::brCvorova() const {
	int brKljuceva = 0;
	if (koren == nullptr) return 0;
	Elem* p = koren;
	bool pom = true;
	int privr1 = 1;
	int privr2 = 0;
	Red r;
	r += p->kljucevi[0];
	while (+r != 0) {
		p = nadjiCvor(--r, pom);
		if (privr1-- == 0) {
			privr1 = privr2 - 1;
			privr2 = 0;
		}
		for (int i = 0; i < p->kap - 1; i++) { 
			if (p->kljucevi[i] != 999) 
				brKljuceva++; 
		}
		for (int i = 0; i < p->kap; i++) {
			if (p->podStabla[i] != nullptr) {
				r += p->podStabla[i]->kljucevi[0];
				privr2++;
			}
		}
	}
	return brKljuceva;
}

int B::brCvorovaSaPraznim() const {
	int brKljuceva = 0;
	if (koren == nullptr) return 0;
	Elem* p = koren;
	bool pom = true;
	int privr1 = 1;
	int privr2 = 0;
	Red r;
	r += p->kljucevi[0];
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
				r += p->podStabla[i]->kljucevi[0];
				privr2++;
			}
		}
	}
	return brKljuceva;
}

void B::izbrisiKljuc(Elem* p, int kljuc) {
	int i;
	for (i = 0; i < p->kap - 1; i++)
		if (kljuc == p->kljucevi[i])
			break;
	for (int j = i; j < p->kap - 2; j++) {
		p->kljucevi[j] = p->kljucevi[j + 1];
		p->indeksi[j] = p->indeksi[j + 1];
		 p->podStabla[j] = p->podStabla[j + 1];
	}
	p->podStabla[p->kap - 2] = p->podStabla[p->kap - 1];
	p->podStabla[p->kap - 1] = nullptr;
	p->kljucevi[p->kap - 2] = 999;
	p->indeksi[p->kap - 2] = -1;
	p->duz--;
}

B::Elem* B::nadjiDBrata(Elem* p, Elem* q) const {
	if (q == koren) return nullptr;
	int i;
	for (i = 0; i < p->kap; i++) if (p->podStabla[i] == q) break;
	if (i == p->duz) return nullptr;
	return p->podStabla[i + 1];
}

B::Elem* B::nadjiLBrata(Elem* p, Elem* q) const {
	if (q == koren) return nullptr;
	int i;
	for (i = 0; i < p->kap - 1; i++) if (p->podStabla[i] == q) break;
	if (i == 0) return nullptr;
	return p->podStabla[i - 1];
}

int B::razdvojniKljucL(Elem* p, Elem* q, Elem* z) const {
	int i;
	for (i = 0; i < z->kap - 1; i++)
		if (z->podStabla[i] == q && z->podStabla[i + 1] == p)
			break;
	return i;
}

int B::razdvojniKljucD(Elem* p, Elem* q, Elem* z) const {
	int i;
	for (i = 0; i < z->kap - 1; i++)
		if (z->podStabla[i] == p && z->podStabla[i + 1] == q)
			break;
	return i;
}

bool B::brisanje(int kljuc) {
	bool postoji = false, prenos = false;
	Elem* p = nadjiCvor(kljuc, postoji);
	if (postoji == false) return false;

	if (!cvorJeList(p)) {
		int i;
		for (i = 0; i < p->kap - 1; i++)
			if (kljuc == p->kljucevi[i])
				break;
		Elem* q = sledbenik(p->podStabla[i + 1]);
		int privr = p->kljucevi[i];
		p->kljucevi[i] = q->kljucevi[0];
		q->kljucevi[0] = privr;
		p = q;
	}
	izbrisiKljuc(p, kljuc);
	while (p != nullptr) {
		if (Min(p)) {
			p = nullptr;
		}
		else {
			Elem* q = nadjiDBrata(p->otac, p);
			if (q != nullptr && imaMin(q)) {
				int indeks = razdvojniKljucD(p, q, p->otac);
				p->kljucevi[p->duz] = p->otac->kljucevi[indeks];
				p->indeksi[p->duz++] = p->otac->indeksi[indeks];
				p->podStabla[p->duz] = q->podStabla[0];
				if (q->podStabla[0] != nullptr)
				    q->podStabla[0]->otac = p;
				p->otac->kljucevi[indeks] = q->kljucevi[0];
				p->otac->indeksi[indeks] = q->indeksi[0];
				izbrisiKljuc(q, q->kljucevi[0]);
				p = nullptr;

			}
			else {
				q = nadjiLBrata(p->otac, p);
				if (q != nullptr && imaMin(q)) {
					int indeks = razdvojniKljucL(p, q, p->otac);
					for (int j = p->kap - 1, i = 0; j > i; j--) p->podStabla[j] = p->podStabla[j - 1];
					for (int j = p->kap - 2, i = 0; j > i; j--) p->kljucevi[j] = p->kljucevi[j - 1];
					for (int j = p->kap - 2, i = 0; j > i; j--) p->indeksi[j] = p->indeksi[j - 1];
					p->kljucevi[0] = p->otac->kljucevi[indeks];
					p->indeksi[0] = p->otac->indeksi[indeks];
					p->podStabla[0] = q->podStabla[q->duz];
					if (q->podStabla[q->duz] != nullptr)
					    q->podStabla[q->duz]->otac = p;
					p->duz++;
					p->otac->kljucevi[indeks] = q->kljucevi[q->duz - 1];
					p->otac->indeksi[indeks] = q->indeksi[q->duz - 1];
					q->podStabla[q->duz] = nullptr;
					q->kljucevi[q->duz - 1] = 999;
					q->indeksi[q->duz - 1] = -1;
					q->duz--;
					p = nullptr;
				}
				else {
					q = nadjiDBrata(p->otac, p);
					if (q != nullptr) {
						int indeks = razdvojniKljucD(p, q, p->otac);
						p->kljucevi[p->duz] = p->otac->kljucevi[indeks];
						p->indeksi[p->duz++] = p->otac->indeksi[indeks];
						for (int i = 0; i < q->duz; i++) {
							p->podStabla[p->duz] = q->podStabla[i];
							if (q->podStabla[i] != nullptr)
							    q->podStabla[i]->otac = p;
							p->kljucevi[p->duz] = q->kljucevi[i];
							p->indeksi[p->duz++] = q->indeksi[i];
						}
						p->podStabla[p->duz] = q->podStabla[q->duz];
						if (q->podStabla[q->duz] != nullptr)
						    q->podStabla[q->duz]->otac = p;
						delete q;
						q = nullptr;
						p->otac->podStabla[indeks + 1] = nullptr;
						izbrisiKljuc(p->otac, p->otac->kljucevi[indeks]);
						p->otac->podStabla[indeks] = p;
						p = p->otac;
					}
					else {
						q = nadjiLBrata(p->otac, p);
						if (q != nullptr) {
							int indeks = razdvojniKljucL(p, q, p->otac);
							q->kljucevi[q->duz] = q->otac->kljucevi[indeks];
							q->indeksi[q->duz++] = q->otac->indeksi[indeks];
							for (int i = 0; i < p->duz; i++) {
								q->podStabla[q->duz] = p->podStabla[i];
								if(p->podStabla[i] != nullptr)
								   p->podStabla[i]->otac = q;
								q->kljucevi[q->duz] = p->kljucevi[i];
								q->indeksi[q->duz++] = p->indeksi[i];
							}
							q->podStabla[q->duz] = p->podStabla[p->duz];
							if(p->podStabla[p->duz] != nullptr)
							   p->podStabla[p->duz]->otac = q;
							delete p;
							p = nullptr;
							q->otac->podStabla[indeks + 1] = nullptr;
							izbrisiKljuc(q->otac, q->otac->kljucevi[indeks]);
							q->otac->podStabla[indeks] = q;
							p = q;
							p = p->otac;
						}
						else {
							if (p == koren && prazanCvor(p)) {
								koren = koren->podStabla[0];
								delete p;
								p = nullptr;
							}
							if (p == koren) p = nullptr;
						}
					}
				}

			}

		}
	}
	return true;
}
