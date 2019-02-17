#include "listeDeTramway.h"
#include "listeArrets.h"
#include "ligne.h"
#include "lectureXML.h"
#include "tracer.h"

using namespace std;
/**
	Permet de lire un fichier XML.
@param[in] nomFichier -  nom du fichier
@param[in] temps - temps d'execution
*/
lectureXML::lectureXML(std::string nomFichier, int temps) : d_nomFichier(nomFichier) {
	TiXmlDocument monDoc(nomFichier.c_str());
	bool loadOkay = monDoc.LoadFile();

	if (!loadOkay)
		cout << "Impossible de ouvrir le fichier : " << nomFichier.c_str() << "." << endl;
	else {
		cout << "Ouverture du fichier XML reussi." << endl;

		//Je recupere la racine du document
		TiXmlElement * racine = monDoc.FirstChildElement("TramWay");

		// -------------- GESTION DES LISTE DARRETS --------------

		//Recupération de la liste des arrets..............
		//Je recupere les listes des arrets puis la premiere liste de cette meme liste
		TiXmlElement * listArrets = racine->FirstChildElement("listArrets");
		TiXmlElement * listArret = listArrets->FirstChildElement("nbListArret");

		int nbListArret = atoi(listArret->Attribute("nombre"));
		vector<listeArrets*> mesArret(nbListArret);

		//Creation des liste d'arrets
		int x = mesArret.size();
		for(int i = 0; i < x ; i++) {
			mesArret[i] = new listeArrets();
		}
		cout << "Liste arret ok" << endl;
		// -------------- GESTION DES ARRETS --------------

		//Recupération des arrets..............
		//Je recupere les arrets puis le premier arret de ces arrets
		TiXmlElement * arrets = racine->FirstChildElement("arrets");
		TiXmlElement * arret = arrets->FirstChildElement("arret");

		//Tant que le programme n'a pas fini de parcourrir les arrets, je recupere chaque arret a créer
		while(arret) {
			//Création des des arrets
			mesArret[atoi(arret->Attribute("IndexlistArretAffect"))]->ajoutAuQueue(atoi(arret->Attribute("posX")), atoi(arret->Attribute("posY")), atoi(arret->Attribute("dureeStop")), arret->Attribute("nom"));
			arret = arret->NextSiblingElement("arret");
		}
		cout << "arret ok" << endl;
		// -------------- GESTION DES LIST DE TRAM --------------

		//Recupération de la liste des trams..............
		//Je recupere les listes des trams puis la premiere liste de cette meme liste
		TiXmlElement * listTrams = racine->FirstChildElement("listTrams");
		TiXmlElement * listTram = listTrams->FirstChildElement("nbListTram");

		//Recupération du nombre de tram a créer
		int nbListTram = atoi(listTram->Attribute("nombre"));
		vector<listeDeTrams*> mesTram(nbListTram);

		//Creation des liste des trams
		int y=mesTram.size();
		for(int i = 0; i <y; i++) {
			mesTram[i] = new listeDeTrams();
		}
		cout << "Liste tram ok" << endl;
		// -------------- GESTION DES LIGNES --------------

		//Recupération de la liste des lignes..............
		//Je recupere les listes des lignes puis la premiere liste de cette meme liste
		TiXmlElement * lignes = racine->FirstChildElement("lignes");
		TiXmlElement * maLigne = lignes->FirstChildElement("ligne");
		TiXmlElement * nombreLigne = lignes->FirstChildElement("nbLigne");

		//Recupération du nombre de ligne a créer
		int nbLigne = atoi(nombreLigne->Attribute("nombre"));
		std::vector<ligne*> mesLigne(nbLigne);
        int z=mesLigne.size();
		for(int i = 0; i <z; i++) {
			mesLigne[i] = new ligne();
		}

		while(maLigne) {
			//Création des des arrets
			mesLigne[atoi(maLigne->Attribute("index"))]->numDeLigne(atoi(maLigne->Attribute("index")));
			mesLigne[atoi(maLigne->Attribute("index"))]->nomDeLigne(maLigne->Attribute("nomLigne"));
			mesLigne[atoi(maLigne->Attribute("index"))]->arrets(mesArret[atoi(maLigne->Attribute("IndexlistArret"))]);
			mesLigne[atoi(maLigne->Attribute("index"))]->trams(mesTram[atoi(maLigne->Attribute("IndexListTram"))]);
			maLigne = maLigne->NextSiblingElement("ligne");
		}
		cout << "ligne ok" << endl;
		// -------------- GESTION DES TRAM --------------

		//Recupération des trams..............
		//Je recupere les trams puis le premier arret de ces tram
		TiXmlElement * trams = racine->FirstChildElement("trams");
		TiXmlElement * tram = trams->FirstChildElement("tram");

		while(tram) {
			//Création des trams
			mesTram[atoi(tram->Attribute("IndexlistTramAffect"))]->ajoutAuQueue(atoi(tram->Attribute("numero")), atoi(tram->Attribute("vitesseMax")), atoi(tram->Attribute("senseDep")), atoi(tram->Attribute("posX")), atoi(tram->Attribute("posY")), mesLigne[atoi(tram->Attribute("IndexLigneAffect"))]);
			tram = tram->NextSiblingElement("tram");
		}
		cout << "Tram  ok" << endl;
		// -------------- GESTION DES ARRETS DE DEPART --------------

		//Recupération des arret de depart des trams..............
		//Je recupere les trams puis le premier arret de ces tram
		TiXmlElement * arretDeparts = racine->FirstChildElement("arretDeparts");
		TiXmlElement * arretDepart = arretDeparts->FirstChildElement("arretDepart");

		while(arretDepart) {
			//définition des arret de depart des trams
			mesTram[atoi(arretDepart->Attribute("IndexListTram"))]->accesAuCorps(atoi(arretDepart->Attribute("indexTram")))->arretActuel = mesArret[atoi(arretDepart->Attribute("indexListArret"))]->accesAuCorps(atoi(arretDepart->Attribute("indexArret")));
			mesTram[atoi(arretDepart->Attribute("IndexListTram"))]->accesAuCorps(atoi(arretDepart->Attribute("indexTram")))->posX = mesArret[atoi(arretDepart->Attribute("indexListArret"))]->accesAuCorps(atoi(arretDepart->Attribute("indexArret")))->posX;
			mesTram[atoi(arretDepart->Attribute("IndexListTram"))]->accesAuCorps(atoi(arretDepart->Attribute("indexTram")))->posY = mesArret[atoi(arretDepart->Attribute("indexListArret"))]->accesAuCorps(atoi(arretDepart->Attribute("indexArret")))->posY;
			mesArret[atoi(arretDepart->Attribute("indexListArret"))]->accesAuCorps(atoi(arretDepart->Attribute("indexArret")))->numTramsSurPlace = mesTram[atoi(arretDepart->Attribute("IndexListTram"))]->accesAuCorps(atoi(arretDepart->Attribute("indexTram")))->numLigne;
			arretDepart = arretDepart->NextSiblingElement("arretDepart");
		}
		cout << "Depart ok" << endl;
		// -------------- FIN DES INITIALISATION DES STRUCTURES -> DEBUT DE SIMULATION --------------
		TiXmlElement * TempsSimulation = racine->FirstChildElement("tempsSimulation")->FirstChildElement("temps");
		//int temps = atoi(TempsSimulation->Attribute("tempsSimu"));
		cout << "Debut de la simulation pour un temps de : " << temps << " secondes." << endl << "Merci de ne pas deplacer la fenetre console durant cette periode." << endl;

		tracer * d = new tracer(800, 800);
		d->simulerTram(mesLigne, temps);
	}
}
