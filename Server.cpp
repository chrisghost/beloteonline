#include "Server.h"

Server::Server()
{
    if (!Server.Listen(Port))
        return;
    std::cout << "Server is listening to port " << Port << ", waiting for connections... " << std::endl;
	
	sf::IPAddress ClientAddress;
    sf::SocketTCP Client;
    Server.Accept(Client, &ClientAddress);
    std::cout << "Client connected : " << ClientAddress << std::endl;
}

bool Server::connecter(string l, string p){
	sf::Packet RegularPacket;
    if (Server.Receive(RegularPacket) != sf::Socket::Done)
        return;

    Character C1;
    if (RegularPacket >> C1)
    {
}

Server::~Server()
{
}
