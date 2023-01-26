#include "../include/convolution.hpp"


//#######################################################################
//CHECK CONVOLUTION
//#######################################################################


Mat conv_using_fft(Mat &m1, Mat &kernel){
    //COST : N*M*Ln(NM)
    //perform the convolution using the fft

    //pad the image with zeros to the right and the bottom
    Mat m1_padded = Mat::zeros(m1.rows+kernel.rows-1, m1.cols+kernel.cols-1, m1.type());
    for (int i = 0; i<m1.rows; i++){
        for (int j =0; j<m1.cols; j++){
            m1_padded.at<float>(i, j) = m1.at<float>(i, j);
        }
    }
    //Mat m1_padded = padd_bottom_left(kernel, m1);

    //pad the kernel with zeros and perform circular symmetry on its coefficients
    //flip_kernel(kernel);
    Mat kernel_padded = kernel_swap_fft(m1_padded, kernel);
    // Mat kernel_padded = Mat::zeros(m1.rows+kernel.rows-1, m1.cols+kernel.cols-1, m1.type());
    // for (int i = 0; i<kernel.rows; i++){
    //     for (int j =0; j<kernel.cols; j++){
    //         kernel_padded.at<float>(i, j) = kernel.at<float>(i, j);
    //     }
    // }
    //Mat kernel_padded = padd_bottom_left(m1, kernel);
    //perform the dft of the padded image
    dft(m1_padded, m1_padded);

    //perform the dft of the padded kernel
    dft(kernel_padded, kernel_padded);

    //perform the Hadamart product between the dft of the image and of the kernel
    Mat product;
    mulSpectrums(m1_padded, kernel_padded, product,0, false);

    //apply the inverse dft of this product
    Mat result;
    idft(product, result);

    //normalize the result
    Mat norm_result = Mat(result.rows, result.cols, result.type(), 1.0/(result.rows*result.cols));
    Mat final_norm = result.mul(norm_result);

    //put away the initial zero padding
    //the image we want is stored at the top left of the output image
    Mat final = Mat::zeros(m1.rows,m1.cols,m1.type());
    for (int i = 0; i<m1.rows; i++){
        for (int j =0; j<m1.cols; j++){
            final.at<float>(i, j) = final_norm.at<float>(i,j);
        }
    }
    return final;
}


Mat conv_using_filter(Mat &m1, Mat &kernel, char border){
//test the 2d discrete convolution with an already implemented function in opencv
//borders are extended with replicated pixel values or with zero values
    flip_kernel(kernel);
    Mat result;
    //we use the option to replicate the pixels at the borders of the image
    if (border=='r') {
        filter2D(m1, result, -1, kernel, Point(-1, -1), 0, BORDER_REPLICATE);
    }
    //by default we zero pad the image
    else{
        filter2D(m1, result, -1, kernel, Point(-1, -1), 0, BORDER_CONSTANT);
    }
    return result;
}

//#######################################################################
//HOME MADE CONVOLUTION
//#######################################################################


Mat discrete_conv(Mat &m1, Mat &kernel, char border){
//COST : N*N*M*M
//perform the 2d discrete convolution
    //we suppose the filter is of odd dimension
    Mat tmp = Mat::zeros(m1.rows + kernel.rows-1, m1.cols+ kernel.cols -1, m1.type());

    if (border == 'r'){
    //we pad the matrix m1 with REPLICATED borders to adapt to the filter
    //the initial matrix is placed at the center of the new matrix
        copyMakeBorder(m1,tmp,kernel.rows/2,kernel.rows/2, kernel.cols/2,kernel.cols/2, BORDER_REPLICATE);
    }

    else{
        //we pad the matrix m1 with ZEROS to adapt to the filter's size
        tmp = padd_center(m1, kernel.rows, kernel.cols);
    }

    //we flip the kernel
    flip_kernel(kernel);
    
    //the output matrix has the same size as the input matrix m1
    Mat result = Mat::zeros(m1.rows, m1.cols, m1.type());

    //COUT : n^2
    //we go through the matrix's coeff to compute each coeff of the output matrix
    for (int n=0; n<m1.rows ; n++){
        for (int m=0; m<m1.cols; m++){
            //we extract a sub-matrix from the matrix m1 with the same dimension of the kernel
            Rect r(m,n, kernel.cols, kernel.rows);
            //COUT : 1 sinon n^2 car kernel petit
            Mat inter = tmp(r).clone();

           

            //we compute the coefficient at position (n, m) by multiplying
            //coef by coef the kernel and the extracted submatrix
            //COUT : 1 car on suppose que le filtre est de petite taille
            result.at<float>(n,m) = convol_coeff(inter,kernel);
        }
    }
    return result;

}

float convol_coeff(Mat &m1, Mat &kernel_flip){
    //compute the product coeff by coeff between the flipped kernel and the matrix m1
    //return one coefficient
    //we suppose m1 and the kernel with same ODD dimensions
    float k = 0;
    for (int i=0; i<m1.rows; i++){
            for (int j=0; j<m1.cols; j++){
                k += m1.at<float>(i, j)* kernel_flip.at<float>(i,j);
            }
        }
    return k;

}

Mat conv_x_y(Mat &m1, int kernel_i, int kernel_j, vector<int> center, float a, float b, char position, char normalize){
    //we suppose the filter is of odd dimensions

    //we add zeros to the matrix m1 to adapt to the filter
    Mat tmp = padd_center(m1, kernel_i, kernel_j);

    Mat result = Mat::zeros(m1.rows, m1.cols, m1.type());
    Mat kernel;
    //COUT : n^2
    for (int n=0; n<m1.rows; n++){
        for (int m=0; m<m1.cols; m++){
            //we extract a sub-matrix from the matrix m1 with the same dimension of the kernel
            Rect r(m, n, kernel_j, kernel_i);
            //COUT : 1 sinon n^2 car kernel petit
            Mat inter = tmp(r).clone();

            //define a kernel for each coefficient of the input matrix depending on its position
            if (pow((float)(n-center[0])/a, 2) + pow((float) (m-center[1])/b, 2) <=1){
                //if the pixel (n,m) is located inside the ellipse, it is applied the identity kernel
                kernel =kernel_id_light_dark(kernel_i, kernel_j, 1);

            }
            else{
                //if the pixel (n,m) is outside the ellipse, it is applied a kernel tending to the identity one
                //in this case, the blurring effect is on the bottom of the image
                if (position=='b'){
                    kernel = kernel_bottom(kernel_i, kernel_j, a, m1.rows, m1.cols, n, m);

                }
                //in this case it is on the top of the image
                else{
                    kernel = kernel_nunif(kernel_i, kernel_j, center, a, b, n, m, normalize);
                }
            }

            //we flip the kernel
            flip_kernel(kernel);

            //we compute the coefficient at position (n, m)
            //it is the Hadamart product between the kernel and the extracted submatrix
            //COUT : 1 car on suppose que le filtre est de petite taille
            result.at<float>(n,m) = convol_coeff(inter,kernel);
        }
    }
    return result;
}

Mat convol_energy(Mat &m1, int kernel_i, int kernel_j, vector<int> center){
    //we suppose the filter is of odd dimensions

    //we add zeros to the matrix m1 to adapt to the filter
    Mat tmp = padd_center(m1, kernel_i, kernel_j);

    //we take the negative version of the image to have a decreasing kernel
    negative_img(tmp);
    Mat result = Mat::zeros(m1.rows, m1.cols, m1.type());
    Mat kernel;
    //COUT : n^2
    for (int n=0; n<m1.rows; n++){
        for (int m=0; m<m1.cols; m++){
            //we extract a sub-matrix from the matrix m1 with the same dimension of the kernel
            Rect r(m, n, kernel_j, kernel_i);
            //COUT : 1 sinon n^2 car kernel petit
            Mat inter = tmp(r).clone();

            kernel = kernel_energy(center, n, m, kernel_i, kernel_j, m1.rows, m1.cols);

            //flip the kernel
            flip_kernel(kernel);
            //compute the Hadamart product between the flipped kernel and the extracted submatrix
            result.at<float>(n,m) = convol_coeff(inter,kernel);
        }
    }
    //we go back to the normal version of the image
    negative_img(result);
    return result;
}

//#######################################################################
//PADDINGS
//#######################################################################


Mat padd_center(Mat &m1, int kernel_i, int kernel_j){
    //we add zeros to the matrix m1 to adapt to the filter
    Mat tmp = Mat::zeros(m1.rows + kernel_i-1, m1.cols+ kernel_j-1, m1.type());
    //we put m1 at the center of the matrix tmp
    //COUT : n^2
    for (int i=(kernel_i-1)/2; i<(kernel_i-1)/2 + m1.rows; i++){
        for (int j=(kernel_j -1)/2; j<(kernel_j -1)/2 + m1.cols; j++){
            tmp.at<float>(i,j) = m1.at<float>(i-(kernel_i-1)/2,j-(kernel_j -1)/2);
        }
    }
    return tmp;
}

//#######################################################################
//KERNEL FLIPS
//#######################################################################


void flip_kernel(Mat &kernel){
    //assume that the kernel dimensions are odd
    //flip the kernel in both directions i and j

    //switch columns of the kernel
    for (int j=0; j<(kernel.cols-1)/2; j++){
        for (int i=0; i<kernel.rows; i++){
            float tmp = kernel.at<float>(i,j);
            kernel.at<float>(i, j) = kernel.at<float>(i, kernel.cols-1-j);
            kernel.at<float>(i, kernel.cols-1-j) = tmp;
        }
    }
    //switch rows of the kernel
    for (int i=0; i<(kernel.rows-1)/2; i++){
        for (int j=0; j<kernel.cols; j++){
            float tmp = kernel.at<float>(i,j);
            kernel.at<float>(i, j) = kernel.at<float>(kernel.rows-1-i, j);
            kernel.at<float>(kernel.rows-1-i,j) = tmp;
        }
    }
}

Mat kernel_swap_fft(Mat &m1, Mat &kernel){
    //pad the kernel with zeros and perform a circular symmetry on its coefficients
    //assume that the kernel's dimensions are odd

    //define the middle of the kernel
    int middle_i = kernel.rows/2;
    int middle_j = kernel.cols/2;

    Mat kernel_padded = Mat::zeros(m1.rows,m1.cols,m1.type());
    //perform a circular symmetry on the kernel's coeff

    //bottom right part of the kernel is stored at the top left of the padded kernel
    //such that the middle of the kernel is now at position (0,0)
    for (int i = middle_i; i<kernel.rows; i++){
        for (int j = middle_j; j<kernel.cols; j++){

            kernel_padded.at<float>(i-middle_i, j-middle_j) = kernel.at<float>(i, j);
        }
    }

    //the top left part of the kernel is stored at the bottom right of the padded kernel
    for (int i = 0; i<middle_i; i++){
        for (int j = 0; j<middle_j; j++){
            kernel_padded.at<float>(i+m1.rows-middle_i, j+m1.cols-middle_j) = kernel.at<float>(i, j);
        }
    }

    //the bottom left part of the kernel is stored at the top right of the padded kernel
    for (int i = middle_i; i<kernel.rows; i++){
        for (int j = 0; j<middle_j; j++){
            kernel_padded.at<float>(i-middle_i, j+m1.cols-middle_j) = kernel.at<float>(i, j);
        }
    }

    //the top right part of the kernel is stored at the bottom left of the padded kernel
    for (int i = 0; i<middle_i; i++){
        for (int j = middle_j; j<kernel.cols; j++){
            kernel_padded.at<float>(i+m1.rows-middle_i, j-middle_j) = kernel.at<float>(i, j);
        }
    }

    return kernel_padded;
}