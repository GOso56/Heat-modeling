// u4-fonctions.h
// Sentinelle d'inclusion
#ifndef _u4_fonctions_h
#define _u4_fonctions_h

// Definition des constantes
#define DUREE_CYCLE 0.015    // 0.500 secondes, depend du materiel utilise

// Declaration des donnees du projet

/*
const double Tglacon = -18+273  ;                   //Temperature du glacon en K
const double Teau = 15+273 ;                     //Temperature de l'eau en K
const double lambda = 2.1 ;		        //Conductivite thermique
const double rho = 917 ;                          //Masse voulmique
const double cp = 2060 ;			   //Capacite thermique massique
*/
//const double alpha = lambda/(rho*cp);              //Coefficient de diffusion thermique
//const double Lx = 0.05 ;                           //Taille du domaine en x 5cm
//const double Time = 4.0 ;                         //Temps d'integration
const int NT = 2000;                           //Nombre de pas de temps
const int NX = 100 ;                            //Nombre de pas d'espace
//const double dt = Time/NT;                       
//const double dx = Lx/NX ;  
//const double E = 9.33e3 ;				//module young de la glace environ de 9.33 GPa              
//const double A = 1 - 4*alpha*dt/(dx*dx);
//const double B = alpha*dt/(dx*dx);


// Structure globale pour les variables fonctionnelles
struct Var
{
	double Tglacon ;
	char nomTglacon[6] ;
	double Teau ;
	char nomTeau[6];
	double lambda ;
	double rho ;
	double cp ;
	double alpha ;
	double B ;
	double rayon;
	char nomRayon[6] ;
	double E;
	double h;
	double contrainteMax;
	int modifier ;
	double Time ;
	double dt;
	double dx ;
} ;

struct Experience
{
	int nbexp ;
	double** Temperature ;
	double* elongation ;
	double*	contrainte;
	double* tempsRupture ;
	double 	Tglacon[4] ;
	double 	Teau[4] ;
	double 	lambda[4] ;
	double 	rho[4] ;
	double 	cp[4] ;
	double 	alpha[4] ;
	double 	B[4] ;
	double 	rayon[4];
	double 	E[4];	
	FILE* 	fexp1;
	FILE* 	fexp2;
	FILE* 	fexp3;
	FILE* 	fexp4;
} ;
struct Donnees
{
   FILE* fp;
   FILE *felong ;
   FILE *fcon ;
   FILE *fevolution ;
   int curseur;
   int demarrer ;
   int compteur ;
   int valider ;
   int debut;
   int astuce[8] ;
   char nom[50];
   int option ;
   int recadrer ;
   int arreterCallback ;
   double *elongation ;
   double *contrainte ;
   double tempsSimulation ;
   struct Var var ;
   struct Experience exp ;
} ;
extern double **temperature ;
extern double **dessinContrainte;
extern struct Donnees gDonnees;

struct Affichage
{
	double x;
	double y;
	double epaisseur;
	double longueur ;
	double contrainteMax;
	int couleur[2] ;
} ;

extern struct Affichage gAffichage ;

void TemperatureInit() ;
void InitialiserMat() ;
void etudeContrainte() ;
void FermerMat() ;
void InitialiserDonnees() ;
void euler_explicite(int i) ;
void ouvertureFichier() ;
void effacerFichier() ;
void fermetureFichier() ;
void JouerSon(char *) ;         // Jouer un son
void Attente(double Seconds);   // Procedure d'attente

#endif // _u4_fonctions_h
