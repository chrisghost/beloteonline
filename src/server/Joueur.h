/*
 * Joueur.h
 *
 *  Created on: 21 janv. 2009
 *      Author: ayarim
 */

#ifndef JOUEUR_H_
#define JOUEUR_H_

class MainJoueur;
#include "Mainjoueur.h"

#include "Belotte.h"
#include <string>
#include <iostream>
#include <SFML/Network.hpp>

using namespace std;


class Equipe;
#include "Equipe.h"

class Joueur {

	public :
		//constructeur
		Joueur(int id, sf::IPAddress ip, Equipe E, string login);

		//methodes d'acces aux attributs de la classe
		int getId(); 			//retourne l'id du joueur
		inline string getLogin(){return login;}
		sf::IPAddress getIp();   //retourne l'ip du joueur
		MainJoueur * getMain();	//retourne la main du joueur
		Equipe getEquipe();		//retourne l'équipe du joueur
		void setMain(MainJoueur * m); //donne une nouvelle main au joueur

	private :
		//attributs
		 int id;
		 string login;
		 sf::IPAddress ip;
		 MainJoueur * main;
		 Equipe * equipe;
};

#endif /* JOUEUR_H_ */
