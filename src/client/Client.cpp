#include "Client.h"

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
        //return;
    cout << "Connected to server " << ServerAddress << endl;
    
    string login;
    
    cout << "Entrez le login : ";
    cin >> login;
    
    this->Connexion(login);

}

bool Client::Connexion(string login){
	login_s plogin;

	plogin.log = login;

    sf::Packet RegularPacket;
    RegularPacket << plogin;
    if (sClient.Send(RegularPacket) != sf::Socket::Done)
        return false;

    cout << "Login sent : " << endl;
    cout << plogin.log << endl;

    return true;
}

Client::~Client()
{
	sClient.Close();
}
