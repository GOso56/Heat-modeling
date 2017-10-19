// u1-interface.h
// Sentinelle d'inclusion
#ifndef _u1_interface_h
#define _u1_interface_h

// Declarations externes - inclusion des fichiers d'entete
#include "main.h"
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <FL/Fl_Value_Output.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_BMP_Image.H>
#include <FL/Fl.H>
#include <FL/fl_draw.H> 
#include <FL/fl_ask.H>
#include <FL/Fl_Shared_Image.H> 
#include <FL/Fl_Box.H> 
#include <FL/Fl_Menu_.H>
#include <FL/Fl_Menu_Bar.H>

// Definition des constantes
#define X_ZONE  0      // X de la zone
#define Y_ZONE  30      // Y de la zone
#define L_ZONE  600     // Largeur de la zone
#define H_ZONE  600     // Hauteur de la zone

// Declaration des objets de l'interface
struct Interface
{
    Fl_Double_Window*   Fenetre ;
    DrawingArea*        ZoneDessin ;
    Fl_Button*          BoutonQuitter ;
    Fl_Box*		box ;
    Fl_JPEG_Image* 	glacon ;
    Fl_Value_Slider* 	Curseur ;
    Fl_Value_Slider* 	Zoom ;
    Fl_Value_Output*	Temps ;
    Fl_Value_Output*	TempsSimulation ;
    Fl_Value_Output*    Temper ;
    Fl_Value_Output*    Contrainte ;
    Fl_Value_Output*	Distance ;
    Fl_Input*           ChampSaisieTxt ;
    Fl_Button*          BoutonRejouer ;
    Fl_Check_Button*    Recadrer ;
    Fl_Choice*          Menu ;
    Fl_Choice*          Experience ;
    Fl_Button*          BoutonDemarrer ;
    Fl_Button*          BoutonMessage ;
    Fl_Button*          BoutonInfo ;
    Fl_Button*          BoutonQuestion ;
    Fl_Menu_Bar*	Item;
} ;

// Declaration des objets de l'interface generale - ne pas supprimer
extern struct Interface gInterface ;

struct Par
{
    Fl_Double_Window*   Fenetre ;
    Fl_Check_Button*    CaseCocher ;
    Fl_Value_Input*     SaisieTeau ;
    Fl_Value_Input*     SaisieTglacon ;
    Fl_Value_Input*     SaisieCp ;
    Fl_Value_Input*     SaisieRo ;
    Fl_Value_Input*     SaisieLambda ;
    Fl_Value_Input*     SaisieRayon ;
    Fl_Value_Input*     SaisieE ;
    Fl_Value_Input*     SaisieH;
    Fl_Value_Input*     SaisieContrainte;
    
    Fl_Value_Output*    Teau ;
    Fl_Value_Output*    Tglacon ;
    Fl_Value_Output*    Cp ;
    Fl_Value_Output*    Ro ;
    Fl_Value_Output*    Lambda ;
    Fl_Value_Output*    Rayon ;
    Fl_Value_Output*    E ;
    Fl_Value_Output*    h ;
    Fl_Value_Output*    ContrainteMax ;
    Fl_Button*          BoutonInfo ;
    Fl_Button*          BoutonValider ;
} ;

extern struct Par par ;

struct Prog
{
    Fl_Double_Window*   Fenetre ;
    Fl_Check_Button*    CaseTime ;
    Fl_Value_Output*    pTime ;
    Fl_Value_Input*     SaisieTime ;
    Fl_Value_Output*    pdx ;
    Fl_Value_Output*    pdt ;
    Fl_Value_Output*    pNt ;
    Fl_Value_Output*    pNx ;
    Fl_Button*          BoutonInfo ;
    Fl_Button*          BoutonQuitter ;
} ;

extern struct Prog prog ;

struct Graph 
{
    Fl_Double_Window*   Fenetre ;
    DrawingArea*        ZoneDessin ;
    Fl_Check_Button*    AfficherContrainteMax ;
    Fl_Button*          Valider ;
    Fl_Choice*		CouleurT ;
    Fl_Choice*		CouleurC ;
} ;

extern struct Graph graph ;

struct Aide
{
    Fl_Double_Window*   Fenetre ;
    DrawingArea*        ZoneDessin ;
    Fl_Button* 		Quitter ;
} ;

extern struct Aide aide ;

struct Xp
{
    Fl_Double_Window*   Fenetre ;
    DrawingArea*        ZoneDessin ;
    DrawingArea*        PetitDessin ;
    Fl_Choice*     	NbXp ;
    Fl_Menu_Bar*	Item;
    Fl_Choice*     	ChoixXp1 ;
    Fl_Choice*     	ChoixXp2 ;
    Fl_Choice*     	ChoixXp3 ;
    Fl_Choice*     	ChoixXp4 ;
    Fl_Value_Input*     De1 ;
    Fl_Value_Input*     De2 ;
    Fl_Value_Input*     De3 ;
    Fl_Value_Input*     A1 ;
    Fl_Value_Input*     A2 ;
    Fl_Value_Input*     A3 ;
    Fl_Value_Input*     ParPas1 ;
    Fl_Value_Input*     ParPas2 ;
    Fl_Value_Input*     ParPas3 ;

    Fl_Value_Input*     SaisieTsolv ;
    Fl_Value_Input*     SaisieTglacon ;
    Fl_Value_Input*     SaisieCp ;
    Fl_Value_Input*     SaisieRo ;
    Fl_Value_Input*     SaisieLambda ;
    Fl_Value_Input*     SaisieRayon ;
    Fl_Value_Input*     SaisieE ;
    //Fl_Button*          BoutonInfo ;
    Fl_Button*          BoutonValider ;
    Fl_Button*          BoutonValider1 ;
    Fl_Button*          BoutonValider2 ;
    Fl_Button*          BoutonValider3 ;
    Fl_Button*          BoutonValider4 ;
} ;

extern struct Xp xp ;

// Declaration des sous-programmes
void CreerInterface();
void ActualiserInterface();

#endif // _u1_interface_h
