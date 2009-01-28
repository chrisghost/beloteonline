#ifndef NETSTRUCT_H
#define NETSTRUCT_H
#define NET 1
/*
 * File:   netstruct.h
 *
 * Created on January 10, 2009, 3:26 PM
 */
#include <string>
#include <SFML/Network.hpp>
#include <stdlib.h>
#include "server/carte.h"
using namespace std;

/* Valeurs du champ id :
 * 1. Connexion
   2. Carte
   3. Reponse
   4. Couleur attout */

struct packet_client // Structure pour les transferts de données depuis le client vers le serveur
{
	int id;
	string log;					//1
	int id_j;					//2,3,4
	enum Valeur val;			//2
	enum Couleur couleur;		//2
	bool reponse;				//3
	enum Couleur couleur_att;	//4
};

inline sf::Packet& operator <<(sf::Packet& Packet, const packet_client& pl) // Pour entrer la structure dans le packet
{
    return Packet << pl.id << pl.log << pl.id_j << pl.val << pl.couleur << pl.reponse << pl.couleur_att;
}

inline sf::Packet& operator >>(sf::Packet& Packet, packet_client& pl) // Pour extraire la structure du packet
{
    Packet >> pl.id >> pl.log >> pl.id_j >> pl.val >> pl.couleur >> pl.reponse >> pl.couleur_att;
    return Packet;
}


#endif
