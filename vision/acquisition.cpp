#include "acquisition.h"
#include "../traj_gen/traj_gen.h"

/**
*@fn double angle( Point pt1, Point pt2, Point pt0 )
*@brief Calcule le cosinus de l'angle entre les vecteurs pt0->pt1 et pt0->pt2.
*@param pt1 Point1.
*@param pt2 Point2.
*@param pt0 Point0.
*@return La fonction renvoie le cosinus de l'angle entre les vecteurs pt0->pt1 et pt0->pt1.
*/
double angle( Point pt1, Point pt2, Point pt0 )
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10); // +1e-10 pour é  viter la division par 0
}

/**
*@fn Mat carre_droit(Mat imgOriginal,vector<Point> carre)
*@brief On applique une rotation au carre trouvé pour qu'il reste droit sur l'image.
*@details La fonction retourne la carte trouvée à la suite de extraction() pour pouvoir avoir un carré droit et non penché.
*@see extraction()
*@param imgOriginal Image que le programme va remettre droite.
*@param carre Liste des coins du carre dans l'image initiale, non extraite.
*@return La fonction renvoit l'image droite.
*/
Mat carre_droit(Mat img_original,vector<Point> carre){

    Point point1 = carre[3],point2 = carre[0];

    // on calcule le cos de l'angle entre un coté de la carte et la verticale
    double cosine = angle(Point(point1.x,0),point2,point1);
    double angle_rot;

    //selon le coté selectionné, on change l'angle de rotation qu'il faudra appliquer
    if( abs(point2.y-point1.y)>abs(point2.x-point1.x)){
        angle_rot =(point2.x-point1.x<0)? -acos(cosine)*180/3.14 : +acos(cosine)*180/3.14 ;
    }
    else{
      angle_rot =(point2.x-point1.x>0)? -(90-acos(cosine)*180/3.14) : 90 - acos(cosine)*180/3.14 ;
    }

    // Le point du milieu d'imgOriginal est au milieu de la carte
    int x = img_original.rows/2;
    int y = img_original.cols/2;
    Mat mat_rotation = getRotationMatrix2D( Point(x, y), angle_rot, 1 );

    // on applique la rotation à l'image
    Mat img_rotation,img_sortie;
    warpAffine( img_original, img_rotation, mat_rotation, img_original.size() );

    vector<vector<Point>> contours;
    findContours(img_rotation,contours,RETR_TREE, CHAIN_APPROX_SIMPLE );

    int max_aire = 0;
    for(vector<vector<Point>>::iterator it = contours.begin(); it <contours.end();it++ ){
        if(abs(contourArea(*it))>1000 &&
        abs(contourArea(*it))>max_aire){
            // on ajoute les contours de la carte dans imgout
            img_sortie=img_rotation(boundingRect(*it));
            max_aire = abs(contourArea(*it));
        }
    }

    return img_sortie;
}

/**
*@fn binarise(Mat& image, Mat& img_bin)
*@brief Réalise la binarisation de l'image donnée en paramètre
*@param image image d'entrée à binariser codée en format BGR
*@param img_bin resultat de la binarisation 
*/
void binarise(Mat& image, Mat& img_bin){

    Mat img_nb,pyr;
    cvtColor(image,img_nb, COLOR_BGR2GRAY);

    GaussianBlur(img_nb,img_nb,Size(5,5),0);
    threshold(img_nb,img_bin,0,255,THRESH_BINARY_INV+THRESH_OTSU);

    
    dilate(img_bin,img_bin,getStructuringElement(MORPH_ELLIPSE, Size(10, 10)));
    erode(img_bin,img_bin,getStructuringElement(MORPH_ELLIPSE, Size(10, 10)));

    // erode(img_bin,img_bin,getStructuringElement(MORPH_ELLIPSE, Size(4, 4)));
    // dilate(img_bin,img_bin,getStructuringElement(MORPH_ELLIPSE, Size(4, 4)));
    
}

/**
*@fn trouve_traj(Mat& img_entree, Mat& img_sortie, vector<Point>& carre)
*@brief Detecte le carré dans lequel est censé se trouver la trajectoire que le robot doit réaliser et extrait l'image de la trajectoire
*@param img_entree image d'entrée (binarisée) donnée en paramètre 
*@param img_sortie image extraite de img_entree contenant le dessin de la trajectoire à suivre  
*@param carre liste de points correspondant à la zone extraite dans l'image d'entree
*/
bool trouve_traj(Mat& img_entree, Mat& img_sortie, vector<Point>& carre){


    vector<vector<Point>> contours;
    // cherche les contours et les stocke dans la liste contours
    findContours(img_entree, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

    vector<Point> approx;
    // pour chaque contours ;
    for( size_t i = 0; i < contours.size(); i++ )
    {
        // on cree un polygone approximant le contour
        approxPolyDP(contours[i], approx, arcLength(contours[i], true)*0.02, true);
        
        Vector2 vlong(approx[0].x - approx[1].x, approx[0].y - approx[1].y);
        Vector2 vlarg(approx[2].x - approx[1].x, approx[2].y - approx[1].y);

        double lon = vlong.norme();
        double larg = vlarg.norme();

        // si le contour est un carre
        if( approx.size() == 4 &&
            fabs(contourArea(approx)) > 5000 &&
            fabs(contourArea(approx))< img_entree.rows * img_entree.cols * 0.7 &&
            isContourConvex(approx) &&
            ( (lon/larg<1.01 && lon/larg>0.99) || (larg/lon<0.99 && larg/lon>1.01 )))
        {                       
                carre = approx;
                img_sortie = img_entree(boundingRect(approx));
                img_sortie = carre_droit(img_sortie,approx);
                //resize(img_sortie, img_sortie, Size(600, 600), INTER_LINEAR);
                img_sortie = img_sortie(Range(10,img_sortie.size().height-10),Range(10,img_sortie.size().width-10));

                //erode(img_sortie,img_sortie,getStructuringElement(MORPH_ELLIPSE, Size(4, 4)));
                return true;
        

        }
    }
      
    //cout<<"aucun carré"<<endl;
    return false;
} 


/**
*@fn deter_traj(Mat& img_traj,vector<Point>& traj)
*@brief Détermine les points par lesquels le robot doit passer pour réaliser la même trajectoire que celle montrée sur l'image binarisée donnée en paramètre
*@param img_traj image d'entrée (binarisée) contenant la trajectoire à réaliser
*@param traj    vecteur des points par lesquels le robot doit passer
*/
void deter_traj(Mat& img_traj,vector<Point>& traj){

    vector<vector<Point>> contours;
    vector<Point> traj_temp;
    findContours(img_traj, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

    double max_long = 0;

    for(size_t i = 0; i< contours.size();i++){
        if(arcLength(contours[i], false)>max_long){
            traj.clear();
            approxPolyDP(contours[i], traj_temp, arcLength(contours[i], false)*0.002, false);
            max_long = arcLength(contours[i], false);
        }
    }

    traj.clear();
    cvtColor(img_traj,img_traj, COLOR_GRAY2BGR);
    for(size_t  i = 0; i< traj_temp.size()/2;i++){
        line(img_traj, traj_temp[i], traj_temp[i+1], Scalar(255, 0, 0),2, LINE_8);
        traj.push_back(traj_temp[i]);
    }
} 
void conversion_point_vect(vector<Point>& traj_point, vector<Vector2>& traj_vect, int taille_point, double taille_vect){

    traj_vect.clear();
    for(size_t i = 0; i<traj_point.size(); i++){

        double x = traj_point[i].x*taille_vect/taille_point;
        double y = traj_point[i].y*taille_vect/taille_point;
        Vector2 v(x,y);
        traj_vect.push_back(v);
    }
}

/**
 * @fn acquisition(Mat& image , vector<Vector2>& traj)
 * @brief Renvoie une suite de points représentant la trajectoire presente sur l'image d'entrée
 * @param image Image à traiter
 * @param traj vecteur de points representant la trajectoire que le robot derva suivre
 * @param carre vecteur de point represenant le carre regardé dans l'image
*/
bool acquisition(Mat& image , vector<Vector2>& traj, vector<Point>& carre, Mat& img_bin,  Mat& img_carre){

    
    binarise(image, img_bin);

    if(trouve_traj(img_bin,img_carre,carre)){

        vector<Point> traj_point;
        deter_traj(img_carre,traj_point);

        vector<Vector2> ref_points;
        conversion_point_vect(traj_point,ref_points,img_carre.rows,TAILLE);
        traj_lin(ref_points[0],ref_points,traj,50);

        return true;
    }

    return false;
}


bool acquisition_camera(vector<Vector2>& traj){
    
    VideoCapture cap(0);

    if(!cap.isOpened()){
        cout<<"La camera n'a pas pu etre ouverte."<<endl;
        return false;
    }    
    
    Mat img,img_carre,img_bin;
    vector<Point>carre;
    bool traj_ok = false;
    while(!traj_ok){
        
        cap.read(img);   
        traj_ok = acquisition(img,traj,carre,img_bin,img_carre);
        if (traj_ok){
            rectangle(img,carre[0],carre[2],Scalar(255,0,0),2);
            imshow("carre",img_carre);

        }
        imshow("video",img);
        imshow("bin",img_bin);

        if (waitKey(30) == 27){ //Si la touche échap est activée, on sort du programme et on ferme toutes les fenêtres
		    cout << "Touche echap pressee" << endl;
		    break;
		}
    }  

    cout<<"ok_traj"<<endl;
    while(1){
        imshow("video",img);
        rectangle(img,carre[0],carre[2],Scalar(255,0,0),2);

        imshow("carre",img_carre);

        if (waitKey(30) == 27){ //Si la touche échap est activée, on sort du programme et on ferme toutes les fenêtres
		    cout << "Touche echap pressee" << endl;
		    break;
		}
    }

    return false;
}