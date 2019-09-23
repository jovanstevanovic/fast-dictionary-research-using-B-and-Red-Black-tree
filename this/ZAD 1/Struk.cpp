#pragma once
#include "Klasa.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Struk {
	string* niz;
	int kap, duz;
	void kopiraj(const Struk& s);
	void premesti(Struk& s) { niz = s.niz; duz = s.duz; kap = s.kap; s.niz = nullptr; }
public:
	explicit Struk(int k = 30) { niz = new string[kap = k]; duz = 0; }
	Struk(const Struk& s) { kopiraj(s); }
	Struk(Struk&& s) { premesti(s); }
	~Struk() { brisi(); }
	Struk& operator= (const Struk& s) { 
		if (this != &s) {
			brisi(); kopiraj(s);
		}
		return *this;
	}
	Struk& operator= (Struk&& s)  {
		if (this != &s) {
			brisi(); premesti(s);
		}
		return *this;
	}
	bool pun () const { return kap == duz; }
	bool prazan() const { return duz == 0; }
	Struk& dodaj(const string& s);
	friend ostream& operator<< (ostream& it, const Struk& s) {
		it << "\n--------------------- STRUKTURA PODATAKA ---------------------" << endl;
		for (int i = 0; i < s.duz; i++) it << s.niz[i] << endl;
		it << "--------------------------------------------------------------" << endl;
		return it;
	}
	friend istream& operator>> (istream& ut, Struk& s);
	bool citajIzDatoteke();
	bool brisanje(const string s);
	void brisi() { delete[] niz; niz = nullptr; kap = duz = 0; }
	bool postoji(const string& s) const;
	bool pretrazi(const string& s, int ind, bool& jedina) const;
	void formirajRedakIndeks(B& b) const;
	void pisiOdr(int i) const;
	Struk& dodajSaIndeksom(const string& s, B& b);
};

Struk& Struk::dodajSaIndeksom(const string& s, B& b) {
	int i = 0;
	for (i = 0; i < duz; i++)
		if (s.size() == niz[i].size() && s < niz[i] || s.size() < niz[i].size())
			break;
	if (pun()) {
		Struk privr(kap);
		privr = *this;
		brisi();
		duz = privr.duz;
		niz = new string[kap = privr.kap + 10];
		for (int j = 0; j < duz; j++) niz[j] = privr.niz[j];
	}
	Struk privr(kap);
	privr = *this;
	brisi();
	duz = privr.duz;
	if (duz == 0) kap = privr.kap;
	else kap = privr.duz + 1;
	niz = new string[kap];
	for (int j = 0; j < duz; j++) niz[j] = privr.niz[j];
	for (int j = duz; j > i; j--) niz[j] = niz[j - 1];
	niz[i] = s;
	b.umetanje(s.size(), i);
	duz++;
	return *this;
}

void Struk::pisiOdr(int ind) const {
	int pr = niz[ind].size();
	while (niz[ind].size() == pr) cout << niz[ind++] << endl;
}

void Struk::formirajRedakIndeks(B& b) const {
	int pom = 0;
	for (int i = 0; i < duz; i++) {
		if (pom != niz[i].size()) {
			b.umetanje(niz[i].size(), i);
			pom = niz[i].size();
		}
	}
}

bool Struk::pretrazi(const string& s, int ind, bool& jedina) const {
	for (int i = ind; i < duz; i++) {
		if (niz[i] == s && niz[i].size() == s.size()) { 
			if (niz[i + 1].size() != s.size())
				jedina = true;
			    return true;
		}
		if (niz[i].size() > s.size()) return false;
	}
	return false;
}

bool Struk::postoji(const string& s) const {
	for (int i = 0; i < duz; i++)
		if (niz[i] == s) return true;
	return false;
}

void Struk::kopiraj(const Struk& s) {
	duz = s.duz;
	niz = new string[kap = s.kap];
	for (int i = 0; i < duz; i++) niz[i] = s.niz[i];
}

istream& operator>> (istream& ut, Struk& s) {
	int br;
	string nova;
	cout << "\nKoliko inicijalno niski zelite da procitate? "; ut >> br;
	for (int i = 0; i < br; i++) {
		cout << i + 1 << ". niska? "; ut >> nova;
		s.dodaj(nova);
	}
	cout << "Ucitavanje je uspesno izvrseno!\n";
	return ut;
}

bool Struk::citajIzDatoteke() {
	ifstream keyFile;
	string nova;
	keyFile.open("Primeri1.txt");
	if (!keyFile.is_open()) {
		cout << "Ucitavanje datoteke nije uspelo!" << endl;
		return false;
	}
	while (keyFile >> nova) 
			dodaj(nova);
	cout << "\nDatoteka je uspesno ucitana!" << endl;
	return true;
}

Struk& Struk::dodaj(const string& s) {
	int i = 0;
	for (i = 0; i < duz; i++)
		if (s.size() == niz[i].size() && s < niz[i] || s.size() < niz[i].size())
			break;
	if (pun()) {
		Struk privr(kap);
		privr = *this;
		brisi();
		duz = privr.duz;
		niz = new string[kap = privr.kap + 100];
		for (int j = 0; j < duz; j++) niz[j] = privr.niz[j];
	}
     Struk privr(kap);
     privr = *this;
     brisi();
     duz = privr.duz;
	 if (duz == 0) kap = privr.kap;
	 else kap = privr.duz + 1;
     niz = new string[kap];
     for (int j = 0; j < duz; j++) niz[j] = privr.niz[j];
	 for (int j = duz; j > i; j--) niz[j] = niz[j - 1];
	 niz[i] = s;
	 duz++;
	 return *this;
}

bool Struk::brisanje(const string s) {
	int i = 0;
	for (i = 0; i < duz; i++)
		if (s == niz[i])
			break;
	if (i == duz) return false;
	for (int j = i; j < duz - 1; j++) niz[j] = niz[j + 1];
	Struk privr(kap - 1);
	duz--; kap--;
	privr = *this;
	brisi();
	duz = privr.duz;
	niz = new string[kap = privr.kap];
	for (int i = 0; i < duz; i++) niz[i] = privr.niz[i];
	return true;
}