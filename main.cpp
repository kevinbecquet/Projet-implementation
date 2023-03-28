#include "pid/pid.h"
#include "Codeur/codeur.hpp"
#include "Controle/control_m.hpp"
#include "config/config.hpp"

void* asser_moteur(void* argc){
  
  wiringPiSetup() ;
  time_t start;
  time(&start);
// declaration des variables

  int compte_prec_g=Codeur::_compteur_g;
  int compte_prec_d=Codeur::_compteur_d;

  double vit_mes_g=0;
  double vit_mes_d=0;
  double vit_des_g=0;
  double vit_des_d=0;
  double vit_out_d=0;
  double vit_out_g=0;

  int compte_cour_g;
  int compte_cour_d;

  Codeur* codeurs= new Codeur();
  Moteur moteur_d(CHAN2);
  Moteur moteur_g(CHAN1);

  moteur_d.vitesse(0xFF);
  moteur_g.vitesse(0xFF);


   while(1){
        //calcul de la vitesse en cours
        compte_cour_d=Codeur::_compteur_d;
        compte_cour_g=Codeur::_compteur_g;

        if(abs(difftime(time(NULL), start))>=2 &&  abs(difftime(time(NULL), start))<=9)
        vit_des_g=vit_des_d=279;

        if(abs(difftime(time(NULL), start))>=10 &&  abs(difftime(time(NULL), start))<=20)
        vit_des_g=vit_des_d=383;

        if(abs(difftime(time(NULL), start))>=21 &&  abs(difftime(time(NULL), start))<=30)
        vit_des_g=vit_des_d=104;
        if(abs(difftime(time(NULL), start))>=31 &&  abs(difftime(time(NULL), start))<=40)
        vit_des_g=vit_des_d=0;

        if(abs(difftime(time(NULL), start))>=41 &&  abs(difftime(time(NULL), start))<=50)
        vit_des_g=vit_des_d=-104;


        vit_mes_d=((double)(compte_cour_d-compte_prec_d)*M_PI)/((double)(NBR_POINT_CODEUR_D*PERIODE_E_S));
        vit_mes_g=((double)(compte_cour_g-compte_prec_g)*M_PI)/((double)(NBR_POINT_CODEUR_G*PERIODE_E_S));

        vit_out_g=pid(vit_mes_g, vit_des_g, vit_out_g);
        vit_out_d=pid(vit_mes_d, vit_des_d, vit_out_d);

        printf("vit_out_d %lf\n", vit_out_d);
        printf("vit_out_g %lf\n", vit_out_g);

        moteur_d.vitesse(vit_ang2hexa_d(vit_out_d));
        moteur_g.vitesse(vit_ang2hexa_g(vit_out_g));

        printf("vit_ %d\n", vit_ang2hexa_d(vit_out_d));
        printf("vit_ %d\n", vit_ang2hexa_g(vit_out_g));

        compte_prec_d=Codeur::_compteur_d;
        compte_prec_g=Codeur::_compteur_g;

        usleep(PERIODE_E);
    }

}




int main(){


return 0;

}

/*
    val_angle_g=angle(Codeur::_compteur_g);
    val_angle_d=angle(Codeur::_compteur_d);
    printf("vit_mes g %d\n", Codeur::_compteur_d);
   if(abs(difftime(te, time(NULL)))>=PERIODE_E){
     time(&te);
     printf("val an %f\n", val_angle_d);
     vit_mes_d=vitesse(val_angle_d, angle(Codeur::_compteur_d));
     vit_mes_g=vitesse(val_angle_g, angle(Codeur::_compteur_g));
     val_angle_d=angle(Codeur::_compteur_d);
     val_angle_g=angle(Codeur::_compteur_g);
     v_out_d=pid(vit_mes_d, v_des_d, v_out_d);
     moteur_d.vitesse(v_out_d);
     v_out_g=pid(vit_mes_g, v_des_g, v_out_g);
     moteur_g.vitesse(v_out_g);
//   printf("vit_mes g %d\n", Codeur::_compteur_d);

   //*/
