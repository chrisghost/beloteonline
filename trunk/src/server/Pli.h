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

#include "carte.h"
#include "Belotte.h"
#include "Equipe.h"

class Pli {
private:
	Couleur couleurDemandee  ;
	vector<Carte> carteDuPli;
	Carte carteMaitre
	//int joueurMaitre;
public :
	Couleur getCouleur();//k
	bool estAttout();//k
	void ajouter_carte(Carte c*);//k
//	void plus_haut_atout();    /// donné par maitre
	Carte  maitre() ;//renvoi la carte maitre
	int convertionPoint(Carte c); //k
	int calcul_points() ; //k
	int gagnant() ;
	bool estVide();//ok

}
#endif /* PLI_H_ */
