#ifndef SERVER_H_
#define SERVER_H_

#include <string>
#include <iostream>
#include <SFML/Network.hpp>
#include "carte.h"
#include "Belotte.h"


using namespace std;
class Server
{
public:
	Server(unsigned short Port, Belotte * b);		// Constructeur
	virtual ~Server();								// Destructeur
	void proposerCarte(Carte c, int id);			// Envoyer une proposition de carte c au client d'id : id
	void demander_couleur(int id);					// Demander au client id de choisir une couleur
	void envoyer_liste_joueurs();					// Envoyer la liste des joueurs aux clients
	void envoyer_main(MainJoueur m, int idj);		// Envoyer une main à un client
	void envoyer_message(string mess, int idj);		// Envoyer un message à un client
	void envoyer_demande(int demande, int idj);		// Envoyer une demande de type demande au client idj

	void envoyer_atout_tous(Couleur atout);			// Envoyer la couleur de l'atout à tous les clients
	void envoyer_atout(Couleur atout, int idj);		// Envoyer la couleur de l'atout à un client

	void envoyer_validation(bool Valid, int idj);	// Envoyer une validation de type booléen

	void envoyer_points_tous(int points[2]);		// Envoyer les points des équipes à tous les clients
	void envoyer_points(int points[2], int idj);	// Envoyer les points des équipes à un client idj

private:
	Belotte * b;
	sf::SocketTCP sServer;
	unsigned short Port;
	sf::IPAddress clients[4];
	sf::SocketTCP Client[4];
	int nb_cl_connected;

	int nb_log;
	string login[4];
};

#endif /*SERVER_H_*/
