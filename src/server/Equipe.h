/*
 * Equipe.h
 *
 *  Created on: 21 janv. 2009
 *      Author: ayarim
 */

#ifndef EQUIPE_H_
#define EQUIPE_H_

#include <string>
#include <iostream>
#include <SFML/Network.hpp>
#include "Joueur.h"

class Equipe
{
	private :
		vector<Joueur> joueurs;
		int idEquipe ;
		int points;
		bool partante;
		bool Belote;

	public :
		//constructeur
		Equipe(int idEquipe, bool partante);

		//methodes d'acces aux attributs de la classe
		bool estPartante(); //retourne vrai si l'equipe est partante et faux sinon
		void setPartante(bool nouvValeur); //modifie la valeur de l'attribut partante
		bool aLaBelote();  //retourne vrai si l'équipe a la belote et faux sinon
		void setBelote(bool nouvValeur);   //modifie la valeur de l'attribut aLaBelote

		//methodes
		void ajouterJoueur(Joueur joueur); //ajoute un joueur al'equipe (2 maximum)
		int partenaire(int id); //retourne l'id du partenaire du joueur passe en parametre
								//si il n'y a pas de joueurs ou que l'id n'appartient pas a un joueur de l'equipe: retourne NULL
		Joueur unJoueur(int id); //retourne le joueur si l'id passé en paramètre est l'id d'un des joueurs de l'équipe
								 //sinon retourne NULL
		void ajouterPoints(int p); //ajoute les points à l'équipe

};


#endif /* EQUIPE_H_ */
