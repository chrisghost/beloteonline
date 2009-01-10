#include <string>
#include <iostream>
#include <SFML/Network.hpp>

using namespace std;
#ifndef CLIENT_H_
#define CLIENT_H_


class Client
{
public:
	Client(unsigned short Port);
	virtual ~Client();
	bool Connexion(string login, string mdp);
private:
	sf::SocketTCP sClient;
	unsigned short Port;
	sf::IPAddress ServerAddress;
};

#endif /*CLIENT_H_*/
