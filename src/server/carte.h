#ifndef CARTE_H
#define CARTE_H

class Belotte;
#include "Belotte.h"

#include "deftype.h"

#include <stdlib.h>
//#include <string>
#include <iostream>
using namespace std ;
class Carte {
private:
	Valeur val;
	Couleur coul;
	int id_joueur;
	Belotte * b;

public:

	//constructeur
	Carte(Valeur val,Couleur coul, Belotte * b);

	//methodes d'acces aux attributs de la classe
	Couleur getCouleur();
	Valeur getValeur();
	int getJoueur();
	void setJoueur(int id);
	string getFichierImage();

	//operateurs
	bool operator<(Carte c);
	bool operator>(Carte c);
	bool operator==(Carte c); // Renvoie vrai si les deux cartes sont identique (même couleur et même valeur)
};

#endif /*CARTE_H*/
