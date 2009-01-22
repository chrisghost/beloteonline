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
			switch (val) {
			case V:
				return false;
				break;
			case 9:
				if (c.getValeur()==V)
					return true;
				else
					return false;
				break;
			default:
				if (c.getValeur()==V || c.getValeur()==9)
					return true;
				else
					return (val < c.getValeur());
				break;
			}
		}
		else
			return true;
	}
	else {
		if (belotte.estAtout(this))
			return false;
		else {
			return (val < c.getValeur());
		}
	}
}

bool Carte::operator>(Carte c) {
	if (belotte.estAtout(c)) {
		if (belotte.estAtout(this)) {
			switch (val) {
				case V:
					return true;
					break;
				case 9:
					if (c.getValeur()==V)
						return false;
					else
						return true;
					break;
				default:
					if (c.getValeur()==V || c.getValeur()==9)
						return false;
					else
						return (val > c.getValeur());
					break;
			}
		}
		else
			return false;
	}
	else {
		if (belotte.estAtout(this))
			return true;
		else {
			return (val > c.getValeur());
		}
	}
}

bool Carte::operator==(Carte c) {
	return (coul==c.getCouleur() && val==c.getValeur());
}
