/*
 * Joueur.cc
 *
 *  Created on: 21 janv. 2009
 *      Author: ayarim
 */

#include <string>
#include <iostream>
#include <SFML/Network.hpp>

/***********************************
 * Constructeur
 ***********************************/
Joueur::Joueur(int id, sf::IpAdress ip)
	:Main(){
	this->id = id;
	this->ip = ip;
}


/***********************************
 * Methodes d'acces aux atributs
 ***********************************/
int Joueur::getId() {
	return this->id;
}

sf::IpAdress Joueur::getIp() {
	return this->ip;
}