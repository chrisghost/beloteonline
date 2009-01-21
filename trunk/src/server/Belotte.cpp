/*
 * File: Belotte.cpp
 * Author: Michael
 *
 * Created on January 21, 2009, 5:37 PM
 */

#include <iostream>
#include "Belotte.h"

/***********************************
 * Constructeur
 ***********************************/
Belotte(Couleur atout, int pointsMax, int preneur)
	:equipes(), pli() {
	this->atout = atout;
	this->pointsMax = pointsMax;
	this->preneur = preneur;
}

/***********************************
 * Methodes d'acces aux atributs
 ***********************************/
void Belotte::setPreneur(int preneur) {
	this->preneur = preneur;
}

void Belotte::setAtout(Couleur atout) {
	this->atout = atout;
}

/***********************************
 * Methodes
 ***********************************/
bool Belotte::verifCarte(Carte carte) {
	if (pli.estVide() == true) //si la carte est la premiere du pli, n'importe quelle carte peu etre jouee
		return true;
	else
	{
		if(carte.getCouleur() == couleurDemandee) //si la carte est de la couleur demandee, c'est bon
			return true;
		else
		{

		}
	}
}

Carte Belotte::plusHaute(vector<Carte> cartes) {
	if (cartes.size() != 0)
	{
		Carte plusHaute = cartes[0];
		for(unsigned int i = 1; i<cartes.size(); i++)
		{
			if(cartes[i].getValeur() > plusHaute.getValeur())
				plusHaute = cartes[i];
		}
		return plusHaute;

	}
	else
		return NULL;
}

bool Belotte::estAtout(Carte carte) {
	if(carte.getCouleur == atout)
		return true;
	else
		return false;
}

void Belotte::ajouterEquipe(Equipe equipe) {
	if(equipes.size() < 2)
		equipes.push_back(equipe);
	else
		cout << "Impossible d'ajouter plus de deux equipe a une partie." << endl;
}
