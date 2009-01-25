#include "Server.h"
#include "../netstruct.h"

////////////////////////////////////////////////////////////

Server::Server(unsigned short Port)
{
	// Create a socket for listening to incoming connections
	if (!sServer.Listen(Port))
		return;
	std::cout << "Listening to port " << Port << ", waiting for connections..." << std::endl;

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
				sf::SocketTCP Client;
				sServer.Accept(Client, &Address);
				std::cout << "Client connected ! (" << Address << ")" << std::endl;

				// Add it to the selector
				Selector.Add(Client);
			}
			else
			{
				// Else, it is a client socket so we can read the data he sent
                sf::Packet Packet;
                if (Socket.Receive(Packet) == sf::Socket::Done)
                {
                    // Extract the message and display it
			        packet_client st;
                    Packet >> st;


                    std::cout << "Client : " << st.log << " envoie la carte : " << st.val
						<< " de " << st.couleur << std::endl;
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
