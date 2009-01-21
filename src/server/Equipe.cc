/*
 * Equipe.cc
 *
 *  Created on: 21 janv. 2009
 *      Author: ayarim
 */

#include "Client.h"
#include "Joueur.h"
#include "Equipe.h"



	int Equipe::partenaire(int idautre){
		this->idautre=s;
			// attention : l'ordre des tests ci-dessous n'est pas innocent !
			if      (s==this->idjoueur1)
				return this->idjoueur2;
			else if      (s==this->idjoueur2)
				return this->idjoueur1;
			else
							return 0;
	}




	bool Equipe::estPartante() {
		return this->partante;

	};
