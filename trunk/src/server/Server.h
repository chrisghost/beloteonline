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
	Server(unsigned short Port, Belotte * b);
	virtual ~Server();
	void proposerCarte(Carte c, int id);
	void demander_couleur(int id);
	void envoyer_liste_joueurs(int id_client, int id_j, string l);
	void envoyer_main(MainJoueur m, int idj);
	void envoyer_message(string mess, int idj);
	void envoyer_demande(int demande, int idj);

	void envoyer_atout_tous(Couleur atout);
	void envoyer_atout(Couleur atout, int idj);

	void envoyer_validation(bool Valid, int idj);

	void envoyer_points_tous(int points[2]);
	void envoyer_points(int points[2], int idj);

private:
	Belotte * b;
	sf::SocketTCP sServer;
	unsigned short Port;
	sf::IPAddress clients[4];
	sf::SocketTCP Client[4];
	int nb_cl_connected;
	string login[4];
};

#endif /*SERVER_H_*/
