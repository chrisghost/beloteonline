/*
 * Joueur.h
 *
 *  Created on: 21 janv. 2009
 *      Author: ayarim
 */

#ifndef JOUEUR_H_
#define JOUEUR_H_

#include "Main.h"

#include <string>
#include <iostream>
#include <SFML/Network.hpp>

using namespace std;

class Joueur {

	public :
		//constructeur
		Joueur(int id, sf::IpAdress ip);

		//methodes d'acces aux attributs de la classe
		int getId(); 			//retourne l'id du joueur
		sf::IpAdress getIp();   //retourne l'ip du joueur
		Main getMain();			//retourne la main du joueur

	private :
		//attributs
		 int id;
		 sf::IpAdress ip;
		 Main main;
};


#endif /* JOUEUR_H_ */
