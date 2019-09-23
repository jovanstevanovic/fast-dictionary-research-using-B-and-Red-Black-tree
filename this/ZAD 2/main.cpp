#include <cstdlib>
#include <string>
#include "KlasaB.h"
#include "KlasaRed.h"
using namespace std;

int main() {
	    B b;
	    int kljuc; bool postoji = false;
		int izbor; bool kraj = false;
		while (!kraj) {
			cout << "\n---------------------\n"
		             << "CRVENO-CRNA STABLA"
			     << "\n---------------------\n" << endl;
			cout << "1. Stvaranje praznog B-stabla\n"
				 << "2. Umetanje kljuca u RB stablo\n"
				 << "3. Pretrazivanje na zadati kljuc\n"
				 << "4. Ispis stabla\n"
				 << "5. Brisanje stabla\n"
				 << "6. Kraj rada!\n" << endl; 
			cout << "Izbor? "; cin >> izbor;

			switch (izbor) {
			  case 1:
				  b.formirajKoren(4);
				  cout << "\nB stablo je formirano!" << endl;
				  break;
			  case 2:
				  postoji = false;
				  cout << "\nKljuc? "; cin >> kljuc;
				  b.nadjiCvor(kljuc, postoji);
				  if (postoji == true) cout << "Kljuc " << kljuc << " postoji u stablu!" << endl;
				  else {
					  postoji = true;
					  postoji = b.umetanje(kljuc);
					  if (postoji)
					     cout << "Kljuc " << kljuc << " je uspesno dodat!" << endl;
					  else 
						 cout << "Stablo jos nije formirano!" << endl;
				  }
				  break;
			  case 3:
				  postoji = false;
				  cout << "\nKljuc za pretrazivanje? "; cin >> kljuc;
				  b.nadjiCvor(kljuc, postoji);
				  if (postoji == true) cout << "Kljuc " << kljuc << " postoji u stablu!" << endl;
				  else cout << "Kljuc " << kljuc << " ne postoji u stablu!" << endl;
				  break;
			  case 4:
				  cout << "\n--------------------- CRVENO-CRNO STABLO ---------------------" << endl;
				  if (b.dohvKoren() != nullptr)
				  b.ispisi_stablo(b.dohvKoren(), 0, &(b.dohvKoren()->kljucevi[1]), 1);
				  cout << "\n--------------------------------------------------------------" << endl;
				  break;
			  case 5:
				  b.brisi();
				  cout << "\nStablo je obrisano!" << endl;
				  break;
			  case 6:
				  kraj = true;
				  cout << "\n **** Izabrana opcija za kraj rada! **** \n" << endl;
				  break;
			  default:
				  cout << "\n **** Nekorektan unos! Pokusajte ponovo! **** \n";
				  break;
			}
		}
}
