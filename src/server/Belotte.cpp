/*
 * File: Belotte.cpp
 * Author: Michael
 *
 * Created on January 21, 2009, 5:37 PM
 */

#include "Belotte.h"
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
	this->preneur = preneur;
}

void Belotte::setAtout(Couleur atout) {
	this->atout = atout;
}

void Belotte::ajouterJoueur(Joueur j) {
	joueurs.push_back(j);
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
		Joueur j(-1, ip, e, "");
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
			Carte c = Carte(Valeur(val), Couleur(coul), this);
			vectCartes.push_back(c); //On créé le jeu de carte
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
	MainJoueur m1(&joueurs[0]);
	MainJoueur m2(&joueurs[1]);
	MainJoueur m3(&joueurs[2]);
	MainJoueur m4(&joueurs[3]);

	//On distribue les cartes aléatoirement :
	int i;
	unsigned int pos;
	srand ( time(NULL) );
	for (i = 0; i < 5; i++) {
		pos = rand() % vectCartes.size();
		m1.ajouterCarte(vectCartes[pos]);
		vectCartes.erase(vectCartes.begin()+pos);
	}
	s->envoyer_main(m1, 0);
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
	pos = rand() % vectCartes.size();
	Carte car = vectCartes[pos];
	vectCartes.erase(vectCartes.begin()+pos);

	//On montre la carte à tous les joueurs et ils décident s'ils la choisissent :
	bool prise = false;
	int num = 0;
	while (!prise && num!= 4) {
		s->proposerCarte(car, num);
		prise = this->attendre_reponse();
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
		switch (this->id_preneur) {
			case 1 :
				m1.ajouterCarte(car);
				for (i = 0; i < 2; i++) {
					pos = rand() % vectCartes.size();
					m1.ajouterCarte(vectCartes[pos]);
					vectCartes.erase(vectCartes.begin()+pos);
				}
				joueurs[0].setMain(&m1);
				s->envoyer_main(m1, 0);
				for (i = 0; i < 3; i++) {
					pos = rand() % vectCartes.size();
					m2.ajouterCarte(vectCartes[pos]);
					vectCartes.erase(vectCartes.begin()+pos);
				}
				joueurs[1].setMain(&m2);
				s->envoyer_main(m2, 1);
				for (i = 0; i < 3; i++) {
					pos = rand() % vectCartes.size();
					m3.ajouterCarte(vectCartes[pos]);
					vectCartes.erase(vectCartes.begin()+pos);
				}
				joueurs[2].setMain(&m3);
				s->envoyer_main(m3, 2);
				for (i = 0; i < 3; i++) {
					pos = rand() % vectCartes.size();
					m4.ajouterCarte(vectCartes[pos]);
					vectCartes.erase(vectCartes.begin()+pos);
				}
				joueurs[3].setMain(&m4);
				s->envoyer_main(m4, 3);
				break;
			case 2:
				m2.ajouterCarte(car);
				for (i = 0; i < 2; i++) {
					pos = rand() % vectCartes.size();
					m2.ajouterCarte(vectCartes[pos]);
					vectCartes.erase(vectCartes.begin()+pos);
				}
				joueurs[1].setMain(&m2);
				s->envoyer_main(m2, 1);
				for (i = 0; i < 3; i++) {
					pos = rand() % vectCartes.size();
					m2.ajouterCarte(vectCartes[pos]);
					vectCartes.erase(vectCartes.begin()+pos);
				}
				joueurs[0].setMain(&m1);
				s->envoyer_main(m1, 0);
				for (i = 0; i < 3; i++) {
					pos = rand() % vectCartes.size();
					m3.ajouterCarte(vectCartes[pos]);
					vectCartes.erase(vectCartes.begin()+pos);
				}
				joueurs[2].setMain(&m3);
				s->envoyer_main(m3, 2);
				for (i = 0; i < 3; i++) {
					pos = rand() % vectCartes.size();
					m4.ajouterCarte(vectCartes[pos]);
					vectCartes.erase(vectCartes.begin()+pos);
				}
				joueurs[3].setMain(&m4);
				s->envoyer_main(m4, 3);
				break;
			case 3 :
				m3.ajouterCarte(car);
				for (i = 0; i < 2; i++) {
					pos = rand() % vectCartes.size();
					m3.ajouterCarte(vectCartes[pos]);
					vectCartes.erase(vectCartes.begin()+pos);
				}
				joueurs[2].setMain(&m3);
				s->envoyer_main(m3, 2);
				for (i = 0; i < 3; i++) {
					pos = rand() % vectCartes.size();
					m2.ajouterCarte(vectCartes[pos]);
					vectCartes.erase(vectCartes.begin()+pos);
				}
				joueurs[1].setMain(&m2);
				s->envoyer_main(m2, 1);
				for (i = 0; i < 3; i++) {
					pos = rand() % vectCartes.size();
					m1.ajouterCarte(vectCartes[pos]);
					vectCartes.erase(vectCartes.begin()+pos);
				}
				joueurs[0].setMain(&m1);
				s->envoyer_main(m1, 0);
				for (i = 0; i < 3; i++) {
					pos = rand() % vectCartes.size();
					m4.ajouterCarte(vectCartes[pos]);
					vectCartes.erase(vectCartes.begin()+pos);
				}
				joueurs[3].setMain(&m4);
				s->envoyer_main(m4, 3);
				break;
			case 4 :
				m4.ajouterCarte(car);
				for (i = 0; i < 2; i++) {
					pos = rand() % vectCartes.size();
					m4.ajouterCarte(vectCartes[pos]);
					vectCartes.erase(vectCartes.begin()+pos);
				}
				joueurs[3].setMain(&m4);
				s->envoyer_main(m4, 3);
				for (i = 0; i < 3; i++) {
					pos = rand() % vectCartes.size();
					m2.ajouterCarte(vectCartes[pos]);
					vectCartes.erase(vectCartes.begin()+pos);
				}
				joueurs[1].setMain(&m2);
				s->envoyer_main(m2, 1);
				for (i = 0; i < 3; i++) {
					pos = rand() % vectCartes.size();
					m3.ajouterCarte(vectCartes[pos]);
					vectCartes.erase(vectCartes.begin()+pos);
				}
				joueurs[2].setMain(&m3);
				s->envoyer_main(m3, 2);
				for (i = 0; i < 3; i++) {
					pos = rand() % vectCartes.size();
					m1.ajouterCarte(vectCartes[pos]);
					vectCartes.erase(vectCartes.begin()+pos);
				}
				joueurs[0].setMain(&m1);
				s->envoyer_main(m1, 0);
				break;
		}
		//On commence à jouer :
		for (int k = 0; k < 8; k++) {
			Pli * p = new p(&this);
			int r = this->id_preneur;
			for (int l =0; l < 4; l++){
				do {
					s->envoyer_demande(3, r);
					Carte carte_jouee = attendre_carte();
				} while (!this->verifCarte(carte_jouee));
				joueurs[r].getMain()->retirerCarte(carte_jouee);
				s->envoyer_main(joueurs[r].getMain());
				p->ajouter_carte(carte_jouee);
				if (carte_jouee == this->plusHaute(p->getVectCarte())) {
					this->id_preneur = r;
				}
				r = (r++) % 4;
			}
			plis.push_back(p);
		}

	}
}

void wait (int secondes)
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
