/*
 * File: Belotte.cpp
 * Author: Michael
 *
 * Created on January 21, 2009, 5:37 PM
 */

#include <iostream>
#include "Belotte.h"
#include "Joueur.h"

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
			Joueur joueur = unJoueur(carte.getJoueur());
			if(joueur == NULL){cout << "Erreur" << endl; return false;} //au cas ou
			if(joueur.getMain().aLaCouleur(couleurDemandee)) //si le joueur a la couleur demandee il doit en jouer
				return false;
			else
			{
				if(carte.getCouleur() == atout) //si la carte est un atout c'est bon
					return true;
				else
				{
					if(joueur.getMain().aLaCouleur(atout)) //si le joueur a un atout il doit en jouer
						return false;
					else
						return true;
				}
			}
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
	if(equipes.size() < 2) //au cas ou
		equipes.push_back(equipe);
	else
		cout << "Impossible d'ajouter plus de deux equipe a une partie." << endl;
}

Joueur Belotte::unJoueur(int id) {
	if(equipes.size() == 2) //au cas ou
	{
		Joueur joueur = equipes[1].unJoueur(id);
		if(joueur != NULL) //si le joueur est dans la premiere equipe c'est termine
			return joueur;
		else
			return equipe[2].unJoueur(id); //sinon on retourne le resultat de la recherche
	}
	else
		return NULL;
}

void Belotte::finMene() {
	vector<Pli>::iterator i = plis.begin();
	Equipe E1,E2;
	int ptsE1 = 0;
	int ptsE2 = 0;
	E1 = *i.gagnant().equipe()
	while(i != plis.end()) {
		.
		i++;
	}
}
