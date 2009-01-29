

#include "carte.h"

Carte::Carte(Valeur val,Couleur coul, Belotte * b) {
	this->val = val;
	this->coul = coul;
	this->b =b;
}

Couleur Carte::getCouleur() {
	return coul;
}

Valeur Carte::getValeur() {
	return val;
}

int Carte::getJoueur() {
	return id_joueur;
}

void Carte::setJoueur(int id) {
	id_joueur = id;
}

string Carte::getFichierImage() {
	string fichier = "images/";
	switch (this->val) {
	case 7 :
		fichier += "7";
		break;
	case 8 :
		fichier += "8";
		break;
	case 9 :
		fichier += "9";
		break;
	case 10 :
		fichier += "10";
	case 11 :
		fichier += "valet";
		break;
	case 12 :
		fichier += "dame";
		break;
	case 13 :
		fichier += "roi";
		break;
	case 14 :
		fichier += "as";
		break;
	default :
		return NULL;
	}
	fichier += "_";
	switch (this->coul) {
	case 1:
		fichier += "p.jpg";
		break;
	case 2:
		fichier += "co.jpg";
		break;
	case 3:
		fichier += "t.jpg";
		break;
	case 4:
		fichier += "ca.jpg";
		break;
	default:
		return NULL;
	}
	return fichier;
}

bool Carte::operator<(Carte c) {
	if (b->estAtout(&c)) {
		if (b->estAtout(this)) {
			switch (val) {			// si les deux cartes sont atout
			case valet:				// le valet est le plus fort
				return false;
				break;
			case neuf:				// ensuite le neuf
				if (c.getValeur()==valet)
					return true;
				else
					return false;
				break;
			default:				// et le reste est dans l'ordre normal
				if (c.getValeur()==valet || c.getValeur()==neuf)
					return true;
				else
					return (val < c.getValeur());
				break;
			}
		}
		else
			return true;			// si seul c est atout
	}
	else {
		if (b->estAtout(this))
			return false;			// si seul this est atout
		else {
			return (val < c.getValeur());		// si les deux cartes ne sont pas atout, on garde l'ordre des cartes initial
		}
	}
}

bool Carte::operator>(Carte c) {
	if (b->estAtout(&c)) {
		if (b->estAtout(this)) {
			switch (val) {			// si les deux cartes sont atout
			case valet:				// le valet est le plus fort
				return true;
				break;
			case neuf:				// ensuite le neuf
				if (c.getValeur()==valet)
					return false;
				else
					return true;
				break;
			default:				// et le reste est dans l'ordre normal
				if (c.getValeur()==valet || c.getValeur()==neuf)
					return false;
				else
					return (val > c.getValeur());
				break;
			}
		}
		else
			return false;			// si seul c est atout
	}
	else {
		if (b->estAtout(this))
			return true;			// si seul this est atout
		else {
			return (val > c.getValeur());		// si les deux cartes ne sont pas atout, on garde l'ordre des cartes initial
		}
	}
}

bool Carte::operator==(Carte c) {
	return (coul==c.getCouleur() && val==c.getValeur());
}
