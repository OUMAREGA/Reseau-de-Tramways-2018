#ifndef LISTEDETRAMWAY_H
#define LISTEDETRAMWAY_H

#include "ligne.h"
#pragma once
class listeArrets;

class tramway
{
	friend class listeDeTrams;
	public:
        tramway(int numLigne, int vitesseMax, bool sens, double posX, double posY, ligne * ligneAffect);
		//Methode qui determine si le tram respecte la distance de securite
		bool respectDistanceDeSecurite();
	    int numLigne;
	    int vitesseMax; // vitesse max du tram

	    // la distance entre le trame et larret suivant
	    bool sens; // le sens de parcours 0 ou 1
	    double posX;
		double posY;
		//Attributs en publi
		ligne * ligneAffect;
		tramway * suivant;
		arret * arretActuel;
		int distanceSecurite;//distance entre deux trams
		int distanceArret;
		int vitesseActuelle; // vitesse à l'arret
        bool terminus;
};
class listeDeTrams
{
	public:
		listeDeTrams();	//Constructeur de liste chaine de trams
		~listeDeTrams();	//Destructeur
		//Ajouts
		void ajoutEnTete(int numero, int vitesseMax, bool sens,double posX,double posY, ligne * ligneAffect);
		void ajoutAuQueue(int numero, int vitesseMax, bool sens,double posX,double posY, ligne * ligneAffect);
		void ajoutAuCorps(int numero, int vitesseMax, bool sens,double posX,double posY, ligne * ligneAffect, int corps);
		//Suppressions
		void supprEnTete();
		void supprAuQueue();
		void supprAuCorps(int corps);
		//ACCES
		tramway * accesEnTete() const;
		tramway * accesAuQueue() const;
		tramway * accesAuCorps(int corps) const;
		void afficherListe() const;
		bool estVide() const;
		int nombreDeTrams() const ;
	private:
		tramway * d_tete;
		int d_nombreDeTrams;
};

#endif // LISTEDETRAMWAY_H
