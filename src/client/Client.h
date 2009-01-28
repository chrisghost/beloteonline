#ifndef CLIENT_H_
#define CLIENT_H_

#include <string>
#include <iostream>
#include <SFML/Network.hpp>
//#include "../server/carte.h"
//#include "../server/Belotte.h"
#include "IG.h"
//#include "../server/deftype.h"

using namespace std;
class Client
{
public:
	Client(unsigned short Port);		// Cnstructeur
	virtual ~Client();					// Desctructeur
	bool Connexion();					// Connexion du client au serveur
	bool envoyer_carte(Carte c);		// Enviyer la carte c au serveur
	bool envoyer_couleur(Couleur coul);	// Envoyer la couleur coul au serveur
	bool envoyer_reponse(bool rep);		// Envoyer une réponse de type booléen au serveur
private:
	int id_j;
	sf::SocketTCP sClient;
	unsigned short Port;
	sf::IPAddress ServerAddress;

	IG * ig;

	string login[4];
	Couleur atout;
	vector<Carte> main;
	int points[2];
};

#endif /*CLIENT_H_*/
