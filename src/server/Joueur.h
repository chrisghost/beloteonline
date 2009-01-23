/*
 * Joueur.h
 *
 *  Created on: 21 janv. 2009
 *      Author: ayarim
 */

#ifndef JOUEUR_H_
#define JOUEUR_H_

#include "Mainjoueur.h"
#include "Equipe.h"

#include <string>
#include <iostream>
#include <SFML/Network.hpp>

using namespace std;

class Joueur {

	public :
		//constructeur
		Joueur(int id, sf::IpAdress ip, Equipe E);

		//methodes d'acces aux attributs de la classe
		int getId(); 			//retourne l'id du joueur
		sf::IpAdress getIp();   //retourne l'ip du joueur
		Mainjoueur getMain();	//retourne la main du joueur
		Equipe equipe();		//retourne l'équipe du joueur
		void setMain(Mainjoueur m); //donne une nouvelle main au joueur

	private :
		//attributs
		 int id;
		 Equipe equipe;
		 sf::IpAdress ip;
		 Mainjoueur main;
};


#endif /* JOUEUR_H_ */
