#ifndef IG_H_
#define IG_H_

using namespace std;
#include <string>

#include "../server/carte.h"
#include "../server/Joueur.h"

class IG
{
public:
	IG();
	virtual ~IG();
	int demande_rep(string message);
	Carte demande_Carte(vector<Carte>);
	void afficher_Carte(Carte c);
	void afficher_message(string mess);
	void afficher_liste_joueurs(vector<Joueur> joueur);
	void afficher_pli(vector<Carte> pli);
	Couleur demander_couleur_atout();
	void afficher_uneCarte(Carte c);
	void afficher_joueur(Joueur joueur);
};

#endif
