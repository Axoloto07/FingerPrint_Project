#include "../include/kernel.hpp"


//#######################################################################
//CREATION OF CONVOLUTION KERNELS
//#######################################################################


Mat kernel_gaussian(float sigma_i, float sigma_j, int size_i, int size_j){
    //size of the kernel is odd
    //create a gaussian blur kernel
    //blurred effect higher in i-direction than in j-direction
    Mat kernel_gauss = Mat::zeros(size_i,size_j,CV_32F);
    int ker_center_i = size_i/2;
    int ker_center_j = size_j/2;
    float sum = 0;
    for (int i = 0; i<size_i; i++){
        for (int j = 0; j<size_j; j++){
            //coefficient values follow a gaussian distribution
            kernel_gauss.at<float>(i, j) = exp(-0.5*pow((float)(i-ker_center_i)/sigma_i, 2));
            kernel_gauss.at<float>(i, j) *= exp(-0.5*pow((float)(j-ker_center_j)/sigma_j, 2));
            sum += kernel_gauss.at<float>(i, j); 
        }
    }
    //normalize the kernel to preserve its energy
    normalize_mat(kernel_gauss, sum);
    return kernel_gauss;
}


Mat kernel_blurred(int size_i, int size_j){
//create a kernel of size size_i*size_j that blurs uniformly the image

    Mat kernel_blurred = Mat::zeros(size_i,size_j,CV_32F);
    for (int i = 0; i<size_i; i++){
        for (int j =0; j<size_j; j++){
            kernel_blurred.at<float>(i, j) = 1.0/(size_i*size_j);
        }
    }
    return kernel_blurred;

}

Mat kernel_sharpen (int size_i, int size_j, float value){
//create a kernel of size size_i*size_j that sharpens the image

    Mat kernel_sharpen = Mat::zeros(size_i,size_j,CV_32F);
    //the center coeff is equal to the sum of the other coeff
    kernel_sharpen.at<float>(size_i/2, size_j/2) = (size_i/2 * 2+size_j/2 * 2) * value + 1;
    //the chosen value is stored along a cross in the kernel
    for (int i = 0; i<size_i; i++){
        if(i!=size_i/2){
            kernel_sharpen.at<float>(i, size_j/2) = -value;
        }
    }
    for (int j = 0; j<size_j; j++){
        if(j!=size_j/2){
            kernel_sharpen.at<float>(size_i/2,j) = -value;
        }
    }
    return kernel_sharpen;
}

Mat kernel_id_light_dark(int size_i, int size_j, float value){
    // /!\ lighten : value > 1 , darken : value < 1 , identity : value = 1
    Mat kernel_lighten = Mat::zeros(size_i,size_j,CV_32F);
    //the only non null coeff is located at the middle of the kernel
    kernel_lighten.at<float>(size_i/2, size_j/2) = value;
    return kernel_lighten;
}

Mat kernel_pull(int size_i, int size_j, int n, int m, vector<int> center){
    //create a motion blur kernel of size size_i*size_j
    //with only one non null column
    //the coefficents can depend on the position of the pixels in the input image
    float sum = 0;
    //compute the distance of the pixels from the center of the finger
    float d_carre = pow(n-center[0],2)+pow(m-center[1],2);

    Mat kernel_pull = Mat::zeros(size_i,size_j,CV_32F);
    for (int i = 0; i<size_i; i++){
        kernel_pull.at<float>(i, size_j/2) = size_i - i;
        //kernel_pull.at<float>(i, size_j/2) = 1;

        //kernel_pull.at<float>(i, size_j/2) = 1;
        //kernel_pull.at<float>(i, size_j/2) = d_carre;
        sum += kernel_pull.at<float>(i, size_j/2);

    }
    //the energy of the kernel is preserved
    normalize_mat(kernel_pull, sum);
    return kernel_pull;

}


//#######################################################################
//NON UNIFORM CONVOLUTION
//#######################################################################


Mat kernel_nunif(int size_i, int size_j, vector<int> center, float a, float b, int n, int m, char normalize){
//create a kernel depending on the position of the pixel, that performs a motion blur
//the kernel tends to the identity kernel for pixels located inside the ellipse of radius a and b
//it contains only one column of non null coefficients located at the middle of the kernel
//the energy of the kernel is either preserved (option 'n'), either slighty increasing
    
    Mat kernel_nunif = Mat::zeros(size_i,size_j,CV_32F);

    //value to adjust the standard deviation of the gaussian coefficients 
    float val_adj_1;
    float val_adj_2;
    if (normalize=='n'){
        val_adj_1 = 0.45;
        val_adj_2 = 0.9;
    }
    else{
        val_adj_1 = 0.65;
        val_adj_2 = 0.7;
    }
   
    float sum = 0;

    for (int i = 0; i<size_i; i++){
            //the coeff at the center is gaussian and tends to 1 when the pixel is inside the ellipse
            if(i==size_i/2){
                kernel_nunif.at<float>(i, size_j/2) = exp(-pow((float)val_adj_1*(n-center[0])/a, 2)) * exp(-pow((float)val_adj_1*(m-center[1])/b, 2)) * exp(pow(val_adj_1, 2));
            
            }
            //other coefficients tend to 0 when the pixel is inside the ellipse
            else{
                kernel_nunif.at<float>(i, size_j/2) =1 - exp(-pow((float)val_adj_2*(n-center[0])/a, 2)) * exp(-pow((float)val_adj_2*(m-center[1])/b, 2)) * exp(pow(val_adj_2,2));
            }
            sum+=kernel_nunif.at<float>(i, size_j/2);
            
    }
    float norm;
    //in this case, the energy of the kernel is equal to 1
    if(normalize=='n'){
        norm = sum /(1- kernel_nunif.at<float>(size_i/2, size_j/2));
    }
    //in this case the energy of the kernel is slighty increasing (between 1 and 2)
    else{
        norm = sum;
    }
    for (int i = 0; i<size_i; i++){
        if (i != size_i/2){
            kernel_nunif.at<float>(i, size_j/2) /= norm;
        }
    }
    
    return kernel_nunif;

}

Mat kernel_bottom(int size_i, int size_j, float r, int m1_rows, int m1_cols, int n , int m){
//create a kernel depending on the position of the pixel, that performs a box blur
//the kernel tends to the identity kernel for pixels located inside the circle of radius r
    
    Mat kernel_bottom = Mat::zeros(size_i,size_j,CV_32F);

    //values to adjust the standard deviations of the gaussian distribution
    float val_adj_1 = 0.9;
    float val_adj_2 = 0.9;
   
    float sum = 0;

    for (int i = 0; i<size_i; i++){
        for (int j = 0; j<size_j; j++){
            //the coeff at the center is gaussian and tends to 1 when the pixel is inside the circle
            if(i==size_i/2 && j==size_j/2){
                kernel_bottom.at<float>(i, j) = exp(-pow((float)val_adj_1*(n-m1_rows/2) / r , 2)) * exp(-pow((float)val_adj_1*(m-m1_cols/2)/r, 2)) * exp(pow(val_adj_1, 2));
            
            }
            //other coefficients tend to 0 when the pixel is inside the circle
            else{
                kernel_bottom.at<float>(i, j) = 1 - exp(-pow((float)val_adj_2*(n-m1_rows/2) / r , 2)) * exp(-pow((float)val_adj_2*(m-m1_cols/2)/r, 2)) * exp(pow(val_adj_2, 2));
            }
            sum+=kernel_bottom.at<float>(i, j);
        }
            
    }

    //to have the energy of the kernel equal to and 1
    normalize_mat(kernel_bottom, sum);

    return kernel_bottom;
}


Mat kernel_energy(vector<int> center, int n, int m, int size_i, int size_j,int m1_rows, int m1_cols){
    //create a kernel depending on the position of the pixel in the image
    //it tends to the identity kernel when the pixel gets closer to the center of the finger
    //the energy of the kernel decreases quadratically when the pixel gets far from the center

    // compute the distance of the pixel from the center of high pressure of the finger
    float d_carre = pow(n-center[0],2)+pow(m-center[1],2);

    //value to adjust the coefficients
    float val_adj = 0.45/m1_rows;

    //create a sharpen kernel whose energy will depend on the position of the pixel
    Mat kernel_energy = kernel_sharpen(size_i, size_j, 1.0/5);
    float sum = 0;
    for (int i = 0; i<size_i; i++){
        for (int j = 0; j<size_j; j++){
            sum += kernel_energy.at<float>(i, j);
        }
    }
    //normalize the kernel sucht that its energy decreases when the distance
    //of the pixel from the center increases
    normalize_mat(kernel_energy, (1+val_adj * sqrt(d_carre)) * sum);
    return kernel_energy;

}

//#######################################################################
//TOOLS
//#######################################################################


void negative_img(Mat m1){
    //compute the negative version of the image
    for (int j = 0; j<m1.cols; j++){
        for (int i = 0; i<m1.rows; i++){
            m1.at<float>(i,j) = 255-m1.at<float>(i,j);
        }
    }
}

void normalize_mat(Mat m1, float sum){
    //divide every coefficient of the kernel by a given value
    //it is used to preserve the energy of the kernel
    for (int i = 0; i<m1.rows; i++){
        for (int j = 0; j<m1.cols; j++){
            
            m1.at<float>(i, j) /= sum; 
        }
    }
}