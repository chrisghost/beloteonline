#include <stdlib.h>
#include <string>
#include <iostream>

class Carte {
private:
	Valeur val;
	Couleur coul;
	int id_joueur;
public:
	Carte(Valeur val,Couleur coul);
	Couleur getCouleur();
	Valeur getValeur();
	int getJoueur();
};
