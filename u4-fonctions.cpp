// u4-fonctions.cpp
// Declarations externes - inclusion des fichiers d'entete
// Librairies standards
#include <iostream>     // cout, cin, ...
#include <stdlib.h>     // exit, rand
#include <time.h>       // time
#include <string.h>     // strcpy
#include <stdio.h>
// Librairie fmod pour le son
#include <api/inc/fmod.h>
#include <api/inc/fmod_errors.h>
// Programmes locaux
#include "u1-interface.h"
#include "u4-fonctions.h"






/* ********************************************************************************************************************************** */
	/*   http://seriss.com/people/erco/fltk/#Animate  */
/* ********************************************************************************************************************************** */

// Declaration pour utiliser iostream
using namespace std;

// Definition des donnees fonctionnelles du projet - structure globale de variables
struct Donnees gDonnees ;
struct Affichage gAffichage ;
double **temperature;
double **dessinContrainte;


// Initialiser
void InitialiserMat()
{
	int i;
	if( (temperature = (double **)calloc((NX+1),sizeof(double *)))==NULL){
		fprintf(stderr,"erreur d'allocation mémoire dynamique\n");
		return ;
	}//allocation de mémoire dynamique pour les N+1 lignes
	
	for( i=0 ; i<=NX ; i++ ){
		if( (temperature[i] = (double *)calloc((NT+1),sizeof(double)))==NULL){
			fprintf(stderr,"erreur d'allocation mémoire dynamique\n");
			return ;
		}
	}//allocation de mémoire dynamique pour les M+1 colonnes
	
	if( (dessinContrainte = (double **)calloc((NX+1),sizeof(double *)))==NULL){
		fprintf(stderr,"erreur d'allocation mémoire dynamique\n");
		return ;
	}//allocation de mémoire dynamique pour les N+1 lignes
	
	for( i=0 ; i<=NX ; i++ ){
		if( (dessinContrainte[i] = (double *)calloc((21),sizeof(double)))==NULL){
			fprintf(stderr,"erreur d'allocation mémoire dynamique\n");
			return ;
		}
	}//allocation de mémoire dynamique pour les M+1 colonnes
}

void FermerMat()
{
	int i;
	for(i=0 ; i<= NX; i++)
		free(temperature[i]);
	free(temperature);

	for(i=0 ; i<= NX; i++)
		free(dessinContrainte[i]);
	free(dessinContrainte);

	free(gDonnees.contrainte);
	free(gDonnees.elongation);
}
	
void InitialiserDonnees()
{
	//Initialisation des conditions de Dirichlet :
	int i;

	effacerFichier() ;
	InitialiserMat();

	gDonnees.var.Tglacon = 273-18 ;
	gDonnees.var.Teau = 20 + 273;
	gDonnees.var.lambda = 2.1 ;
	gDonnees.var.rho = 917 ;
	gDonnees.var.cp = 2060;
	gDonnees.var.alpha = 1.112e-6;
	gDonnees.var.rayon = 0.010;
	gDonnees.var.E = 9.33e3;
	gDonnees.var.modifier = 0 ;
	gDonnees.var.h = 100 ;
	gDonnees.var.Time = 4 ;
	gDonnees.var.contrainteMax = 2.8 ;
	gDonnees.var.dt = (gDonnees.var.Time)/NT ;
	gDonnees.var.dx = (gDonnees.var.rayon)/NX ;
	gDonnees.var.B = ((gDonnees.var.alpha)*(gDonnees.var.dt))/(gDonnees.var.dx*gDonnees.var.dx) ;

	gDonnees.demarrer = 0;
	gDonnees.recadrer = 0 ;
	gDonnees.arreterCallback = 0 ;
	gDonnees.valider = 0 ;
	gDonnees.compteur = 0;
	gDonnees.curseur = 1 ;
	gDonnees.debut = 0 ;
	gDonnees.option = 0 ;
	gDonnees.nom[0] = ' ';
	gDonnees.tempsSimulation = 0 ;

	for(i=0;i<8;i++)
		gDonnees.astuce[i] = 0;

	gAffichage.contrainteMax = 0 ;
	gAffichage.x = 70 ;
	gAffichage.y = 150 ;
	gAffichage.epaisseur = 5 ;
	gAffichage.longueur = 400 ;
	gAffichage.couleur[0] = 2;
	gAffichage.couleur[1] = 3;  

	if( (gDonnees.contrainte = (double *)calloc(NX+1,sizeof(double)))==NULL)
		return ;

	if( (gDonnees.elongation = (double *)calloc(NT+1,sizeof(double)))==NULL)
		return ;
	
	gInterface.Menu->activate() ; 
	
}
void TemperatureInit()
{
	int i;
	//Initialisation des conditions de Dirichlet :
	for( i=0 ; i<=NX ; i++){
	temperature[i][0] = gDonnees.var.Tglacon;
	}
}



void euler_explicite(int i)
{
	int j;
	double dist = 0;
	 
	temperature[NX][i] = ( gDonnees.var.lambda*temperature[NX-1][i]+gDonnees.var.Teau*(gDonnees.var.h)*gDonnees.var.dx )/(gDonnees.var.lambda + (gDonnees.var.h)*(gDonnees.var.dx)) ;
		
	
	temperature[0][i] = ( gDonnees.var.lambda*temperature[1][i]+gDonnees.var.Teau*(gDonnees.var.h)*gDonnees.var.dx )/(gDonnees.var.lambda + gDonnees.var.h*gDonnees.var.dx) ;
	
	for ( j=1 ; j<NX ; j++){
		temperature[j][i+1] = temperature[j][i] + gDonnees.var.B * ( temperature[j-1][i] + temperature[j+1][i] -2*temperature[j][i] );
		fprintf(gDonnees.fp,"%lf\t%lf\n",dist-gDonnees.var.rayon/2,temperature[j-1][i]);
		dist += gDonnees.var.dx ;
		}
	gDonnees.tempsSimulation += gDonnees.var.dt ;
	gInterface.TempsSimulation->value(gDonnees.tempsSimulation) ;
	fprintf(gDonnees.fp,"%lf\t%lf\n",dist-gDonnees.var.rayon/2,temperature[j-1][i]);
	fprintf(gDonnees.fp,"%lf\t%lf\n",dist-gDonnees.var.rayon/2,temperature[j][i]);
	fprintf(gDonnees.fp,"\n");
}


void etudeContrainte()
{
	//NX(l'-l)=l*alpha*somme(T[i]-T[0])
	//l' = (l*alpha*somme(T[i]-T[0]))/NX + l
	int i,j,k, astuce=0;
	double calcul=0 ; 
	double count=0; 
	
	for(i=0;i<NT;i++)
	{
		for(j=0;j<NX;j++)
		{
			calcul += gDonnees.var.rayon*gDonnees.var.alpha*(temperature[j][i]-temperature[NX/2][i])/NX ;
		}
		gDonnees.elongation[i] = calcul + gDonnees.var.rayon ;
		fprintf(gDonnees.felong,"%lf\t%lf\n",count,gDonnees.elongation[i]);
		count += gDonnees.var.dt ;
	}

	k=0;
	count = 0;
	for(i=0;i<NT;i++)
	{
		calcul = 0;
		for(j=0;j<=NX;j++)
		{
			gDonnees.contrainte[j] = ( (gDonnees.elongation[i]-gDonnees.var.rayon)/gDonnees.var.rayon - gDonnees.var.alpha*(temperature[j][i]-temperature[NX/2][i]) ) * gDonnees.var.E ;

			if(gDonnees.contrainte[j] > gDonnees.var.contrainteMax && astuce == 0)
			{
				gInterface.Temps->value(count) ;
				astuce = 1 ;
			}
			if(i%100 == 0)
			{
				if(k<20)
				{
					dessinContrainte[j][k] = gDonnees.contrainte[j] ;
					fprintf(gDonnees.fcon,"%lf\t%lf\n",calcul-gDonnees.var.rayon/2,gDonnees.contrainte[j]) ;
				}
				fprintf(gDonnees.fevolution,"%lf\t%lf\n",calcul-gDonnees.var.rayon/2,temperature[j][i]);
			}
			calcul += gDonnees.var.dx ;
		}
		if(i%100 == 0)
		{
			fprintf(gDonnees.fcon,"\n");
			fprintf(gDonnees.fevolution,"\n");
			k++ ;
		}
		count += gDonnees.var.dt ;
	}
}

void effacerFichier()
{
	gDonnees.fp = fopen("temperature.txt","w+");
	fclose(gDonnees.fp) ;

	gDonnees.felong = fopen("elongation.txt","w+");
	fclose(gDonnees.felong) ;

	gDonnees.fcon = fopen("contrainte.txt","w+");
	fclose(gDonnees.fcon) ;

	gDonnees.fevolution = fopen("evolution.txt","w+");
	fclose(gDonnees.fevolution) ;
}


void ouvertureFichier()
{
	gDonnees.fp = fopen("temperature.txt","a");
	if (gDonnees.fp == NULL)
		return;

	gDonnees.felong = fopen("elongation.txt","a");
	if (gDonnees.felong == NULL)
		return;

	gDonnees.fcon = fopen("contrainte.txt","a");
	if (gDonnees.fcon == NULL)
		return;

	gDonnees.fevolution = fopen("evolution.txt","a");
	if (gDonnees.fevolution == NULL)
		return;

}

void fermetureFichier()
{
	fclose(gDonnees.fp) ;
	fclose(gDonnees.fcon) ;
	fclose(gDonnees.felong) ;
	fclose(gDonnees.fevolution) ;
}

// Fonctions utilitaires

// Joue le fichier son passe en parametre, mp3, etc...
void JouerSon(char * FichierSon)
{
    // Musique de fond
    FMOD_SYSTEM      *system;
    FMOD_SOUND       *sound;
    FMOD_CHANNEL     *channel = 0;
    FMOD_RESULT       result;
    int               key;
    unsigned int      version;
    /*
        Create a System object and initialize.
    */
    result = FMOD_System_Create(&system);
    result = FMOD_System_GetVersion(system, &version);
    result = FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, NULL);
    result = FMOD_System_CreateSound(system, FichierSon, FMOD_SOFTWARE, 0, &sound);
    result = FMOD_Sound_SetMode(sound, FMOD_LOOP_OFF);
    result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sound, 0, &channel);
}

// Cette procedure permet une attente de x secondes, x peut etre en secondes mais aussi en flottant par exemple : 0.1 s
void Attente ( double Seconds )
{
    clock_t Endwait;
    Endwait = (int) (clock () + Seconds * CLOCKS_PER_SEC);
    while (clock() < Endwait);
}
