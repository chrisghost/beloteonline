/*
 * netstruct_server.h
 *
 *  Created on: Jan 28, 2009
 *      Author: chrissou
 */

#ifndef NETSTRUCT_SERVER_H_
#define NETSTRUCT_SERVER_H_
#define NETS 1

#include <string>
#include <SFML/Network.hpp>
#include <stdlib.h>
#include "server/carte.h"
using namespace std;

/* Valeurs du champ id :
 * 1. Joueur
   2. Message
   3. Carte
   4. Demande
   5. Atout
   6. Validation
   7. Cartes
   8. Points */

struct packet_serveur // Structure pour les transferts de données depuis le serveur vers le client
{
	int id;
	string log;					//1
	int id_j;					//1
	string message;				//2
	enum Valeur val;			//3
	enum Couleur couleur;		//3
	int demande;				//4 - (1- prendre carte; 2- choisir attout; 3- joueur carte)
	enum Couleur couleur_att;	//5
	bool valid;					//6
    int nb_cartes;				//7 - nombre de cartes dans le tableau
    enum Valeur vals[8];		//7
    enum Couleur couls[8];		//7
    int points[2];				//8

};

inline sf::Packet& operator <<(sf::Packet& Packet, const packet_serveur& pl) // Pour entrer la structure dans le packet
{
    return Packet << pl.id << pl.log << pl.id_j << pl.message << pl.val << pl.couleur << pl.demande << pl.couleur_att
		<< pl.valid << pl.nb_cartes << pl.vals << pl.couls << pl.points;
}

inline sf::Packet& operator >>(sf::Packet& Packet, packet_serveur& pl) // Pour extraire la structure du packet
{
    Packet >> pl.id >> pl.log >> pl.id_j >> pl.message >> pl.val >> pl.couleur >> pl.demande >> pl.couleur_att
		>> pl.valid >> pl.nb_cartes >> pl.vals[8] >> pl.couls[8] >> pl.points[2];
    return Packet;
}



#endif /* NETSTRUCT_SERVER_H_ */
