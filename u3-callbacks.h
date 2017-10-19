// u3-callbacks.h
// Sentinelle d'inclusion
#ifndef _u3_callbacks_h
#define _u3_callbacks_h

// Declarations externes
#include <FL/Fl_Widget.H>

// Declaration des sous-programmes
void TraiterCycleCB() ;
void ZoneDessinSourisCB( Fl_Widget* widget, void* data ) ;
void ZoneDessinClavierCB( Fl_Widget* widget, void* data ) ;
void BoutonQuitterCB( Fl_Widget* w, void* data ) ;
void CurseurCB(Fl_Widget* w, void* data) ;
void BoutonRejouerCB(Fl_Widget* w, void* data) ;
void BoutonDemarrerCB(Fl_Widget* w, void* data) ;
void MenuCB(Fl_Widget* w, void* data) ;
void ParametreCB(Fl_Widget *w, void *) ;
void SaisieTglaconCB(Fl_Widget *, void *) ;
void SaisieTeauCB(Fl_Widget *, void *) ;
void SaisieRoCB(Fl_Widget *, void *) ;void QuitCB(Fl_Widget *, void *) ;
void SaisieLambdaCB(Fl_Widget *, void *) ;
void SaisieCpCB(Fl_Widget *, void *) ;
void BoutonInfoCB(Fl_Widget* w, void* data) ;
void BoutonValiderCB(Fl_Widget* w, void* data) ;
void ZoomCB(Fl_Widget* w, void* data) ;
void QuitCB(Fl_Widget *, void *) ;
void ChampSaisieTxtCB(Fl_Widget* w, void* data) ;
void SaisieRayonCB(Fl_Widget *, void *) ;
void CaseCocherCB(Fl_Widget* w, void* data) ;
void ProgCB(Fl_Widget *w, void *) ;
void BoutonQuitterProgCB(Fl_Widget* w, void* data) ;
void BoutonInfoProgCB(Fl_Widget* w, void* data) ;
void RecadrerCB(Fl_Widget* w, void* data) ;
void SaisieContrainteCB(Fl_Widget *, void *) ;
void SaisieHCB(Fl_Widget *, void *) ;

void BoutonValiderGraphCB(Fl_Widget* w, void* data);
void AfficherContrainteCB(Fl_Widget* w, void* data);
void InterfaceCB(Fl_Widget *w, void *);
void MenuTCB(Fl_Widget* w, void* data) ;
void MenuCCB(Fl_Widget* w, void* data) ;


void BoutonQuitterAideCB(Fl_Widget* w, void* data) ;
void MessageAideCB(Fl_Widget* w, void* data) ;
void AideCB(Fl_Widget *w, void *) ;
void CaseTimeCB(Fl_Widget* w, void* data) ;
void SaisieTimeCB(Fl_Widget* w, void* data) ;

void ExperienceCB(Fl_Widget *w, void *) ;
void NbExpCB(Fl_Widget *w, void *);
void DessinXpCB(Fl_Widget *w, void *) ;
void Xp1CB(Fl_Widget *w, void *) ;
void Xp2CB(Fl_Widget *w, void *) ;
void Xp3CB(Fl_Widget *w, void *) ;
void Xp4CB(Fl_Widget *w, void *) ;
void Choix1CB(Fl_Widget *w, void *) ;
void Choix2CB(Fl_Widget *w, void *) ;
void Choix3CB(Fl_Widget *w, void *) ;
void Choix4CB(Fl_Widget *w, void *) ;
void Valider1CB(Fl_Widget *w, void *) ;
void Valider2CB(Fl_Widget *w, void *) ;
void Valider3CB(Fl_Widget *w, void *) ;
void Valider4CB(Fl_Widget *w, void *) ;
void CacherFonction() ;

#endif // _u3_callbacks_h
