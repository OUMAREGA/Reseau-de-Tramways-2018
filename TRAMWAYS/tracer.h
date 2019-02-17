#ifndef TRACER_H
#define TRACER_H
#include <iostream>
#include <vector>
#include "listeArrets.h"
#include "ligne.h"
#include "listeDeTramway.h"
#pragma once

class tracer
{
public:
    tracer(int largeur,int hauteur);
    void placerArret(arret * unArret) const ;
    void placerArrets(ligne * uneLigne) const;
    void liensArrets(ligne * uneLigne) const;
    void placerTram(tramway * tram) const ;
    void placerTrams(ligne * uneLigne) const;
    void buildLigne(ligne * uneLigne) const ;
    void moveTram(tramway * tram);
    void moveTrams(ligne * uneLigne);
    void simulerTram(std::vector<ligne*> &lignes, int tempsSimul);
};
#endif // TRACER_H
