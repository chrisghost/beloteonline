/*
 * Joueur.cc
 *
 *  Created on: 21 janv. 2009
 *      Author: ayarim
 */
#include "Joueur.h"
#include <string>
#include <iostream>
#include <SFML/Network.hpp>

/***********************************
 * Constructeur
 ***********************************/
Joueur::Joueur(int id, Equipe E, string login){
	main = new MainJoueur(this);
	this->id = id;
	this->equipe = &E;
	this->login = login;
}


/***********************************
 * Methodes d'acces aux atributs
 ***********************************/
int Joueur::getId() {
	return this->id;
}


MainJoueur * Joueur::getMain() {
	return this->main;
}

Equipe Joueur::getEquipe() {
	return *equipe;
}

void Joueur::setMain(MainJoueur * m) {
	this->main = m;
}
