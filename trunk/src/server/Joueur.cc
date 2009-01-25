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
Joueur::Joueur(int id, sf::IPAddress ip, Equipe E): equipe(-1,false){
	main = new MainJoueur(this);
	this->id = id;
	this->ip = ip;
	this->equipe = E;
}


/***********************************
 * Methodes d'acces aux atributs
 ***********************************/
int Joueur::getId() {
	return this->id;
}

sf::IPAddress Joueur::getIp() {
	return this->ip;
}

MainJoueur * Joueur::getMain() {
	return this->main;
}

Equipe Joueur::getEquipe() {
	return equipe;
}

void Joueur::setMain(MainJoueur * m) {
	this->main = m;
}
