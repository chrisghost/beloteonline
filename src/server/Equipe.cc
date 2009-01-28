/*
 * Equipe.cc
 *
 *  Created on: 21 janv. 2009
 *      Author: ayarim
 */

#include "Joueur.h"
#include "Equipe.h"

/***********************************
 * Constructeur
 ***********************************/
Equipe::Equipe(int idEquipe, bool partante)
    :joueurs(){
	this->idEquipe = idEquipe;
	this->partante = partante;
	this->points = 0;
}

/***********************************
 * Methodes d'acces aux atributs
 ***********************************/
bool Equipe::estPartante() {
	return this->partante;
}

void Equipe::setPartante(bool nouvValeur) {
	this->partante = nouvValeur;
}

/***********************************
 * Methodes
 ***********************************/
void Equipe::ajouterJoueur(Joueur joueur) {
	if(joueurs.size() < 2)
		joueurs.push_back(joueur);
	else
		cout << "Impossible d'ajouter plus de deux equipe a une partie." << endl;
}

int Equipe::partenaire(int id){
	if (joueurs.size() == 2)
	{
		if(id == joueurs[1].getId())
			return joueurs[2].getId();
		else if(id == joueurs[2].getId())
			return joueurs[1].getId();
		else
			return NULL;
	}
	else
		return NULL;
}

Joueur * Equipe::unJoueur(int id){
	if (joueurs[1].getId() == id)
		return &joueurs[1];
	else if (joueurs[2].getId() == id)
		return &joueurs[2];
	else
		return NULL;

}

void Equipe::ajouterPoints(int p) {
	this->points = this->points+p;
}

void Equipe::setBelote(bool nouvValeur) {
	Belote = nouvValeur;
}

bool Equipe::aLaBelote() {
	return Belote;
}
