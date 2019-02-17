#include <iostream>
#include "listeDeTramway.h"
#include <cmath>
using namespace std;
/**
Constructeur tramway
@param[in] numLigne -
@param[in] vitesseMax -
@param[in] sens -
@param[in] posX -
@param[in] posY -
@param[in] ligneAffect -
*/
tramway::tramway(int numLigne, int vitesseMax, bool sens, double posX, double posY,ligne * ligneAffect):numLigne{numLigne},vitesseMax{vitesseMax},sens{sens},posX{posX},posY{posY},ligneAffect(ligneAffect),suivant{NULL},terminus{0}
{
    distanceSecurite=50;
};

//Methode qui determine si le tram respecte la distance de securite
/**
@return - si la distance est respectee
*/
bool tramway::respectDistanceDeSecurite()
{
    tramway * tramSuivant = NULL;
    bool reste = false;
    //Recuperer le tram suivant
    if(this->suivant != NULL)
    {
        tramSuivant = this->suivant;
    }
    else reste = true;
    //Si j'ai trouvÃ© un tram suivant et que ils ont le meme sense de dÃ©placement alors je calcule sa distance
    if(tramSuivant != NULL  && this->sens == tramSuivant->sens)
    {
        int disX = (tramSuivant->posX - this->posX);
        int disY = (tramSuivant->posY - this->posY);
        int distance = sqrt(disX*disX + disY*disY);
        //Si la distance entre les deux trams est infÃ©rieur ou Ã©gale a la distance de securitÃ© alors return false
        if(distance > this->distanceSecurite)
        {
            reste = true;
        }
        else
        {
            //cout << "Le tram " << numero << " ne respecte pas la distance de securite de " << distanceSecurite << "m : Arret du tram..." <<endl;
        }
    }
    else reste = true;
    return reste;
}

/**
Le constructeur
*/
listeDeTrams::listeDeTrams():d_tete{NULL},d_nombreDeTrams{0}
{}

/**
    Affiche la liste tram au niveau console
*/
void listeDeTrams::afficherListe() const
{
    if (d_nombreDeTrams > 0)
    {
        tramway * tmp = d_tete;
        while(tmp != NULL)
        {
            cout << tmp->numLigne << endl;
            tmp = tmp->suivant;
        }
        delete tmp;
    }
    else
    {
        cout << "Affichage impossible : la liste chainee est vide." << endl;
    }
}
//!AJOUTS
/**
@param[in] numLigne -
@param[in] vitesseMax -
@param[in] sens -
@param[in] posX -
@param[in] posY -
@param[in] ligneAffect -
*/
void listeDeTrams::ajoutEnTete(int numLigne, int vitesseMax, bool sens, double posX, double posY, ligne * ligneAffect)
{
    //On cree le chainon correspondant au parametres
    tramway * nouveau = new tramway(numLigne, vitesseMax, sens, posX, posY, ligneAffect);
    //On affecte a nouveau->suivant la tete actuelle
    nouveau->suivant = d_tete;
    //On definit la tete actuelle comme etant le nouveau chainon
    d_tete = nouveau;
    d_nombreDeTrams++;
}
/**
@param[in] numLigne -
@param[in] vitesseMax -
@param[in] sens -
@param[in] posX -
@param[in] posY -
@param[in] ligneAffect -
*/
void listeDeTrams::ajoutAuQueue(int numero, int vitesseMax,bool sens,double posX,double posY,ligne * ligneAffect)
{
    if(d_nombreDeTrams==0)
    {
        tramway * nouveauTram = new tramway(numero,vitesseMax,sens,posX,posY,ligneAffect);
        d_tete=nouveauTram;
    }
    else
    {
        tramway * nouveauTram = new tramway(numero,vitesseMax,sens,posX,posY,ligneAffect);
        tramway * tmp=d_tete;
        while(tmp->suivant!=NULL)
        {
            tmp=tmp->suivant;
        }
        nouveauTram->suivant=NULL;
        tmp->suivant=nouveauTram;
    }
    d_nombreDeTrams++;
}
/**
@param[in] numLigne -
@param[in] vitesseMax -
@param[in] sens -
@param[in] posX -
@param[in] posY -
@param[in] corps -
@param[in] ligneAffect -
*/
void listeDeTrams::ajoutAuCorps(int numero,int vitesseMax,bool sens,double posX,double posY,ligne * ligneAffect,int corps)
{
    if(corps<0 || corps>d_nombreDeTrams)
    {
        cout<<"Ajout incorrecte";
    }
    else if(corps==0)
        ajoutEnTete(numero,vitesseMax,sens,posX,posY,ligneAffect);
    else if(corps==d_nombreDeTrams)
        ajoutAuQueue(numero,vitesseMax,sens,posX,posY,ligneAffect);
    else
    {
        tramway * nouveauTram = new tramway(numero,vitesseMax,sens,posX,posY,ligneAffect);
        tramway * tmp=d_tete;
        for(int i=1; i<corps; i++)
            tmp=tmp->suivant;
        nouveauTram->suivant=tmp->suivant;
        tmp->suivant=nouveauTram;
    }
}
//!SUPPRESSIONS
/**
delete en tete
*/
void listeDeTrams::supprEnTete()
{
    if(d_nombreDeTrams<=0)
        cout<<"Suppression impossible";
    else
    {
        tramway * a_Suppr = d_tete;
        d_tete = d_tete->suivant;
        delete a_Suppr;
    }
    d_nombreDeTrams--;
}
/**
delete au queue
*/
void listeDeTrams::supprAuQueue()
{
    if(d_nombreDeTrams<=0)
            cout<<"Suppresssion impossible";
    else if(d_nombreDeTrams==1)
    {
        delete d_tete;
        d_tete=NULL;
        d_nombreDeTrams--;
    }
    else
    {
        tramway * avantDernierTram = d_tete;
        for(int i=0; i<d_nombreDeTrams-2; i++)
                avantDernierTram = avantDernierTram->suivant;
            delete avantDernierTram;
            avantDernierTram->suivant=NULL;
            d_nombreDeTrams--;
        }
}
/**
delete a une position int corps
*/
void listeDeTrams::supprAuCorps(int corps)
{
    if(d_nombreDeTrams<0 || d_nombreDeTrams<corps)
        cout<<"Suppression impossible";
    else if (corps==0)
        supprEnTete();
    else if (corps==d_nombreDeTrams)
        supprAuQueue();
    else
    {
        tramway * tmp = d_tete;
        for(int i=0; i<corps -1; i++)
            tmp = tmp->suivant;
        tramway * a_Suppr = tmp->suivant;
        tmp->suivant = a_Suppr->suivant;
        delete a_Suppr;
        d_nombreDeTrams--;
    }
}
//!ACCES
/**
@return - le premier tram de la liste
*/
tramway * listeDeTrams::accesEnTete() const
{
    if(d_nombreDeTrams>0)
        return d_tete;
    else
        return 0;
}
/**
@return - le dernier tram de la liste
*/
tramway * listeDeTrams::accesAuQueue() const
{
     tramway * tmp = d_tete;
    if(d_nombreDeTrams<=0)
    {
        cout<<"Acces au queue impossible";
        tmp=NULL;
        return 0;
    }
    else
    {

        while(tmp->suivant!=NULL)
            tmp=tmp->suivant;
        return tmp;
    }
}
/**
@return - le corps ieme tram de la liste
*/
tramway * listeDeTrams::accesAuCorps(int corps) const
{
    //tramway * tmp=d_tete;
    if(d_nombreDeTrams <= 0 || corps > d_nombreDeTrams)
    {
        cout<<"Acces au corps impossible"<<endl;
        return 0;
    }
    else if (corps==0)
    {
        tramway * tmp = d_tete;
        return tmp;
    }
    else if(corps==d_nombreDeTrams)
    {
        tramway * tmp =d_tete;
        while(tmp->suivant != NULL)
            tmp=tmp->suivant;
        return tmp;
    }
    else
    {
        tramway * tmp = d_tete;
        for(int i =0; i<corps; i++)
            tmp=tmp->suivant;
        return tmp;
    }
}
/**
@return - si le nombre tram =0
*/
bool listeDeTrams::estVide() const
{
    return d_nombreDeTrams == 0;
}
/**
@return - le nombre tram
*/
int listeDeTrams::nombreDeTrams() const
{
    return d_nombreDeTrams;
}
//!DESTRUCTEUR
listeDeTrams::~listeDeTrams()
{
    while(d_nombreDeTrams>0)
    {
        tramway * a_Suppr = d_tete;
        d_tete = d_tete->suivant;
        delete a_Suppr;
        d_nombreDeTrams--;
    }
}
