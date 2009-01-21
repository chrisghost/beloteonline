#ifndef CLIENT_H_
#define CLIENT_H_

#include <string>
#include <iostream>
#include <SFML/Network.hpp>


using namespace std;
class Client
{
public:
	Client(unsigned short Port);
	virtual ~Client();
	bool Connexion(string login);
private:
	sf::SocketTCP sClient;
	unsigned short Port;
	sf::IPAddress ServerAddress;
};

#endif /*CLIENT_H_*/
