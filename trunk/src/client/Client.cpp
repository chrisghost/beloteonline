#include "Client.h"
#include "../netstruct.h"
////////////////////////////////////////////////////////////

Client::Client(unsigned short Port)
{
	ig = new IG();
	points[0] = 0;
	points[1] = 1;
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

    	if(!this->Connexion())
    		std::cout << "Erreur à la connexion" << endl;
    	bool continuer = true;

    	while (continuer){

    		sf::Packet packet;
    		if (sClient.Receive(packet) == sf::Socket::Done){
    			packet_serveur st;
    			packet >> st;

    			switch (st.id){
    			case 1 ://Joueur
    					login[st.id_j] = st.log;
    				break;
    			case 2 ://message
						ig->afficher_message(st.message);
    				break;
    			case 3 ://carte
						Carte c(st.val,st.couleur,null);
						ig->afficher_uneCarte(c);
						int i = ig->demande_rep("Prendre la carte?(1 = oui / 2 = non)");

    				break;
    			case 4 :{//demande
						if(st.demande == 2) // Choisir atout
							Couleur c = ig->demander_couleur_atout();
						else if(st.demande == 3){ // Jouer une carte
							Carte c = ig->demande_Carte(main);}
    				break;}
    			case 5 ://atout
						this->atout = st.couleur_att;
    				break;
    			case 6 ://validation
						if(st.valid)
							ig->afficher_message("ok");
						else
							ig->afficher_message("erreur");
    				break;
    			case 7 ://cartes
					unsigned int j = 0;
					for(j = 0; j < st.nb_cartes; j++){
						Carte cc(st.vals[j], st.couls[j], null);
						this->main[j] = cc;}
					while (j<8){
						Carte cc(zero, rien, null);
						this->main[j] = cc;}
    				break;
    			case 8 ://points
						this->points[0] = st.points[0];
						this->points[1] = st.points[1];
    				break;
    			}
    		}

    	}
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

bool Client::envoyer_reponse(bool rep){
	packet_client pk = {3 , "" , id_j , zero , rien , rep , rien};
    sf::Packet Packet;

    Packet << pk;

    return (sClient.Send(Packet) == sf::Socket::Done);
}

bool Client::envoyer_couleur(Couleur coul){
	packet_client pk = {4 , "" , id_j , zero , rien , rep , coul};
    sf::Packet Packet;

    Packet << pk;

    return (sClient.Send(Packet) == sf::Socket::Done);
}


Client::~Client()
{
	sClient.Close();
}
