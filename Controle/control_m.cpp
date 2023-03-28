#include "control_m.hpp"


void Moteur::vitesse(int vitesse) {
  int tmp=0;
  if(vitesse <0){
    tmp=((-vitesse)<<8) | chan;
    //printf("%x\n", tmp);
    wiringPiI2CWriteReg16(fd_addr_i2c, M_CMD_CCW - chan, tmp);
  }
  else {
    tmp=((vitesse)<<8) | chan;
    //printf("%x\n", tmp);
    wiringPiI2CWriteReg16(fd_addr_i2c, M_CMD_CW + chan, tmp);
  }
}

void Moteur::arret(){
  wiringPiI2CWriteReg16(fd_addr_i2c, M_CMD_BRAKE, chan);
}







/*prototype
int wiringPiI2CWriteReg8 (int fd, int reg, int data) ;
int wiringPiI2CWriteReg16 (int fd, int reg, int data)
*/
/*
int main(int argc, char** argv){
  wiringPiSetup();
  time_t start;
  time(&start);
  Moteur m(CHAN1);
  Moteur m2(CHAN2);
  m2.vitesse(0xAF);
  m.vitesse(0xAF);
  while( abs(difftime(start, time(NULL)))<10)
  {printf(".");}
  m2.vitesse(0x00);
  m.vitesse(0x00);
  return 0;

}
*/
