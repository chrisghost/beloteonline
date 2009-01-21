#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>

#include "carte.h"
#include "Joueur.h"

class MainJoueur {
private:
	Joueur joueur;
	vector<Carte> main;
public:
	MainJoueur(Joueur j);
	bool aLaCouleur(Couleur coul); // Renvoie vrai si le joueur a au moins une carte de la couleur donnée dans sa main
	bool aUnAtoutSuperieur(Carte c); // Renvoie vrai si le joueur a un atout superieur à celui donné dans sa main
	void ajouterCarte(Carte c); // Ajoute une carte à la main du joueur
	void retirerCarte(Carte c); // Retire une carte de la main du joueur

};
