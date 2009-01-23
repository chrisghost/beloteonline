#ifndef IG_H_
#define IG_H_

using namespace std;


class IG
{
public:
	IG();
	virtual ~IG();
	Carte demande_carte(vector<carte>);
	void afficher_carte(Carte c);
	void afficher_message(string mess);
	void afficher_liste_joueurs();
	void afficher_pli();
	Couleur demander_couleur_atout();
	void afficher_unecarte();
	void afficher_joueur();
};
