#ifndef CLIENT_H_
#define CLIENT_H_

#include <string.h>
#include <iostream>

using namespace std;

class Client
{
public:
	Client(unsigned short Port);
	virtual ~Client();
	bool Connexion(string login, string mdp);
private:
	sf::SocketTCP Client;
	unsigned short Port;
	sf::IPAddress ServerAddress;
};

struct login
{
    std::string log;
    std::string mdp;
};

sf::Packet& operator <<(sf::Packet& Packet, const login& pl)
{
    return Packet << pl.log << pl.mdp;
}

sf::Packet& operator >>(sf::Packet& Packet, const login& pl)
{
    return Packet >> pl.log >> pl.mdp;
}

#endif /*CLIENT_H_*/
