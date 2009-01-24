/*
 * File: Belotte.cpp
 * Author: Michael
 *
 * Created on January 21, 2009, 5:37 PM
 */

#include "Belotte.h"
#include <stdlib.h>

/***********************************
 * Constructeur
 ***********************************/
Belotte::Belotte(Couleur atout, int pointsMax, int preneur)
	:equipes(), plis(), joueurs() {
	this->atout = atout;
	this->pointsMax = pointsMax;
	this->preneur = preneur;
	this->pliEnCours = 0;
}

/***********************************
 * Methodes d'acces aux atributs
 ***********************************/
void Belotte::setPreneur(int preneur) {
	this->preneur = preneur;
}

void Belotte::setAtout(Couleur atout) {
	this->atout = atout;
}

void Belotte::ajouterJoueur(Joueur j) {

}

/***********************************
 * Methodes
 ***********************************/
bool Belotte::verifCarte(Carte carte) {
	if (plis[pliEnCours].estVide() == true) //si la carte est la premiere du pli, n'importe quelle carte peu etre jouee
		return true;
	else
	{
		if(carte.getCouleur() == plis[pliEnCours].getCouleur()) //si la carte est de la couleur demandee, c'est bon
			return true;
		else
		{
			Joueur joueur = unJoueur(carte.getJoueur());
			if(joueur.getId() == NULL){cout << "Erreur" << endl; return false;} //au cas ou
			if(joueur.getMain().aLaCouleur(plis[pliEnCours].getCouleur())) //si le joueur a la couleur demandee il doit en jouer
				return false;
			else
			{
				if(carte.getCouleur() == atout) //si la carte est un atout c'est bon
					return true;
				else
				{
					if(joueur.getMain().aLaCouleur(atout)) //si le joueur a un atout il doit en jouer
						return false;
					else
						return true;
				}
			}
		}
	}
}

Carte Belotte::plusHaute(vector<Carte> cartes) {
	if (cartes.size() != 0)
	{
		Carte plusHaute = cartes[0];
		for(unsigned int i = 1; i<cartes.size(); i++)
		{
			if(cartes[i].getValeur() > plusHaute.getValeur())
				plusHaute = cartes[i];
		}
		return plusHaute;

	}
}

bool Belotte::estAtout(Carte carte) {
	if(carte.getCouleur() == atout)
		return true;
	else
		return false;
}

void Belotte::ajouterEquipe(Equipe equipe) {
	if(equipes.size() < 2) //au cas ou
		equipes.push_back(equipe);
	else
		cout << "Impossible d'ajouter plus de deux equipe a une partie." << endl;
}

Joueur Belotte::unJoueur(int id) {
	if(equipes.size() == 2) //au cas ou
	{
		if(equipes[1].unJoueur(id).getId() != NULL) //si le joueur est dans la premiere equipe c'est termine
			return equipes[1].unJoueur(id);
		else
			return equipes[2].unJoueur(id); //sinon on retourne le resultat de la recherche
	}
	else{
		Equipe e(-1,false);
		sf::IPAddress ip("localhost");
		Joueur j(-1, ip, e);
		return j;
	}
}

void Belotte::finMene() {
	bool e2undef = true;
	vector<Pli>::iterator i = plis.begin();

	int ptsE1 = 0;
	int ptsE2 = 0;
	Equipe E1 = Belotte::unJoueur(i->gagnant()).getEquipe();
	Equipe E2 = Belotte::unJoueur(i->gagnant()).getEquipe(); // ligne absurde pour éviter les erreurs de compilation (adrien)
	ptsE1 = ptsE1 + i->calcul_points();
	i++;
	while(i != plis.end()) {
		if (Belotte::unJoueur(i->gagnant()).getEquipe().getId() == E1.getId())
			ptsE1 = ptsE1 + i->calcul_points();
		else {
			if(e2undef){
				Equipe E2 = Belotte::unJoueur(i->gagnant()).getEquipe();
				e2undef = false;}
			ptsE2 = ptsE2 + i->calcul_points();
		}
		i++;
	}
	vector<Pli>::reverse_iterator rit;
	rit=plis.rbegin();
	if (Belotte::unJoueur(rit->gagnant()).getEquipe().getId() == E1.getId()) //ajout des "10 de der"
		ptsE1 = ptsE1 + 10;
	else
		ptsE2 = ptsE2 + 10;

	if (ptsE1 == 0 && E2.estPartante()) { //si E2 est partie et met capot E1
		if (E2.aLaBelote())
			E2.ajouterPoints(272);
		else
			E2.ajouterPoints(252);
	}
	else if (ptsE1 == 0 && E1.estPartante()) { //si E2 n'est pas partie et met capot E1
		if (E2.aLaBelote())
			E2.ajouterPoints(182);
		else
			E2.ajouterPoints(162);
	}
	if (ptsE2 == 0 && E1.estPartante()) { //si E1 est partie et met capot E2
		if (E1.aLaBelote())
			E1.ajouterPoints(272);
		else
			E1.ajouterPoints(252);
	}
	else if (ptsE2 == 0 && E2.estPartante()) { //si E1 n'est pas partie et met capot E2
		if (E1.aLaBelote())
			E1.ajouterPoints(182);
		else
			E1.ajouterPoints(162);
	}
	else if (E1.estPartante() && ptsE1 > 82) { //si E1 est partie et fait ses points
		if (E1.aLaBelote())
			ptsE1 = ptsE1 + 20;
		else if (E2.aLaBelote())
			ptsE2 = ptsE2 + 20;
		E1.ajouterPoints(ptsE1);
		E2.ajouterPoints(ptsE2);
	}
	else if (E2.estPartante() && ptsE2 > 82) { //si E2 est partie et fait ses points
		if (E1.aLaBelote())
			ptsE1 = ptsE1 + 20;
		else if (E2.aLaBelote())
			ptsE2 = ptsE2 + 20;
		E1.ajouterPoints(ptsE1);
		E2.ajouterPoints(ptsE2);
	}
	else if (E1.estPartante() && ptsE1 < 82) { //si E1 est partie mais est dedans
		if (E1.aLaBelote() || E2.aLaBelote())
			ptsE2 = ptsE2 + 20;
		E2.ajouterPoints(162);
	}
	else if (E2.estPartante() && ptsE2 < 82) { //si E2 est partie mais est dedans
		if (E1.aLaBelote() || E2.aLaBelote())
			ptsE1 = ptsE1 + 20;
		E1.ajouterPoints(162);
	}
	plis.clear();
}

void Belotte::jeu() {
	vector<Carte> vectCartes;
	int coul = 1;
	int val = 7;
	while (coul <= 4) { // coul <= carreau
		while (val <= 14) {// val <= 14
			Carte c = Carte(Valeur(val), Couleur(coul));
			vectCartes.push_back(c); //il faudrait randomiser le vecteur mais je sais pas encore comment
			if (val < 14)
				val=val+1;
			else
				val=7;
		}
		coul=coul+1;
	}
	Equipe E1(1, true);
	Equipe E2(2, false);

	//initialisation des 4 mains :
	MainJoueur m1(joueurs[0]);
	MainJoueur m2(joueurs[1]);
	MainJoueur m3(joueurs[2]);
	MainJoueur m4(joueurs[3]);
	int i;
	unsigned int pos;
	srand ( time(NULL) );
	for (i = 0; i < 5; i++) {
		pos = rand() % vectCartes.size();
		m1.ajouterCarte(vectCartes[pos]);
		vectCartes.erase(vectCartes.begin()+pos);
	}
	for (i = 0; i < 5; i++) {
		pos = rand() % vectCartes.size();
		m2.ajouterCarte(vectCartes[pos]);
		vectCartes.erase(vectCartes.begin()+pos);
	}
	for (i = 0; i < 5; i++) {
		pos = rand() % vectCartes.size();
		m3.ajouterCarte(vectCartes[pos]);
		vectCartes.erase(vectCartes.begin()+pos);
	}
	for (i = 0; i < 5; i++) {
		pos = rand() % vectCartes.size();
		m4.ajouterCarte(vectCartes[pos]);
		vectCartes.erase(vectCartes.begin()+pos);
	}
	pos = rand() % vectCartes.size();
	Carte car = vectCartes[pos];
	vectCartes.erase(vectCartes.begin()+pos);

	//Comment montrer cette carte à tous les joueurs ??
}
