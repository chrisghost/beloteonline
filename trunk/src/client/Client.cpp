#include "Client.h"
#include "../netstruct.h"
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

    cout << "Connexion à " << ServerAddress << " sur le port " << Port << endl;

    if (sClient.Connect(Port, ServerAddress)){
        cout << "Erreur a la connexion !" << endl;
        return;}
    cout << "Connected to server " << ServerAddress << endl;

    	sf::Packet re;
    	if( sClient.Receive(re) == sf::Socket::Done){
    		packet_serveur pk;
    		re >> pk;
			this->id_j = pk.id_j;
    	}

    	this->Connexion();
}

bool Client::Connexion(){
        string login;
        cout << "Entrez le login : ";
        cin >> login;
        cin.ignore(1000, '\n');

    	packet_client pk = {1 , login , this->id_j , sept, carreau , false , carreau};

        sf::Packet Packet;

        Packet << pk;
    return (sClient.Send(Packet) == sf::Socket::Done);
}
bool Client::envoyer_carte(Carte c){// ID = 2
	packet_client pk = {2 , "" , id_j , c.getValeur() , c.getCouleur() , false , carreau};
    sf::Packet Packet;

    Packet << pk;

    return (sClient.Send(Packet) == sf::Socket::Done);
}

Client::~Client()
{
	sClient.Close();
}
