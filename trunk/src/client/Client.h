#ifndef CLIENT_H_
#define CLIENT_H_

#include <string>
#include <iostream>
#include <SFML/Network.hpp>
#include "../server/carte.h"
//#include "../server/deftype.h"

using namespace std;
class Client
{
public:
	Client(unsigned short Port);
	virtual ~Client();
	bool Connexion();
	bool envoyer_carte(Carte c);
private:
	int id_j;
	sf::SocketTCP sClient;
	unsigned short Port;
	sf::IPAddress ServerAddress;
};

#endif /*CLIENT_H_*/
