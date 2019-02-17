#ifndef LISTEARRETS_H
#define LISTEARRETS_H

#include <string>
#pragma once
class arret
{
friend class listeArrets;
public:
    arret(double posX,double posY, int tempsArret,std::string nomArret);
    arret * prochainArret;
    double posX;
    double posY; // coordonnees de l'arret suivant x et y
    int tempsArret; // le temps d'arret en seconde au niveau des arrets
    std::string nomArret; // nom de l'arret
    int numTramsSurPlace;
};

class listeArrets
{
public:
    //!Constructeur
    listeArrets();

    //!AJOUTS
    void ajoutEnTete(double posX,double posY,int tempsArret,std::string nomArret);
    void ajoutAuCorps(double posX,double posY,int tempsArret,std::string nomArret,int corps);
    void ajoutAuQueue(double posX,double posY,int tempsArret,std::string nomArret);
    //!SUPPRIMER
    void supprEnTete();
    void supprAuCorps(int corps);
    void supprAuQueue();
    //!ACCES
    arret * accesEnTete() const;
    arret * accesAuCorps(int corps) const ;
    arret *accesAuQueue() const;
    void afficherListe() const ;

    bool estAucunArret() const;
    int nombreArrets() const ;
    //!Destructeur
    ~listeArrets();
private:
    arret * d_tete;
    int d_nombreArrets;


};
#endif // LISTEARRETS_H
