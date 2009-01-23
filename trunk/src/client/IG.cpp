#include "IG.h"

IG::IG() {

}


IG::~IG() {

}


Carte IG::demande_carte(vector<carte> main){
	//affiche les 8 cartes de la main
	int n=1;
	cout << "Affichage de la main :" << endl;
		for (i=0;i<main.size();i++){
			cout << "Carte n°" << n << endl;
			afficher_unecarte(main[i]);
			n=n+1;
		}
}

void IG::afficher_carte(Carte c){

	cout << "La carte du joueur ";
	cout << c.id_joueur;
	cout <<	" est le ";
	cout << c.val;
	cout << " de ";
	cout << c.coul << endl;

}


void IG::afficher_message(string mess) {

	cout << "Message: ";
	cout << mess;

}


void IG::afficher_liste_joueurs(vector<joueur> joueur) {
	//affiche les joueurs présents dans la partie
	cout << "Les joueurs présents sont ";
	for (i=0; i<=joueur.size; i++) {
		afficher_joueur(joueur[i]);
	}
}


void IG::afficher_pli(vector<carte> pli){
	//affiche les cartes jouées dans le pli
	cout << "Les cartes du pli sont :" << endl;
	for (i=0; i<=pli.size; i++) {
		afficher_carte(pli[i]);
	}
}


Couleur IG::demander_couleur_atout() {

	Couleur coul;
	cout << "Veuillez choisir une couleur: " << endl;
	cout << carte.Couleur << endl;
	cin >> coul;
	return (coul);
}


void IG::afficher_unecarte(Carte c){

	cout << "La carte est le ";
	cout << c.val;
	cout << " de ";
	cout << c.coul << endl;
}


void IG::afficher_joueur(Joueur j) {

	cout << "Le joueur ";
	cout << j.login;
	cout << "a l'id ";
	cout << j.id;
}
