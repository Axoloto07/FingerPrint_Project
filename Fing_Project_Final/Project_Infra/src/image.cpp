#include "../include/image.hpp"


//#######################################################################
//CONSTRUCTORS
//#######################################################################

img::img(std::string filename){
//create a image from a filename
    matrix = imread(filename, IMREAD_GRAYSCALE);
    
}

img::img(Mat mat){
//constructor of an image from a instance of mat
    matrix = mat;

}

img::img(){

    matrix = Mat();

}


//#######################################################################
//SAVE THE IMAGE
//#######################################################################

void img::save(std::string filename){
//save an image in a file
    std::cout<<"The file "<<filename<<" has been created"<<std::endl;
    std::cout<<std::endl;
    imwrite(filename, matrix);

}


//#######################################################################
//GETTERS
//#######################################################################

int img::get_pix_val(int i, int j){
//return the value of a pixel located at position (i,j)
    return matrix.at<uchar>(i, j);

}

int img::get_rows(){
//return the nb of rows of the matrix
    return matrix.rows;
}

int img::get_cols(){
//return the nb of columns of the matrix
    return matrix.cols;
}

Mat img::get_matrix(){
//return the matrix containing the pixel intensity of the image
    return matrix;
}

//#######################################################################
//MODIFICATION OF TYPE / VALUE OF PIXELS
//#######################################################################


void img::modif_pix(int i, int j, int val){
//modify the value of a pixel located at position (i,j) with a new value val
    matrix.at<uchar>(i, j) = val;

}

img img::cast_to_float(){
//cast every pixel intensity to float
//return a new image

    Mat result = Mat_<float>(matrix.rows, matrix.cols, matrix.type());
    for (int i = 0; i<matrix.rows; i++){
        for (int j = 0; j<matrix.cols; j++){
            result.at<float>(i,j)=(float)(matrix.at<uchar>(i,j));
        }
    }
    return img(result);
}


img img::convert_to_0_1(){
//converts the intensity pixels from [0,255] to [0,1]
//return an image

    //creation of the output image
    Mat result = Mat_<float>(matrix.rows, matrix.cols, matrix.type());
    for (int i = 0; i<matrix.rows; i++){
        for (int j = 0; j<matrix.cols; j++){
            //divide each intensity by 255
            result.at<float>(i,j)=(float)(matrix.at<uchar>(i,j))/255;
        }
    }

    return img(result);
}

img img::convert_to_0_255(){
//converts the intensity pixels from [0,1] to [0,255]
//return an image

    //creation of the output image
    Mat result = Mat_<uchar>(matrix.rows, matrix.cols, matrix.type());
    for (int i = 0; i<matrix.rows; i++){
        for (int j = 0; j<matrix.cols; j++){
            //multiply each intensity by 255
            result.at<uchar>(i,j)=(uchar)(matrix.at<float>(i,j)*255);
        }
    }
    return img(result);
}

//#######################################################################
//MAXIMUM / MINIMUM
//#######################################################################

std::vector<int> img::max(){
//compute the maximum of the pixel intensity in an image
//return its coordinates and the intensity of this pixel in a vector
    std::vector<int> max {0, 0, matrix.at<uchar>(0, 0)};

    for (int i = 0; i<matrix.rows; i++){
        for (int j = 0; j<matrix.cols; j++){

            if (matrix.at<uchar>(i, j) > max[2]){
                //coordinates of the maximum pixel
                max[0] = i;
                max[1] = j;
                //intensity of the maximum pixel
                max[2] = matrix.at<uchar>(i, j);

            }
        }
    }
    return max;
}


std::vector<int> img::min(){
//compute the minimum of the pixel intensity in an image
//return its coordinates and the intensity of this pixel in a vector
    std::vector<int> min {0, 0, matrix.at<uchar>(0, 0)};

    for (int i = 0; i<matrix.rows; i++){
        for (int j = 0; j<matrix.cols; j++){

            if (matrix.at<uchar>(i, j) < min[2]){
                //coordinates of the minimum pixel
                min[0] = i;
                min[1] = j;
                //intensity of the minimum pixel
                min[2] = matrix.at<uchar>(i, j);

            }
        }
    }
    return min;
}

//#######################################################################
//SYMMETRIES
//#######################################################################

img img::sym_y(){
//perform the symmetry w.r.t. the y-axis on an input image

    //creation of the output image
    img sym = img(Mat(matrix.rows, matrix.cols, matrix.type()));
    //go through the input image
    for (int j = 0; j<matrix.cols; j++){
        for (int i = 0; i<matrix.rows; i++){
            //store the input pixels at the good positions in the output image
            sym.modif_pix(i, j, (*this).get_pix_val(i, matrix.cols -1 - j));
        }
    }
    return sym;

}   


img img::sym_x(){
//perform the symmetry w.r.t. the x-axis on an input image

    //creation of the output image
    img sym = img(Mat(matrix.rows, matrix.cols, matrix.type()));
    //go through the input image
    for (int j = 0; j<matrix.cols; j++){
        for (int i = 0; i<matrix.rows; i++){
            //store the input pixels at the good positions in the output image
            sym.modif_pix(i, j, (*this).get_pix_val(matrix.rows -1 - i, j));

        }
    }
    return sym;
}   


img img::sym_diag(){
//perform the symmetry w.r.t. the y-axis diagonal on an input image

    //creation of the output image
    img sym = img(Mat(matrix.cols, matrix.rows, matrix.type()));
    //go through the input image
    for (int i = 0; i<matrix.rows; i++){
        for (int j = 0; j<matrix.cols; j++){
            //store the input pixels at the good positions in the output image
            sym.modif_pix(j, i, (*this).get_pix_val(i, j));

        }
    }
    return sym;
}   

img img::sym_diag_inv(){
//perform the symmetry w.r.t. the -y-axis diagonal on an input image

    //creation of the output image
    img sym = img(Mat(matrix.cols, matrix.rows, matrix.type()));
    //go through the input image
    for (int i = 0; i<matrix.rows; i++){
        for (int j = 0; j<matrix.cols; j++){
            //store the input pixels at the good positions in the output image
            sym.modif_pix(j, i, (*this).get_pix_val(matrix.rows-1-i, matrix.cols-1-j));
        }
    }
    return sym;
} 

//#######################################################################
//CENTER OF THE FINGER
//#######################################################################

std::vector<int> img::coord_center(){
    //find the center of the finger and return its coordinates

    int i_center=0;
    int j_center=0;
    std::vector<int> v;
    //we go throw the matrix from top to bottom
    //we don't begin at the very first lines or rows to avoid 'noise' at the boundaries of the image
    for (int i = 5; i<matrix.rows-5; i++){
        for (int j = matrix.cols-1; j>0; j--){
            //when we meet the first pixel dark enough (whose intensity is > 30)
            //we save the coordinate
            if(matrix.at<uchar>(i,j)<30){
                j_center=j;
                goto secondloop;
            }
        
        }
    
    }
    //we go throw the matrix from right to left
    //we don't begin at the very first lines or rows to avoid 'noise' at the boundaries of the image
    secondloop:
    for (int j = matrix.cols-1; j>0; j--){
        for (int i = 5; i<matrix.rows-5; i++){
            if(matrix.at<uchar>(i,j)<30){
                i_center=i;
                goto exit;
            }

        }
    }
    exit:
    //store the founded coordinates in a vector
    v.push_back(i_center);
    v.push_back(j_center);
    return v;
}


//#######################################################################
//OPTIMIZATION FOR IMAGE REGISTRATION
//#######################################################################


img img::translation(float tx, float ty){
// translation of the image
    Mat result = Mat(matrix.rows, matrix.cols, matrix.type());
    float warp_values[] = {1, 0, tx, 0, 1, ty};
    Mat translation_matrix = Mat(2.0, 3.0, CV_32F, warp_values);
    warpAffine(matrix, result, translation_matrix, result.size());
    img res = img(result);
    return res;
}

img img::translation_precize(double tx, double ty){
// translation of the image more precise than the default one, thanks to double instead of uchar
    int itx = (int)tx;
    int ity = (int)ty;
    double ftx = tx - itx;
    double fty = ty - ity;
    Mat result = Mat(get_rows(), get_cols(), CV_64F, Scalar(0.0));
    Mat result2 = Mat(get_rows(), get_cols(), CV_64F, Scalar(0.0));
    double warp_values[] = {1, 0, (double)itx, 0, 1, (double)ity};
    Mat translation_matrix = Mat(2.0, 3.0, CV_64F, warp_values);
    warpAffine(matrix, result, translation_matrix, result.size());
    //translation is default for int but the change is for small translation (between 0 and 1)
    if (tx >=0){
        for (int i = 0; i<get_rows(); i++){
            result2.at<double>(i,itx) = (1-ftx)*(double)result.at<uchar>(i,itx);
            for (int j = itx+1; j<get_cols(); j++){
                result2.at<double>(i,j) = (1-ftx)*(double)result.at<uchar>(i,j) + ftx*(double)result.at<uchar>(i,j-1);
            }
        }
    }
    //tx<0
    else {
        for (int i = 0; i<get_rows(); i++){
            result2.at<double>(i,get_cols()+itx-1) = (1+ftx)*(double)result.at<uchar>(i,get_cols()+itx-1);
            for (int j = 0; j<get_cols()+itx-1; j++){
                result2.at<double>(i,j) = (1+ftx)*(double)result.at<uchar>(i,j) + (-ftx)*(double)result.at<uchar>(i,j+1);
            }
        }
    }
    img res2 = img(result2);
    return res2;
}



float img::mean(){
// mean of the image
    float m = 0;
    int n = get_rows()*get_cols();
    for (int i = 0; i<get_rows(); i++){
        for (int j = 0; j<get_cols(); j++){
            m += get_pix_val(i, j);
        }
    }
    return m/n;
}



img img::difference(img image){
// return the difference between two images
    img res = img(Mat(matrix.rows, matrix.cols, matrix.type()));
    for (int i = 0; i<get_rows(); i++){
        for (int j = 0; j<get_cols(); j++){
            res.modif_pix(i, j, 255-abs(get_pix_val(i, j)-image.get_pix_val(i, j)));
        }
    }
    return res;
}

//#######################################################################
//OVERLOADED PRINT
//#######################################################################

std::ostream &operator<<(std::ostream &o, const img &image){
    o<<image.matrix<<std::endl;
    return o;
}