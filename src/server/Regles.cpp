/*
 * File: Regles.cpp
 * Author: Michael
 *
 * Created on January 21, 2009, 4:35 PM
 */

#include "Regles.h"

/***********************************
 * Constructeur
 ***********************************/
Regles(Couleur atout, int preneur){
	this->serveur = serveur;
	this->atout = atout;
	this->preneur = preneur;
}

/***********************************
 * Methodes d'acces aux atributs
 ***********************************/
void Regles::setPreneur(int preneur) {
	this->preneur = preneur;
}

void Regles::setAtout(Couleur atout) {
	this->atout = atout;
}

/***********************************
 * Methodes
 ***********************************/
bool Regles::verifCarte(Carte carte) {
	//A FAIRE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

Carte Regles::plusHaute(vector<Carte> cartes) {
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

bool Regles::estAtout(Carte carte) {
	if(carte.getCouleur == atout)
		return true;
	else
		return false;
}
