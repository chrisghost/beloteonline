/*
 * File: Belotte.h
 * Author: Michael
 *
 * Created on January 21, 2009, 5:37 PM
 */

#ifndef BELOTTE_H_
#define BELOTTE_H_

#include <vector>

class Belotte {
	private:
		//attributs
		Pli pli;
		Vector<Equipe> equipes;
		Couleur atout;
		int pointsMax;
		int preneur;

	public:

		//constructeur
		Belotte(Couleur atout, int pointsMax, int preneur);

		//methodes d'acces aux attibuts
		void setAtout(Couleur atout);
		void setPreneur(int id);

		//methodes
		bool estAtout(Carte carte); 			//retourne vrai si la carte  est un atout
		bool verifCarte(Carte carte); 			//retourne vrai si la carte peu etre jouee a ce moment de la partie
		Carte plusHaute(vector<Carte> cartes);	//retourne la carte ayant la plus haute valeur du vecteur cartes
		void ajouterEquipe(Equipe equipe);		//ajoute une equipe a la liste d'equipe (2 maximum)
};

#endif BELOTTE_H_ /*BELOTTE_H_*/
