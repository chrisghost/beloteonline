#ifndef SERVER_H_
#define SERVER_H_

class Server
{
public:
	Server();
	virtual ~Server();
	bool connecter(string l, string p);
private:
	sf::SocketTCP Server;
	unsigned short Port;
};

#endif /*SERVER_H_*/
