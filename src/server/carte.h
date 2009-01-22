#ifndef CARTE_H
#define CARTE_H

#include <stdlib.h>
#include <string>
#include <iostream>

#include "deftype.h"
#include "Belotte.h"

class Carte {
private:
	Valeur val;
	Couleur coul;
	int id_joueur;
	Belotte belotte;
public:
	Carte(Valeur val,Couleur coul);
	Couleur getCouleur();
	Valeur getValeur();
	int getJoueur();
	void setJoueur(int id);
	bool operator<(Carte c);
	bool operator>(Carte c);
	bool operator==(Carte c); // Renvoie vrai si les deux cartes sont identique (même couleur et même valeur)
};

#endif // CARTE_H
