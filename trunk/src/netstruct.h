#ifndef NETSTRUCT_H
#define NETSTRUCT_H
/*
 * File:   netstruct.h
 * Author: chrissou
 *
 * Created on January 10, 2009, 3:26 PM
 */
#include <string>
#include <SFML/Network.hpp>
#include <stdlib.h>
#include "server/carte.h"
using namespace std;

/* 1. Connexion
   2. Carte
   3. Reponse
   4. Couleur attout */

struct packet_client // Structure pour les transferts de données
{
	int id;
	string log;					//1
	int id_j;					//2,3,4
	enum Valeur val;			//2
	enum Couleur couleur;		//2
	bool reponse;				//3
	enum Couleur couleur_att;	//4
};

sf::Packet& operator <<(sf::Packet& Packet, const packet_client& pl)
{
    return Packet << pl.id << pl.log << pl.id_j << pl.val << pl.couleur << pl.reponse << pl.couleur_att;
}

sf::Packet& operator >>(sf::Packet& Packet, packet_client& pl)
{
    Packet >> pl.id >> pl.log >> pl.id_j >> pl.val >> pl.couleur >> pl.reponse >> pl.couleur_att;
    return Packet;
}

/* 1. Joueur
   2. Message
   3. Carte
   4. Demande
   5. Atout
   6. Validation
   7. Cartes
   8. Points */

struct packet_serveur // Structure pour les transferts de données
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
    enum Valeur vals[5];		//7
    enum Couleur couls[5];		//7
    int points[2];				//8

};

sf::Packet& operator <<(sf::Packet& Packet, const packet_serveur& pl)
{
    return Packet << pl.id << pl.log << pl.id_j << pl.message << pl.val << pl.couleur << pl.demande << pl.couleur_att
		<< pl.valid << pl.nb_cartes << pl.vals << pl.couls << pl.points;
}

sf::Packet& operator >>(sf::Packet& Packet, packet_serveur& pl)
{
    Packet >> pl.id >> pl.log >> pl.id_j >> pl.message >> pl.val >> pl.couleur >> pl.demande >> pl.couleur_att
		>> pl.valid >> pl.nb_cartes >> pl.vals[5] >> pl.couls[5] >> pl.points[2];
    return Packet;
}

#endif
