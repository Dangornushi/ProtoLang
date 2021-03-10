#include "main.hpp"

int main( int argc, char **arg ) {

    string comp = "./comp ";
    string passbuf = "./run ";

    comp = comp + arg[1];
    passbuf = passbuf + arg[1] + "s";

    system(comp.c_str());
    system(passbuf.c_str());

    return 0;
    
}
