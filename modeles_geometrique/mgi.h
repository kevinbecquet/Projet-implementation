#ifndef MGI_H
#define MGI_H

    #include "Vector2.hpp"
    #include "mgd.h"

    #include <iostream>
    using namespace std;
    

    /**
    *@fn next_speed(double& v_0, double& w_0, double& w_d, double& w_g)
    *@brief Détermine les prochaine rotations des roues en fonction des prochaines vitesses du robot
    *@param v_0 prochaine vitesse du robot
    *@param w_0 prochaine vitesse angulaire du robot 
    *@param w_d rotation de la roue droite
    *@param w_g rotation de la roue gauche 
    */
    void next_speed(double& v_0, double& w_0, double& w_d, double& w_g){

        w_d = (v_0/r + w_0*d/2/r)/te;
        w_g = (v_0/r - w_0*d/2/r)/te;
    }


    /**
    *@fn geo2cine(Vector2& curr_pos, double& orientation, Vector2& next_pos, double& v, double& w , double& te)
    *@brief Détermine les prochaines vitesse de translation et rotation désirées à partir de la position actuelle du robot et de sa prochaine position désirée
    *@param curr_pos    position actuelle du robot
    *@param orientation orientation actuelle du robot par rapport a son axe de départ
    *@param next_pos    prochaine position désirée du robot
    *@param v           prochaine vitesse de translation tu robot
    *@param w           prochaine vitesse angulaire du robot 
    *@param te          periode d'échantilllonage
    */
    void geo2cine(Vector2& curr_pos, double& orientation, Vector2& next_pos, double& v, double& w , double& te){
        Vector2 dplct_des = next_pos - curr_pos;
        v = dplct_des.norme()/te;

        Vector2 dplct_sans_rotation(v * cos(orientation), v * sin(orientation) );

        w = dplct_sans_rotation.angle(dplct_des)/te;
    }

    /**
    *@fn mgi( Vector2& curr_pos, double& orientation, Vector2& next_pos, double& te, double& w_d, double& w_g){
    *@brief Détermine les prochaines vitesse de rotation des roues en fonction de la prochaine position souhaitée du robot
    *@param curr_pos    position actuelle du robot
    *@param orientation orientation actuelle du robot par rapport a son axe de départ
    *@param next_pos    prochaine position désirée du robot
    *@param te          periode d'échantilllonage
    *@param v           prochaine vitesse de translation tu robot
    *@param w           prochaine vitesse angulaire du robot 
    */
    void mgi( Vector2& curr_pos, double& orientation, Vector2& next_pos, double& te, double& w_d, double& w_g){
        double v,w;
        geo2cine(curr_pos,orientation,next_pos,v,w,te);

        next_speed(v,w,w_d,w_g);
    }

#endif