#ifndef VECTOR_H
    #define VECTOR_H

    #include <iostream>
    #include <cstdlib>
    #include <cmath>

    class Vector2 {

        public:
            double x;
            double y;

            Vector2(): x(0),y(0){};
            Vector2(double a, double b): x(a), y(b){};

            double get_x(){ return x;}
            double get_y(){ return y;}

            /**
            *@fn scalar(Vector2& u)
            *@brief Retourne le produit scalaire entre le vecteur courant et le vecteur u
            *@param u deuxieme vecteur 
            *@return le resultat du produit scalaire
            */
            double scalar(Vector2& u){
                return x * u.x + y * u.y;
            }
            
            /**
            *@fn cross(Vector2& u)
            *@brief Retourne le produit vectoriel entre le vecteur courant et le vecteur u
            *@param u deuxieme vecteur 
            *@return le resultat du produit vectoriel
            */
            double cross(Vector2& u){
                return x * u.y - y * u.x;
            }

            /**
            *@fn angle(Vector2& u)
            *@brief Retourne l'angle entre le vecteur courant et le vecteur u
            *@param u deuxieme vecteur 
            *@return l'angle en radiant
            */
            double angle(Vector2&u){

                double angle = atan2(this->cross(u),this->scalar(u));
                return angle;

            }

            /**
            *@fn norme(Vector2& u)
            *@brief Retourne la norme du vecteur courant
            *@return la norme
            */
            double norme(){
                return sqrt(this->scalar(*this));
            }        

            /**
            *@fn operator+(Vector2& u)
            *@brief Retourne la somme entre le vecteur courant et le vecteur u
            *@param u deuxieme vecteur 
            *@return le vecteur resultat
            */
            Vector2 operator+(Vector2 u){
                Vector2 v(x+u.x, y+u.y);
                return v;
            }

            /**
            *@fn operator-(Vector2& u)
            *@brief Retourne la différence entre le vecteur courant et le vecteur u
            *@param u deuxieme vecteur 
            *@return le vecteur resultat
            */
            Vector2 operator-(Vector2 u){
                Vector2 v(x-u.x, y-u.y);
                return v;
            }

            /**
            *@fn operator-(Vector2& u)
            *@brief Retourne la multiplication entre le vecteur courant et un reel k
            *@param k le reel multiplicateur 
            *@return le vecteur resultat
            */
            Vector2 operator*(double k){
                Vector2 v(k*x,k*y);
                return v;
            }

            /**
            *@fn operator-(Vector2& u)
            *@brief Retourne la division entre le vecteur courant et un reel k
            *@param k le reel divisant 
            *@return le vecteur resultat
            */
            Vector2 operator/(double k){
                Vector2 v(k/x,k/y);
                return v;
            }

    };

#endif