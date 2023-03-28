#include "acquisition.h"


int main(int argc, char const *argv[])
{
    if( argc > 1){

        const char* img_nom = argv[1];
        Mat image = imread(img_nom);

        Mat imbin = image,img_carre;
        binarise(image,imbin);


        vector<Point> carre,traj;
        if(!trouve_traj(imbin,img_carre,carre)){
            cout<<"aucun carré"<<endl;rectangle(image, carre[0], carre[2], Scalar(0, 255, 0), 2, 8, 0);
        // deter_traj(img_carre,traj);

        // cvtColor(img_carre,img_carre, COLOR_GRAY2BGR);
        // for(size_t i = 0; i< traj.size()-1;i++){
        //     line(img_carre, traj[i], traj[i+1], Scalar(255, 0, 0),2, LINE_8);

        
            return 0;
        }
        rectangle(image, carre[0], carre[2], Scalar(0, 255, 0), 2, 8, 0);
        deter_traj(img_carre,traj);

        // cvtColor(img_carre,img_carre, COLOR_GRAY2BGR);
        // for(size_t i = 0; i< traj.size()-1;i++){
        //     line(img_carre, traj[i], traj[i+1], Scalar(255, 0, 0),2, LINE_8);

        // }

        while(true){
            
             imshow("image originale",image);
            imshow("carre",img_carre);

            if (waitKey(30) == 27){ //Si la touche échap est activée, on sort du programme et on ferme toutes les fenêtres
		    cout << "esc key is pressed by user" << endl;
		    break;
		    }
        } 
        
    }
    else{
        vector<Vector2> traj;
        acquisition_camera(traj);
    }
    return 0;
}
