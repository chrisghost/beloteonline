/* 
 * File:   main.cpp
 * Author: chrissou
 *
 * Created on January 10, 2009, 3:37 PM
 */

#include <stdlib.h>
#include <string>
#include <iostream>
#include "Client.h"
#include "Server.h"
#include "netstruct.h"


/*
 * 
 */
int main(int argc, char** argv) {
    char rep;
    
    cout << "Choose : Server (s) or Client (c) ?" << endl;
    cin >> rep;
    
    if(rep=='s')
        Server s(1234);
    else if(rep=='c')
        Client c(1234);
    
    
    return (EXIT_SUCCESS);
}

