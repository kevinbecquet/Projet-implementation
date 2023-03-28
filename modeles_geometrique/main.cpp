#include "mgi.h"
int main(int argc, char* argv[]){
    
    Vector2* pos1 = new Vector2;
    if (argc >2){
        double posx = atof(argv[1]);
        double posy = atof(argv[2]);
        pos1->x = posx;
        pos1->y = posy;
    }
    else Vector2 pos1(1,1);

    double w_d,w_g;
    
    cout<< "position desirée(en m): x: "<<pos1->get_x()<<"; y: "<<pos1->get_y()<<endl;

    mgi(position,orientation,*pos1,te,w_d,w_g);
    
    cout<<"sortie du mgi(en rad/s): w_d: "<<w_d<<"; w_g: "<<w_g<<endl;

    mgd(w_d,w_g,orientation,position,1);

    cout<<"sortie du mgd: x: "<<position.get_x()<<" m; y: "<< position.get_y()<<" m; orientation: "<<orientation<<" rad"<<endl;

    return 0;
}