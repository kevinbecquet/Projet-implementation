
#ifndef TRAJ_GEN_H
    #define TRAJ_GEN_H

    #include <iostream> 
    #include <vector>
    #include "../modeles_geometrique/Vector2.hpp"

    using namespace std;

    /**
    *@fn interpolation_lin(Vector2& point_init, Vector2& point_fin, vector<Vector2>& points_int, int n)
    *@brief Réalise une interpolation linéaire entre point_init et point_fin en placant n point intermédiaires
    *@param point_init Point initial de l'interpolation.
    *@param point_fin Point final de l'interpolation.
    *@param points_int Vecteur contenant les points intermediaires créés
    *@param n Nombre de point créés
    */
    void interpolation_lin(Vector2& point_init, Vector2& point_fin, vector<Vector2>& points_int, int n){

        for (int i = 0 ; i<n ; ++i){

            double x = (point_fin.get_x()-point_init.get_x())*i/n+point_init.get_x();
            double y = (point_fin.get_y()-point_init.get_y())*i/n+point_init.get_y();
            Vector2 p(x,y);
            points_int.push_back(p);
        }
    }


    /**
    *@fn traj_lin(Vector2& point_init, vector<Vector2>& points_res, vector<Vector2>& traj, int n)
    *@brief Construit une trajectoir à l'aide d'une interpolation linéaire à partir d'un point de départ et d'un ensemble de points de passage
    *en placant n points intermédiaires en chacuns de ces points 
    *@param point_init Point initial de l'interpolation.
    *@param points_ref Vecteur des points de passage 
    *@param traj Vecteur contenant les points intermediaires créés
    *@param n Nombre de point créés entre chaque points de passage
    */
    void traj_lin(Vector2& point_init, vector<Vector2>& points_ref, vector<Vector2>& traj, int n){

        Vector2 temp = point_init;
        for(Vector2 point : points_ref){
            interpolation_lin(temp, point,traj,n);
            temp = point;
        }

    }

#endif