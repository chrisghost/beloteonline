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
using namespace std;


struct login_s // Structure pour les transferts de données liées au login
{
    string log;
    string mdp;
};

sf::Packet& operator <<(sf::Packet& Packet, login_s& pl)
{
    return Packet << pl.log << pl.mdp;
}

sf::Packet& operator >>(sf::Packet& Packet, login_s& pl)
{
    return Packet >> pl.log >> pl.mdp;
}

#endif
