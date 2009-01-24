#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>

#include "Mainjoueur.h"

MainJoueur::MainJoueur(Joueur j) {
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
		if (main[i] > c)
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
	while (i < main.size() && !(main[i] == c)) {
		i++;
	}
	if (i != main.size() && main[i] == c)
		main.erase(main.begin()+i);		// sinon ?
}
