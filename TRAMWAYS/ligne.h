#ifndef LIGNE_H
#define LIGNE_H

#include <string>
#include "listeArrets.h"
#pragma once
class listeDeTrams;
class ligne
{
public:
    ligne();
    ligne(int numDeLigne,std::string nomDeLigne,double distanceEntreArrets, listeArrets * arrets, listeDeTrams * trams);
    ligne(ligne * ligne_a_Creer);
    //! Methodes Accés
    std::string nomDeLigne() const;
    int numDeLigne() const;
    listeArrets * arrets() const;
    listeDeTrams * trams() const;
    double distanceEntreArrets() const ;
    //! Methodes de modification
    void nomDeLigne(std::string nomDeLigne);
    void numDeLigne(int numDeLigne);
    void arrets(listeArrets * arrets);
    void trams(listeDeTrams * trams);
    void distanceEntreArrets(double distanceEntreArrets);
    //!Destructeur
    ~ligne();
private:
    int d_numDeLigne;
    std::string d_nomDeLigne; // nom de l'arret
    double d_distanceEntreArrets; // distance entre chaque arret
    listeArrets * d_arrets ;
    listeDeTrams * d_trams ;
};
#endif // LIGNE_H
