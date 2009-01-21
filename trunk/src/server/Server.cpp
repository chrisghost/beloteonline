#include "Server.h"

struct login_s // Structure pour les transferts de données liées au login
{
    string log;
};

sf::Packet& operator <<(sf::Packet& Packet, login_s& pl)
{
    return Packet << pl.log;
}

sf::Packet& operator >>(sf::Packet& Packet, login_s& pl)
{
    return Packet >> pl.log;
}

////////////////////////////////////////////////////////////

Server::Server(unsigned short Port)
{
    if (!sServer.Listen(Port))
        return;
    std::cout << "Server is listening to port " << Port << ", waiting for connections... " << std::endl;

    sf::IPAddress ClientAddress;
    sf::SocketTCP Client;
    sServer.Accept(Client, &ClientAddress);
    std::cout << "Client connected : " << ClientAddress << std::endl;
    
    sf::Packet RegularPacket;
    if (sServer.Receive(RegularPacket) != sf::Socket::Done)
        return ;

    login_s lsd;
    if (RegularPacket >> lsd)
    {
        cout << "Login : " << lsd.log << endl;
    }
}

bool Server::connecter(){
	sf::Packet RegularPacket;
    if (sServer.Receive(RegularPacket) != sf::Socket::Done)
        return false;

    login_s lsd;
    if (RegularPacket >> lsd)
    {
        cout << "Login : " << lsd.log << endl;
    }
    return true;
}

Server::~Server()
{
}
