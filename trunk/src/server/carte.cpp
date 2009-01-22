#include <stdlib.h>
#include <string>
#include <iostream>

#include "carte.h"

Carte::Carte(Valeur val,Couleur coul) {
	this->val = val;
	this->coul = coul;
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

bool Carte::operator<(Carte c) {
	if (belotte.estAtout(c)) {
		if (belotte.estAtout(this)) {
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
		if (belotte.estAtout(this))
			return false;			// si seul this est atout
		else {
			return (val < c.getValeur());		// si les deux cartes ne sont pas atout, on garde l'ordre des cartes initial
		}
	}
}

bool Carte::operator>(Carte c) {
	if (belotte.estAtout(c)) {
		if (belotte.estAtout(this)) {
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
		if (belotte.estAtout(this))
			return true;			// si seul this est atout
		else {
			return (val > c.getValeur());		// si les deux cartes ne sont pas atout, on garde l'ordre des cartes initial
		}
	}
}

bool Carte::operator==(Carte c) {
	return (coul==c.getCouleur() && val==c.getValeur());
}
