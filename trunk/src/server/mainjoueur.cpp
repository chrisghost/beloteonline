#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>

#include "mainjoueur.h"

MainJoueur::MainJoueur(Joueur j) : main() {
	joueur = j;
}

bool MainJoueur::aLaCouleur(Couleur coul) {
	bool oui = false;
	for (unsigned int i=0;i<main.size();i++) {
		if (main[i].getCouleur() == coul)
			oui = true;
	}
	return oui;
}

bool MainJoueur::aUnAtoutSuperieur(Carte c) {
	bool oui = false;
	for (unsigned int i=0;i<main.size();i++) {
		if (main[i] > c)		// operateur de comparaison à définir, en tenant compte de la couleur de l'atout...
			oui = true;
	}
	return oui;
}

void MainJoueur::ajouterCarte(Carte c) {
	if (main.size() < 8)
		main.push_back(c);		// sinon ?
}

void MainJoueur::retirerCarte(Carte c) {
	unsigned int i=0;
	while (i < main.size() && main[i] != c) {		// idem, operateur à définir
		i++;
	}
	if (i != main.size() && main[i] == c)
		main.erase(main.begin()+i);		// sinon ?
}
