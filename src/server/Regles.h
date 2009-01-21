#include "Carte.h"

class Regles {

	private:
		//attributs
		Serveur serveur;
		Couleur atout;
		int preneur;

	public:
		//constructeur
		Regles(Serveur serveur, Couleur atout, int preneur);

		//methodes d'acces aux attibuts
		void setPreneur(int id);
		void setAtout(Couleur atout);

		//methodes
		bool estAtout(Carte carte); 			//retourne vrai si la carte  est un atout
		bool verifCarte(Carte carte); 			//retourne vrai si la carte peu etre jouee a ce moment de la partie
		Carte plusHaute(vector<Carte> cartes);	//retourne la carte ayant la plus haute valeur du vecteur cartes

};

