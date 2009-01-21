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

class Equipe
{
public :
	int idjoueur1 ;
	int idjoueur2 ;
	int idequipe ;
	int point;
	bool partante;

private :

	int partenaire(int);
	bool : estPartante();

};


#endif /* EQUIPE_H_ */
