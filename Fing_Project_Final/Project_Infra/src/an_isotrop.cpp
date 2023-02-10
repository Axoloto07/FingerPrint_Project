#include <cmath>
#include <iostream>
#include "../include/an_isotrop.hpp"

//#######################################################################
//ISOTROPIC TRANSFORMATIONS
//#######################################################################


float coef1(int x, int y, int p, int ci, int cj, Mat matrix){
// compute the coefficient of the gaussian filter

    float r = sqrt(pow(x-ci,2)+pow(y-cj,2)); //distance between the center of the finger and the current pixel
    // compute the distance between the center of the finger and the further corner of the image
    float d = std::max(sqrt(pow(matrix.rows-ci, 2) +  pow(matrix.cols-cj, 2)), sqrt(pow(ci, 2) +  pow(cj, 2)));
    float res = exp(-p*pow(r/d,2));
    //cout <<res<<endl;
    return res;
}

float coef2(int x, int y, int p, int ci, int cj, Mat matrix){
// compute the coefficient of the gaussian with plateau filter
    float s = 0.8; //standard deviation
    float r = sqrt(pow(x-ci,2)+pow(y-cj,2)); //distance between the center of the finger and the current pixel
    // compute the distance between the center of the finger and the further corner of the image
    float d = std::max(sqrt(pow(matrix.rows-ci, 2) +  pow(matrix.cols-cj, 2)), sqrt(pow(ci, 2) +  pow(cj, 2)));
    double res = p*exp(-pow(r/(d*s),p))/(2*s*tgamma((float)1/p));
    //cout <<res <<endl;
    return (float) res;
}

img isotrop_transf(int p, img input){
// compute the coefficient image
    Mat matrix = input.get_matrix();
    img res = img(Mat(matrix.rows, matrix.cols, matrix.type()));
    int ci = input.coord_center()[0];
    int cj = input.coord_center()[1];
    for (int i = 0; i<matrix.rows; i++){
        for (int j = 0; j<matrix.cols; j++){
            res.modif_pix(i, j, 255-((255-input.get_pix_val(i, j))*coef1(i, j, p, ci, cj, matrix)));
        }
    }
    return res;
}


//#######################################################################
//ANISOTROPIC TRANSFORMATIONS
//#######################################################################


float c_i_j(int i, int j, int a, int b, std::vector<int> center, Mat matrix){
    //compute the coeff to apply to the pixel (i,j) in the input image

    //apply a first few decreasing gaussian transform in the i-axis
    float transf_1_i = exp(-(float)pow(i-center[0],2)/(100*matrix.rows)); 
    //apply a first more decreasing gaussian transform in the j-axis
    float transf_1_j = exp(-(float)pow(j-center[1],2)/(80*matrix.cols));
    //apply a second gaussian transform in both direcions on pixels outside the first ellipse
    float transf_2_i = exp(-(float)pow(i-center[0],2)/pow(a, 2));
    float transf_2_j = exp(-(float)pow(j-center[1],2)/pow(b, 2));
    //apply a last gaussian transform in both direcions on pixels outside the second ellipse
    float transf_3_i = exp(-(float)pow(i-center[0],2)/pow(a+10, 2));
    float transf_3_j = exp(-(float)pow(j-center[1],2)/pow(b+10, 2));

    //for pixels in the first ellipse
    if (pow((float)(i-center[0])/a, 2) + pow((float) (j-center[1])/b, 2) <=1){
        //apply a gaussian transform to a pixel in direction i and j
        return transf_1_i * transf_1_j * 1 * 1;
    }
    //for pixels between the 2 ellipses
    else if ((pow((float)(i-center[0])/a, 2) + pow((float) (j-center[1])/b, 2) > 1) && (pow((float)(i-center[0])/(a+10), 2) + pow((float) (j-center[1])/(b+10), 2) <=1)){
        //make the previous transform continuous on the boundary of the first ellipse
        return transf_1_i * transf_1_j * transf_2_i * transf_2_j * exp(1) * 1;
    }
    //for pixels outside both ellipses
    else{
        //make the previous transform continuous on the boundary of the second ellipse
        return transf_1_i * transf_1_j * transf_2_i * transf_2_j * exp(1) * transf_3_i * transf_3_j * exp(1);
    }

}

img anisotrop_transf(float alpha, img input){
    //perform an anisotropic transform on the whole finger in a given direction
    //alpha is the angle between the x-axis and the direction of the pressure that the user enters
    Mat matrix = input.get_matrix();
    img res = img(Mat(matrix.rows, matrix.cols, matrix.type())); 
    std::vector<int> center;
    //if the image is rotated (we consider it is warp1_finger)
    //compute the center of pressure of the image
    if (alpha !=0){
        center = {(int)(3.0/4*matrix.rows),(int)(0.7*matrix.cols)};
        // img fingerprint("../Project_Infra/images/clean_finger.png");
        // center = fingerprint.coord_center();


    }
    else{
        center = input.coord_center();

    }
    //compute the new center after a rotation of angle alpha
    std::vector<int> center_rot = {(int)(-sin(alpha) * center[1] + cos(alpha) * center[0]),(int)(cos(alpha) * center[1] + sin(alpha) * center[0])};
    //axis lenght of the ellipse
    int a = 7*matrix.rows/16;
    int b = 1*matrix.cols/4;
    //declaration of the new coord of each coeff after rotation
    float i_p, j_p;

    for (int i = 0; i<matrix.rows; i++){
        for (int j = 0; j<matrix.cols; j++){
            //application of the anisotrop gaussian transform on the whole image
            i_p = -sin(alpha) * j + cos(alpha) * i;
            j_p = cos(alpha) * j + sin(alpha) * i;
            res.modif_pix(i, j, 255-(255-input.get_pix_val(i, j))*c_i_j(i_p,j_p,a, b, center_rot, matrix));
        }
    }
    return res;

}
