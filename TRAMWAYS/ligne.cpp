#include <iostream>
#include <fstream>
#include <string>
#include "ligne.h"

//! Constructeur par default
ligne::ligne()
{}
/**
Constructeur par défaut
@param[in] numLigne - numero de ligne
@param[in] nomLigne - nom de ligne
@param[in] arrets - liste des arrets
@param[in] trams - listes des trams
@param[in] distanceArret - distance entre chaque arret
*/
ligne::ligne( int numDeLigne,std::string nomDeLigne,double distanceEntreArrets,listeArrets * arrets, listeDeTrams * trams):d_numDeLigne{numDeLigne},d_nomDeLigne{nomDeLigne},d_distanceEntreArrets{distanceEntreArrets},d_arrets{arrets},d_trams{trams}
{}
/**
Constructeur par ligne
@param[in] maligne - ligne à crée
*/
ligne::ligne(ligne * ligne_a_Creer)
{
    d_nomDeLigne=ligne_a_Creer->nomDeLigne();
    d_numDeLigne=ligne_a_Creer->numDeLigne();
    d_arrets=ligne_a_Creer->arrets();
    d_trams=ligne_a_Creer->trams();
    d_distanceEntreArrets =ligne_a_Creer->distanceEntreArrets();
}
/**
@return - retourne le nom de la ligne
*/
std::string ligne::nomDeLigne() const
{
    return d_nomDeLigne;
}
/**
@return - retourne le numero de la ligne
*/
int ligne::numDeLigne() const
{
    return d_numDeLigne;
}
/**
@return - return un private d_arrets
*/
listeArrets * ligne::arrets() const
{
    return d_arrets;
}
/**
@return - return un private d_trams
*/
listeDeTrams * ligne::trams() const
{
    return d_trams;
}
/**
@return - return un private d_distanceEntrArrets
*/
double ligne::distanceEntreArrets() const
{
    return d_distanceEntreArrets;
}
/**
@param[in] nomLigne - nom de ligne
*/
void ligne::nomDeLigne(std::string nomDeLigne)
{
    d_nomDeLigne=nomDeLigne;
}
/**
@param[in] numDeLigne - numero de ligne
*/
void ligne::numDeLigne(int numDeLigne)
{
    d_numDeLigne=numDeLigne;
}
/**
@param[in] arrets - liste des arrets
*/
void ligne::arrets(listeArrets * arrets)
{
    d_arrets=arrets;
}
/**
@param[in] trams - liste de trams
*/
void ligne::trams(listeDeTrams * trams)
{
    d_trams=trams;
}
/**
@param[in] distanceEntreArrets - distance entre les arrets
*/
void ligne::distanceEntreArrets(double distanceEntreArrets)
{
    d_distanceEntreArrets=distanceEntreArrets;
}
//!Destructeur
ligne::~ligne()
{
    delete this;
}
