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
    if (b2-b1>1){
        float b1_ = pmin - (b2-b1)/4;
        float b2_ = pmin + (b2-b1)/4;
        min = find_min_x(i1, i2, b1_, b2_, min, pmin);
    }
    else{
        cout << "min_final = " << min << endl;
        cout << "pmin_final = " << pmin << endl;
    }
}

float loss_function_opt(img i1, img i2, float tx, float ty, float theta){
// loss function for the image registration (can be seen as a covariance)
    img t_image = i1.translation(tx, ty);
    img* r_image_pt = new img;
    // rotate the image if theta != 0
    //necessary of this "if else" condition because the rotate function affects the coeff even if theta = 0
    if (theta != 0){
        *r_image_pt = rotate(t_image, i1.coord_center()[0], i1.coord_center()[1], theta);
    }
    else{
        *r_image_pt = t_image;
    }
    float lnum = 0;
    float ldenl = 0;
    float ldenr = 0;
    float m = i1.mean(); // We stock these 2 means to avoid to calculate them at every iterations (time complexity is much improved!!)
    float rm = r_image_pt->mean();
    for (int i = 0; i<i1.get_rows(); i++){
        for (int j = 0; j<i1.get_cols(); j++){
            lnum += (i1.get_pix_val(i, j)-m)*(r_image_pt->get_pix_val(i, j)-rm);
            ldenl += pow(i1.get_pix_val(i, j)-m,2);
            ldenr += pow(r_image_pt->get_pix_val(i, j)-rm,2);
        }
    }
    float loss = lnum/(std::sqrt(ldenl*ldenr));
    delete r_image_pt;
    return loss;
}


float loss_function_diff(img i1, img i2, float tx, float ty){
// loss function for the image registration (absolute difference)
    img t_image = i2.translation(tx, ty);
    float loss = 0;
    for (int i = 0; i<i1.get_rows(); i++){
        for (int j = 0; j<i1.get_cols(); j++){
            loss += abs(t_image.get_pix_val(i, j) - i1.get_pix_val(i, j));
        }
    }
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




void draw_loss_function_x(img i1, img i2, double b1, double b2, int a){
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
            for (float j=b1; j<b2; j+=(b2-b1)/1000) {
                float y = loss_function(i1, i2, j, 0);
                if (y<min){
                    min = y;
                    pmin = j;
                }
                fprintf(gnuplotPipe, "%f %f\n", j, y);
            }
            cout << "valeur min "<< min <<endl;
            cout << "position min "<< pmin <<endl;
            break;
        case 1:
            for (int j=b1; j<=b2; j+=(b2-b1)/1000) {
                float y = loss_function_opt(i1, i2, j, 0);
                if (y>max){
                    max = y;
                    pmax = j;
                }
                fprintf(gnuplotPipe, "%d %f\n", j, y);
            }
            cout << "valeur max "<< max <<endl;
            cout << "position max "<< pmax <<endl;
            break;
    }
    fprintf(gnuplotPipe, "e\n");

    // Close the pipe
    pclose(gnuplotPipe);    
}


void draw_loss_function_pderivative_x(img i1, img i2, double b1, double b2, double h){
// draw the loss function for the translation in x
    // plot the loss function
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
    int m = i1.get_cols();
    fprintf(gnuplotPipe, "plot '-' with lines\n");
    for (double j=b1   ; j<=b2; j+=(b2-b1)/1000) {
        double y = loss_function_pderivative_x(i1, i2, j, 0, h);

        fprintf(gnuplotPipe, "%f %f\n", j, y);
    }
    fprintf(gnuplotPipe, "e\n");

    // Close the pipe
    pclose(gnuplotPipe);
}

void draw_loss_function_xy(img i1, img i2, int a){
// a = 0 for the loss function
// a = 1 for the loss function opt
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
    int n = i1.get_rows();
    int m = i1.get_cols();
    float min = INFINITY;
    float pminj = 0;
    float pmini = 0;

    float max = -INFINITY;
    int pmaxj = 0;
    int pmaxi = 0;

    fprintf(gnuplotPipe, "splot '-' with lines\n");
    switch (a){
        case 0:

            for (float i=-50; i<=50; i+=1) {
                for (float j=-50; j<=50; j+=1) {
                    float y = loss_function(i1, i2, j, i);
                    if (y<min){
                        min = y;
                        pminj = j;
                        pmini = i;
                    }
                    fprintf(gnuplotPipe, "%f %f %f\n", j, i, y);
                }
            }
            cout << "value min "<< min << endl;
            cout << "position min i: "<< pmini << " j: " << pminj << endl;
            break;
        case 1:
            
            for (int i=-n; i<=n; i+=1) {
                for (int j=-m; j<=m; j+=1) {
                    float y = loss_function_opt(i1, i2, j, i);
                    if (y>max){
                        max = y;
                        pmaxj = j;
                        pmaxi = i;
                    }
                    fprintf(gnuplotPipe, "%d %d %f\n", j, i, y);
                }
            }
            cout << "value max "<< max << endl;
            cout << "position max i: "<< pmaxi << " j: " << pmaxj << endl;
            break;
    }
    fprintf(gnuplotPipe, "e\n");

    // Close the pipe
    pclose(gnuplotPipe);
}


void display_loss_function_xytheta(img i1, img i2, int a){
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
            for (float i=-10; i<=10; i+=1) {
                for (float j=-10; j<=10; j+=1) {
                    for (float theta=0; theta<=2*M_PI; theta+=0.1) {
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
            cout << "valeur min "<< min << endl;
            cout << "position min i: "<< pmini << " j: " << pminj << " theta: " << thetamin << endl;
            cout << "theta min " << thetamin << endl;
            break;
        case 1:
            for (int i=-10; i<=10; i+=1) {
                for (int j=-10; j<=10; j+=1) {
                    for (float theta=0; theta<=2*M_PI; theta+=0.1) {
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
            cout << "valeur max "<< max << endl;
            cout << "position max i: "<< pmaxi << " j: " << pmaxj << " theta: " << thetamax << endl;
            cout << "theta max " << thetamax << endl;
            break;
    }
}



// -------------------- coordinate descent algorithm --------------------


void coord_descent(img i1, img i2, float pi, float pj, float al, std::vector<float>* list_al, float* p_res, int cpt){
// coordinate descent algorithm recusrive function
// used for draw convergence of the algorithm
    float p[2] = {pi, pj};
    int n = i1.get_rows();
    int m = i1.get_cols();
    float c = loss_function_opt(i1, i2, p[1], p[0]);
    list_al->push_back(al);
    if (cpt < 5000 && al>1e-10){
        if (loss_function_opt(i1, i2, p[1]*(1+al), p[0]*(1+al)) > c){
            coord_descent(i1, i2, p[0]*(1+al), p[1]*(1+al), al*1.1, list_al, p_res, cpt+1);
        }
        else if(loss_function_opt(i1, i2, p[1]*(1-al), p[0]*(1-al)) > c){
            coord_descent(i1, i2, p[0]*(1-al), p[1]*(1-al), al*1.1, list_al, p_res, cpt+1);
        }
        else{
            coord_descent(i1, i2, p[0], p[1], al*0.9, list_al, p_res, cpt+1);
        }
    }
    else{
        p_res[0] = p[0];
        p_res[1] = p[1];
    } 
}


void coord_descent_2(img i1, img i2, float pi, float pj, float al, float *p_res, int cpt){
// coordinate descent algorithm recusrive function
// used for result convergence of the algorithm
    float p[2] = {pi, pj};
    int n = i1.get_rows();
    int m = i1.get_cols();
    float c = loss_function_opt(i1, i2, p[1], p[0]);
    if (cpt < 5000 && al>1e-10){
        if (loss_function_opt(i1, i2, p[1]*(1+al), p[0]*(1+al)) > c){
            coord_descent_2(i1, i2, p[0]*(1+al), p[1]*(1+al), al*1.1, p_res, cpt+1);
        }
        else if(loss_function_opt(i1, i2, p[1]*(1-al), p[0]*(1-al)) > c){
            coord_descent_2(i1, i2, p[0]*(1-al), p[1]*(1-al), al*1.1, p_res, cpt+1);
        }
        else{
            coord_descent_2(i1, i2, p[0], p[1], al*0.9, p_res, cpt+1);
        }
    }
    else{
        p_res[0] = p[0];
        p_res[1] = p[1];
    }
}

void draw_convergence(img i1, img i2, float al){
// draw convergence of the algorithm
    int n = i1.get_rows();
    int m = i1.get_cols();
    std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> dis_pi(-n, n);
    std::uniform_int_distribution<int> dis_pj(-m, m);
    float pi = dis_pi(generator);
    float pj = dis_pj(generator);
    // generate random pi and pj uniformely distributed
    float p[2] = {pi, pj};
    int cpt = 0;
    std::vector<float> *list_al = new std::vector<float>;
    float p_res[2];
    coord_descent(i1, i2, pi, pj, al, list_al, p_res, cpt);
    cout << "final result coord descent : pi " << p_res[0] << ", pj  " << p_res[1] << endl;
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
    int n = i1.get_rows();
    int m = i1.get_cols();
    std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> dis_pi(-n, n);
    std::uniform_int_distribution<int> dis_pj(-m, m);
    int cpt = 0;
    // list of results
    std::vector<float*> *list_p = new std::vector<float*>;
    for (int i=0; i<100; i++){
        float pi = dis_pi(generator);
        float pj = dis_pj(generator);
        // generate random pi and pj uniformely distributed
        float p[2] = {pi, pj};
        float p_res[2];
        coord_descent_2(i1, i2, pi, pj, al, p_res, cpt);
        list_p->push_back(p_res);
        cout << "final result coord descent : pi " << p_res[0] << ", pj  " << p_res[1] << endl;
    }
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
    cout << "p le debut " << p[0] << " "<<p[1] <<endl;
    int cpt = 0;
    double k = 0.5; // variation rate/2
    for (int i=0; i<1000; i++){
        if (abs(eps)>50){
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
            cout << "cpt " << cpt << endl;
            return;
        }
    }
    if (eps>0){
        p_res[1] = p[1] - k;
    }
    else{
        p_res[1] = p[1] + k;
    }
    cout << "cpt " << cpt << endl;
}

void grad_descent_2_y(img i1, img i2, double pi, double pj, double al, double *p_res){
    // initials values
    double p[2] = {pi, pj};
    int n = i1.get_rows();
    int m = i1.get_cols();
    double eps = 1000;
    // the algorithm
    cout << "p le debut " << p[0] << " "<<p[1] <<endl;
    int cpt = 0;
    double k = 0.5; // variation rate/2
    for (int i=0; i<1000; i++){
        if (abs(eps)>50){
            eps = loss_function_pderivative_y(i1, i2, p[1], p[0]);
            p[0] = p[0] -al*eps;
            cpt+=1;
        }       
        else{
            if (eps>0){
                p_res[0] = p[0] - k;

            }
            else{
                p_res[0] = p[0] + k;
            }
            cout << "cpt " << cpt << endl;
            return;
        }
    }
    if (eps>0){
        p_res[0] = p[0] - k;
    }
    else{
        p_res[0] = p[0] + k;
    }
    cout << "cpt " << cpt << endl;
}


void grad_descent_2(img i1, img i2, double pi, double pj, double al, double *p_res){
    // initials values
    double p[2] = {pi, pj};
    int n = i1.get_rows();
    int m = i1.get_cols();
    double eps = 1000;
    double eps2 = 1000;
    // the algorithm
    cout << "p le debut " << p[0] << " "<<p[1] <<endl;
    int cpt = 0;
    double k = 0.5; // variation rate/2
    for (int i=0; i<10000; i++){
        if (abs(eps)>3 || abs(eps2)>3){
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
            cout << "cpt " << cpt << endl;
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
    cout << "cpt " << cpt << endl;
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
    cout << "final result grad descent : pi " << p_res[0] << ", pj  " << p_res[1] << endl;
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
    std::uniform_int_distribution<int> dis_pi(-20, 20);
    std::uniform_int_distribution<int> dis_pj(-20, 20);
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
        cout << "final result grad descent : pi " << p_res[0] << ", pj  " << p_res[1] << endl;
    }
    delete list_p;
}