// u1-interface.cpp
// Declarations externes - inclusion des fichiers d'entete
// Librairies standards
#include <iostream>         // cin, cout, ...
// Programmes locaux
#include "u1-interface.h"
#include "u2-dessin.h"
#include "u3-callbacks.h"
#include "u4-fonctions.h"

// Declaration pour utiliser iostream
using namespace std;

// Definition des donnees de l'interface - structure globale de variables
struct Interface gInterface ;
struct Par par ;
struct Prog prog ;
struct Aide aide ;
struct Graph graph ;
struct Xp xp ;
// CreerInterface
void CreerInterface()
{
    
    // Creation de la fenetre principale
    gInterface.Fenetre = new Fl_Double_Window(800,700);
    gInterface.Fenetre->label("equation de la chaleur") ;
    gInterface.Fenetre->begin() ;

    // Creation de la zone de dessin
    gInterface.ZoneDessin = new DrawingArea(X_ZONE,Y_ZONE,L_ZONE,H_ZONE);
    gInterface.ZoneDessin->draw_callback( ZoneDessinDessinerCB, NULL ) ;
    gInterface.ZoneDessin->mouse_callback( ZoneDessinSourisCB, NULL ) ;
    gInterface.ZoneDessin->keyboard_callback( ZoneDessinClavierCB, NULL ) ;

     //Creation du menu
    gInterface.Item = new Fl_Menu_Bar(0,0,L_ZONE,25) ;
    gInterface.Item->add("Fichier/Fermer",   FL_CTRL+'c', QuitCB);
    gInterface.Item->add("Options/Parametres",FL_CTRL+'p', ParametreCB);
    gInterface.Item->add("Options/Programme",FL_CTRL+'m', ProgCB);
    gInterface.Item->add("Affichage/Interface graphique",FL_CTRL+'a',InterfaceCB);
    gInterface.Item->add("Experiences/Experiences",0,ExperienceCB);
    gInterface.Item->add("Aide/aide",0,AideCB);


    // Creation du bouton Demarrer
    gInterface.BoutonDemarrer = new Fl_Button(630, 10, 100, 20, "Demarrer") ;
    gInterface.BoutonDemarrer->callback( BoutonDemarrerCB, NULL ) ;

    // Creation du bouton Rejouer
    gInterface.BoutonRejouer = new Fl_Button(630, 40, 150, 20, "Relancer la simulation") ;
    gInterface.BoutonRejouer->callback( BoutonRejouerCB, NULL ) ;
    
    //Creation d'une zone de texte
    gInterface.TempsSimulation = new Fl_Value_Output( 730, 70, 70, 50,"Temps de\nla simulation " ) ; //730,70
   
    //Creation du curseur
    gInterface.Curseur = new Fl_Value_Slider( 700,150, 100, 50, "vitesse" ) ;
    gInterface.Curseur->type( FL_HORIZONTAL ) ;
    gInterface.Curseur->align( FL_ALIGN_LEFT ) ;
    gInterface.Curseur->bounds(1, NT) ;
    gInterface.Curseur->callback( CurseurCB, NULL ) ;

    //Creation du curseur ZOOM
    gInterface.Zoom = new Fl_Value_Slider( 700,250, 100, 50, "Zoom" ) ;
    gInterface.Zoom->type( FL_HORIZONTAL ) ;
    gInterface.Zoom->align( FL_ALIGN_LEFT ) ;
    gInterface.Zoom->bounds(0.5, 3) ;
    gInterface.Zoom->callback( ZoomCB, NULL ) ;

    // Creation du menu d'options
    gInterface.Menu = new Fl_Choice( 700, 340, 100, 20, "Courbes" ) ;
    gInterface.Menu->add( "T = f(x)", "", MenuCB ) ;
    gInterface.Menu->add( "L' = f(t)", "", MenuCB ) ;
    gInterface.Menu->add( "sigma = f(t)", "", MenuCB ) ;
    gInterface.Menu->add("evolution de la temperature","",MenuCB);
    
    // Creation du menu Experience
    gInterface.Experience = new Fl_Choice( 700, 380, 100, 20, "Experience" ) ;
    gInterface.Experience->hide() ;
    /*gInterface.Experience->add( "T = f(x)", "", MenuCB ) ;
    gInterface.Experience->add( "L' = f(t)", "", MenuCB ) ;
    gInterface.Experience->add( "sigma = f(t)", "", MenuCB ) ;
    gInterface.Experience->add("evolution de la temperature","",MenuCB);*/
    

    // Creation du champ de saisie texte
    gInterface.ChampSaisieTxt = new Fl_Input(730, 450, 70, 20, "Nom du solvant: ") ;
    gInterface.ChampSaisieTxt->when( FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE ) ;
    gInterface.ChampSaisieTxt->callback(ChampSaisieTxtCB, NULL ) ;

    //Creation du bouton recadrer
    gInterface.Recadrer = new Fl_Check_Button(700,550,60,20,"Recadrer") ;
    gInterface.Recadrer -> callback(RecadrerCB, NULL) ; 

    //Creation de la zone Temps
    gInterface.Temps = new Fl_Value_Output(50, 650, 70, 40,"Temps " ) ; 

     //Creation d'une zone de texte temperature
    gInterface.Temper = new Fl_Value_Output( 200, 650, 70, 40,"Temperature " ) ; 

     //Creation d'une zone de texte Contrainte
    gInterface.Contrainte = new Fl_Value_Output( 350, 650, 70, 40,"Contrainte" ) ; 
  
    //Creation d'une zone de texte
    gInterface.Distance = new Fl_Value_Output( 500, 650, 70, 40,"Distance " ) ; 

    // Creation du bouton Quitter
    gInterface.BoutonQuitter = new Fl_Button(740, 670, 50, 20, "Quitter") ;
    gInterface.BoutonQuitter->callback( BoutonQuitterCB, NULL ) ;
    
    //gInterface.box = new Fl_Box(100,100,L_ZONE-20,H_ZONE-20,""); // widget that will contain image 
    //gInterface.glacon = new Fl_JPEG_Image("media/glacon.jpg") ;
    
    //Fl_Shared_Image *img = Fl_Shared_Image::get("media/glacon.jpg"); 
    //gInterface.box->image(gInterface.glacon);
    //gInterface.box->redraw() ;
    //Fl_JPEG_Image phelma("media/logophelma.jpg") ;
    //phelma.draw(10,10,76,120,0,0);

    
    // Affichage de la fenetre
    gInterface.Fenetre->end();
    gInterface.Fenetre->show();
}

void ActualiserInterface()
{

}
