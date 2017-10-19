// u2-dessin.cpp
// Declarations externes - inclusion des fichiers d'entete
// Librairies standards
#include <iostream>         // cin, cout, ...
// Librairies fltk
#include <FL/Fl.H>
#include <FL/fl_draw.H>     // fonctions de dessin
// Programmes locaux
#include "u1-interface.h"
#include "u2-dessin.h"
#include "u4-fonctions.h"


// Declaration pour utiliser iostream
using namespace std;

// DessinerZone
void ZoneDessinDessinerCB( Fl_Widget* widget, void* data )
{
    // On efface toute la zone ( en dessinant dessus un rectangle plein, noir )
    fl_color(FL_WHITE);
    fl_rectf(X_ZONE, Y_ZONE, L_ZONE, H_ZONE);
    
    fl_font(FL_HELVETICA_BOLD, 25);
    fl_color(FL_BLACK);
    fl_draw("Etude du choc thermique d'un glacon",L_ZONE/5,50);
    fl_font(FL_HELVETICA, 20);
    fl_color(FL_BLACK);
    fl_draw("Elisa,Morgan,Clement et Gauthier",L_ZONE/5,75) ;

    fl_color(FL_BLACK) ;
    fl_rectf(gAffichage.x,gAffichage.y,gAffichage.epaisseur,gAffichage.longueur) ;
    fl_rectf(gAffichage.x,gAffichage.y+gAffichage.longueur,gAffichage.longueur,gAffichage.epaisseur) ;
    fl_rectf(gAffichage.x+gAffichage.longueur,gAffichage.y,gAffichage.epaisseur,gAffichage.longueur) ;
    //fl_rectf(gAffichage.x,gAffichage.y,gAffichage.longueur,gAffichage.longueur);
    //fl_color(FL_WHITE) ;
    //fl_rectf(gAffichage.x+gAffichage.epaisseur,gAffichage.y,gAffichage.longueur-gAffichage.epaisseur,gAffichage.longueur-2*gAffichage.epaisseur);
    fl_color(FL_BLACK) ;
    fl_rectf(gAffichage.x+(gAffichage.longueur)/2,gAffichage.y,10,gAffichage.longueur) ;

   /* fl_font(FL_HELVETICA, 2*gAffichage.epaisseur);
    fl_color(FL_BLACK);
    fl_draw("Temperature (K)",gAffichage.x+(gAffichage.longueur)/2,gAffichage.y - 10);*/
    //fl_draw("Distance",gAffichage.x + gAffichage.longueur+gAffichage.epaisseur+10, gAffichage.y+gAffichage.longueur) ;
    fl_font(FL_HELVETICA, 15);
    fl_color(FL_BLACK);
    fl_draw("Coeur du glacon",gAffichage.x+(gAffichage.longueur)/2-30,gAffichage.y+gAffichage.longueur+gAffichage.epaisseur + 10);
    fl_draw("Paroi",gAffichage.x,gAffichage.y+gAffichage.longueur+gAffichage.epaisseur+10);
    fl_draw("Paroi",gAffichage.x+gAffichage.longueur+gAffichage.epaisseur+10,gAffichage.y+gAffichage.longueur+gAffichage.epaisseur+10);
    fl_color(FL_BLUE);
    fl_draw("Solvant ",gAffichage.x-60,gAffichage.y+(gAffichage.longueur)/2);
    fl_draw("Solvant ",gAffichage.x+gAffichage.longueur+gAffichage.epaisseur+10,gAffichage.y+(gAffichage.longueur)/2);

    fl_color(FL_RED);
    fl_draw("Condition initiale",gAffichage.x+gAffichage.longueur+gAffichage.epaisseur,gAffichage.y);
    fl_draw("Teau (K)",gAffichage.x+gAffichage.longueur+gAffichage.epaisseur+15,gAffichage.y+30);
    fl_draw("Tglacon (k)",gAffichage.x+gAffichage.longueur+gAffichage.epaisseur+15,gAffichage.y+60);
    fl_draw("Taille du glacon\n(m)",gAffichage.x+gAffichage.longueur+gAffichage.epaisseur+15,gAffichage.y+90);
    fl_rect(gAffichage.x+gAffichage.longueur+gAffichage.epaisseur+5,gAffichage.y+17,gAffichage.epaisseur,80);
  
    fl_font(FL_HELVETICA_BOLD, 15);
    fl_color(FL_BLUE);
    fl_draw(gDonnees.nom,gAffichage.x-60,gAffichage.y+(gAffichage.longueur)/2+30);
    fl_draw(gDonnees.nom,gAffichage.x+gAffichage.longueur+gAffichage.epaisseur+10,gAffichage.y+(gAffichage.longueur)/2+30);
   
    Fl_BMP_Image ImageLogoPhelma("media/logophelma.bmp") ;
    //Fl_JPEG_Image ImageLogoPhelma("media/logophelma.jpg") ;
    ImageLogoPhelma.draw(480,30);

    Fl_BMP_Image ImageGlacon("media/glacon.bmp") ;
    //Fl_JPEG_Image ImageLogoPhelma("media/logophelma.jpg") ;
    ImageGlacon.draw(-50,20);


    int i,j;
    double posx, posy,echelle ;
    posx = gAffichage.longueur/NX ;
    posy = gAffichage.y+gAffichage.longueur ;
    echelle = (gAffichage.longueur)/(273.15-gDonnees.var.Tglacon) ;


    if(gAffichage.contrainteMax == 1)
    {
	double ymax;
	ymax = gAffichage.y + gAffichage.longueur ;
	//gInterface.Contrainte->value((ymax - Fl::event_y())*30/gAffichage.longueur) ;
	fl_color(FL_GREEN);
	fl_rectf(gAffichage.x,ymax - gAffichage.contrainteMax*gAffichage.longueur/15,gAffichage.longueur,3) ;
	fl_font(FL_HELVETICA, 20);
	fl_color(FL_GREEN);
	fl_draw("Contrainte",gAffichage.x-70,ymax - gDonnees.var.contrainteMax*gAffichage.longueur/15);
	fl_draw("max",gAffichage.x-40,ymax - gDonnees.var.contrainteMax*gAffichage.longueur/15+20);
    }
    
    if(gDonnees.demarrer != 0)
    {
	fl_color(FL_RED);
	fl_draw(gDonnees.var.nomTeau,gAffichage.x+gAffichage.longueur+gAffichage.epaisseur+120,gAffichage.y+30);
    	fl_draw(gDonnees.var.nomTglacon,gAffichage.x+gAffichage.longueur+gAffichage.epaisseur+120,gAffichage.y+60);
   	fl_draw(gDonnees.var.nomRayon,gAffichage.x+gAffichage.longueur+gAffichage.epaisseur+120,gAffichage.y+90);

	for(i = 0; i < NT; i++)
    	{
		for(j=0;j<=NX;j++)
		{
			ChoisirCouleurPion(gAffichage.couleur[0] );
			//fl_line_style( FL_SOLID, gAffichage.epaisseur ) ; //FL_SOLID, FL_DASH, FL_DASH_DOT
			//fl_line( gAffichage.x+gAffichage.epaisseur+posx*j,posy+(gDonnees.var.Tglacon-temperature[j][i])*echelle, gAffichage.x+gAffichage.epaisseur+posx*j,posy+(gDonnees.var.Tglacon-temperature[j+1][i])*echelle) ;
    			//fl_point(X+3*j,(Y+400)-temperature[j][i]);
			fl_point(gAffichage.x+gAffichage.epaisseur+posx*j,posy+(gDonnees.var.Tglacon-temperature[j][i])*echelle);

		}
    	}
    }	


    if(gDonnees.astuce[0] != 0)
    {
	for(i=0;i<20;i++)
	{
		for(j=0;j<NX;j++)
		{
			ChoisirCouleurPion(gAffichage.couleur[1]) ;
			fl_point(gAffichage.x+gAffichage.epaisseur+posx*j,posy - dessinContrainte[j][i]*((gAffichage.longueur)/15)) ;
		}
	}
    }	
}



void ChoisirCouleurPion(int Pion) // Correspondance numero de pion avec couleur associee, sert au dessin des pions du jeu
{
    switch (Pion) {
        // -1 : case vide pour placer un pion de couleur
        case 0 : fl_color(FL_DARK2); break;
        case 1 : fl_color(FL_CYAN); break;
        case 2 : fl_color(FL_BLUE); break;
        case 3 : fl_color(FL_RED); break;
        case 4 : fl_color(FL_YELLOW); break;
        case 5 : fl_color(FL_GREEN); break;
        case 6 : fl_color(FL_MAGENTA); break;
    }
}








