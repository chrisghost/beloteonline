#include <string>
#include <iostream>
#include <SFML/Network.hpp>

using namespace std;

#ifndef SERVER_H_
#define SERVER_H_

class Server
{
public:
	Server(unsigned short Port);
	virtual ~Server();
	bool connecter(string l, string p);
private:
	sf::SocketTCP sServer;
	unsigned short Port;
};

#endif /*SERVER_H_*/
