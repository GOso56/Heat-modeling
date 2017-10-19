// u3-callbacks.cpp
// Declarations externes - inclusion des fichiers d'entete
// Librairies standards
#include <iostream>     // cout, cin, ...
// Librairies fltk
#include <FL/Fl.H>
#include <FL/fl_ask.H>  // fl_message, fl_alert, fl_ask
#include <FL/Fl_File_Chooser.H> // fl_file_chooser
// Programmes locaux
#include "u1-interface.h"
#include "u3-callbacks.h"
#include "u4-fonctions.h"

// Declaration pour utiliser iostream
using namespace std;

// TraiterCycle
void TraiterCycleCB()
{
	if(gDonnees.demarrer != 0)
	{
		if(gDonnees.astuce[0] == 0)
		{
			int i;
			ouvertureFichier() ;
			for( i=gDonnees.debut ; i< gDonnees.curseur && i < NT; i++)
				euler_explicite(i) ;
			
    			gDonnees.debut = i ;
			gDonnees.curseur++ ;

			if(i == NT)
			{
				etudeContrainte() ;
				gDonnees.astuce[0] = 1 ;
			}
			fermetureFichier() ;
		}
	}
	gInterface.ZoneDessin->redraw() ;
	
}

// ZoneDessinSourisCB
void ZoneDessinSourisCB( Fl_Widget* widget, void* data )
{
    // ATTENTION : X et Y ne sont pas relatifs a la zone mais a la fenetre qui la contient !!!!

    // Exemple d'evenement : clic souris
    if ( Fl::event() == FL_PUSH )
    {
	double xmin,xmax,ymin,ymax,echelle,dist;
	xmin = gAffichage.x +gAffichage.epaisseur ;
	xmax = gAffichage.x + gAffichage.longueur ;
	ymin = gAffichage.y;
	ymax = gAffichage.y + gAffichage.longueur ;
	echelle = -(gDonnees.var.Tglacon -273.15)/gAffichage.longueur ;
	dist = gDonnees.var.rayon*2/gAffichage.longueur ;

	//printf("event y %i\n",Fl::event_y());
	//printf("ymax: %lf\n",ymax);
	//printf("en y: %lf\n",gAffichage.y) ;
	if(xmin<Fl::event_x()<xmax && ymin<Fl::event_y()<ymax)
	{
		gInterface.Contrainte->value((ymax - Fl::event_y())*15/gAffichage.longueur) ;
		gInterface.Temper -> value((ymax - Fl::event_y())*echelle+gDonnees.var.Tglacon-273.15) ;

		if(Fl::event_x()>xmin+gAffichage.longueur/2)		
			gInterface.Distance->value((xmax - Fl::event_x())*dist) ;
		else
			gInterface.Distance->value(-(gAffichage.x - Fl::event_x())*dist) ;
	}

	if(gDonnees.recadrer == 1)
	{
		gAffichage.x += -Fl::event_x()+L_ZONE/2 ;
		gAffichage.y += -Fl::event_y()+Y_ZONE+H_ZONE/2;
	}

    }

}



// ZoneDessinClavierCB
void ZoneDessinClavierCB( Fl_Widget* widget, void* data )
{
    // Definition des variables
    int Touche ;

    // Recuperation de la touche clavier activee
    Touche = Fl::event_key() ;

    // Traitement de la touche
    switch ( Touche )
    {
        // Touches speciales
        case FL_Left :
            printf("Appui sur la touche Gauche\n");
            break;
        case FL_Right :
            printf("Appui sur la touche Droite\n");
            break;
        case FL_Up :
            printf("Appui sur la touche Haut\n");
            break ;
        case FL_Down :
            printf("Appui sur la touche Bas\n");
            break ;
        // Caracteres
        case ' ' :
            printf("Appui sur la touche Espace\n");
            break ;
        case 'a' :
            printf("Appui sur le caractere a\n");
            break ;
        case 'b' :
            printf("Appui sur le caractere b\n");
            break ;
        case '1' :
            printf("Appui sur le caractere 1\n");
            break ;
        case '2' :
            printf("Appui sur le chiffre 2\n");
            break ;
    }
}


void CurseurCB(Fl_Widget* w, void* data)
{
    gDonnees.curseur += (int)gInterface.Curseur->value() ;
}



void BoutonRejouerCB(Fl_Widget* w, void* data)
{
    InitialiserDonnees();
    gInterface.Fenetre->redraw();
}

void RecadrerCB(Fl_Widget* w, void* data)
{
	gDonnees.recadrer = (int) gInterface.Recadrer->value() ;
}


void BoutonDemarrerCB(Fl_Widget* w, void* data)
{
	if(gDonnees.astuce[1] == 0)
	{
		fl_message("Bonjour!\nCe programme a pour objectif d'etudier les glacons.\n Un menu ci-contre vous permet d'exploiter des resultats experimentales.\n" );
		gDonnees.astuce[1] = 1 ;
	}

	if(gDonnees.valider == 1) 
	{	
		gDonnees.demarrer = 1; //equivalent a var.demarrer = gInterface.BoutonDemarrer->value();
		gDonnees.astuce[0] = 0;
		
		sprintf(gDonnees.var.nomTeau,"%.1lf",gDonnees.var.Teau) ;
		sprintf(gDonnees.var.nomTglacon,"%.1lf",gDonnees.var.Tglacon) ;
		sprintf(gDonnees.var.nomRayon,"%.1lf",gDonnees.var.rayon) ;
		
	}
	else
	{
		gDonnees.option = fl_choice("Les parametres ont ete regles par defaut, souhaitez vous les modifier?","non","oui","quitter") ;
		if(gDonnees.option == 0)
		{
			gDonnees.demarrer = 1;
			gDonnees.astuce[0] = 0 ;
			TemperatureInit() ;
			sprintf(gDonnees.var.nomTeau,"%lf",gDonnees.var.Teau) ;
			sprintf(gDonnees.var.nomTglacon,"%lf",gDonnees.var.Tglacon) ;
			sprintf(gDonnees.var.nomRayon,"%lf",gDonnees.var.rayon) ;
			
			
		}
		else if(gDonnees.option == 1)
			fl_message("Options/parametres/activer la modification") ;
		else
		{
			FermerMat();
			exit(0) ;
		}
	}
}

void MenuCB(Fl_Widget* w, void* data)
{
    if(gDonnees.demarrer != 0) //Si l'on a lance la simulation 
    {
    	FILE *gp = NULL;
    	int valeur;
    	valeur = gInterface.Menu->value();
    	switch(valeur) //selon le choix de l'utilisateur, on affiche avec gnuplot le graph
    	{
		case 0: gp = popen("gnuplot -persist", "w"); //GNUPLOT_PATH
			fprintf(gp,"set title 'Simulation numerique equation de la chaleur'\n");
			fprintf(gp,"set xlabel 'Distance au coeur du glacon'\n");
			fprintf(gp,"set ylabel 'Temperature'\n");
			fprintf(gp,"plot 'temperature.txt' with lines\n") ;
			pclose(gp);
			break;
		case 1: gp = popen("gnuplot -persist", "w"); //GNUPLOT_PATH
			fprintf(gp,"set title 'Elongation du glacon en fonction du temps'\n");
			fprintf(gp,"set xlabel 'temps'\n");
			fprintf(gp,"set ylabel 'elongation'\n");
			fprintf(gp,"plot 'elongation.txt' with lines\n") ;
			pclose(gp);
			break;
		case 2: gp = popen("gnuplot -persist", "w"); //GNUPLOT_PATH
			fprintf(gp,"set title 'Contrainte en fonction du temps'\n");
			fprintf(gp,"set xlabel 'distance au coeur du glacon'\n");
			fprintf(gp,"set ylabel 'Contrainte (Gpa)'\n");
			fprintf(gp,"plot 'contrainte.txt' with lines\n") ;
			pclose(gp);
			break;
		case 3: gp = popen("gnuplot -persist", "w"); //GNUPLOT_PATH
			fprintf(gp,"set title 'Temperature en fonction du temps'\n");
			fprintf(gp,"set xlabel 'distance au coeur du glacon'\n");
			fprintf(gp,"set ylabel 'Temperature (K)'\n");
			fprintf(gp,"plot 'evolution.txt' with lines\n") ;
			pclose(gp);
			break;
		default: break;
    	}
    }
    else
	gInterface.Menu->deactivate() ; //si le mode lancer la simulation n'a pas ete choisi, on desactive le bouton energie
}


void ChampSaisieTxtCB(Fl_Widget* w, void* data)
{
    strcpy( gDonnees.nom, gInterface.ChampSaisieTxt->value() ) ;
}

void BoutonQuitterCB(Fl_Widget* w, void* data)
{
    FermerMat() ;
    // Fin du programme
    exit(0) ;
}


void QuitCB(Fl_Widget *, void *) 
{
    FermerMat();
    exit(0);
}		

void ZoomCB(Fl_Widget* w, void* data)
{
    gAffichage.longueur = 400;
    gAffichage.epaisseur = 5 ;
    gAffichage.longueur *= (double)gInterface.Zoom->value() ;
    gAffichage.epaisseur*= (double)gInterface.Zoom->value() ; 
}


/* ************************************************************************************************************************************************************************************************************************* /
						Menu / Parametre / Parametres
/ ************************************************************************************************************************************************************************************************************************* */

void ParametreCB(Fl_Widget *w, void *) 
{
	// Creation de la fenetre principale
    	par.Fenetre = new Fl_Double_Window(330,330);
    	par.Fenetre->label("Options") ;
    	par.Fenetre->begin() ;

	// Creation de la case a cocher
    	par.CaseCocher = new Fl_Check_Button(10, 10, 200, 20, "Activer les modifications") ;
    	par.CaseCocher->callback(CaseCocherCB, NULL ) ;
		

	// Creation du champ de saisie numerique pour Tglacon
    	par.SaisieTglacon = new Fl_Value_Input(250, 30, 50, 20, "") ;
    	par.SaisieTglacon->when( FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE ) ;
    	par.SaisieTglacon->callback(SaisieTglaconCB, NULL ) ;
	par.SaisieTglacon -> hide() ;

	// Creation du champ de saisie numerique pour Teau
    	par.SaisieTeau = new Fl_Value_Input(250, 60, 50, 20, "") ;
    	par.SaisieTeau->when( FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE ) ;
    	par.SaisieTeau->callback(SaisieTeauCB, NULL ) ;
	par.SaisieTeau->hide();

	// Creation du champ de saisie numerique pour masse volumique
    	par.SaisieRo = new Fl_Value_Input(250, 90, 50, 20, "") ;
    	par.SaisieRo->when( FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE ) ;
    	par.SaisieRo->callback(SaisieRoCB, NULL ) ;
	par.SaisieRo->hide();

	// Creation du champ de saisie numerique pour lambda
	par.SaisieLambda = new Fl_Value_Input(250, 120, 50, 20, "") ;
	par.SaisieLambda->when( FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE ) ;
	par.SaisieLambda->callback(SaisieLambdaCB, NULL ) ;
	par.SaisieLambda->hide();

	// Creation du champ de saisie numerique pour Cp
	par.SaisieCp = new Fl_Value_Input(250, 150, 50, 20, "") ;
	par.SaisieCp->when( FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE ) ;
	par.SaisieCp->callback(SaisieCpCB, NULL ) ;
	par.SaisieCp->hide();

	// Creation du champ de saisie numerique pour rayon
	par.SaisieRayon = new Fl_Value_Input(250, 180, 50, 20, "") ;
	par.SaisieRayon->when( FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE ) ;
	par.SaisieRayon->callback(SaisieRayonCB, NULL ) ;
	par.SaisieRayon->hide();

	// Creation du champ de saisie numerique pour module Young E
	par.SaisieE = new Fl_Value_Input(250, 210, 50, 20, "") ;
	par.SaisieE->when( FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE ) ;
	par.SaisieE->callback(SaisieRayonCB, NULL ) ;	
	par.SaisieE->hide() ;

	// Creation du champ de saisie numerique pour coeff conductoconvectif
	par.SaisieH = new Fl_Value_Input(250, 240, 50, 20, "") ;
	par.SaisieH->when( FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE ) ;
	par.SaisieH->callback(SaisieHCB, NULL ) ;	
	par.SaisieH->hide() ;

	//Creation du champ de saisie de la contrainte a la rupture
	par.SaisieContrainte = new Fl_Value_Input(250, 270, 50, 20, "") ;
	par.SaisieContrainte->when( FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE ) ;
	par.SaisieContrainte->callback(SaisieContrainteCB, NULL ) ;	
	par.SaisieContrainte->hide() ;

	// Creation du champ de saisie numerique pour Tglacon
    	par.Tglacon = new Fl_Value_Output(160, 30, 50, 20, "Temperature glacon ") ;
	par.Tglacon->value(-18+273.15) ;

	// Creation du champ de saisie numerique pour Teau
    	par.Teau = new Fl_Value_Output(160, 60, 50, 20, "Temperature liquide ") ;
    	par.Teau->value(18+273.15) ;

	// Creation du champ de saisie numerique pour masse volumique
    	par.Ro = new Fl_Value_Output(160, 90, 50, 20, "Masse volumique ") ;
    	par.Ro->value(917) ;

	// Creation du champ de saisie numerique pour lambda
	par.Lambda = new Fl_Value_Output(160, 120, 50, 20, "Lambda ") ;
	par.Lambda->value(2.1) ;

	// Creation du champ de saisie numerique pour Cp
	par.Cp = new Fl_Value_Output(160, 150, 50, 20, "Cp ") ;
	par.Cp->value(2060) ;

	// Creation du champ de saisie numerique pour rayon
	par.Rayon = new Fl_Value_Output(160, 180, 50, 20, "Rayon ") ;
	par.Rayon->value(gDonnees.var.rayon) ;

	// Creation du champ de saisie numerique pour module Young E
	par.E = new Fl_Value_Output(160, 210, 50, 20, "E ") ;
	par.E->value(9.33e3) ;

	// Creation du champ de saisie numerique pour h
	par.h = new Fl_Value_Output(160, 240, 50, 20, "h ") ;
	par.h->value(100) ;

	// Creation du champ de saisie numerique pour sigma max
	par.ContrainteMax = new Fl_Value_Output(160, 270, 50, 20, "Contrainte Max ") ;
	par.ContrainteMax->value(2.8) ;

	// Creation du bouton Quitter
	par.BoutonValider = new Fl_Button(80, 300, 100, 20, "Valider") ;
	par.BoutonValider->callback( BoutonValiderCB, NULL ) ;	

	// Creation du bouton Info
    	par.BoutonInfo = new  Fl_Button( 0, 300, 20, 20, "?") ;
    	par.BoutonInfo->callback( BoutonInfoCB) ;

	par.Fenetre->end();
    	par.Fenetre->show();

}

void CaseCocherCB(Fl_Widget* w, void* data)
{
    gDonnees.var.modifier = par.CaseCocher->value();
    if(gDonnees.var.modifier == 1)
    {
	par.SaisieTglacon -> show() ;
	par.SaisieTeau -> show() ;
	par.SaisieRo -> show() ;
	par.SaisieLambda -> show ();
	par.SaisieCp -> show() ;
	par.SaisieRayon->show();
	par.SaisieE->show(); 
	par.SaisieH->show() ;
	par.SaisieContrainte->show() ;
     }
     else
     {
	par.SaisieTglacon -> hide() ;
	par.SaisieTeau -> hide() ;
	par.SaisieRo -> hide() ;
	par.SaisieLambda -> hide ();
	par.SaisieCp -> hide() ;
	par.SaisieRayon->hide();
	par.SaisieE->hide(); 
	par.SaisieH->hide() ;
	par.SaisieContrainte->hide() ;
     }
	
}

void BoutonInfoCB(Fl_Widget* w, void* data)
{
	fl_alert("Remplir tous les champs de saisie:\n**Temperature de l'eau\nTemperature du glacon\nmasse volumique\nconductivite thermique\nchaleur specifique\nRayon du glacon\n");
}

void BoutonValiderCB(Fl_Widget* w, void* data)
{
	gDonnees.var.alpha = gDonnees.var.lambda/((gDonnees.var.rho)*(gDonnees.var.cp)) ;
	//printf("alpha: %lf\n",gDonnees.var.alpha);
	gDonnees.var.B = (gDonnees.var.alpha)*gDonnees.var.dt/(gDonnees.var.dx*gDonnees.var.dx) ;
	//printf("B: %lf\n",gDonnees.var.B);
	gDonnees.valider = 1 ;
	TemperatureInit() ;
	par.Fenetre->hide() ;
}


void SaisieTglaconCB(Fl_Widget *, void *) 
{
	gDonnees.var.Tglacon = (double)par.SaisieTglacon->value() ;
	
}

void SaisieTeauCB(Fl_Widget *, void *) 
{
	gDonnees.var.Teau = (double)par.SaisieTeau->value() ;
}


void SaisieRoCB(Fl_Widget *, void *) 
{
	gDonnees.var.rho = (double)par.SaisieRo->value() ;
}

void SaisieLambdaCB(Fl_Widget *, void *) 
{
	gDonnees.var.lambda = (double)par.SaisieLambda->value() ;
}

void SaisieCpCB(Fl_Widget *, void *) 
{
	gDonnees.var.cp = (double)par.SaisieCp->value() ;
}

void SaisieRayonCB(Fl_Widget *, void *) 
{
	gDonnees.var.rayon = (double)par.SaisieRayon->value() ;
}

void SaisieECB(Fl_Widget *, void *) 
{
	gDonnees.var.E = (double)par.SaisieE->value() ;
}

void SaisieHCB(Fl_Widget *, void *) 
{
	gDonnees.var.h = (double)par.SaisieH->value() ;
}

void SaisieContrainteCB(Fl_Widget *, void *) 
{
	gDonnees.var.contrainteMax = (double)par.SaisieContrainte->value() ;
}
/* ************************************************************************************************************************************************************************************************************************* /
						Menu / Parametre / Programme
/ ************************************************************************************************************************************************************************************************************************* */

void ProgCB(Fl_Widget *w, void *) 
{
	// Creation de la fenetre principale
    	prog.Fenetre = new Fl_Double_Window(280,210);
    	prog.Fenetre->label("Programme") ;
    	prog.Fenetre->begin() ;

	// Creation de la case a cocher
    	prog.CaseTime = new Fl_Check_Button(5, 5, 200, 20, "Modifier le temps d'integration") ;
    	prog.CaseTime->callback(CaseTimeCB, NULL ) ;

	// Creation du champ de saisie numerique pour Temps integration
    	prog.pTime = new Fl_Value_Output(180, 30, 50, 20, "Temps d'integration") ;
    	prog.pTime->value(gDonnees.var.Time) ;

	// Creation du champ de saisie numerique pour Temps integration
    	prog.SaisieTime = new Fl_Value_Input(230, 30, 50, 20, " ") ;
    	prog.SaisieTime->when( FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE ) ;
	prog.SaisieTime->callback(SaisieTimeCB, NULL ) ;
	prog.SaisieTime->hide();

	// Creation du champ de saisie numerique pourpas d'espace
    	prog.pdx = new Fl_Value_Output(180, 60, 50, 20, "pas d'espace") ;
    	prog.pdx->value(gDonnees.var.rayon/NX) ;

	// Creation du champ de saisie numerique pour pas de temps
	prog.pdt = new Fl_Value_Output(180, 90, 50, 20, "pas de temps") ;
	prog.pdt->value(gDonnees.var.Time/NT) ;

	// Creation du champ de saisie numerique pour nombre de pas
	prog.pNx = new Fl_Value_Output(180, 120, 50, 20, "Nombre de pas d'espace") ;
	prog.pNx->value(NX) ;

	// Creation du champ de saisie numerique pour nombre de pas
	prog.pNt = new Fl_Value_Output(180, 150, 50, 20, "Nombre de pas de temps") ;
	prog.pNt->value(NT) ;

	// Creation du bouton Quitter
	prog.BoutonQuitter = new Fl_Button(180, 180, 100, 20, "Quitter") ;
	prog.BoutonQuitter->callback( BoutonQuitterProgCB, NULL ) ;	

	// Creation du bouton Info
    	prog.BoutonInfo = new  Fl_Button( 0, 180, 20, 20, "?") ;
    	prog.BoutonInfo->callback( BoutonInfoProgCB) ;

	prog.Fenetre->end();
    	prog.Fenetre->show();

}

void CaseTimeCB(Fl_Widget* w, void* data)
{
    switch(prog.CaseTime->value())
    {
	case 0: prog.SaisieTime->hide() ;
		break ;

	case 1: prog.SaisieTime->show() ;
		break ;
	
	default: break ;
    }	
}

void SaisieTimeCB(Fl_Widget* w, void* data)
{
	gDonnees.var.Time = (double)prog.SaisieTime->value() ;
}

void BoutonQuitterProgCB(Fl_Widget* w, void* data)
{
	prog.Fenetre->hide() ;
}

void BoutonInfoProgCB(Fl_Widget* w, void* data)
{
	fl_alert("Donnees du programme\n");
}
	



/* ************************************************************************************************************************************************************************************************************************* /
						Menu / Affichage / Interface Graphique 
/ ************************************************************************************************************************************************************************************************************************* */
void InterfaceCB(Fl_Widget *w, void *)
{
	// Creation de la fenetre principale
    	graph.Fenetre = new Fl_Double_Window(280,260);
    	graph.Fenetre->label("Interface Graphique") ;
    	graph.Fenetre->begin() ;

	//Creation bouton contrainte max
	graph.AfficherContrainteMax = new Fl_Check_Button(50,60,40,20,"Afficher la contrainte max") ;
    	graph.AfficherContrainteMax -> callback(AfficherContrainteCB, NULL) ;
	
	// Creation du menu d'options Couleur de temperature
   	graph.CouleurT = new Fl_Choice( 150, 100, 100, 20, "Couleur de la \ncourbe temperature" ) ;
    	graph.CouleurT->add( "Noir", "", MenuTCB ) ;
    	graph.CouleurT->add( "Cyan", "", MenuTCB ) ;
    	graph.CouleurT->add( "Bleu", "", MenuTCB ) ;
    	graph.CouleurT->add("Rouge","",MenuTCB);
	graph.CouleurT->add("Jaune","",MenuTCB);
	graph.CouleurT->add("Vert","",MenuTCB);
	graph.CouleurT->add("Magenta","",MenuTCB);

	// Creation du menu d'options Couleur de temperature
   	graph.CouleurC = new Fl_Choice( 150, 150, 100, 20, "Couleur de la \ncourbe temperature" ) ;
    	graph.CouleurC->add( "Noir", "", MenuCCB ) ;
    	graph.CouleurC->add( "Cyan", "", MenuCCB ) ;
    	graph.CouleurC->add( "Bleu", "", MenuCCB ) ;
    	graph.CouleurC->add("Rouge","",MenuCCB);
	graph.CouleurC->add("Jaune","",MenuCCB);
	graph.CouleurC->add("Vert","",MenuCCB);
	graph.CouleurC->add("Magenta","",MenuCCB);

	 // Creation du bouton Quitter
	graph.Valider = new Fl_Button(150, 240, 100, 20, "Quitter") ;
	graph.Valider->callback( BoutonValiderGraphCB, NULL ) ;

	graph.Fenetre->end();
    	graph.Fenetre->show();
}

void MenuTCB(Fl_Widget* w, void* data)
{
	gAffichage.couleur[0] = (int)graph.CouleurT->value() ;
}

void MenuCCB(Fl_Widget* w, void* data)
{
	gAffichage.couleur[1] = (int)graph.CouleurC->value() ;
}

void AfficherContrainteCB(Fl_Widget* w, void* data)
{
	gAffichage.contrainteMax = (double)graph.AfficherContrainteMax->value() ;
}

void BoutonValiderGraphCB(Fl_Widget* w, void* data)
{
	graph.Fenetre->hide() ;
}




/* ************************************************************************************************************************************************************************************************************************* /
						Menu / Aide / aide
/ ************************************************************************************************************************************************************************************************************************* */


void AideCB(Fl_Widget *w, void *)
{
	// Creation de la fenetre principale
    	aide.Fenetre = new Fl_Double_Window(300,250);
    	aide.Fenetre->label("Aide") ;
    	aide.Fenetre->begin() ;

	
    	// Creation de la zone de dessin
    	gInterface.ZoneDessin = new DrawingArea(0,0,250,200);
    	gInterface.ZoneDessin->draw_callback( MessageAideCB, NULL ) ;

	 // Creation du bouton Quitter
	aide.Quitter = new Fl_Button(100, 200, 100, 20, "Quitter") ;
	aide.Quitter->callback( BoutonQuitterAideCB, NULL ) ;

	aide.Fenetre->end();
    	aide.Fenetre->show();
}

void MessageAideCB(Fl_Widget* w, void* data)
{

    	// On efface toute la zone ( en dessinant dessus un rectangle plein, noir )
    	fl_color(FL_WHITE);
    	fl_rectf(0, 0,250,200);

	fl_font(FL_HELVETICA,10);
   	fl_color(FL_BLACK);
    	fl_draw("Pour tout probleme technique, veuillez ",10,10);
	fl_draw("contacter",10,60);
	fl_draw("Numero de tel:",10,110);
	fl_draw("adresse mail:",10,160);
	fl_font(FL_HELVETICA_BOLD,20);
   	fl_color(FL_BLACK);
	fl_draw("Morgan RUSINOVISCZ",100,60);
	fl_draw("0788347111",100,110);
	fl_draw("morganrusino@gmail.com",100,160);
}

void BoutonQuitterAideCB(Fl_Widget* w, void* data)
{
	aide.Fenetre->hide() ;
}




/* ************************************************************************************************************************************************************************************************************************* /
						Menu / Experience/ Experience
/ ************************************************************************************************************************************************************************************************************************* */

void ExperienceCB(Fl_Widget *w, void *)
{
	// Creation de la fenetre principale
    	xp.Fenetre = new Fl_Double_Window(320,380);
    	xp.Fenetre->label("Experimentation") ;
    	xp.Fenetre->begin() ;

	//Creation de la zone de saisie de la contrainte max
	xp.NbXp = new Fl_Choice(150,20,40,20,"Nombre d'experiences");
	xp.NbXp->add("1","",NbExpCB);
	xp.NbXp->add("2","",NbExpCB);
	xp.NbXp->add("3","",NbExpCB);
	xp.NbXp->add("4","",NbExpCB);

	//Creation du menu
   	xp.Item = new Fl_Menu_Bar(30,50,280,25) ;
	xp.Item->hide() ;

	// Creation de la zone de dessin
    	xp.ZoneDessin = new DrawingArea(0,200,200,200);
	xp.ZoneDessin -> draw_callback( DessinXpCB, NULL ) ;	

	xp.PetitDessin = new DrawingArea(0,280,100,100);
	xp.PetitDessin -> hide();

	xp.ChoixXp1 = new Fl_Choice(170,90,130,20,"Parametre a faire varier\nExperience 1");
	xp.ChoixXp1->add("Temperature de l'eau","",Choix1CB);
	xp.ChoixXp1->add("Temperature du glacon","",Choix1CB);
	xp.ChoixXp1->add("Taille du glacon","",Choix1CB);
	xp.ChoixXp1->add("Proprietes du solvant","",Choix1CB);
	xp.ChoixXp1->hide() ;	

	xp.ChoixXp2 = new Fl_Choice(170,90,130,20,"Parametre a faire varier\nExperience 2");
	xp.ChoixXp2->add("Temperature de l'eau","",Choix2CB);
	xp.ChoixXp2->add("Temperature du glacon","",Choix2CB);
	xp.ChoixXp2->add("Taille du glacon","",Choix2CB);
	xp.ChoixXp2->add("Proprietes du solvant","",Choix2CB);
	xp.ChoixXp2->hide() ;	

	xp.ChoixXp3 = new Fl_Choice(170,90,130,20,"Parametre a faire varier\nExperience 3");
	xp.ChoixXp3->add("Temperature de l'eau","",Choix3CB);
	xp.ChoixXp3->add("Temperature du glacon","",Choix3CB);
	xp.ChoixXp3->add("Taille du glacon","",Choix3CB);
	xp.ChoixXp3->add("Proprietes du solvant","",Choix3CB);
	xp.ChoixXp3->hide() ;	

	xp.ChoixXp4 = new Fl_Choice(170,90,130,20,"Parametre a faire varier\nExperience 4");
	xp.ChoixXp4->add("Temperature de l'eau","",Choix4CB);
	xp.ChoixXp4->add("Temperature du glacon","",Choix4CB);
	xp.ChoixXp4->add("Taille du glacon","",Choix4CB);
	xp.ChoixXp4->add("Proprietes du solvant","",Choix4CB);
	xp.ChoixXp4->hide() ;	

	xp.De1 = new Fl_Value_Input(60,130,40,20,"Min");
	xp.De1->hide();
	xp.A1 = new Fl_Value_Input(150,130,40,20,"Max");
	xp.A1->hide();
	xp.ParPas1 = new Fl_Value_Input(80,170,40,20,"Intervalle de mesure");
	xp.ParPas1->hide();
	
	xp.De2 = new Fl_Value_Input(60,130,40,20,"Min");
	xp.De2->hide();
	xp.A2 = new Fl_Value_Input(150,130,40,20,"Max");
	xp.A2->hide();
	xp.ParPas2 = new Fl_Value_Input(80,170,40,20,"Intervalle de mesure");
	xp.ParPas2->hide();

	xp.De3 = new Fl_Value_Input(60,130,40,20,"Min");
	xp.De3->hide();
	xp.A3 = new Fl_Value_Input(150,130,40,20,"Max");
	xp.A3->hide();
	xp.ParPas3 = new Fl_Value_Input(80,170,40,20,"Intervalle de mesure");
	xp.ParPas3->hide();

	xp.SaisieTsolv = new Fl_Value_Input(280,210,30,20,"Tsolvant") ;
	xp.SaisieTsolv->hide() ;
    	xp.SaisieTglacon = new Fl_Value_Input(280,250,30,20,"Tglacon") ; 
	xp.SaisieTglacon->hide(); 
    	xp.SaisieCp = new Fl_Value_Input(280,280,30,20,"Cp") ;
	xp.SaisieCp->hide();
   	xp.SaisieRo = new Fl_Value_Input(100,130,30,20,"Masse volumique") ;
	xp.SaisieRo->hide();
   	xp.SaisieLambda = new Fl_Value_Input(280,160,30,20,"Conductivite thermique") ;
	xp.SaisieLambda->hide(); 
   	xp.SaisieRayon = new Fl_Value_Input(100,160,30,20,"Rayon du glacon") ;
	xp.SaisieRayon->hide();
    	xp.SaisieE = new Fl_Value_Input(280,130,30,20,"Module de Young") ;
	xp.SaisieE->hide();

	xp.BoutonValider1 = new Fl_Button(320,290,50,20,"Valider");
	xp.BoutonValider1->callback(Valider1CB, NULL);

	xp.BoutonValider2 = new Fl_Button(320,290,50,20,"Valider");
	xp.BoutonValider2->callback(Valider2CB, NULL);

	xp.BoutonValider3 = new Fl_Button(320,290,50,20,"Valider");
	xp.BoutonValider3->callback(Valider3CB, NULL);	

	xp.BoutonValider4 = new Fl_Button(320,290,50,20,"Valider");
	xp.BoutonValider4->callback(Valider4CB, NULL);

	xp.Fenetre->end();
    	xp.Fenetre->show();
}

void NbExpCB(Fl_Widget *w, void *)
{
	gDonnees.exp.nbexp = (int)xp.NbXp->value() ;
	xp.Item->hide() ;

	switch(gDonnees.exp.nbexp)
	{
		case 0:	xp.Item->add("Exp1",0, Xp1CB);
			xp.Item->show() ;
			break ;
		case 1: xp.Item->add("Exp1",0, Xp1CB);
			xp.Item->show() ;
   			xp.Item->add("Exp2",0, Xp2CB);
			xp.Item->show() ;
			break;
		case 2:	xp.Item->add("Exp1",0, Xp1CB);
			xp.Item->show() ;
   			xp.Item->add("Exp2",0, Xp2CB);
			xp.Item->show() ;
			xp.Item->add("Exp3",0, Xp3CB);
			xp.Item->show() ;
			break;
		case 3: xp.Item->add("Exp1",0, Xp1CB);
			xp.Item->show() ;
   			xp.Item->add("Exp2",0, Xp2CB);
			xp.Item->show() ;
			xp.Item->add("Exp3",0, Xp3CB);
			xp.Item->show() ;
   			xp.Item->add("Exp4",0,Xp4CB);
			xp.Item->show() ;
			break;
		default: break;
	}	
}

void DessinXpCB(Fl_Widget *w, void *)
{
	Fl_BMP_Image ImageGlacon("media/glacon2.bmp") ;
    	//Fl_JPEG_Image ImageLogoPhelma("media/logophelma.jpg") ;
    	ImageGlacon.draw(50,200);
}

void CacherFonction()
{
	xp.De2->hide();
	xp.A2->hide() ;
	xp.ParPas2->hide() ;
	xp.BoutonValider2->hide() ;
	xp.De3->hide();
	xp.A3->hide() ;
	xp.ParPas3->hide() ;
	xp.BoutonValider3->hide() ;
	xp.BoutonValider4->hide() ;
	xp.De1->hide();
	xp.A1->hide() ;
	xp.ParPas1->hide() ;
	xp.BoutonValider1->hide() ;
	xp.SaisieTsolv->hide() ;
	xp.SaisieTglacon->hide(); 
	xp.SaisieCp->hide();
	xp.SaisieRo->hide();
	xp.SaisieLambda->hide(); 
	xp.SaisieRayon->hide();
	xp.SaisieE->hide();
}		

void Choix1CB(Fl_Widget *w, void *)
{
	int choix = (int)xp.ChoixXp1->value() ;
	switch(choix)
	{
		case 0:	CacherFonction() ;
			xp.De1->show();
			xp.A1->show() ;
			xp.ParPas1->show() ;
			xp.BoutonValider1->show() ;
			break;
		case 1:	CacherFonction() ;
			xp.De2->show();
			xp.A2->show() ;
			xp.ParPas2->show() ;
			xp.BoutonValider2->show() ;
			break;
		case 2:	CacherFonction() ;
			xp.De3->show();
			xp.A3->show() ;
			xp.ParPas3->show() ;
			xp.BoutonValider3->show() ;
			break;
		case 3:	CacherFonction() ;
			xp.SaisieTsolv->show() ;
			xp.SaisieTglacon->show(); 
			xp.SaisieCp->show();
			xp.SaisieRo->show();
			xp.SaisieLambda->show(); 
			xp.SaisieRayon->show();
			xp.SaisieE->show();
			xp.BoutonValider4->show() ;
			break;
		default: break ;
	}
	
}

void Choix2CB(Fl_Widget *w, void *)
{
	int choix = (int)xp.ChoixXp1->value() ;
	switch(choix)
	{
		case 0:	CacherFonction() ;
			xp.De1->show();
			xp.A1->show() ;
			xp.ParPas1->show() ;
			xp.BoutonValider1->show() ;
			break;
		case 1:	CacherFonction() ;
			xp.De2->show();
			xp.A2->show() ;
			xp.ParPas2->show() ;
			xp.BoutonValider2->show() ;
			break;
		case 2:	CacherFonction() ;
			xp.De3->show();
			xp.A3->show() ;
			xp.ParPas3->show() ;
			xp.BoutonValider3->show() ;
			break;
		case 3:	CacherFonction() ;
			xp.SaisieTsolv->show() ;
			xp.SaisieTglacon->show(); 
			xp.SaisieCp->show();
			xp.SaisieRo->show();
			xp.SaisieLambda->show(); 
			xp.SaisieRayon->show();
			xp.SaisieE->show();
			xp.BoutonValider4->show() ;
			break;
		default: break ;
	}
	
}

void Choix3CB(Fl_Widget *w, void *)
{
	int choix = (int)xp.ChoixXp1->value() ;
	switch(choix)
	{
		case 0:	CacherFonction() ;
			xp.De1->show();
			xp.A1->show() ;
			xp.ParPas1->show() ;
			xp.BoutonValider1->show() ;
			break;
		case 1:	CacherFonction() ;
			xp.De2->show();
			xp.A2->show() ;
			xp.ParPas2->show() ;
			xp.BoutonValider2->show() ;
			break;
		case 2:	CacherFonction() ;
			xp.De3->show();
			xp.A3->show() ;
			xp.ParPas3->show() ;
			xp.BoutonValider3->show() ;
			break;
		case 3:	CacherFonction() ;
			xp.SaisieTsolv->show() ;
			xp.SaisieTglacon->show(); 
			xp.SaisieCp->show();
			xp.SaisieRo->show();
			xp.SaisieLambda->show(); 
			xp.SaisieRayon->show();
			xp.SaisieE->show();
			xp.BoutonValider4->show() ;
			break;
		default: break ;
	}	
}

void Choix4CB(Fl_Widget *w, void *)
{
	int choix = (int)xp.ChoixXp1->value() ;
	switch(choix)
	{
		case 0:	CacherFonction() ;
			xp.De1->show();
			xp.A1->show() ;
			xp.ParPas1->show() ;
			xp.BoutonValider1->show() ;
			break;
		case 1:	CacherFonction() ;
			xp.De2->show();
			xp.A2->show() ;
			xp.ParPas2->show() ;
			xp.BoutonValider2->show() ;
			break;
		case 2:	CacherFonction() ;
			xp.De3->show();
			xp.A3->show() ;
			xp.ParPas3->show() ;
			xp.BoutonValider3->show() ;
			break;
		case 3:	CacherFonction() ;
			xp.SaisieTsolv->show() ;
			xp.SaisieTglacon->show(); 
			xp.SaisieCp->show();
			xp.SaisieRo->show();
			xp.SaisieLambda->show(); 
			xp.SaisieRayon->show();
			xp.SaisieE->show();
			xp.BoutonValider4->show() ;
			break;
		default: break ;
	}
}

void Valider1CB(Fl_Widget *w, void *)
{
	
}

void Valider2CB(Fl_Widget *w, void *)
{
	
}

void Valider3CB(Fl_Widget *w, void *)
{
	
}

void Valider4CB(Fl_Widget *w, void *)
{
	
}

void Xp1CB(Fl_Widget *w, void *)
{
	/* xp.PetitDessin->hide();
	*/
	xp.ChoixXp2->hide();
	xp.ChoixXp3->hide();
	xp.ChoixXp4->hide();
	xp.ChoixXp1->show();
	
}

void Xp2CB(Fl_Widget *w, void *)
{
	/*xp.PetitDessin->hide();

	
	xp.De3->hide();
	xp.A3->hide() ;
	xp.ParPas3->hide() ;
	xp.BoutonValider3->hide() ;

	
	xp.BoutonValider4->hide() ;

	
	xp.De1->hide();
	xp.A1->hide() ;
	xp.ParPas1->hide() ;
	xp.BoutonValider1->hide() ;

	
	xp.De2->hide();
	xp.A2->hide() ;
	xp.ParPas2->hide() ;
	xp.BoutonValider2->hide() ;*/
	xp.ChoixXp3->hide();
	xp.ChoixXp4->hide();
	xp.ChoixXp1->hide();
	xp.ChoixXp2->show();
}

void Xp3CB(Fl_Widget *w, void *)
{
	/*xp.PetitDessin->hide();

	
	xp.De2->hide();
	xp.A2->hide() ;
	xp.ParPas2->hide() ;
	xp.BoutonValider2->hide() ;

	
	xp.BoutonValider4->hide() ;

	
	xp.De1->hide();
	xp.A1->hide() ;
	xp.ParPas1->hide() ;
	xp.BoutonValider1->hide() ;

	
	xp.De3->show();
	xp.A3->show() ;
	xp.ParPas3->show() ;
	xp.BoutonValider3->show() ;*/
	xp.ChoixXp2->hide();
	xp.ChoixXp1->hide();
	xp.ChoixXp4->hide();
	xp.ChoixXp3->show();
}

void Xp4CB(Fl_Widget *w, void *)
{
	/*xp.PetitDessin->hide();

	
	xp.De3->hide();
	xp.A3->hide() ;
	xp.ParPas3->hide() ;
	xp.BoutonValider3->hide() ;

	xp.De2->hide();
	xp.A2->hide() ;
	xp.ParPas2->hide() ;
	xp.BoutonValider2->hide() ;

	xp.De1->hide();
	xp.A1->hide() ;
	xp.ParPas1->hide() ;
	xp.BoutonValider1->hide() ;

	xp.BoutonValider4->show() ;*/
	xp.ChoixXp3->hide();
	xp.ChoixXp2->hide();
	xp.ChoixXp1->hide();
	xp.ChoixXp4->show();
	
}




