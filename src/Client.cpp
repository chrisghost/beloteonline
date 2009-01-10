#include "Client.h"
#include "netstruct.h"

Client::Client(unsigned short Port)
{
	this->Port = Port;
    do
    {
        cout << "Type address or name of the server to connect to : ";
        cin  >> ServerAddress;
    }
    while (!ServerAddress.IsValid());
	
    if (!sClient.Connect(Port, ServerAddress))
        return;
    cout << "Connected to server " << ServerAddress << endl;

}

bool Client::Connexion(string login, string mdp){
    struct login plogin{login, mdp};
	
    sf::Packet RegularPacket;
    RegularPacket << plogin;
    if (sClient.Send(RegularPacket) != sf::Socket::Done)
        return;

    std::cout << "Login sent : " << std::endl;
    std::cout << plogin.log << ":" << plogin.mdp << endl;
	
}

Client::~Client()
{
	sClient.Close();
}
