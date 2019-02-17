#include <iostream>
#include "listeDeTramway.h"
#include "listeArrets.h"
#include "ligne.h"
#include "tracer.h"
#include "lectureXML.h"
#include <windows.h>
#include "graphics.h"

using namespace std;
/*int main()
{
    //int temps;
    //lectureXML xml{"C:/Users/oumar12/Desktop/TRAMWAYS/TRAMWAYS/Tram_V5.xml",30};
	return 0 ;
}*/
int main(int argc, char *argv[]) {
    //Recupération des paramettres
   if(argv[1] != NULL && argv[2] != NULL || argc > 3) {
        lectureXML * doc = new lectureXML(argv[1], atoi(argv[2]));
    	getchar();
    }
    else {
        cout << "Parametre(s) incorrecte(s) : Utilisation -> PARAM1 = CHEMIN | PARAM2 = TEMPS." << endl;
        getchar();
    }


    /*lectureXML * doc = new lectureXML("C:/Users/Fadel/Desktop/Tram_V5.xml", 55540);
	getchar();*/
}

