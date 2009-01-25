#include "Server.h"
#include "../netstruct.h"

////////////////////////////////////////////////////////////

Server::Server(unsigned short Port)
{
	// Create a socket for listening to incoming connections
	if (!sServer.Listen(Port))
		return;
	std::cout << "Listening to port " << Port << ", waiting for connections..." << std::endl;

	nb_cl_connected = 0;

	// Create a selector for handling several sockets (the listener + the socket associated to each client)
	sf::SelectorTCP Selector;

	// Add the listener
	Selector.Add(sServer);

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

				//pl.id << pl.log << pl.id_j << pl.message << pl.val << pl.couleur << pl.demande << pl.couleur_att
				//<< pl.valid << pl.nb_cartes << pl.vals << pl.couls << pl.points;

				packet_serveur pk = {1 , "" , nb_cl_connected , "", sept, carreau, 0, carreau, false, 0,{sept,sept,sept,sept,sept},
						{carreau,carreau,carreau,carreau,carreau},{0,0}};
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
						case 2 ://Carte
							std::cout << "Le client " << st.log << "("<< st.id_j << ") envoie la carte "<< st.val
								<< " de " << st.couleur << std::endl;
							break;
						case 3 ://Reponse
							std::cout << "Le client " << st.log << "("<< st.id_j << ") répond "<< st.reponse << std::end;
							break;
						case 4 ://Couleur attout
							std::cout << "Le client " << st.log << "("<< st.id_j << ") envoie la couleur "<<
								st.couleur << std::endl;
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
