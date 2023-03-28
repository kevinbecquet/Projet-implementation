#ifndef MGD_H
#define MGD_H

    #include "Vector2.hpp"
    #include <cmath>


    // données géometriques du robot
    double r = 24.0/1000;
    double d = (116+19.4)/1000;


    // pose initiale du robot
    double orientation = 0;
    Vector2 position(0,0);

    // période d'échantillonnage en s
    double te = 1;

    /**
    *@fn next_pos(double& w_d , double& w_g, double& orientation, Vector2& pos)
    *@brief Détermine la prochaine posistion du robot en se basant sur sa position actuelle et la rotation de ses roues
    *@param w_d rotation de la roue droite
    *@param w_g rotation de la roue gauche
    *@param orientation orientation actuelle du robot par rapport a son axe de départ
    *@param pos position du robot 
    */
    void next_pos(double& w_d , double& w_g, double& orientation, Vector2& pos){

        float v_curr = r/2*(w_d+w_g);
        orientation += r/d*(w_d-w_g);

        Vector2 depl(v_curr*cos(orientation)*te,v_curr*sin(orientation)*te);

        pos= pos+depl;
    }

    /**
    *@fn next_pos(double& w_d , double& w_g, double& orientation, Vector2& pos)
    *@brief Détermine un ensemble de position du robot à partir d'une séquence de rotation de ses roues 
    *@param w_d rotation de la roue droite
    *@param w_g rotation de la roue gauche
    *@param orientation orientation actuelle du robot par rapport a son axe de départ
    *@param pos position du robot
    *@param length longueur de la séquence 
    */
    void mgd(double& w_d, double& w_g, double& orientation, Vector2& position, int length){

    for(int i = 0; i<length; ++i){
        next_pos(w_d,w_g,orientation,position);
    }

}

#endif