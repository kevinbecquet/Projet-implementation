#ifndef VISION_H
    #define VISION_H

    #include <iostream>
    #include "../modeles_geometrique/Vector2.hpp"

    #include "opencv2/highgui/highgui.hpp"
    #include "opencv2/imgproc/imgproc.hpp"

    using namespace std; 
    using namespace cv;


    #define TAILLE 0.2 // longueur en metre de la zone de detection


    void binarise(Mat& image, Mat& img_bin);
    bool trouve_traj(Mat& img_entree, Mat& img_sortie,vector<Point>& carre);
    void deter_traj(Mat& img_traj,vector<Point>& traj);
    bool acquisition_camera(vector<Vector2>& traj);


#endif