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

    	this->Connexion();

}

bool Client::Connexion(){
        string login;
        cout << "Entrez le login : ";
        cin >> login;
        cin.ignore(1000, '\n');

    	packet_client pk = {1 , login , id_j , SEPT , CARREAU , false , CARREAU};

        sf::Packet Packet;

        // << pl.id << pl.log << pl.id_j << pl.val << pl.couleur << pl.reponse << pl.couleur_att;

        Packet << pk;
    return (sClient.Send(Packet) == sf::Socket::Done);
    // RECUPERE LE PACKET DEPUIS LE SERVER AVEC L ID JOUEUR
}
bool Client::envoyer_carte(Carte c){// ID = 2
	packet_client pk = {2 , "" , id_j , c.getValeur() , c.getCouleur() , false , CARREAU};
    sf::Packet Packet;

    Packet << pk;

    return (sClient.Send(Packet) == sf::Socket::Done);
}

Client::~Client()
{
	sClient.Close();
}
