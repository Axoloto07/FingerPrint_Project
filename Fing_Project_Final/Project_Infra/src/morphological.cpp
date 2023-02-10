#include "../include/morphological.hpp"


//#######################################################################
//BINARIZATION OF IMAGES
//#######################################################################

std::vector<float> proba_distr(Mat &input){
    //compute the occurence of each pixel intensity (from 0 to 255)
    int size = input.rows*input.cols;
    //for each level of gray store the nb of pixels with this intensity
    std::vector<float> frequency(256);
    for (int i=0; i<input.rows; i++){
        for (int j=0; j<input.cols; j++){
            frequency[input.at<float>(i,j)]+=(1.0/size);
        }
    }
    return frequency;
}

float between_class_variance(int level, std::vector<float> &frequency){
    //the pixels will be separated in two classes given an intensity threshold 'level'
    //this function computes the between-class variance
    float omega_0 = 0;
    float mu_0 = 0;
    
    for (int i=0; i<=level;i++){
        //compute the probability of class occurence for the first class
        omega_0 += frequency[i];
        //compute the mean of the first class
        mu_0 += i*frequency[i];
    }
    mu_0 /= omega_0;
    //compute the probability of class occurence for the second class
    float omega_1 = 1-omega_0;
    //compute the total mean
    float mu_tot = mu_0;
    for (int i=level+1; i<frequency.size();i++){
            mu_tot += i*frequency[i];
    }
    //compute the mean of the second class
    float mu_1 = (mu_tot-mu_0)/omega_1;
    //compute the between-class variance
    float sigma_b_square = omega_0*omega_1*pow(mu_1-mu_0,2);
    return sigma_b_square;
}

float find_threshold(std::vector<float> &frequency){
    //compute the optimal intensity threshold used to separate pixels in 2 classes
    float threshold = 0;
   
    for (int level=1; level<256; level++){
        //for each pixel intensity used as threshold, compute the between-class variance
        //look for the maximal between-class variance
        if(between_class_variance(level,frequency)>between_class_variance(threshold,frequency)){
            threshold = level;
        }
    }
    return threshold;
}

Mat binarization(Mat &input, int threshold){
    //commpute the binarized version of an input image given an intensity threshold
    Mat binarized= Mat::zeros(input.rows,input.cols,input.type());
    for (int i=0; i<input.rows; i++){
        for (int j=0; j<input.cols; j++){
            //when pixel intensity is lower than the threshold, the pixel is turned black
            if(input.at<float>(i,j)<threshold){
                binarized.at<float>(i,j)=1;
            }
            //otherwise it is turned white
            else{
                binarized.at<float>(i,j)=0;
            }
        }
    }
    return binarized;
}

void convert_negative(Mat &input){
    //compute the negative version of an image
    //used for binary erosion/dilation filterings
    for (int n=0; n<input.rows ; n++){
        for (int m=0; m<input.cols; m++){
           
            input.at<float>(n,m) = 255*(1-input.at<float>(n,m));
        }
    }
}

//#######################################################################
//EROSION & DILATION FILTERINGS
//#######################################################################

float erosion_coeff(Mat &elt_struct, Mat &input){
    //compute the erosion coefficient for the center pixel of a binary image
    //here we suppose that the struct element and the image totally overlap (have the same sizes)
    float coeff = 0;
    float nb_one = 0;
    for (int i=0; i<elt_struct.rows; i++){
        for (int j=0; j<elt_struct.cols; j++){
            //if the black pixels of the kernel are totally included in the black pixels of the image
            //the pixel of the image takes value 1 (stay black)
            nb_one += elt_struct.at<float>(i,j);
            coeff += elt_struct.at<float>(i,j) * input.at<float>(i, j);
        }
    }
    return coeff == nb_one?1:0;
}

float dilatation_coeff(Mat &elt_struct, Mat &input){
    //compute the dilation coefficient for the center pixel of a binary image
    //here we suppose that the struct element and the image totally overlap (have the same sizes)
    float coeff = 0;
    for (int i=0; i<elt_struct.rows; i++){
        for (int j=0; j<elt_struct.cols; j++){
            //if at least one black pixel of the kernel overlap one black pixel of the image
            //the pixel of the image takes value 1 (stay black)
            coeff += elt_struct.at<float>(i,j) * input.at<float>(i, j);
        }
    }
    return coeff != 0?1:0;
}

float erosion_coeff_grayscale(Mat &elt_struct, Mat &input){
    //compute the dilation coefficient for the center pixel of a grayscale image
    //here we suppose that the struct element and the image totally overlap (have the same sizes)
    float max = 0;
    for (int i=0; i<elt_struct.rows; i++){
        for (int j=0; j<elt_struct.cols; j++){
            //the new value of the pixel of the image is equal to the maximal intensity among 
            //the black pixels of the image overlapped by the black pixels of the kernel
            if (elt_struct.at<float>(i,j) == 1 && input.at<float>(i,j) > max){
                max = input.at<float>(i,j);
            }
        }
    }
    return max;
}

float dilatation_coeff_grayscale(Mat &elt_struct, Mat &input){
    //compute the dilation coefficient for the center pixel of a grayscale image
    //here we suppose that the struct element and the image totally overlap (have the same sizes)
    float min = 255;
    for (int i=0; i<elt_struct.rows; i++){
        for (int j=0; j<elt_struct.cols; j++){
            //the new value of the pixel of the image is equal to the minimal intensity among 
            //the black pixels of the image overlapped by the black pixels of the kernel
            if (elt_struct.at<float>(i,j) == 1 && input.at<float>(i,j) < min){
                min = input.at<float>(i,j);
            }
        }
    }
    return min;
}

Mat erosion_dilatation(Mat &elt_struct, Mat &bin, std::string filter_type){
    //compute the eroded/dilated version of a binary or grayscale input image given a structuring element

    //pad the input image, so that the filter works also for pixels at the borders
    Mat padded = Mat::zeros(bin.rows+elt_struct.rows-1 , bin.cols+elt_struct.cols-1 , bin.type());
    float value_pad;
    //the value used to pad depends on the filtering
    //if it is dilation for grayscale image we pad with white
    //otherwise we pad with zeros
    value_pad = (filter_type== "dil_gray")?255:0;
    copyMakeBorder(bin,padded,elt_struct.rows/2,elt_struct.rows/2,elt_struct.cols/2,elt_struct.cols/2,BORDER_CONSTANT,value_pad);

    Mat result = Mat::zeros(bin.rows, bin.cols, bin.type());
    for (int n=0; n<bin.rows ; n++){
        for (int m=0; m<bin.cols; m++){
            //we extract a sub-matrix from the matrix of the input image with the same dimensions as the kernel
            Rect r(m,n, elt_struct.cols, elt_struct.rows);
            Mat inter = padded(r).clone();
            //we compute the new coefficient at position (n, m) by calling the suitable function
            //now that the submatrix and the kernel have same dimensions
            //erosion for binary image
            if(filter_type == "ero_bin"){
                result.at<float>(n,m) = erosion_coeff(elt_struct,inter);
           }
           //dilation for binary image
            else if (filter_type == "dil_bin"){
                result.at<float>(n,m) = dilatation_coeff(elt_struct,inter);
           }
           //erosion for grayscale image
            else if(filter_type== "ero_gray"){
                result.at<float>(n,m) = erosion_coeff_grayscale(elt_struct,inter);
           }
           //dilation for grayscale image
            else{
                result.at<float>(n,m) = dilatation_coeff_grayscale(elt_struct,inter);
            }
        }
    }
    return result;
}


//#######################################################################
//NON UNIFORM FILTERINGS
//#######################################################################


Mat dilation_nunif(int elt_struct_i, int elt_struct_j, float a, float b, float radius, std::vector<int> &center, Mat &bin, std::string bin_gray){
    //compute the dilated version of a grayscale input image
    //the filtering is not uniform (the kernel changes depending on the position of the pixel)

    //pad the input image with white pixels, so that the filter works also for pixels at the borders
    Mat padded = Mat::zeros(bin.rows+elt_struct_i-1 , bin.cols+elt_struct_j-1 , bin.type());
    copyMakeBorder(bin,padded,elt_struct_i/2,elt_struct_i/2,elt_struct_j/2,elt_struct_j/2,BORDER_CONSTANT,255);
 
    Mat result = Mat::zeros(bin.rows, bin.cols, bin.type());
    Mat elt_struct;
    for (int n=0; n<bin.rows ; n++){
        for (int m=0; m<bin.cols; m++){
            //we extract a sub-matrix from the matrix m1 with the same dimension of the kernel
            Rect r(m,n, elt_struct_j, elt_struct_i);
            Mat inter = padded(r).clone();
            //define the kernel to apply
            //if the pixel is located at the very top of the finger
            //it is applied the identity filter
            if (pow(n-center[0], 2) + pow(m-center[1], 2) > pow(radius, 2)){
                elt_struct = elt_struct_id(elt_struct_i, elt_struct_j);
            }
            else {
                //if the pixel is located at the middle of the finger
                //it is applied the cross filter
                if (pow((float)(n-(bin.rows-1))/a, 2) + pow((float) (m)/b, 2) >1 && pow((float)(n-(bin.rows-1))/a, 2) + pow((float) (m-(bin.cols-1))/b, 2) >1){
                    elt_struct = elt_struct_cross_col_row(elt_struct_i, elt_struct_j, "cross");
                }
                //if the pixel is located at the bottom left of the finger
                //it is applied the inverse diagonal filter
                else if (pow((float)(n-(bin.rows-1))/a, 2) + pow((float) (m)/b, 2) <=1){
                    elt_struct = elt_struct_diag(elt_struct_i, elt_struct_j, "diag_inv");
                }
                else{
                    //if the pixel is located at the bottom right of the finger
                    //it is applied the diagonal filter
                    elt_struct = elt_struct_diag(elt_struct_i, elt_struct_j, "diag");
                }
            }
            //for grayscale image : call the suitable function
            if (bin_gray=="gray"){
                result.at<float>(n,m) = dilatation_coeff_grayscale(elt_struct,inter);
            }
            //for binary image : call the suitable function
            else{
                result.at<float>(n,m) = dilatation_coeff(elt_struct,inter);
            }
        }
    }
    return result;
}


Mat erosion_nunif(int elt_struct_i, int elt_struct_j, Mat &bin, float a, float b, std::vector<int> center, float radius){
    //compute the eroded version of grayscale input image 
    //the filtering is not uniform (the kernel changes depending on the position of the pixel)

    //pad the input image with zeros, so that the filter works also for pixels at the borders
    Mat padded = Mat::zeros(bin.rows+elt_struct_i-1 , bin.cols+elt_struct_j-1 , bin.type());
    copyMakeBorder(bin,padded,elt_struct_i/2,elt_struct_i/2,elt_struct_j/2,elt_struct_j/2,BORDER_CONSTANT,0);
 
    Mat result = Mat::zeros(bin.rows, bin.cols, bin.type());
    Mat elt_struct;
    int counter = 0;
    for (int n=0; n<bin.rows ; n++){
        for (int m=0; m<bin.cols; m++){
            //we extract a sub-matrix from the matrix m1 with the same dimension of the kernel
            Rect r(m,n, elt_struct_j, elt_struct_i);
            Mat inter = padded(r).clone();
            //define the kernel to apply
            //at the top of the finger, we want to create black dots and white holes
            if (pow((float)(n-(bin.rows-1))/a, 2) + pow((float)(m-(bin.cols/2))/b, 2) > 1){
                if (counter%16 <= 10){
                    //for lot of pixels, apply a disc kernel to lighten the pixel
                    elt_struct = elt_struct_disc(elt_struct_i, elt_struct_j);
                }
                else{
                    //for the remaining pixels, the kernel fits the shape of the stripes
                    //to keep black/dark pixels
                    //for the pixels on the left of the finger
                    if ( m < 1.0*bin.cols/3){
                        elt_struct = elt_struct_diag(3, 3, "diag_inv");
                    }
                    //for the pixels on the right of the finger
                    else if (m > 2.0*bin.cols/3){
                        elt_struct = elt_struct_diag(3, 3, "diag");
                    }
                    //for the pixels in the middle of the finger
                    else{
                        elt_struct = elt_struct_cross_col_row(3, 3, "row");
                    }
                }
                counter++;
            }
            else{
                //apply identity kernel for pixels at the center of the finger
                if (pow(n-center[0], 2) + pow(m-center[1], 2) <= pow(radius, 2)){
                    elt_struct = elt_struct_id(3, 3);
                }
                //at the bottom of the finger, pixels are applied a row kernel
                //to have a light erosion
                else{
                    elt_struct = elt_struct_cross_col_row(3,3, "row");
                }
            }
            result.at<float>(n,m) = erosion_coeff_grayscale(elt_struct,inter);
        }
    }
    //apply an opening with a cross kernel to smooth the filtering
    elt_struct = elt_struct_cross_col_row(3,3, "cross");
    result = erosion_dilatation(elt_struct, result,"ero_gray");
    result = erosion_dilatation(elt_struct, result, "dil_gray");
    return result;
} 

Mat erosion_nunif_bin(int elt_struct_i, int elt_struct_j, Mat &bin, float a, float b, std::vector<int> center){
    //compute the eroded version of binary input image
    //the filtering is not uniform (the kernel changes depending on the position of the pixel)
    //pad the input image with zeros, so that the filter works also for pixels at the borders
    Mat padded = Mat::zeros(bin.rows+elt_struct_i-1 , bin.cols+elt_struct_j-1 , bin.type());
    copyMakeBorder(bin,padded,elt_struct_i/2,elt_struct_i/2,elt_struct_j/2,elt_struct_j/2,BORDER_CONSTANT,0);
 
    Mat result = Mat::zeros(bin.rows, bin.cols, bin.type());
    Mat elt_struct;
    for (int n=0; n<bin.rows ; n++){
        for (int m=0; m<bin.cols; m++){
            //we extract a sub-matrix from the matrix bin with the same dimension of the kernel
            Rect r(m,n, elt_struct_j, elt_struct_i);
            Mat inter = padded(r).clone();
            //definition of the kernels
            //for pixels at the top of the finger
            if (pow((float)(n-(bin.rows-1))/a, 2) + pow((float)(m-(bin.cols/2))/b, 2) > 1){
                //we lighten the top of the finger with a disc structuring element
                elt_struct = elt_struct_disc(elt_struct_i, elt_struct_j);
            }
            else{
                //for pixels in the rest of the image we apply a light erosion
                elt_struct = elt_struct_cross_col_row(3,3, "cross");
            }
            result.at<float>(n,m) = erosion_coeff(elt_struct,inter);
        }
    }
    //apply a light opening to smooth the result
    elt_struct = elt_struct_cross_col_row(3,3, "row");
    result = erosion_dilatation(elt_struct, result,"ero_bin");
    result = erosion_dilatation(elt_struct, result, "dil_bin");
    return result;
}


//#######################################################################
//TOOLS
//#######################################################################


std::ostream & operator<<(std::ostream &o, const std::vector<float> &v){
    //overloading of operator <<
    //print out the content of a vector of float
    for (int i = 0; i<v.size(); i++){
        o<<v[i]<<std::endl;
    }
    o<<std::endl;
    return o;
}