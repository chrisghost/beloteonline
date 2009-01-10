#include "Server.h"
#include "Client.h"

Server::Server(unsigned short Port)
{
    if (!sServer.Listen(Port))
        return;
    std::cout << "Server is listening to port " << Port << ", waiting for connections... " << std::endl;
	
    sf::IPAddress ClientAddress;
    sf::SocketTCP Client;
    sServer.Accept(Client, &ClientAddress);
    std::cout << "Client connected : " << ClientAddress << std::endl;
}

bool Server::connecter(string l, string p){
	sf::Packet RegularPacket;
    if (sServer.Receive(RegularPacket) != sf::Socket::Done)
        return false;

    struct login lsd;
    if (RegularPacket >> l)
    {
        cout << "Login : " << lsd.log << "  Password : " << lsd.mdp << endl;
    }
    return true;
}

Server::~Server()
{
}
