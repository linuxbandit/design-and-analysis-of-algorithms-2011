/* Bellicano Fabrizio
 * 3257630
 * File main richiamante una classe avente metodi per parsare un grafo da un file
 * e calcolarne il flusso massimo
 */

#include<iostream>

#include "MaxFlow.h"

#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif
#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif


int main(int argc, char* argv[]) {

    MaxFlow obj;
    if(obj.Parser(argv[1])) return EXIT_FAILURE; //convenzione UNIX: 0 significa ok, 1 significa male
    //cout<<" V "<<obj.getV()<<" E "<<obj.getE()<<" s "<<obj.gets()<<" t "<<obj.gett()<<endl;
    //ogg.debugger();
    obj.calculatemaxflow();
    //ogg.debugger();
    //cout << "Max flow s -> t  : " << obj.getflow() << endl;  
    cout << obj.getflow() << endl;
    return EXIT_SUCCESS;
}