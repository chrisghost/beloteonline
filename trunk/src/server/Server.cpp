#include "Server.h"

#ifndef NETS
#include "../netstruct_server.h"
#endif
#ifndef NET
#include "../netstruct_client.h"
#endif

////////////////////////////////////////////////////////////

Server::Server(unsigned short Port, Belotte * b)
{
	this->b = b;

	for (int i=0; i<4;i++)
		login[i] = "";

	// Create a socket for listening to incoming connections
	if (!sServer.Listen(Port))
		return;
	std::cout << "Listening to port " << Port << ", waiting for connections..." << std::endl;

	nb_cl_connected = 0;
	nb_log = 0;

	// Create a selector for handling several sockets (the listener + the socket associated to each client)
	sf::SelectorTCP Selector;

	// Add the listener
	Selector.Add(sServer);


	Equipe * e1 = new Equipe(1, false);
	Equipe * e2 = new Equipe(2, false);

/*	Client[0] = sf::SocketTCP();
	Client[1] = sf::SocketTCP();
	Client[2] = sf::SocketTCP();
	Client[3] = sf::SocketTCP();*/


	// Loop while... we close the program :)
	while (true)
	{
		cout << "Boucle principale starts " << endl;

		if(nb_cl_connected == 4 && this->nb_log == 4){
			cout << "Lancement de la partie ..." << endl;
			b->jeu();}

		// Get the sockets ready for reading
		unsigned int NbSockets = Selector.Wait();

		cout << "Boucle! de " << NbSockets  << endl;


		// We can read from each returned socket
		for (unsigned int i = 0; i < NbSockets; ++i)
		{
			// Get the current socket
			sf::SocketTCP Socket = Selector.GetSocketReady(i);

			cout << "Packet recu!0" << endl;

			if (Socket == sServer)
			{
				// If the listening socket is ready, it means that we can accept a new connection
				sf::IPAddress Address;

				sf::SocketTCP tmp;

				sServer.Accept(tmp, &Address);
				std::cout << "Client connected ! (" << Address << ")" << std::endl;

				Client[nb_cl_connected] = tmp;

				clients[nb_cl_connected] = Address;

				if(nb_cl_connected<2){
					Joueur * j = new Joueur(nb_cl_connected, e1, "");
					b->ajouterJoueur(j);}
				else{
					Joueur * j = new Joueur(nb_cl_connected, e2, "");
					b->ajouterJoueur(j);}

				packet_serveur pk = {1 , "" , nb_cl_connected , "", sept, carreau, 0, carreau, false, 0,
						{sept,sept,sept,sept,sept,sept,sept,sept},
						{carreau,carreau,carreau,carreau,carreau,carreau,carreau,carreau},{0,0}};
		        sf::Packet Packet;
		        Packet << pk;
				Client[nb_cl_connected].Send(Packet);

				Selector.Add(Client[nb_cl_connected]);

				nb_cl_connected++;


			}
			else
			{cout << "Packet recu!1" << endl;
				// Else, it is a client socket so we can read the data he sent
                sf::Packet Packet;
                if (Socket.Receive(Packet) == sf::Socket::Done)
                {
                	cout << "Packet recu!2" << endl;
			        packet_client st;
                    Packet >> st;

                    switch (st.id){
						case 1 ://Connexion
							std::cout << "Le client " << st.id_j <<" s'apelle " << st.log << std::endl;
							login[st.id_j] = st.log;
							nb_log++;
							break;
						case 2 :{//Carte
							std::cout << "Le client " << st.log << "("<< st.id_j << ") envoie la carte "<< st.val
								<< " de " << st.couleur << std::endl;
							Carte cc(st.val, st.couleur, this->b);
							b->retour_carte(cc);
							break;}
						case 3 ://Reponse
							std::cout << "Le client " << st.log << "("<< st.id_j << ") répond "<< st.reponse << std::endl;
							b->retour_reponse(st.reponse);
							break;
						case 4 ://Couleur attout
							std::cout << "Le client " << st.log << "("<< st.id_j << ") envoie la couleur "<<
								st.couleur << std::endl;
							b->retour_couleur(st.couleur);
							break;


                    }
                }
                else
                {
                	cout << "REMOVE!!!!" << endl;
                    // Error : we'd better remove the socket from the selector
                    Selector.Remove(Socket);
                }
			}
			cout << "Boucle for finie" << endl;
		}
	cout << "Boucle principale finie" << endl;
	}

	cout << "Sortie inatendue!" << endl;
}

Server::~Server()
{
}
void Server::proposerCarte(Carte c, int id){
	//    return Packet << pl.id << pl.log << pl.id_j << pl.message << pl.val << pl.couleur << pl.demande << pl.couleur_att
	//<< pl.valid << pl.nb_cartes << pl.vals << pl.couls << pl.points;
	packet_serveur pk = { 3, "" , id , "", c.getValeur() , c.getCouleur(), 1, carreau, false ,0,
			{sept,sept,sept,sept,sept,sept,sept,sept},
			{carreau,carreau,carreau,carreau,carreau,carreau,carreau,carreau},{0,0}};
    sf::Packet Packet;

    Packet << pk;

    if (!Packet)
    	cout << "Erreur packet " << endl;

    if(Packet)
    	cout << "Packet OK" << endl;

    if(!Client[id].IsValid())
    	cout << "Socket invalide" << endl;

	if(this->Client[id].Send(Packet) == sf::Socket::Done)
		cout << "Transfert OK" << endl;
	else
		cout << "Erreur de transfert" << endl;

}

void Server::demander_couleur(int id){

	packet_serveur pk = { 4, "" , id , "", sept , carreau, 2, carreau, false ,0,
			{sept,sept,sept,sept,sept,sept,sept,sept},
			{carreau,carreau,carreau,carreau,carreau,carreau,carreau,carreau},{0,0}};
    sf::Packet Packet;

    Packet << pk;

	Client[id].Send(Packet);

}

void Server::envoyer_liste_joueurs(){

	for(int i=0; i<4;i++){
		for(int j=0; j<4;j++){

			packet_serveur pk = { 1, login[j] , j , "", sept , carreau, 2, carreau, false ,0,
					{sept,sept,sept,sept,sept,sept,sept,sept},
					{carreau,carreau,carreau,carreau,carreau,carreau,carreau,carreau},{0,0}};
			sf::Packet Packet;

			Packet << pk;

			Client[i].Send(Packet);
		}
	}
}

void Server::envoyer_main(MainJoueur m, int idj){

	cout << "Init vars" << endl;

	vector<Carte> main = m.getCartes();
	Couleur couls[8];
	Valeur vals[8];
	unsigned int i;
	cout << "OK" << endl;

	for(i = 0; i< main.size(); i++){
		couls[i] = main[i].getCouleur();
		vals[i] = main[i].getValeur();
		cout << "Carte "<<i<<" transformée" << endl;
	}
	int nb_cartes = i+1;

	cout << "Boucle " <<i << " < 8" << endl;

	while(i<8){

		couls[i] = main[i].getCouleur();
		vals[i] = main[i].getValeur();

		i++;
		cout << "Carte complementaires num " << i <<endl;
	}

	cout << "Tableaux OK" << endl;

	packet_serveur pk = { 7, "" , idj , "", sept , carreau, 0, carreau, false ,nb_cartes,
			{* vals}, {* couls}, {0,0}};
    sf::Packet Packet;

    Packet << pk;

    cout << "Packet prêt" << endl;

	if(Client[idj].Send(Packet) == sf::Socket::Done)
		cout << "Transfert OK" << endl;
	else
		cout << "Erreur de transfert" << endl;

}

void Server::envoyer_message(string mess, int idj){

	packet_serveur pk = { 2, mess , idj , "", sept , carreau, 2, carreau, false ,0,
			{sept,sept,sept,sept,sept,sept,sept,sept},
			{carreau,carreau,carreau,carreau,carreau,carreau,carreau,carreau},{0,0}};
    sf::Packet Packet;

    Packet << pk;

	Client[idj].Send(Packet);
}
void Server::envoyer_demande(int demande, int idj){

	packet_serveur pk = { 4, "" , idj , "", sept , carreau, demande, carreau, false ,0,
			{sept,sept,sept,sept,sept,sept,sept,sept},
			{carreau,carreau,carreau,carreau,carreau,carreau,carreau,carreau},{0,0}};
    sf::Packet Packet;

    Packet << pk;

	Client[idj].Send(Packet);
}

void Server::envoyer_atout_tous(Couleur atout){
	for (int i=0; i< 4; i++)
		this->envoyer_atout(atout,i);
}
void Server::envoyer_atout(Couleur atout, int idj){

	packet_serveur pk = { 5, "" , idj , "", sept , carreau, 2, atout, false ,0,
			{sept,sept,sept,sept,sept,sept,sept,sept},
			{carreau,carreau,carreau,carreau,carreau,carreau,carreau,carreau},{0,0}};
    sf::Packet Packet;

    Packet << pk;

	Client[idj].Send(Packet);
}

void Server::envoyer_validation(bool Valid, int idj){

	packet_serveur pk = { 6, "" , idj , "", sept , carreau, 2, carreau, Valid ,0,
			{sept,sept,sept,sept,sept,sept,sept,sept},
			{carreau,carreau,carreau,carreau,carreau,carreau,carreau,carreau},{0,0}};
    sf::Packet Packet;

    Packet << pk;

	Client[idj].Send(Packet);
}

void Server::envoyer_points_tous(int points[2]){
	for(int i=0; i<4; i++)
		envoyer_points(points,i);
}
void Server::envoyer_points(int points[2], int idj){

	packet_serveur pk = { 8, "" , idj , "", sept , carreau, 2, carreau, false ,0,
			{sept,sept,sept,sept,sept,sept,sept,sept},
			{carreau,carreau,carreau,carreau,carreau,carreau,carreau,carreau}, {points[0],points[1]}};
    sf::Packet Packet;

    Packet << pk;

	Client[idj].Send(Packet);
}
