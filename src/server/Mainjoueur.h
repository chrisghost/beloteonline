#ifndef MAINJOUEUR_H
#define MAINJOUEUR_H

class Joueur;
#include "Joueur.h"

#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
#include "carte.h"



class MainJoueur {
private:
	std::vector<Carte> main;
	Joueur * joueur;
public:
	MainJoueur(Joueur j);
	bool aLaCouleur(Couleur coul); // Renvoie vrai si le joueur a au moins une carte de la couleur donnée dans sa main
	bool aUnAtoutSuperieur(Carte c); // Renvoie vrai si le joueur a un atout superieur à celui donné dans sa main
	void ajouterCarte(Carte c); // Ajoute une carte à la main du joueur
	void retirerCarte(Carte c); // Retire une carte de la main du joueur

};

#endif // MAINJOUEUR_H
