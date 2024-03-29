/*
 * Pli.h
 *
 *  Created on: 22 janv. 2009
 *      Author: ayarim
 */

#ifndef PLI_H_
#define PLI_H_
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>

#include "Equipe.h"
#include "deftype.h"
#include "Belotte.h"

class Carte;
#include "carte.h"

class Pli {
private:
	Couleur couleurDemandee;
	std::vector<Carte> carteDuPli;
	Carte * carteMaitre;
	Belotte * b;

public :
	Pli(Belotte * b);
	std::vector<Carte> getVectCarte();
	Couleur getCouleur();//k
	bool estAttout(Carte c);//k
	void ajouter_carte(Carte c);//k
	Carte * maitre();//renvoi la carte maitre
	int convertionPoint(Carte c); //k
	int calcul_points(); //k
	int gagnant();//ok
	bool estVide();//ok
	void setCoulDemandee(Couleur coul); //initialise la couleur demandee
};

#endif /* PLI_H_ */
