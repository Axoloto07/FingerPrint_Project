#include "../include/optimization.hpp"
#include "../include/geometrical_op.hpp"



//---------------- loss functions ----------------


double loss_function(img i1, img i2, float tx, float ty, float theta){
    // make the transformations for i2
    img t_image = i2.translation((double)tx, (double)ty);
    img* r_image_pt = new img;
    // rotate the image if theta != 0
    //necessary of this "if else" condition because the rotate function affects the coeff even if theta = 0
    if (theta != 0){
        *r_image_pt = rotate(t_image, i1.coord_center()[0], i1.coord_center()[1], theta);
    }
    else{
        *r_image_pt = t_image;
    }
    // compute the loss
    double loss = 0;
    for (int i = 0; i<i1.get_rows(); i++){
        for (int j = 0; j<i1.get_cols(); j++){
            loss += pow(((double)r_image_pt->get_pix_val(i, j) - (double)i1.get_pix_val(i, j)), 2);
        }
    }
    double n = i1.get_rows()*i1.get_cols();
    delete r_image_pt;    
    return loss/n;  
}

float find_min_x(img i1, img i2, float b1, float b2, float min, float pmin){
    for (float j=b1; j<b2; j+=(b2-b1)/1000) {
        float y = loss_function(i1, i2, j, 0);
        if (y<min){
            min = y;
            pmin = j;
        }
    }
    if (b2-b1>10){
        float b1_ = pmin - (b2-b1)/4;
        float b2_ = pmin + (b2-b1)/4;
        std::cout << "min = " << min << std::endl;
        std::cout << "pmin = " << pmin << std::endl;
        std::cout << "\n";
        min = find_min_x(i1, i2, b1_, b2_, min, pmin);
    }
    else{
        std::cout << "min_final = " << min << std::endl;
        std::cout << "pmin_final = " << pmin << std::endl;
        return min;
    }
    return min;
}

float find_min_xy(img i1, img i2, float bi1, float bi2, float bj1, float bj2, float min, float pmini, float pminj){
    for (float j=bj1; j<bj2; j+=(bj2-bj1)/100) {
        for (float i=bi1; i<bi2; i+=(bi2-bi1)/100){
            float y = loss_function(i1, i2, j, i);
            //std::cout << "y = " << y << std::endl;
            if (y<min){
                min = y;
                pminj = j;
                pmini = i;
            }
        }
    }
    if (bi2-bi1>10 || bj2-bj1>10){
        float bi1_ = pmini - (bi2-bi1)/8;
        float bi2_ = pmini + (bi2-bi1)/8;
        float bj1_ = pminj - (bj2-bj1)/8;
        float bj2_ = pminj + (bj2-bj1)/8;
        std::cout << "min = " << min << std::endl;
        std::cout << "pmini = " << pmini << std::endl;
        std::cout << "pminj = " << pminj << std::endl;
        std::cout << "\n";
        min = find_min_xy(i1, i2, bi1_, bi2_, bj1_, bj2_, min, pmini, pminj);
    }
    else{
        std::cout << "min_final = " << min << std::endl;
        std::cout << "pmini_final = " << pmini << std::endl;
        std::cout << "pminj_final = " << pminj << std::endl;
        return min;
    }
    return min;
}


float find_min_xytheta(img i1, img i2, float bi1, float bi2, float bj1, float bj2, float bt1, float bt2, float min, float pmini, float pminj, float ptheta){
    for (float j=bj1; j<bj2; j+=(bj2-bj1)/100) {
        for (float i=bi1; i<bi2; i+=(bi2-bi1)/100){
            for (float theta=bt1; theta<bt2; theta+=(bt2-bt1)/100){
                float y = loss_function(i1, i2, j, i, theta);
                // std::cout << "y = " << y << std::endl;
                if (y<min){
                    min = y;
                    pminj = j;
                    pmini = i;
                    ptheta = theta;
                }
            }
        }
    }
    if (bi2-bi1>20 || bj2-bj1>20 || bt2-bt1>1){
        float bi1_ = pmini - (bi2-bi1)/4;
        float bi2_ = pmini + (bi2-bi1)/4;
        float bj1_ = pminj - (bj2-bj1)/4;
        float bj2_ = pminj + (bj2-bj1)/4;
        float bt1_ = ptheta - (bt2-bt1)/4;
        float bt2_ = ptheta + (bt2-bt1)/4;
        std::cout << "min = " << min << std::endl;
        std::cout << "pmini = " << pmini << std::endl;
        std::cout << "pminj = " << pminj << std::endl;
        std::cout << "ptheta = " << ptheta << std::endl;
        std::cout<<"\n";
        min = find_min_xytheta(i1, i2, bi1_, bi2_, bj1_, bj2_,bt1_, bt2_, min, pmini, pminj, ptheta);
    }
    else{
        std::cout << "min_final = " << min << std::endl;
        std::cout << "pmini_final = " << pmini << std::endl;
        std::cout << "pminj_final = " << pminj << std::endl;
        std::cout << "ptheta_final = "<< ptheta << std::endl;
        return min;
    }
    return min;
}

double loss_function_opt(img i1, img i2, float tx, float ty, float theta){
// loss function for the image registration (can be seen as a covariance)
    img t_image = i2.translation(tx, ty);
    img* r_image_pt = new img;
    // rotate the image if theta != 0
    //necessary of this "if else" condition because the rotate function affects the coeff even if theta = 0
    if (theta != 0){
        *r_image_pt = rotate(t_image, i1.coord_center()[0], i1.coord_center()[1], theta);
    }
    else{
        *r_image_pt = t_image;
    }
    double lnum = 0;
    double ldenl = 0;
    double ldenr = 0;
    double m = (double)i1.mean(); // We stock these 2 means to avoid to calculate them at every iterations (time complexity is much improved!!)
    double rm = (double)r_image_pt->mean();
    for (int i = 0; i<i1.get_rows(); i++){
        for (int j = 0; j<i1.get_cols(); j++){
            lnum += ((double)i1.get_pix_val(i, j)-m)*((double)r_image_pt->get_pix_val(i, j)-rm);
            ldenl += pow((double)i1.get_pix_val(i, j)-m,2);
            ldenr += pow((double)r_image_pt->get_pix_val(i, j)-rm,2);
        }
    }
    double loss = lnum/(std::sqrt(ldenl*ldenr));
    delete r_image_pt;
    return loss;
}


float loss_function_diff(img i1, img i2, float tx, float ty, float theta){
// loss function for the image registration (absolute difference)
    img t_image = i2.translation(tx, ty);
    img* r_image_pt = new img;
    if (theta != 0){
        *r_image_pt = rotate(t_image, i2.coord_center()[0], i2.coord_center()[1], theta);
    }
    else{
        *r_image_pt = t_image;
    }
    float loss = 0;
    for (int i = 0; i<i1.get_rows(); i++){
        for (int j = 0; j<i1.get_cols(); j++){
            loss += abs(t_image.get_pix_val(i, j) - i1.get_pix_val(i, j));
        }
    }
    delete r_image_pt;
    return loss;   
}



double loss_function_pderivative_x(img i1, img i2, double tx, double ty, double theta, double h){
    double n = i1.get_rows()*i1.get_cols();
    img t_image = i2.translation(tx, ty);
    img dt_image = i2.translation(tx+h, ty);
    Mat res_dev = Mat(i1.get_rows(), i1.get_cols(), CV_64F, Scalar(0.0));
    double loss1 = 0.0;
    double loss2 = 0.0;
    for (int i = 0; i<i1.get_rows(); i++){
        for (int j = 0; j<i1.get_cols(); j++){
            loss1 += pow((double)i1.get_pix_val(i, j)-(double)dt_image.get_pix_val(i, j),2);
            loss2 += pow((double)i1.get_pix_val(i, j) - (double)t_image.get_pix_val(i, j),2);
        }
    }
    loss1 = loss1/n;
    loss2 = loss2/n;
    double loss = loss1 - loss2;
    return loss/h; 
}

double loss_function_pderivative_y(img i1, img i2, double tx, double ty, double theta, double h){
    double n = i1.get_rows()*i1.get_cols();
    img t_image = i2.translation(tx, ty);
    img dt_image = i2.translation(tx, ty+h);
    Mat res_dev = Mat(i1.get_rows(), i1.get_cols(), CV_64F, Scalar(0.0));
    double loss1 = 0.0;
    double loss2 = 0.0;
    for (int i = 0; i<i1.get_rows(); i++){
        for (int j = 0; j<i1.get_cols(); j++){
            loss1 += pow((double)i1.get_pix_val(i, j)-(double)dt_image.get_pix_val(i, j),2);
            loss2 += pow((double)i1.get_pix_val(i, j) - (double)t_image.get_pix_val(i, j),2);
        }
    }
    loss1 = loss1/n;
    loss2 = loss2/n;
    double loss = loss1 - loss2;
    return loss/h;    
}




//---------------- draw loss functions ----------------




void draw_loss_function_x(img i1, img i2, double b1, double b2, int nb, int a){
// draw the loss function for the translation in x
// a = 0 for the loss function
// a = 1 for the loss function opt
    // plot the loss function
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");

    float min = INFINITY;
    float pmin = 0;
    float max = -INFINITY;
    int pmax = 0;
    fprintf(gnuplotPipe, "plot '-' with lines\n");
    switch (a){
        case 0:
            for (float j=b1; j<b2; j+=(b2-b1)/nb) {
                float y = loss_function(i1, i2, j, 0);
                if (y<min){
                    min = y;
                    pmin = j;
                }
                fprintf(gnuplotPipe, "%f %f\n", j, y);
            }
            std::cout << "valeur min "<< min <<std::endl;
            std::cout << "position min "<< pmin <<std::endl;
            break;
        case 1:
            for (int j=b1; j<=b2; j+=(b2-b1)/nb) {
                float y = loss_function_opt(i1, i2, j, 0);
                if (y>max){
                    max = y;
                    pmax = j;
                }
                fprintf(gnuplotPipe, "%d %f\n", j, y);
            }
            std::cout << "valeur max "<< max <<std::endl;
            std::cout << "position max "<< pmax <<std::endl;
            break;
        case 2:
            for (int j=b1; j<=b2; j+=(b2-b1)/nb) {
                float y = loss_function_diff(i1, i2, j, 0);
                if (y<min){
                    min = y;
                    pmin = j;
                }
                fprintf(gnuplotPipe, "%d %f\n", j, y);
            }
            std::cout << "valeur min "<< min <<std::endl;
            std::cout << "position min "<< pmin <<std::endl;
            break;
    }
    fprintf(gnuplotPipe, "e\n");

    // Close the pipe
    pclose(gnuplotPipe);    
}


void draw_loss_function_pderivative_x(img i1, img i2, double b1, double b2, int nb, double h){
// draw the loss function for the translation in x
    // plot the loss function
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
    int m = i1.get_cols();
    fprintf(gnuplotPipe, "plot '-' with lines\n");
    for (double j=b1   ; j<=b2; j+=(b2-b1)/nb) {
        double y = loss_function_pderivative_x(i1, i2, j, 0, h);

        fprintf(gnuplotPipe, "%f %f\n", j, y);
    }
    fprintf(gnuplotPipe, "e\n");

    // Close the pipe
    pclose(gnuplotPipe);
}

void draw_loss_function_xy(img i1, img i2, double bi1, double bi2, double bj1, double bj2, int nb, int a){
// a = 0 for the loss function
// a = 1 for the loss function opt
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
    int n = i1.get_rows();
    int m = i1.get_cols();
    float min = INFINITY;
    float pminj = 0;
    float pmini = 0;

    float max = 0;
    int pmaxj = 0;
    int pmaxi = 0;
    fprintf(gnuplotPipe, "splot '-'\n");
    switch (a){
        case 0:

            for (float i=bi1; i<=bi2; i+=(bi2-bi1)/nb) {
                for (float j=bj1; j<=bj2; j+=(bj2-bj1)/nb) {
                    float y = loss_function(i1, i2, j, i);
                    if (y<min){
                        min = y;
                        pminj = j;
                        pmini = i;
                    }
                    fprintf(gnuplotPipe, "%f %f %f\n", j, i, y);
                }
            }
            std::cout << "value min "<< min << std::endl;
            std::cout << "position min i: "<< pmini << " j: " << pminj << std::endl;
            break;
        case 1:
            
            for (float i=bi1; i<=bi2; i+=(bi2-bi1)/nb) {
                for (float j=bj1; j<=bj2; j+=(bj2-bj1)/nb) {
                    float y = loss_function_opt(i1, i2, j, i);
                    if (y>max){
                        max = y;
                        pmaxj = j;
                        pmaxi = i;
                    }
                    fprintf(gnuplotPipe, "%f %f %f\n", j, i, y);
                }
            }
            std::cout << "value max "<< max << std::endl;
            std::cout << "position max i: "<< pmaxi << " j: " << pmaxj << std::endl;
            break;
        case 2:

            for (float i=bi1; i<=bi2; i+=(bi2-bi1)/nb) {
                for (float j=bj1; j<=bj2; j+=(bj2-bj1)/nb) {
                    float y = loss_function_diff(i1, i2, j, i);
                    if (y<min){
                        min = y;
                        pminj = j;
                        pmini = i;
                    }
                    fprintf(gnuplotPipe, "%f %f %f\n", j, i, y);
                }
            }
            std::cout << "value min "<< min << std::endl;
            std::cout << "position min i: "<< pmini << " j: " << pminj << std::endl;
            break;

    }
    fprintf(gnuplotPipe, "e\n");

    // Close the pipe
    pclose(gnuplotPipe);
}


void display_loss_function_xytheta(img i1, img i2, double bi1, double bi2, double bj1, double bj2, double bt1, double bt2, int nb, int a){
// draw the loss function for the translation in x and y and rotation
// a = 0 for the loss function
// a = 1 for the loss function opt
    int n = i1.get_rows();
    int m = i1.get_cols();

    float min = INFINITY;
    float pminj = 0;
    float pmini = 0;
    float thetamin = 0; 

    float max = -INFINITY;
    int pmaxj = 0;
    int pmaxi = 0;
    float thetamax = 0;
    
    switch (a){
        case 0:
            for (float i = bi1; i <= bi2; i += (bi2-bi1)/nb) {
                for (float j = bj1; j <= bj2; j += (bj2-bj1)/nb) {
                    for (float theta = bt1; theta <= bt2; theta += (bt2-bt1)/nb) {
                        float y = loss_function(i1, i2, j, i, theta);
                        if (y<min){
                            min = y;
                            pminj = j;
                            pmini = i;
                            thetamin = theta;
                        }
                    }
                }
            }
            std::cout << "valeur min "<< min << std::endl;
            std::cout << "position min i: "<< pmini << " j: " << pminj << " theta: " << thetamin << std::endl;
            break;
        case 1:
            for (float i = bi1; i <= bi2; i += (bi2-bi1)/nb) {
                for (float j = bj1; j <= bj2; j += (bj2-bj1)/nb) {
                    for (float theta = bt1; theta <= bt2; theta += (bt2-bt1)/nb) {
                        float y = loss_function_opt(i1, i2, j, i, theta);
                        if (y>max){
                            max = y;
                            pmaxj = j;
                            pmaxi = i;
                            thetamax = theta;
                        }
                    }
                }
            }
            std::cout << "valeur max "<< max << std::endl;
            std::cout << "position max i: "<< pmaxi << " j: " << pmaxj << " theta: " << thetamax << std::endl;
            break;
        case 2:
            for (float i = bi1; i <= bi2; i += (bi2-bi1)/nb) {
                for (float j = bj1; j <= bj2; j += (bj2-bj1)/nb) {
                    for (float theta = bt1; theta <= bt2; theta += (bt2-bt1)/nb) {
                        float y = loss_function_diff(i1, i2, j, i, theta);
                        if (y<min){
                            min = y;
                            pminj = j;
                            pmini = i;
                            thetamin = theta;
                        }
                    }
                }
            }
            std::cout << "valeur min "<< min << std::endl;
            std::cout << "position min i: "<< pmini << " j: " << pminj << " theta: " << thetamin << std::endl;
            break;
    }
}



// -------------------- coordinate descent algorithm --------------------


float coord_descent(img i1, img i2, float pj, float al, std::vector<float>* list_al, int cpt){
// coordinate descent algorithm recusrive function
// used for draw convergence of the algorithm
    int n = i1.get_rows();
    int m = i1.get_cols();
    float c = loss_function(i1, i2, pj);
    list_al->push_back(al);
    if (cpt < 5000 && al>1e-10){
        if (loss_function(i1, i2, pj*(1+al)) < c){
            coord_descent(i1, i2, pj*(1+al), al*1.1, list_al, cpt+1);
        }
        else if(loss_function(i1, i2, pj*(1-al)) < c){
            coord_descent(i1, i2, pj*(1-al), al*1.1, list_al, cpt+1);
        }
        else{
            coord_descent(i1, i2, pj, al*0.9, list_al, cpt+1);
        }
    }
    else{
        return pj;
    } 
    return 0;
}


void coord_descent_2(img i1, img i2, float pj, float *p_res, float al, int cpt){
// coordinate descent algorithm recusrive function
// used for result conv
    int m = i1.get_cols();
    float c = loss_function(i1, i2, pj);
    if (cpt < 500 && al>1e-10){
        if (loss_function(i1, i2, pj*(1+al)) < c){
            coord_descent_2(i1, i2, pj*(1+al), p_res, al*1.1, cpt+1);
        }
        else if(loss_function(i1, i2, pj*(1-al)) < c){
            coord_descent_2(i1, i2, pj*(1-al), p_res, al*1.1, cpt+1);
        }
        else{
            coord_descent_2(i1, i2, pj,  p_res, al*0.9, cpt+1);
        }
    }
    else{
        *p_res = pj;
    }
}

void draw_convergence(img i1, img i2, float al){
// draw convergence of the algorithm
    int n = i1.get_rows();
    int m = i1.get_cols();
    std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> dis_pj(-m, m);
    float pj = dis_pj(generator);
    // generate random pi and pj uniformely distributed
    int cpt = 0;
    std::vector<float> *list_al = new std::vector<float>;
    coord_descent(i1, i2, pj, al, list_al, cpt);
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
    fprintf(gnuplotPipe, "plot '-' with lines\n");
    for (int i=0; i<list_al->size(); i++){
        fprintf(gnuplotPipe, "%d %f\n", i, (*list_al)[i]);
    }
    fprintf(gnuplotPipe, "e\n");
    delete list_al;
}

void result_conv(img i1, img i2, float al){
// show the result of the convergence of the algorithm
// display several result of the algorithm  for random initial values
    int m = i1.get_cols();
    std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> dis_pj(-m, m);
    int cpt = 0;
    // list of results
    std::vector<float> *list_p = new std::vector<float>;
    for (int i=0; i<20; i++){
        float pj = dis_pj(generator);
        // generate random pi and pj uniformely distributed
        float* p_res = new float;
        coord_descent_2(i1, i2, pj, p_res, al, cpt);
        list_p->push_back(*p_res);
        std::cout << "coord descent : pj  " << *p_res << std::endl;
    }
    float min = INFINITY;
    int i_res = 0;
    for (int i=0; i<list_p->size(); i++){
        if (loss_function(i1, i2, (*list_p)[i]) < min){
            min = loss_function(i1, i2, (*list_p)[i]);
            i_res = i;
        }
    }
    std::cout<<"\n";
    std::cout << "final result coord descent : pj  " << (*list_p)[i_res] << std::endl;
    delete list_p;
}




// ----------------------- gradient descent algorithm ------------------------------


void grad_descent(img i1, img i2, double pi, double pj, double al, std::vector<double>* list_eps, double *p_res, double eps){
    // initials values
    double p[2] = {pi, pj};
    int n = i1.get_rows();
    int m = i1.get_cols();
    double c = loss_function_pderivative_x(i1, i2, p[1], p[0]);
    // list of results
    // the algorithm
    for (int i=0; i<10000; i++){
        eps = loss_function_pderivative_x(i1, i2, p[1], p[0]);
        list_eps->push_back(eps);
        p[1] = p[1] - al*loss_function_pderivative_x(i1, i2, p[1], p[0]);
    }
    // final result
    double k = 0.5; // variation rate/2
    if (eps>0){
        p_res[1] = p[1] - k;
        p_res[0] = p[0] - k;
    }
    else{
        p_res[1] = p[1] + k;
        p_res[0] = p[0] + k;
    }
}

void grad_descent_2_x(img i1, img i2, double pi, double pj, double al, double *p_res){
    // initials values
    double p[2] = {pi, pj};
    int n = i1.get_rows();
    int m = i1.get_cols();
    double eps = 1000;
    // the algorithm
    int cpt = 0;
    double k = 0.5; // variation rate/2
    for (int i=0; i<2000; i++){
        if (abs(eps)>1){
            eps = loss_function_pderivative_x(i1, i2, p[1], p[0]);
            p[1] = p[1] -al*eps;
            cpt+=1;
        }       
        else{
            if (eps>0){
                p_res[1] = p[1] - k;

            }
            else{
                p_res[1] = p[1] + k;
            }
            return;
        }
    }
    if (eps>0){
        p_res[1] = p[1] -k;
    }
    else{
        p_res[1] = p[1] + k;
    }
}



void grad_descent_2(img i1, img i2, double pi, double pj, double al, double *p_res){
    // initials values
    double p[2] = {pi, pj};
    int n = i1.get_rows();
    int m = i1.get_cols();
    double eps = 1000;
    double eps2 = 1000;
    // the algorithm
    std::cout << "p at the beginning " << p[0] << " "<<p[1] <<std::endl;
    int cpt = 0;
    double k = 0.5; // variation rate/2
    for (int i=0; i<20000; i++){
        if (abs(eps)>0.1 || abs(eps2)>3){
            eps = loss_function_pderivative_x(i1, i2, p[1], p[0]);
            eps2 = loss_function_pderivative_y(i1, i2, p[1], p[0]);
            p[0] = p[0] -al*eps2;
            p[1] = p[1] -al*eps;
            cpt+=1;
        }       
        else{
            if (eps>0 && eps2>0){
                p_res[0] = p[0] - k;
                p_res[1] = p[1] - k;
            }
            else if (eps>0 && eps2<0){
                p_res[0] = p[0] + k;
                p_res[1] = p[1] - k;
            }
            else if (eps<0 && eps2>0){
                p_res[0] = p[0] - k;
                p_res[1] = p[1] + k;
            }
            else{
                p_res[0] = p[0] + k;
                p_res[1] = p[1] + k;
            }
            std::cout << "cpt " << cpt << std::endl;
            return;
        }
    }
    if (eps > 0 && eps2 > 0){
        p_res[0] = p[0] - k;
        p_res[1] = p[1] - k;
    }
    else if (eps > 0 && eps2 < 0){
        p_res[0] = p[0] + k;
        p_res[1] = p[1] - k;
    }
    else if (eps < 0 && eps2 > 0){
        p_res[0] = p[0] - k;
        p_res[1] = p[1] + k;
    }
    else{
        p_res[0] = p[0] + k;
        p_res[1] = p[1] + k;
    }
    std::cout << "cpt " << cpt << std::endl;
}

void draw_convergence_grad(img i1, img i2, double al){
// draw convergence of the algorithm
    int n = i1.get_rows();
    int m = i1.get_cols();
    std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> dis_pi(-n, n);
    std::uniform_int_distribution<int> dis_pj(-m, m);
    double pi = (double)dis_pi(generator);
    double pj = (double)dis_pj(generator);
    // generate random pi and pj uniformely distributed
    double p[2] = {0, pj};
    int cpt = 0;
    std::vector<double> *list_eps = new std::vector<double>;
    double p_res[2];
    grad_descent(i1, i2, p[0], p[1], al, list_eps, p_res);
    //std::cout << "final result grad descent : pi " << p_res[0] << ", pj  " << p_res[1] << std::endl;
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
    fprintf(gnuplotPipe, "plot '-' with lines\n");
    // send data to gnuplot
    for (int i=0; i<list_eps->size(); i++){
        fprintf(gnuplotPipe, "%d %f\n", i, (*list_eps)[i]);
    }
    // close the plot
    fprintf(gnuplotPipe, "e\n");
    delete list_eps;
}

void result_conv_grad(img i1, img i2, double al){
// show the result of the convergence of the algorithm
// display several result of the algorithm  for random initial values
    int n = i1.get_rows();
    int m = i1.get_cols();
    std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> dis_pi(-30, 0);
    std::uniform_int_distribution<int> dis_pj(0, 50);
    // list of results
    std::vector<double*> *list_p = new std::vector<double*>;
    for (int i=0; i<20; i++){
        double pi = (double)dis_pi(generator);
        double pj = (double)dis_pj(generator);
        // generate random pi and pj uniformely distributed
        double p[2] = {pi, pj};
        double p_res[2];
        grad_descent_2(i1, i2, pi, pj, al, p_res);
        list_p->push_back(p_res);
        std::cout << "final result grad descent : pi " << p_res[0] << ", pj  " << p_res[1] << std::endl;
    }
    float min = INFINITY;
    int i_res = 0;
    for (int i=0; i<list_p->size(); i++){
        if (loss_function(i1, i2, (*list_p)[i][1], (*list_p)[i][0]) < min){
            min = loss_function(i1, i2, (*list_p)[i][1], (*list_p)[i][0]);
            i_res = i;
        }
    }
    std::cout<<"\n";
    std::cout << "final result grad descent : pi"<< (*list_p)[i_res][0] << " pj "<< (*list_p)[i_res][1] << std::endl;
    std::cout << "\n";

    delete list_p;
}

void result_conv_grad_x(img i1, img i2, double al){
// show the result of the convergence of the algorithm
// display several result of the algorithm  for random initial values
    int m = i1.get_cols();
    std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> dis_pj(-50, 50);
    // list of results
    std::vector<double> *list_p = new std::vector<double>;
    for (int i=0; i<20; i++){
        double pj = (double)dis_pj(generator);
        // generate random pi and pj uniformely distributed
        double p[2] = {0, pj};
        double p_res[2];
        grad_descent_2_x(i1, i2, 0, pj, al, p_res);
        list_p->push_back(p_res[1]);
        std::cout << "grad descent : pj  " << p_res[1] << std::endl;
    }
    float min = INFINITY;
    int i_res = 0;
    for (int i=0; i<list_p->size(); i++){
        if (loss_function(i1, i2, (*list_p)[i]) < min){
            min = loss_function(i1, i2, (*list_p)[i]);
            i_res = i;
        }
    }
    std::cout<<"\n";
    std::cout << "final result grad descent : pj  " << (*list_p)[i_res] << std::endl;

    delete list_p;
}