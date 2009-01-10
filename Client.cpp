#include "Client.h"


Client::Client(unsigned short Port)
{
	this->Port = Port;
    do
    {
        cout << "Type address or name of the server to connect to : ";
        cin  >> ServerAddress;
    }
    while (!ServerAddress.IsValid());
	
    if (!Client.Connect(Port, ServerAddress))
        return;
    cout << "Connected to server " << ServerAddress << endl;

}

bool Client::Connexion(string login, string mdp){
	login pLogin;
	pLogin.log = login;
	pLogin.mdp = mdp;
	
    sf::Packet RegularPacket;
    RegularPacket << pLogin;
    if (Client.Send(RegularPacket) != sf::Socket::Done)
        return;

    std::cout << "Login sent : " << std::endl;
    std::cout << pLogin.log << ":" << pLogin.mdp << endl;
	
}

Client::~Client()
{
	Client.Close();
}
