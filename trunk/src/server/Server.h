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
	bool connecter();
private:
	sf::SocketTCP sServer;
	unsigned short Port;
};

#endif /*SERVER_H_*/
