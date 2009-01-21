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
