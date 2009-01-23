/*
 * File: Belotte.h
 * Author: Michael
 *
 * Created on January 21, 2009, 5:37 PM
 */

#ifndef BELOTTE_H_
#define BELOTTE_H_
#include "Equipe.h"
#include "Mainjoueur.h"
#include "Joueur.h"


#include "Pli.h"
#include "deftype.h"
#include <stdlib.h>
#include <vector>
#include <iostream>

class Belotte {

	private:
		//attributs
		vector<Pli> plis; // pour conserver les points de la mène et pouvoir les ajouter à l'équipe a la fin de la mène
		vector<Equipe> equipes;
		vector<Joueur> joueurs;
		Couleur atout;
		int pointsMax;
		int preneur;
		int pliEnCours;

	public:

		//constructeur
		Belotte(Couleur atout, int pointsMax, int preneur);

		//methodes d'acces aux attibuts
		void setAtout(Couleur atout);
		void setPreneur(int id);
		void ajouterJoueur(Joueur j);

		//methodes
		bool estAtout(Carte carte); 			//retourne vrai si la carte  est un atout
		bool verifCarte(Carte carte); 			//retourne vrai si la carte peu etre jouee a ce moment de la partie
		Carte plusHaute(vector<Carte> cartes);	//retourne la carte ayant la plus haute valeur du vecteur cartes
		void ajouterEquipe(Equipe equipe);		//ajoute une equipe a la liste d'equipe (2 maximum)
		Joueur unJoueur(int id);				//retourne le joueur de l'id si il existe, NULL sinon
		void finMene();							//compte les points, les ajoute à l'équipe gagnante de la mène
												// et vide le vecteur de plis pour commencer une nouvelle mène
		void jeu(); 							//methode qui gere tout le déroulement du jeu (distribution des cartes,
												//choix de l'atout par les joueurs, passage d'une mène à une autre, etc ...)
};

#endif /*BELOTTE_H_*/
