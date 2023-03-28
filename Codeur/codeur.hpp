#ifndef CODEUR_HPP
#define CODEUR_HPP
#include "../config/config.hpp"
#include <wiringPi.h>
#include <unistd.h>
#include <iostream>
#include <cmath>
#include <ctime>

/**
*@fn int vit_ang2hexa_g(double vit_ang)
*@brief Calcul la valeur de la vitesse sur 8 bit à envoyer au moteur partant de la vitesse angulaire pour le moteur Gauche
*@param double vit_ang , vitesse angulaire
*@see int vit_ang2hexa_d(double vit_ang)
*@return int vitesse compris entre 0 et 255

*/
int vit_ang2hexa_g(double vit_ang);

/**
*@fn int vit_ang2hexa_d(double vit_ang)
*@brief Calcul la valeur de la vitesse sur 8 bit à envoyer au moteur partant de la vitesse angulaire pour le moteur droit
*@param double vit_ang , vitesse angulaire
*@see int vit_ang2hexa_g(double vit_ang)
*@return int vitesse compris entre 0 et 255

*/
int vit_ang2hexa_d(double vit_ang);

/**
*@brief Classe codeur permettant des gerer les codeurs du robot.
*/
class Codeur {

public:
  static int _compteur_g;
  static int _compteur_d;

  /**
  *@brief Constructeur, initialise les pin du GPIO
  */
  Codeur(){
    pinMode(CODEUR_D1, INPUT);
    pinMode(CODEUR_D2, INPUT);
    pinMode(CODEUR_G1, INPUT);
    pinMode(CODEUR_G2, INPUT);

    wiringPiISR(CODEUR_D1,INT_EDGE_RISING,&compter_d);
    wiringPiISR(CODEUR_G1,INT_EDGE_RISING,&compter_g);
  }

  /**
  *@fn static void compter_g()
  *@brief  Méthode statique permettant de compter les points du codeur gauche
  *@see   static void compter_d()
  */
  static void compter_g();

  /**
  *@fn static void compter_d()
  *@brief  Méthode statique permettant de compter les points du codeur gauche
  *@see static void compter_g()
  */
  static void compter_d();

};

#endif
