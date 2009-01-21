#include <stdlib.h>
#include <string>
#include <iostream>

#include "carte.h"

Carte::Carte(val,coul) {
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
