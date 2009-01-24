#ifndef CARTE_H
#define CARTE_H

class Belotte;
#include "Belotte.h"

#include "deftype.h"

#include <stdlib.h>
#include <string>
#include <iostream>

class Carte {
private:
	Valeur val;
	Couleur coul;
	int id_joueur;

public:

	//constructeur
	Carte(Valeur val,Couleur coul);

	//methodes d'acces aux attributs de la classe
	Couleur getCouleur();
	Valeur getValeur();
	int getJoueur();
	void setJoueur(int id);

	//operateurs
	bool operator<(Carte c);
	bool operator>(Carte c);
	bool operator==(Carte c); // Renvoie vrai si les deux cartes sont identique (même couleur et même valeur)
};

#endif /*CARTE_H*/
