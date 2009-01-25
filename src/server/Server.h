#ifndef SERVER_H_
#define SERVER_H_

#include <string>
#include <iostream>
#include <SFML/Network.hpp>

using namespace std;
class Server
{
public:
	Server(unsigned short Port);
	virtual ~Server();
	//methode pour afficher à chaque joueur la carte pour qu'ils choisissent si ils la prennent ou non (renvoie l'adresse du joueur ou null si personne la prend)
private:
	sf::SocketTCP sServer;
	unsigned short Port;
};

#endif /*SERVER_H_*/
