#ifndef PID_H
#define PID_H

#define d_approx    0.0000001
#define Kp          1.5
#define Ki          0.3
#define Kd          0.3
#define Kff         0

#define SEUIL_HAUT  1
#define SEUIL_BAS  -1

#define Te          0.01

double err_prec =   0.0;
double d_out_prec = 0.0;
double i_out =      0.0;
double v_prec =     0.0;

double pid(double& v_mes, double& v_des, double& v_out) {

    double err = v_mes - v_des;

    double ff_out = Kff * v_des; // terme de sortie predictif (feedforward)

    double p_out = Kp * err; // composante proportionnelle du pid

    double d_out = (d_approx * d_out_prec + Kd * (v_mes - v_prec)) / (Te + d_approx); //composante derivative du pid approximée

    v_out = ff_out + p_out + i_out + d_out;

    if ((v_out <= SEUIL_HAUT) && (v_out >= SEUIL_BAS)) {

        i_out += Ki *Te * err; //integration de l'erreur si la sortie n'est pas saturée
        v_out = ff_out + p_out + i_out + d_out; //sortie du PID
    }

    // mise a jour des termes gardés en memoire
    err_prec = err;
    d_out_prec = d_out;

    return v_out;
}
#endif
