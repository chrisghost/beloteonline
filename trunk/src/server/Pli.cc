/*
 * Pli.cc
 *
 *  Created on: 22 janv. 2009
 *      Author: ayarim
 */

#include "Pli.h"

bool Pli::estVide(){
	return carteDuPli.size()==0;
}

Couleur Pli::getCouleur() {
	return couleurDemandee;
}

void Pli::ajouterCarte(Carte c) {
	if (carteDuPli.size() < 4)
		{carteDuPli.push_back(c);}// sinon ?
	if (carteDuPli.size() =1 )
		carteMaitre = c; // si le pli est vide, la premiere carte est maitre
	else if (carteDuPli.size() !=1 )
			{
				if (c > carteMaitre)
					carteMaitre = c ;
			}

}

bool Pli::estAttout(c  carte ) {
	return (c.Couleur == getCouleur() );
}

Carte Pli::maitre() {
	return carteMaitre;
}
int Pli::convertionPoint(Carte c){
	if (c.estAtout = true)
		{
		if (c.Valeur=sept | huit)
			return 0;
		else if ( c.Valeur = damme)
			return 3;
		else if ( c.Valeur = roi)
					return 4;
		else if ( c.Valeur = dix)
					return 10;
		else if ( c.Valeur = as)
					return 11;
		else if ( c.Valeur = neuf)
					return 14;
		else if ( c.Valeur = valet)
					return 20;
		}
	else if  (c.estAtout = false)
	{ if (c.Valeur=sept | huit)
		return 0;
	else if ( c.Valeur = damme)
		return 3;
	else if ( c.Valeur = roi)
				return 4;
	else if ( c.Valeur = dix)
				return 10;
	else if ( c.Valeur = as)
				return 11;
	else if ( c.Valeur = neuf)
				return 0;
	else if ( c.Valeur = valet)
				return 2;
	}
}

int Pli::calcul_points() { 	//retourne la valeur de toutes les cartes
	int point =0;
	//Carte cm= maitre();
	vector<Carte>::iterator it;
	for ( it=carteDePli.begin() ; it < carteDePli.end(); it++ )
		{
				point = point +convertionPoint( carteDePli[it]);
		}
	return point;

}

int Pli::gagnant() {
	return carteMaitre.getJoueur();
	//retrourn l'id du joueur ayant jouer carteMaitre
}
