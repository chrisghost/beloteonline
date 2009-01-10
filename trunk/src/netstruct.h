/* 
 * File:   netstruct.h
 * Author: chrissou
 *
 * Created on January 10, 2009, 3:26 PM
 */
#include <string>
using namespace std;

struct login // Structure pour els transfert de données liées au login
{
    string log;
    string mdp;
};

sf::Packet& operator <<(sf::Packet& Packet, login& pl)
{
    return Packet << pl.log << pl.mdp;
}

sf::Packet& operator >>(sf::Packet& Packet, login& pl)
{
    return Packet >> pl.log >> pl.mdp;
}

