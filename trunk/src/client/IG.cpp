#include "IG.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

IG::IG() {

    sf::RenderWindow App(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "SFML Graphics");
	const sf::Input& Input = App.GetInput();

    sf::Sprite fond;
    sf::Image back;
    back.LoadFromFile("images/fond.png");
    fond.SetImage(back);

	App.SetFramerateLimit(60);

	while (App.IsOpened())
	{


	App.Draw(fond);
	App.Display();
	}

}


IG::~IG() {

}

int IG::demande_rep(string message){
	this->afficher_message(message);
	int i;
	cin >> i;
	return i;
}

Carte IG::demande_Carte(vector<Carte> main){
	//affiche les 8 Cartes de la main
	cout << "Affichage de la main :" << endl;
		for (int i=0;i < main.size();i++){
			cout << "Carte n°" << i << endl;
			afficher_uneCarte(main[i]);
		}
	cout << "Entrez le numéro de la carte :";
	int i = 0;
	cin >> i;
	return main[i];
}

void IG::afficher_Carte(Carte c){

	cout << "La Carte du joueur ";
	cout << c.getJoueur();
	cout <<	" est le ";
	cout << c.getValeur();
	cout << " de ";
	cout << c.getCouleur()<< endl;

}


void IG::afficher_message(string mess) {

	cout << "Message: ";
	cout << mess;

}


void IG::afficher_liste_joueurs(vector<Joueur> joueur) {
	//affiche les joueurs présents dans la partie
	cout << "Les joueurs présents sont ";
	for (int i=0; i<=joueur.size(); i++) {
		afficher_joueur(joueur[i]);
	}
}


void IG::afficher_pli(vector<Carte> pli){
	//affiche les Cartes jouées dans le pli
	cout << "Les Cartes du pli sont :" << endl;
	for (int i=0; i<=pli.size(); i++) {
		afficher_Carte(pli[i]);
	}
}


Couleur IG::demander_couleur_atout() {
	bool ok = false;
	Couleur c;
	do {
		int coul;
		cout << "Veuillez choisir une couleur: (pique=1,coeur=2,trefle=3,carreau=4)" << endl;
		cin >> coul;
		c = Couleur (coul);
		switch (c) {
		case 1 :
			ok = true;
			break;
		case 2 :
			ok = true;
			break;
		case 3 :
			ok = true;
			break;
		case 4 :
			ok =true;
			break;
		default :
			break;
		}
	} while (!ok);
	return (c);
}


void IG::afficher_uneCarte(Carte c){

	cout << "La Carte est le ";
	cout << c.getValeur();
	cout << " de ";
	cout << c.getCouleur() << endl;
}


void IG::afficher_joueur(Joueur j) {

	cout << "Le joueur ";
	cout << j.getLogin();
	cout << "a l'id ";
	cout << j.getId() << endl;
}
