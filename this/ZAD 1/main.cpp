#include "Klasa1.h"
#include "Klasa.h"
#include "KlasaStruktura.h"

int main() {
	Struk s, privr; string nova; int m;
	int izbor; bool kraj = false;
	int kljuc; bool postoji = false, jedina = false;
	int* niz1, *niz2;
	B b;
	while (!kraj) {
		cout << "\n----------------------------";
		cout << "\nSTABLA OPSTEG PRETRAZIVANJA" << endl;
		cout << "----------------------------" << '\n' << endl;
		cout << "Struktura podataka:\n"
			<< "       1. Stvaranje citanjem sa standardnog ulaza\n"
			<< "       2. Stvaranje citanjem iz datoteke\n"
			<< "       3. Umetanje niske\n"
			<< "       4. Brisanje niske\n"
			<< "       5. Unistavanje strukture podataka\n"
			<< "       6. Ispisivanje na glavni izlaz\n"
			<< "Redak ideks(B-stablo):\n"
			<< "       7. Stvaranje praznog stabla zadate velicine\n"
			<< "       8. Brisanje stabla\n"
			<< "       9. Odredjivanje visine stabla\n"
			<< "      10. Odredjivanje broja kljuceva u stablu!\n"
			<< "      11. Pronalazenje kljuca u stablu\n"
			<< "      12. Ispisivanje stabla\n"
			<< "Dinamicka manipulacija retkim indeksom:\n"
			<< "      13. Formiranje retkog indeksa koriscenjem strukture podataka\n"
			<< "      14. Umetanje kljuca u stablo\n"
			<< "      15. Brisanje kljuca iz stabla\n"
			<< "Dinamicka manipulacija strukturom podataka uz koriscenje retkog indeksa:\n"
			<< "      16. Pronalazenje niske\n"
			<< "      17. Umetanje niske\n"
			<< "      18. Brisanje niske\n"
			<< "      19. Ispisivanje svih niski odredjene duzine\n"
			<< "Kraj rada:\n"
			<< "      20. Kraj!" << endl;
		cout << "Izbor? "; cin >> izbor;

		switch (izbor) {
		    case 1:
				cin >> s;
				break;
			case 2:
				s.citajIzDatoteke();
				break;
			case 3:
				cout << "\nKoju nisku zelite da umetnete? "; cin >> nova;
				if (s.postoji(nova)) { 
					cout << "Niska vec posotoji!" << endl;  
					break; 
				}
				s.dodaj(nova);
				cout << "Niska je dodata!" << endl;
				break;
			case 4:
				cout << "\nKoju nisku zelite da obrisete? "; cin >> nova;
				if (!s.postoji(nova)) { 
					cout << "Niska ne postoji!" << endl; 
					break; 
				}
				s.brisanje(nova);
				cout << "Niska je obrisana!" << endl;
				break;
			case 5:
				s.brisi();
				cout << "\nStruktura podataka je unistena!\n";
				break;
			case 6:
				cout << s;
				break;
			case 7:
				cout << "\nRed stabla? "; cin >> m;
				b.formirajKoren(m);
				cout << "Prazno stablo je napravljeno!" << endl;
				break;
			case 8:
				b.brisi();
				cout << "\nStablo je obrisano!" << endl;
				break;
			case 9:
				cout << "\nVisina stabla je: " << b.visinaStabla() << endl;
				break;
			case 10:
				cout << "\nBroj kljuceva u stablu je: " << b.brCvorova() << endl;
				break;
			case 11:
				postoji = false;
				cout << "\nKljuc za pretrazivanje? "; cin >> kljuc;
				b.nadjiCvor(kljuc, postoji);
				if (postoji == true) cout << "Kljuc " << kljuc << " postoji u stablu!" << endl;
				else cout << "Kljuc " << kljuc << " ne postoji u stablu!" << endl;
				break;
			case 12:
				cout << "\n--------------------- B STABLO -------------------------------" << endl;
				b.pisi();
				cout << "\n--------------------------------------------------------------" << endl;
				break;
			case 13:
				s.formirajRedakIndeks(b);
				cout << "\nRedak indeks je formiran!" << endl;
				break;
			case 14:
				postoji = false;
				cout << "\nKljuc? "; cin >> kljuc;
				b.nadjiCvor(kljuc, postoji);
				if (postoji == true) cout << "Kljuc " << kljuc << " postoji u stablu!" << endl;
				else { 
					b.umetanje(kljuc);
					cout << "Kljuc " << kljuc << " je uspesno dodat!" << endl; 
				}
				break;
			case 15:
				postoji = false;
				cout << "\nKljuc za brisanje? "; cin >> kljuc;
				postoji = b.brisanje(kljuc);
				if (postoji == false) cout << "Kljuc " << kljuc << " ne postoji u stablu!" << endl;
				else cout << "Kljuc " << kljuc << " je obrisan iz stabla!" << endl;
				break;
			case 16:
				int i;
				postoji = false;
				cout << "\nKoju nisku zelite da pronadjete? "; cin >> nova;
				niz1 = b.nadjiCvor(nova.size(), postoji)->indeksi;
				niz2 = b.nadjiCvor(nova.size(), postoji)->kljucevi;
				if (postoji == false) { 
					cout << "Niska " << nova << " ne postoji u strukturi podataka!\n";
					break;
				}
				for (i = 0; i < m - 1; i++)
					if (niz2[i] == nova.size())
						break;
				postoji = s.pretrazi(nova, niz1[i], jedina);
				if (postoji == false) cout << "Niska " << nova << " ne postoji u strukturi podataka!\n";
				else cout << "Niska " << nova << " postoji u strukturi podataka!\n";
				break;
			case 17:
				postoji = false;
				cout << "\nKoju nisku zelite da umetnete? "; cin >> nova;
				if (s.postoji(nova)) {
					cout << "Niska vec postoji!" << endl;
					break;
				}
				b.nadjiCvor(nova.size(), postoji);
				if (postoji == false) s.dodajSaIndeksom(nova, b);
				else s.dodaj(nova);
				b.azurirajInd(nova.size(), 1);
				cout << "Niska je dodata!" << endl;
				break;
			case 18:
				postoji = false;
				cout << "\nNiska koju zelite da obrisete? "; cin >> nova;
				niz1 = b.nadjiCvor(nova.size(), postoji)->indeksi;
				niz2 = b.nadjiCvor(nova.size(), postoji)->kljucevi;
				if (postoji == false) {
					cout << "Niska " << nova << " ne postoji u strukturi podataka!\n";
					break;
				}
				for (i = 0; i < m - 1; i++)
					if (niz2[i] == nova.size())
						break;
				postoji = s.pretrazi(nova, niz1[i], jedina);
				if (postoji == false) cout << "Niska " << nova << " ne postoji u strukturi podataka!\n";
				else cout << "Niska " << nova << " je obrisana iz strukture podataka!\n";
				s.brisanje(nova);
				if (jedina) b.brisanje(nova.size());
				jedina = false;
				b.azurirajInd(nova.size(), -1);
				break;
			case 19:
				int j;
				postoji = false;
				cout << "\nKoje duzine ce biti ispisane niske? "; cin >> kljuc;
				niz1 = b.nadjiCvor(kljuc, postoji)->indeksi;
				niz2 = b.nadjiCvor(kljuc, postoji)->kljucevi;
				if (postoji == false) {
					cout << "Niske duzine " << kljuc << " ne postoje u strukturi podataka!\n";
					break;
				}
				for (j = 0; j < m - 1; j++)
					if (niz2[j] == kljuc)
						break;
				cout << "--------------------- NISKE L = " << kljuc << " ---------------------" << endl;
				s.pisiOdr(niz1[j]);
				cout << "-------------------------------------------------------" << endl;
				break;
			case 20:
				kraj = true;
				cout << "\n **** Izabrana opcija za kraj rada! **** \n" << endl;
				break;
			default:
				cout << "\n **** Nekorektan unos! Pokusajte ponovo! **** \n";
				break;
		}
	}
}