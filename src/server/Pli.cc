/*
 * Pli.cc
 *
 *  Created on: 22 janv. 2009
 *      Author: ayarim
 */

#include "Pli.h"


Pli::Pli(Belotte * b){
	this->b = b;
}

std::vector<Carte> Pli::getVectCarte() {
	return this->carteDuPli;
}

bool Pli::estVide(){
	return carteDuPli.size()==0;
}

Couleur Pli::getCouleur() {
	return couleurDemandee;
}

void Pli::ajouter_carte(Carte c) {
	if (carteDuPli.size() < 4)
		{carteDuPli.push_back(c);}// sinon ?
	if (carteDuPli.size() == 1 )
		carteMaitre = &c; // si le pli est vide, la premiere carte est maitre
	else if (carteDuPli.size() !=1 )
			{
				if (c > *carteMaitre)
					carteMaitre = &c ;
			}

}

bool Pli::estAttout(Carte c) {
	return (c.getCouleur() == getCouleur() );
}

Carte * Pli::maitre() {
	return carteMaitre;
}
int Pli::convertionPoint(Carte c){
	if (b->estAtout(&c))
		{
		if (c.getValeur()== (sept | huit))
			return 0;
		else if ( c.getValeur() == dame)
			return 3;
		else if ( c.getValeur() == roi)
					return 4;
		else if ( c.getValeur() == dix)
					return 10;
		else if ( c.getValeur() == as)
					return 11;
		else if ( c.getValeur() == neuf)
					return 14;
		else if ( c.getValeur() == valet)
					return 20;
		}
	else if  (b->estAtout(&c) == false)
	{ if (c.getValeur()== (sept | huit))
		return 0;
	else if ( c.getValeur() == dame)
		return 3;
	else if ( c.getValeur() == roi)
				return 4;
	else if ( c.getValeur() == dix)
				return 10;
	else if ( c.getValeur() == as)
				return 11;
	else if ( c.getValeur() == neuf)
				return 0;
	else if ( c.getValeur() == valet)
				return 2;
	}
}

int Pli::calcul_points() { 	//retourne la valeur de toutes les cartes
	int point =0;
	//Carte cm= maitre();
	unsigned int it;
	for ( it=0 ; it < carteDuPli.size(); it++ )
		{
				point += convertionPoint( carteDuPli.at(it));
		}
	return point;

}

int Pli::gagnant() {
	return carteMaitre->getJoueur();
	//retrourn l'id du joueur ayant jouer carteMaitre
}

void Pli::setCoulDemandee(Couleur coul) {
	this->couleurDemandee = coul;
}
