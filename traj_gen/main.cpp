#include "traj_gen.h"

int main(int argc, char const *argv[])
{
    int n;
    if (argc >1){
        n = atoi(argv[1]);
    }
    else n = 5;

    Vector2 point_init(0,0);
    vector<Vector2> points_ref;
    vector<Vector2> traj;

    for (int i = 1; i < 4;++i){
        
        Vector2 point(i,i+1);
        points_ref.push_back(point);

    }

    traj_lin(point_init,points_ref,traj,n);

    int i = 0;
    for(Vector2 p : traj){
        cout<<"point n."<<i<<": x= "<<p.get_x()<<" y="<<p.get_y()<<endl;
        ++i;
    }       

    return 0;
}
