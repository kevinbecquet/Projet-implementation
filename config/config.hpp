#ifndef CONFIG
#define CONFIG

#define M_I2C_ADDR             0x14
#define M_CMD_BRAKE            0x00
#define M_CMD_STOP             0x01
#define M_CMD_CW               0x02
#define M_CMD_CCW              0x03
#define M_CMD_STANDBY          0x04
#define M_CMD_NOT_STANDBY      0x05
#define M_CMD_STEPPER_RUN      0x06
#define M_CMD_STEPPER_STOP     0x07
#define M_CMD_STEPPER_KEEP_RUN 0x08
#define M_CMD_SET_ADDR         0x11
#define CODEUR_G1              2
#define CODEUR_G2              25
#define CODEUR_D1              5
#define CODEUR_D2              6
#define CHAN1                  0x00
#define CHAN2                  0x01
#define RAYON_ROUE             24 //MM
#define NBR_POINT_CODEUR_G     703
#define NBR_POINT_CODEUR_D     650
#define PERIODE_E              10000 //microsecondes
#define PERIODE_E_S		         0.01
#define COEF_VIT_G_UP          0.66
#define COEF_VIT_G_DW          0.84
#define COEF_VIT_G_M           0.76
#define COEF_VIT_D_UP          0.66
#define COEF_VIT_D_DW          0.88
#define COEF_VIT_D_M           0.78




#endif
