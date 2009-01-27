#include "Server.h"
#include "netstruct.h"

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

	// Create a selector for handling several sockets (the listener + the socket associated to each client)
	sf::SelectorTCP Selector;

	// Add the listener
	Selector.Add(sServer);


	Equipe e1(1, false);
	Equipe e2(2, false);


	// Loop while... we close the program :)
	while (true)
	{
		// Get the sockets ready for reading
		unsigned int NbSockets = Selector.Wait();

		// We can read from each returned socket
		for (unsigned int i = 0; i < NbSockets; ++i)
		{
			// Get the current socket
			sf::SocketTCP Socket = Selector.GetSocketReady(i);

			if (Socket == sServer)
			{
				// If the listening socket is ready, it means that we can accept a new connection
				sf::IPAddress Address;

				sServer.Accept(Client[nb_cl_connected], &Address);
				std::cout << "Client connected ! (" << Address << ")" << std::endl;

				clients[nb_cl_connected] = Address;

				if(nb_cl_connected<2){
					Joueur j(nb_cl_connected, e1, "");
					b->ajouterJoueur(j);}
				else{
					Joueur j(nb_cl_connected, e2, "");
					b->ajouterJoueur(j);}

				packet_serveur pk = {1 , "" , nb_cl_connected , "", sept, carreau, 0, carreau, false, 0,
						{sept,sept,sept,sept,sept,sept,sept,sept},
						{carreau,carreau,carreau,carreau,carreau,carreau,carreau,carreau},{0,0}};
		        sf::Packet Packet;
		        Packet << pk;
				Client[nb_cl_connected].Send(Packet);

				nb_cl_connected++;


				// Add it to the selector
				Selector.Add(Client[nb_cl_connected]);
			}
			else
			{
				// Else, it is a client socket so we can read the data he sent
                sf::Packet Packet;
                if (Socket.Receive(Packet) == sf::Socket::Done)
                {
			        packet_client st;
                    Packet >> st;

                    switch (st.id){
						case 1 ://Connexion
							std::cout << "Le client " << st.id_j <<" s'apelle " << st.log << std::endl;
							login[st.id_j] = st.log;
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
                    // Error : we'd better remove the socket from the selector
                    Selector.Remove(Socket);
                }
			}
		}
	}
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

	Client[id].Send(Packet);
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
	vector<Carte> main = m.getCartes();
	Couleur couls[8];
	Valeur vals[8];
	unsigned int i;
	for(i = 0; i< main.size(); i++){
		couls[i] = main[i].getCouleur();
		vals[i] = main[i].getValeur();
	}
	int nb_cartes = i+1;

	while(i<8){
		couls[i] = main[i].getCouleur();
		vals[i] = main[i].getValeur();
	}

	packet_serveur pk = { 7, "" , idj , "", sept , carreau, 0, carreau, false ,nb_cartes,
			{* vals}, {* couls}, {0,0}};
    sf::Packet Packet;

    Packet << pk;

	Client[idj].Send(Packet);

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
