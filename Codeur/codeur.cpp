#include "codeur.hpp"

int Codeur::_compteur_g=0;
int Codeur::_compteur_d=0;


void Codeur::compter_g(){

  if(digitalRead(CODEUR_G2)==1)
    ++(*(&Codeur::_compteur_g));

  else --*(&(Codeur::_compteur_g));

}


void Codeur::compter_d(){

  if(digitalRead(CODEUR_D2)==1)
   ++(*(&Codeur::_compteur_d));

  else --(*(&Codeur::_compteur_d));


}


int vit_ang2hexa_d(double vit_ang){

  if(abs(vit_ang)>=280){
    int vit=vit_ang*COEF_VIT_D_UP;

    if(abs(vit)<=254)
      return vit;
    else if( vit > 0)
      return 255;
    else return -255;
  }



  else if (abs(vit_ang)>=180)
    return vit_ang*COEF_VIT_D_M;

  else return vit_ang*COEF_VIT_D_DW;
}

int vit_ang2hexa_g(double vit_ang){

  if(abs(vit_ang)>=280){
    int vit=vit_ang*COEF_VIT_G_UP;

    if(abs(vit)<=254)
      return vit;
    else if( vit > 0)
      return 255;
    else return -255;
  }

  else if (abs(vit_ang)>=180)
    return vit_ang*COEF_VIT_G_M;

  else return vit_ang*COEF_VIT_G_DW;
}
