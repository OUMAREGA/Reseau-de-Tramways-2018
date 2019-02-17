#include <iostream>
#include <fstream>
#include "listeArrets.h"
using namespace std;
/**
Constructeur d'arret
@param[in] posX -
@param[in] posY -
@param[in] tempsArret -
@param[in] nomArret -
*/
arret::arret(double posX,double posY, int tempsArret,std::string nomArret):posX{posX},posY{posY},tempsArret{tempsArret},nomArret{nomArret},numTramsSurPlace{-1}
{}
//! Constructeur
listeArrets::listeArrets():d_tete{NULL},d_nombreArrets{0}
{}
//!AJOUTS
/**
@param[in] posX -
@param[in] posY -
@param[in] tempsArret -
@param[in] nomArret -
*/
void listeArrets::ajoutAuQueue(double posX,double posY,int tempsArret,std::string nomArret)
{
    if(d_nombreArrets==0)
    {
        arret * nouveauChaine = new arret(posX,posY,tempsArret,nomArret);
        d_tete=nouveauChaine;
    }
    else
    {
        arret * nouveauChaine = new arret(posX,posY,tempsArret,nomArret);
        arret * tmp = d_tete;
        while(tmp->prochainArret!=NULL)
        {
            tmp = tmp->prochainArret;
        }
        nouveauChaine->prochainArret=NULL;
        tmp->prochainArret=nouveauChaine;
    }
    d_nombreArrets++;
}
/**
@param[in] posX -
@param[in] posY -
@param[in] tempsArret -
@param[in] nomArret -
*/
void listeArrets::ajoutEnTete(double posX,double posY, int tempsArret, std::string nomArret)
{
    arret * nouveauChaine = new arret (posX,posY,tempsArret,nomArret);
    nouveauChaine->prochainArret = d_tete;
    d_tete = nouveauChaine;
    d_nombreArrets++;
}
/**
@param[in] posX -
@param[in] posY -
@param[in] tempsArret -
@param[in] nomArret -
@param[in] corsp - la position
*/
void listeArrets::ajoutAuCorps(double posX,double posY, int tempsArret, std::string nomArret,int corps)
{
    if(corps < 0 || corps > d_nombreArrets)
        cout<<"Ajout incorrecte";
    else if(corps==0)
        ajoutEnTete(posX,posY,tempsArret,nomArret);
    else if(corps==d_nombreArrets)
        ajoutAuQueue(posX,posY,tempsArret,nomArret);
    else
    {
        arret * nouveauChaine = new arret(posX,posY,tempsArret,nomArret);
        arret * tmp = d_tete;
        for(int i=1;i<corps;i++ )
        {
            tmp = tmp->prochainArret;
        }
        nouveauChaine->prochainArret=tmp->prochainArret;
        tmp->prochainArret=nouveauChaine;
    }
}
//! Affiche la liste des arrets au niveau console
void listeArrets::afficherListe() const
{
    if(d_nombreArrets>0)
    {
        arret * tmp = d_tete;
        while(tmp!=NULL)
        {
            cout<<tmp->nomArret<<endl;
            tmp = tmp->prochainArret;
        }
        delete tmp;
    }
    else
        cout<<"Impossible d'afficher une liste chainee vide."<<endl;
}
//!SUPPRESSION
/**
Delete en tete
*/
void listeArrets::supprEnTete()
{
    if(d_nombreArrets<=0)
        cout<<"Suppression de chainon impossible, car la liste chainee est vide."<<endl;
    else
    {
        arret * tmp = d_tete;
        d_tete=d_tete->prochainArret;
        delete tmp;
    }
    d_nombreArrets--;
}
/**
delete au queue
*/
void listeArrets::supprAuQueue()
{
    if(d_nombreArrets<=0 )
        cout<<"Suppression de chainon impossible, car la liste chainee est vide."<<endl;
    else if(d_nombreArrets==1)
    {
        delete d_tete;
        d_tete=NULL;
        d_nombreArrets--;
    }
    else
    {
        arret * avantDernierArret = d_tete;
        for(int i = 0;i<d_nombreArrets-1;i++)
        {
            avantDernierArret=avantDernierArret->prochainArret;
        }
        delete avantDernierArret->prochainArret;

        avantDernierArret->prochainArret=NULL;
        d_nombreArrets--;
    }
}
/**
@param[in] - corps -supprimer a une position
*/
void listeArrets::supprAuCorps(int corps)
{
    if(d_nombreArrets<0 || d_nombreArrets<corps)
        cout<<"Suppression de chainon impossible, car la liste chainee est vide."<<endl;
    else if(corps==0)
        supprEnTete();
    else if(corps==d_nombreArrets)
        supprAuQueue();
    else
    {
        arret * tmp = d_tete;
        for(int i =0; i<corps-1; i++)
        {
            tmp = tmp->prochainArret;
        }
        arret * tmp2 = tmp->prochainArret;
        tmp->prochainArret = tmp2->prochainArret;
        delete tmp2;
        d_nombreArrets--;
    }
}
//!ACCES
/**
@return - le premier arret
*/
arret * listeArrets::accesEnTete() const
{
    if(d_nombreArrets>0)
        return d_tete;
    else
        cout<<"Impossible d'acceder a la tete, la chaine est vide."<<endl;
        return 0;
}
/**
@param[in] - corps
@return - a une position
*/
arret * listeArrets::accesAuCorps(int corps) const
{
    //arret * tmp = d_tete;
    if(d_nombreArrets<=0 || corps > d_nombreArrets)
    {
        cout<<"Impossible d'acceder au corps, la chaine est vide."<<endl;
        return 0;
    }

    else if(corps==0)
    {
        arret * tmp = d_tete;
        return tmp;
    }
    else if(corps==d_nombreArrets)
    {
        arret * tmp = d_tete;
        while(tmp->prochainArret!=NULL)
        {
                tmp = tmp->prochainArret;
        }
        return tmp;
    }
    else
    {
        arret * tmp = d_tete;
        for(int i=0; i<corps;i++)
        {
            tmp = tmp->prochainArret;
        }
        return tmp;
    }
}
/**
@return - retourne le dernier arret
*/
arret * listeArrets::accesAuQueue() const
{
    arret * tmp = d_tete;
    if(d_nombreArrets<=0)
    {
        cout<<"Consultation impossible"<<endl;
        tmp=NULL;
        return 0;
    }
    else
    {
        while(tmp->prochainArret!=NULL)
        {
            tmp=tmp->prochainArret;
        }
        return tmp;
    }
}
/**
@return - si le nombre arret est vide
*/
bool listeArrets::estAucunArret() const
{
    return d_nombreArrets==0;
}
/**
@return - le nombre d'arrets
*/
int listeArrets::nombreArrets() const
{
    return d_nombreArrets;
}
//!DESTRUCTEUR
listeArrets::~listeArrets()
{
   if(d_nombreArrets>0)
    {
        arret * a_Suppr = d_tete;
        d_tete=d_tete->prochainArret;
        delete a_Suppr;
        d_nombreArrets--;
    }
}
