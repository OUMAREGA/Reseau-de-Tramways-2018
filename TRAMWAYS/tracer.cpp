#include "graphics.h"
#include <iostream>
#include <ctime>
#include <tchar.h>
#include <math.h>
#include "tracer.h"
#include <windows.h>
using namespace std;
tracer::tracer(int largeur,int hauteur)
{
   initwindow(largeur,hauteur,"defaut");
}
void tracer::placerArret(arret * unArret) const
{
    setbkcolor(WHITE);
    //emplavement darret en circle GREEN
    setcolor(GREEN);
    circle(unArret->posX,unArret->posY,10);
    setfillstyle(SOLID_FILL, GREEN);
    floodfill(unArret->posX,unArret->posY,GREEN);

    //le text en BLEU pour larret
    setcolor(BLUE);
    std::string str = unArret->nomArret;
    char * writable = new char[str.size()+ 1 ];
    copy(str.begin(),str.end(),writable);
    writable[str.size()]='\0';
    settextstyle(SMALL_FONT,HORIZ_DIR,5);
    outtextxy(unArret->posX+5,unArret->posY+5,writable);
    delete[] writable;
}
// placer les arrets une ligne sur la fenetre
void tracer::placerArrets(ligne * uneLigne) const
{
    for(int i = 0 ; i<uneLigne->arrets()->nombreArrets();i++)
    {
        placerArret(uneLigne->arrets()->accesAuCorps(i));
    }
}
void tracer::liensArrets(ligne * uneLigne) const
{
    for(int i =0;i<uneLigne->arrets()->nombreArrets()-1;i++)
    {
        setcolor(uneLigne->numDeLigne()+11);
        line(uneLigne->arrets()->accesAuCorps(i)->posX,uneLigne->arrets()->accesAuCorps(i)->posY,uneLigne->arrets()->accesAuCorps(i+1)->posX,uneLigne->arrets()->accesAuCorps(i+1)->posY);
    }
}
void tracer::placerTram(tramway * tram) const
{
    setcolor(RED);
    rectangle(tram->posX-12,tram->posY-12,tram->posX+12,tram->posY+12);
    stringstream convert;
    convert<<tram->numLigne;
    string str = convert.str();
    char * writable = new char[str.size()+1];
    copy(str.begin(),str.end(),writable);
    writable[str.size()]='\0';
    setcolor(BLACK);
    settextstyle(COMPLEX_FONT,HORIZ_DIR,1);
    outtextxy(tram->posX-5,tram->posY-10,writable);
    delete[] writable;
}
void tracer::placerTrams(ligne * uneLigne)const
{
    for(int i=0;i<uneLigne->trams()->nombreDeTrams();i++)
        placerTram(uneLigne->trams()->accesAuCorps(i));
}
void tracer::buildLigne(ligne * uneLigne)const
{
    placerArrets(uneLigne);
    liensArrets(uneLigne);
    placerTrams(uneLigne);

}
void tracer::moveTram(tramway * tram)
{
    if(!tram->sens)
     {
         arret * arretArrive=tram->arretActuel->prochainArret;
         double deltaX=(arretArrive->posX-tram->posX)/tram->vitesseMax;
         double deltaY=(arretArrive->posY-tram->posY)/tram->vitesseMax;
         if(tram->posX==arretArrive->posX || tram->posY==arretArrive->posY || (deltaX<0.1 && deltaY<0.1))
           {
             tram->arretActuel=arretArrive;
             tram->posX=arretArrive->posX;
             tram->posY=arretArrive->posY;
             cout<<"L'arret "<<arretArrive->nomArret<<" est desservie par le tram " <<tram->numLigne<< "."<<endl;

           }
         if(tram->respectDistanceDeSecurite())
         {
             tram->posX+=deltaX;
             tram->posY+=deltaY;
             tram->terminus= false;
         }

         if(tram->arretActuel->prochainArret==NULL)
         {
             cout<<"Le tram "<<tram->numLigne<<"a atteint son terminus "<<endl;
             tram->terminus=true;
             tram->sens=true;
         }
        }
        else if(tram->sens)
        {
            arret * arretArriverInvers=tram->ligneAffect->arrets()->accesEnTete();

            while(arretArriverInvers->prochainArret!=tram->arretActuel)
            {
                arretArriverInvers=arretArriverInvers->prochainArret;
            }

                double deltaX=(arretArriverInvers->posX-tram->posX)/tram->vitesseMax;
                double deltaY=(arretArriverInvers->posY-tram->posY)/tram->vitesseMax;

                if((tram->posX==arretArriverInvers->posX) || (tram->posY==arretArriverInvers->posY) || (deltaX>-0.1 && deltaY>-0.1))
                {
                    tram->arretActuel= arretArriverInvers;
                    tram->posX=arretArriverInvers->posX;
                    tram->posY=arretArriverInvers->posY;

                }
                if(tram->respectDistanceDeSecurite())
                {
                    tram->posX+=deltaX;
                    tram->posY+=deltaY;
                    tram->terminus=false;
                }
                if(tram->arretActuel==tram->ligneAffect->arrets()->accesEnTete())
                {
                    cout<<"Le tram "<<tram->numLigne<<"a atteint son terminus "<<endl;
                    tram->terminus=true;
                    tram->sens=true;

                }
        }
}

void tracer::moveTrams(ligne * uneLigne)
{
    for(int i = 0;i<uneLigne->trams()->nombreDeTrams();i++)
    {
        moveTram(uneLigne->trams()->accesAuCorps(i));
    }
}
void tracer::simulerTram(vector<ligne*> &lignes, int tempsSimul)
{
    time_t depart,arrivee;
    time(&depart);
    int longueurLigne = lignes.size();
    while( difftime(arrivee,depart)<tempsSimul )
    {
        cleardevice();
        for(int i=0;i<longueurLigne;i++)
        {
            buildLigne(lignes[i]);
        }
        for(int i=0;i<longueurLigne;i++)
        {
            moveTrams(lignes[i]);
        }
        Sleep(150);
        time(&arrivee);
    }
    closegraph();
    cout<<"Fin du temps d'execution."<<endl;
}

