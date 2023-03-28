#ifndef CONTROL_HPP
#define CONTROL_HPP
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <iostream>
#include <ctime>
#include "../config/config.hpp"

/**
*@brief Class Moteur permettant le controle d'un moteur
*/
class Moteur{
protected:

  int chan; //adresse I2C du Moteur à controler
  int fd_addr_i2c=wiringPiI2CSetup(M_I2C_ADDR);
  float val_compteur=0;


public:
  /**
  *@fn double angle( Point pt1, Point pt2, Point pt0 )
  *@brief Constructeur de Moteur
  *@param int chan adresse I2C du Moteur
  */
  Moteur(int chan){this->chan=chan;}

  /**
  *@fn void vitesse( int vitesse )
  *@brief envoie la commande de vitesse au moteur
  *@param int vitesse, vitesse désirée en 8 bit (max 255)
  */
  void vitesse(int vitesse);

  /**
  *@fn void arret()
  *@brief envoie une commande d'arret au moteur
  */
  void arret();

};

#endif
