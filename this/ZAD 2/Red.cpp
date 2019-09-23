#pragma once
#pragma once
#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

class Red {
	struct Elem {
		int pod;
		Elem* sled;
		Elem(int p, Elem* s = 0) { pod = p; sled = s; }
	};
	Elem *prvi, *posl;
	int duz;
	void kopiraj(const Red& r);
	void brisi();
public:
	Red() { prvi = posl = 0; duz = 0; }
	Red(int a) { prvi = posl = new Elem(a); duz = 1; }
	Red(const Red& r) { kopiraj(r); }
	~Red() { brisi(); }
	Red& operator= (const Red& r) {
		if (this != &r) { brisi(); kopiraj(r); }
		return *this;
	}
	int vodeci() const {
		if (!prvi) exit(1);
		return prvi->pod;
	}
	int operator+() const { return duz; }
	Red& operator+= (const Red& r);
	Red operator+ (const Red& r) const;
	int operator-- ();
	int operator- () const {
		return duz ? prvi->pod : 0;
	}
	Red operator- (int k) const;
	Red& operator-= (int k) {
		return *this = *this - k;
	}
	Red& operator~ () {
		brisi(); return *this;
	}

};

void Red::kopiraj(const Red& r) {
	prvi = posl = 0;
	duz = r.duz;
	for (Elem* tek = r.prvi; tek; tek = tek->sled)
		posl = (!prvi ? prvi : posl->sled) = new Elem(tek->pod);
}

void Red::brisi() {
	while (prvi) { Elem* stari = prvi; prvi = prvi->sled; delete stari; }
	posl = 0; duz = 0;
}

Red Red::operator+ (const Red& r) const {
	Red s(*this); s += r; return s;
}

int Red::operator-- () {
	if (duz == 0) return 0;
	int pod = prvi->pod;
	Elem* stari = prvi;
	if ((prvi = prvi->sled) == 0) posl = 0;
	delete stari;
	duz--;
	return pod;
}

Red Red::operator- (int k) const {
	Red r;
	for (Elem* tek = prvi; tek; tek = tek->sled) if (tek->pod != k) r += tek->pod;
	return r;
}

Red& Red::operator+= (const Red& r) {
	Red s(r);
	(!prvi ? prvi : posl->sled) = s.prvi;
	posl = s.posl; duz += s.duz;
	s.prvi = s.posl = 0;
	s.duz = 0;
	return *this;
}



