/*
 * File: Belotte.cpp
 * Author: Michael
 *
 * Created on January 21, 2009, 5:37 PM
 */

#include "Belotte.h"
#include <SFML/Network.hpp>
#include <stdlib.h>
#include <time.h>

/***********************************
 * Constructeur
 ***********************************/
Belotte::Belotte(int pointsMax)
	:equipes(), joueurs(){
	this->s = new Server(1234, this);
	this->rep = 0;
	this->atout = carreau;
	this->atout_defini = false;
	this->pointsMax = pointsMax;
	this->pliEnCours = 0;
	this->id_preneur = -1;

}

/***********************************
 * Methodes d'acces aux atributs
 ***********************************/
void Belotte::setPreneur(int preneur) {
	this->id_preneur = preneur;
}

void Belotte::setAtout(Couleur atout) {
	this->atout = atout;
}

void Belotte::ajouterJoueur(Joueur * j) {
	joueurs.push_back(j);
	if (equipes.size() == 0) {
		equipes.push_back(j->getEquipe());
	}
	else if (equipes.size() == 1 && j->getEquipe()->getId() != equipes[0]->getId()) {
		equipes.push_back(j->getEquipe());
	}
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
			if(joueur.getMain()->aLaCouleur(plis[pliEnCours].getCouleur())) //si le joueur a la couleur demandee il doit en jouer
				return false;
			else
			{
				if(carte.getCouleur() == atout) //si la carte est un atout c'est bon
					return true;
				else
				{
					if(joueur.getMain()->aLaCouleur(atout)) //si le joueur a un atout il doit en jouer
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

bool Belotte::estAtout(Carte * carte) {
	if(carte->getCouleur() == atout)
		return true;
	else
		return false;
}

void Belotte::ajouterEquipe(Equipe * equipe) {
	if(equipes.size() < 2) //au cas ou
		equipes.push_back(equipe);
	else
		cout << "Impossible d'ajouter plus de deux equipe a une partie." << endl;
}

Joueur Belotte::unJoueur(int id) {
	if(equipes.size() == 2) //au cas ou
	{
		if(equipes[1]->unJoueur(id).getId() != NULL) //si le joueur est dans la premiere equipe c'est termine
			return equipes[1]->unJoueur(id);
		else
			return equipes[2]->unJoueur(id); //sinon on retourne le resultat de la recherche
	}
	else{
		Equipe e(-1,false);
		Joueur j(-1, &e, "");
		return j;
	}
}

void Belotte::finMene() {
	bool e2undef = true;
	vector<Pli>::iterator i = plis.begin();

	int ptsE1 = 0;
	int ptsE2 = 0;
	Equipe * E1 = Belotte::unJoueur(i->gagnant()).getEquipe();
	Equipe * E2 = Belotte::unJoueur(i->gagnant()).getEquipe(); // ligne absurde pour éviter les erreurs de compilation (adrien)
	ptsE1 = ptsE1 + i->calcul_points();
	i++;
	while(i != plis.end()) {
		if (Belotte::unJoueur(i->gagnant()).getEquipe()->getId() == E1->getId())
			ptsE1 = ptsE1 + i->calcul_points();
		else {
			if(e2undef){
				Equipe * E2 = Belotte::unJoueur(i->gagnant()).getEquipe();
				e2undef = false;}
			ptsE2 = ptsE2 + i->calcul_points();
		}
		i++;
	}
	vector<Pli>::reverse_iterator rit;
	rit=plis.rbegin();
	if (Belotte::unJoueur(rit->gagnant()).getEquipe()->getId() == E1->getId()) //ajout des "10 de der"
		ptsE1 = ptsE1 + 10;
	else
		ptsE2 = ptsE2 + 10;

	if (ptsE1 == 0 && E2->estPartante()) { //si E2 est partie et met capot E1
		if (E2->aLaBelote())
			E2->ajouterPoints(272);
		else
			E2->ajouterPoints(252);
	}
	else if (ptsE1 == 0 && E1->estPartante()) { //si E2 n'est pas partie et met capot E1
		if (E2->aLaBelote())
			E2->ajouterPoints(182);
		else
			E2->ajouterPoints(162);
	}
	if (ptsE2 == 0 && E1->estPartante()) { //si E1 est partie et met capot E2
		if (E1->aLaBelote())
			E1->ajouterPoints(272);
		else
			E1->ajouterPoints(252);
	}
	else if (ptsE2 == 0 && E2->estPartante()) { //si E1 n'est pas partie et met capot E2
		if (E1->aLaBelote())
			E1->ajouterPoints(182);
		else
			E1->ajouterPoints(162);
	}
	else if (E1->estPartante() && ptsE1 > 82) { //si E1 est partie et fait ses points
		if (E1->aLaBelote())
			ptsE1 = ptsE1 + 20;
		else if (E2->aLaBelote())
			ptsE2 = ptsE2 + 20;
		E1->ajouterPoints(ptsE1);
		E2->ajouterPoints(ptsE2);
	}
	else if (E2->estPartante() && ptsE2 > 82) { //si E2 est partie et fait ses points
		if (E1->aLaBelote())
			ptsE1 = ptsE1 + 20;
		else if (E2->aLaBelote())
			ptsE2 = ptsE2 + 20;
		E1->ajouterPoints(ptsE1);
		E2->ajouterPoints(ptsE2);
	}
	else if (E1->estPartante() && ptsE1 < 82) { //si E1 est partie mais est dedans
		if (E1->aLaBelote() || E2->aLaBelote())
			ptsE2 = ptsE2 + 20;
		E2->ajouterPoints(162);
	}
	else if (E2->estPartante() && ptsE2 < 82) { //si E2 est partie mais est dedans
		if (E1->aLaBelote() || E2->aLaBelote())
			ptsE1 = ptsE1 + 20;
		E1->ajouterPoints(162);
	}
	plis.clear();
}

void Belotte::jeu() {

	cout << "Lancement de la methode  de jeu " << endl;

do {

	cout << "Boucle de partie " << endl;

	cout << "Création des cartes... " << endl;

	cout << "	-Vecteur";
	vector<Carte> vectCartes;
	cout <<"	[Done]" << endl;

	cout << "	-Init vars";
	int coul = 1;
	int val = 7;
	int count = 0;
	cout << "	[Done]" << endl;


	while (coul <= 4) { // coul <= carreau
		cout << "	-Boucle Couleur n°" << coul;
		while (val <= 14) {// val <= 14

			Carte c = Carte(Valeur(val), Couleur(coul), this);
			count++;
			cout << "carte num" << count << endl;
			vectCartes.push_back(c); //On créé le jeu de carte

			val=val+1;
		}
		cout << "	[Done]"<< endl;
		coul=coul+1;
		val=7;
	}

	cout << "[Done]"<<endl;
	cout << "Création des equipes ... ";

	Equipe E1(1, true);
	Equipe E2(2, false);

	cout << "[Done]"<<endl;
	cout << "Création des mains... " << endl;

	//initialisation des 4 mains :
	cout << "		Main 1";
	MainJoueur m1(joueurs[0]);
	cout << "	OK"<<endl;
	cout << "		Main 2";
	MainJoueur m2(joueurs[1]);
	cout << "	OK"<<endl;
	cout << "		Main 3";
	MainJoueur m3(joueurs[2]);
	cout << "	OK"<<endl;
	cout << "		Main 4";
	MainJoueur m4(joueurs[3]);
	cout << "	OK"<<endl;

	cout << "[Done]"<<endl;
	cout << "Distribution... ";

	//On distribue les cartes aléatoirement :
	cout << "	-Init vars";
	int i;
	unsigned int pos;
	srand ( time(NULL) );
	cout << "	OK"<< endl;

	cout << "	-Main 1" << endl;
	for (i = 0; i < 5; i++) {
		pos = rand() % vectCartes.size();
		m1.ajouterCarte(vectCartes[pos]);
		vectCartes.erase(vectCartes.begin()+pos);
		cout << "Carte " << i << endl;
	}
	cout << "	Envoi... " << endl;
	s->envoyer_main(m1, 0);
	cout << "	OK" << endl;
	for (i = 0; i < 5; i++) {
		pos = rand() % vectCartes.size();
		m2.ajouterCarte(vectCartes[pos]);
		vectCartes.erase(vectCartes.begin()+pos);
	}
	s->envoyer_main(m2, 1);
	for (i = 0; i < 5; i++) {
		pos = rand() % vectCartes.size();
		m3.ajouterCarte(vectCartes[pos]);
		vectCartes.erase(vectCartes.begin()+pos);
	}
	s->envoyer_main(m3, 2);
	for (i = 0; i < 5; i++) {
		pos = rand() % vectCartes.size();
		m4.ajouterCarte(vectCartes[pos]);
		vectCartes.erase(vectCartes.begin()+pos);
	}
	s->envoyer_main(m4, 3);

	cout << "[Done]"<<endl;
	cout <<"Tirage d'un carte...";

	pos = rand() % vectCartes.size();
	Carte car = vectCartes[pos];
	vectCartes.erase(vectCartes.begin()+pos);

	cout << "[Done]"<<endl;


	//On montre la carte à tous les joueurs et ils décident s'ils la choisissent :

	cout << "Choix de l'atout, init vars" << endl;
	bool prise = false;
	int num = 0;

	cout << "ok" << endl;

	while (!prise && num!= 4) {
		cout << "Porposition num " << num << endl;
		s->proposerCarte(car, num);
		cout << "Attente reponse" << endl;
		prise = this->attendre_reponse();
		cout << "reponse = " << prise<< endl;
		if (prise) {
			this->id_preneur = num;
			this->setAtout(car.getCouleur());
			this->atout_defini = true;
		}
		num++;
	}
	if (!prise) {
		num = 0;
		Couleur couleur_atout;
		while (!prise && num!=4) {
			s->proposerCarte(car, num);
			prise = this->attendre_reponse();
			if (prise) {
				s->demander_couleur(num);
				couleur_atout = this->attendre_couleur();
				this->id_preneur = num;
			}
			num++;
		}
		if (prise) {
			this->setAtout(couleur_atout);
			this->atout_defini = true;
			s->envoyer_atout_tous(this->atout);
		}
	}
	else {
		s->envoyer_atout_tous(this->atout);
	}

	if (this->atout_defini){ //une fois l'atout défini, on fini de distribuer :
		unJoueur(this->id_preneur).getEquipe()->setPartante(true);
		switch (this->id_preneur) {
			case 1 :
				m1.ajouterCarte(car);
				for (i = 0; i < 2; i++) {
					pos = rand() % vectCartes.size();
					m1.ajouterCarte(vectCartes[pos]);
					vectCartes.erase(vectCartes.begin()+pos);
				}
				joueurs[0]->setMain(&m1);
				s->envoyer_main(m1, 0);
				for (i = 0; i < 3; i++) {
					pos = rand() % vectCartes.size();
					m2.ajouterCarte(vectCartes[pos]);
					vectCartes.erase(vectCartes.begin()+pos);
				}
				joueurs[1]->setMain(&m2);
				s->envoyer_main(m2, 1);
				for (i = 0; i < 3; i++) {
					pos = rand() % vectCartes.size();
					m3.ajouterCarte(vectCartes[pos]);
					vectCartes.erase(vectCartes.begin()+pos);
				}
				joueurs[2]->setMain(&m3);
				s->envoyer_main(m3, 2);
				for (i = 0; i < 3; i++) {
					pos = rand() % vectCartes.size();
					m4.ajouterCarte(vectCartes[pos]);
					vectCartes.erase(vectCartes.begin()+pos);
				}
				joueurs[3]->setMain(&m4);
				s->envoyer_main(m4, 3);
				break;
			case 2:
				m2.ajouterCarte(car);
				for (i = 0; i < 2; i++) {
					pos = rand() % vectCartes.size();
					m2.ajouterCarte(vectCartes[pos]);
					vectCartes.erase(vectCartes.begin()+pos);
				}
				joueurs[1]->setMain(&m2);
				s->envoyer_main(m2, 1);
				for (i = 0; i < 3; i++) {
					pos = rand() % vectCartes.size();
					m2.ajouterCarte(vectCartes[pos]);
					vectCartes.erase(vectCartes.begin()+pos);
				}
				joueurs[0]->setMain(&m1);
				s->envoyer_main(m1, 0);
				for (i = 0; i < 3; i++) {
					pos = rand() % vectCartes.size();
					m3.ajouterCarte(vectCartes[pos]);
					vectCartes.erase(vectCartes.begin()+pos);
				}
				joueurs[2]->setMain(&m3);
				s->envoyer_main(m3, 2);
				for (i = 0; i < 3; i++) {
					pos = rand() % vectCartes.size();
					m4.ajouterCarte(vectCartes[pos]);
					vectCartes.erase(vectCartes.begin()+pos);
				}
				joueurs[3]->setMain(&m4);
				s->envoyer_main(m4, 3);
				break;
			case 3 :
				m3.ajouterCarte(car);
				for (i = 0; i < 2; i++) {
					pos = rand() % vectCartes.size();
					m3.ajouterCarte(vectCartes[pos]);
					vectCartes.erase(vectCartes.begin()+pos);
				}
				joueurs[2]->setMain(&m3);
				s->envoyer_main(m3, 2);
				for (i = 0; i < 3; i++) {
					pos = rand() % vectCartes.size();
					m2.ajouterCarte(vectCartes[pos]);
					vectCartes.erase(vectCartes.begin()+pos);
				}
				joueurs[1]->setMain(&m2);
				s->envoyer_main(m2, 1);
				for (i = 0; i < 3; i++) {
					pos = rand() % vectCartes.size();
					m1.ajouterCarte(vectCartes[pos]);
					vectCartes.erase(vectCartes.begin()+pos);
				}
				joueurs[0]->setMain(&m1);
				s->envoyer_main(m1, 0);
				for (i = 0; i < 3; i++) {
					pos = rand() % vectCartes.size();
					m4.ajouterCarte(vectCartes[pos]);
					vectCartes.erase(vectCartes.begin()+pos);
				}
				joueurs[3]->setMain(&m4);
				s->envoyer_main(m4, 3);
				break;
			case 4 :
				m4.ajouterCarte(car);
				for (i = 0; i < 2; i++) {
					pos = rand() % vectCartes.size();
					m4.ajouterCarte(vectCartes[pos]);
					vectCartes.erase(vectCartes.begin()+pos);
				}
				joueurs[3]->setMain(&m4);
				s->envoyer_main(m4, 3);
				for (i = 0; i < 3; i++) {
					pos = rand() % vectCartes.size();
					m2.ajouterCarte(vectCartes[pos]);
					vectCartes.erase(vectCartes.begin()+pos);
				}
				joueurs[1]->setMain(&m2);
				s->envoyer_main(m2, 1);
				for (i = 0; i < 3; i++) {
					pos = rand() % vectCartes.size();
					m3.ajouterCarte(vectCartes[pos]);
					vectCartes.erase(vectCartes.begin()+pos);
				}
				joueurs[2]->setMain(&m3);
				s->envoyer_main(m3, 2);
				for (i = 0; i < 3; i++) {
					pos = rand() % vectCartes.size();
					m1.ajouterCarte(vectCartes[pos]);
					vectCartes.erase(vectCartes.begin()+pos);
				}
				joueurs[0]->setMain(&m1);
				s->envoyer_main(m1, 0);
				break;
		}
		//On commence à jouer :
		for (int k = 0; k < 8; k++) {
			Pli * p = new Pli(this);
			int r = this->id_preneur;
			for (int l =0; l < 4; l++){
				Carte * carte_jouee;
				do {
					s->envoyer_main(*joueurs[r]->getMain(), r);
					s->envoyer_demande(3, r);
					*carte_jouee = attendre_carte();
				} while (!this->verifCarte(*carte_jouee));
				joueurs[r]->getMain()->retirerCarte(*carte_jouee);
				s->envoyer_main(*joueurs[r]->getMain(), r);
				p->ajouter_carte(*carte_jouee);
				if (*carte_jouee == this->plusHaute(p->getVectCarte())) {
					this->setPreneur(r);
				}
				r++;
				r = (r) % 4;
			}
			plis.push_back(*p);
		}
		finMene();
	}
} while (!this->partieFinie());
}

bool Belotte::partieFinie() {
	return (equipes[0]->getPts()>this->pointsMax || equipes[1]->getPts()>this->pointsMax);
}

void Belotte::wait (int secondes)
{
  clock_t endwait;
  endwait = clock () + secondes * CLOCKS_PER_SEC ;
  while (clock() < endwait) {}
}

bool Belotte::attendre_reponse() {
	int i = 0;
	while (this->rep == 0) {
		wait(3);
		i++;
		if (i == 10) {
			cout << "Erreur : réponse non arrivée" << endl;
			exit(0);
		}
	}
	int r = rep;
	this->rep = 0;
	return (r);
}

Carte Belotte::attendre_carte() {
	int i = 0;
	while (this->c == NULL) {
		wait(3);
		i++;
		if (i == 10) {
			cout << "Erreur : carte non arrivée" << endl;
			exit(0);
		}
	}
	return *(this->c);
}

Couleur Belotte::attendre_couleur() {
	int i = 0;
	while (this->coul == NULL) {
		wait(3);
		i++;
		if (i == 10) {
			cout << "Erreur : carte non arrivée" << endl;
			exit(0);
		}
	}
	return *(this->coul);
}

void Belotte::retour_reponse(bool rep) {
	this->rep = rep;
}

void Belotte::retour_carte(Carte car) {
	this->c = &car;
}

void Belotte::retour_couleur(Couleur coul) {
	this->coul = &coul;
}
