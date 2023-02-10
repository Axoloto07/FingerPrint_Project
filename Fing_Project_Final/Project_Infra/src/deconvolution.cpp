#include "../include/deconvolution.hpp"


//#######################################################################
//CONVOLUTION - MATRIX METHOD
//#######################################################################


Mat circulate_coeff(Mat &kernel_ligne, Mat &input){
    //make a circulant matrix from a vector
    //the new matrix has the same dimensions as the input matrix
    Mat circulante = Mat::zeros(input.cols,input.cols,kernel_ligne.type());

    for (int j=0; j<circulante.cols; j++){
        for (int i=0; i<circulante.rows; i++){
            //the elements of the vector are stored in column in the matrix and moved one row down for each column
            //the coef at the top left of the circulant matrix corresponds to the middle coef of the vector
            if (kernel_ligne.cols / 2 + j - i >= 0 && kernel_ligne.cols / 2 + j -i < kernel_ligne.cols){
                circulante.at<float>(i , j) = kernel_ligne.at<float>(kernel_ligne.cols / 2 + j - i);
            }
        }
    }
    return circulante;
}


std::vector<Mat> list_circulante(Mat &kernel, Mat &input){
    //create a vector containing the circulant matrices created for each row of the kernel
    std::vector<Mat> v;
    for (int i=0; i<kernel.rows; i++){
        //we take and copy a row of the kernel
        Rect rect(0, i, kernel.cols, 1);
        Mat row = kernel(rect).clone();
        //create the circulant matrix corresponding to this row
        Mat circ = circulate_coeff(row, input);
        //add this matrix to the vector v
        v.push_back(circ);
    }
    return v;
}

Mat circulate_matrix(std::vector<Mat> &v, Mat &input){
    //create a doubly block circulant matrix from a list of matrices stored in vector v
    //each column/row of this matrix contains smaller matrices from vector v
    //the block-dimensions of this circulant matrix is equal to those of the input matrix
    Mat doubly_block = Mat::zeros(input.rows * v[0].rows, input.rows * v[0].cols ,input.type());

    //make the smaller matrices circulate in the doubly blocked matrix from column to column
    //matrices are moved one block down at each block_column in the doubly block circulant matrix
    //the block at the top left corner corresponds to the circulant matrix stored at the middle position
    //in the vector
    for (int j=0; j<doubly_block.cols; j+=v[0].cols){
        for (int i=0; i<doubly_block.rows; i+=v[0].rows){
            if (v.size()/2 + j/v[0].cols - i / v[0].rows >=0 && v.size()/2 + j/v[0].cols - i / v[0].rows < v.size()){
              
                modif_block(i ,j, v[0].rows, v[0].cols, v[v.size()/2 + j/v[0].cols - i / v[0].rows], doubly_block);
            }
        }
      
    }
    return doubly_block;

}


Mat blurr(Mat &K, Mat &input){
    //vectorize the input image
    Mat input_vector = vectorise(input);
    //compute the product with the matrix of the convolution built from the kernel
    Mat result_vector =  K  * input_vector;
    //transform the result back to a matrix ofthe same size as the input
    Mat result = matricise(result_vector, input.rows , input.cols );
    return result;
}

//#######################################################################
//DECONVOLUTION - LEAST SQUARES METHOD
//#######################################################################

Mat least_squares_result(Mat &doubly_block, float lmbda, Mat &output){
    //solve a linear system Kx = y with the least squares method given a damping/regularization coefficient lmbda
    //this coefficient is used to have a well posed system
    
    //convert the convolution matrix K to sparse matrix
    sparsematrix K = matrix_to_sparse(doubly_block);
    //convert the right member to dense matrix
    real_1d_array output_dense = matrix_to_vector_dense(output);
    //convert K to the right format for the solver
    sparseconverttocrs(K);
    //create the solver environment
    linlsqrstate s;
    linlsqrreport rep;
    real_1d_array x;
    linlsqrcreate(doubly_block.rows, doubly_block.cols, s);
    //define the regularization coefficient
    linlsqrsetlambdai(s, lmbda);
    //solve the system with least squares method
    linlsqrsolvesparse(s, K, output_dense);
    linlsqrresults(s, x, rep);
    //convert the result into matrix
    Mat result = tab_to_matrix(x, output);

    return result;
}

//#######################################################################
//TOOLS
//#######################################################################


void modif_block(int i_begin, int j_begin, int size_i, int size_j, Mat &src, Mat &dest){
    //copy the content of 'src' into a submatrix (whose top left corner is at (i_begin, j_begin))
    //of 'dest' of dimensions size_i*size_j
    for (int i=i_begin; i<i_begin + size_i; i++){
        for (int j=j_begin; j<j_begin + size_j; j++){
            dest.at<float>(i,j) = src.at<float>(i-i_begin, j-j_begin);
        }

    }
}

Mat cut(Mat &m1, int i_suppr_top, int i_suppr_bott, int j_suppr){
    //put away i_suppr rows at the bottom of the matrix m1 and j_suppr/2 columns on the left and right
    Mat result = Mat::zeros(m1.rows - i_suppr_top - i_suppr_bott, m1.cols-j_suppr, m1.type());
    for (int i=i_suppr_top; i<m1.rows-i_suppr_bott; i++){
        for (int j=j_suppr/2; j<m1.cols - j_suppr/2; j++){
            result.at<float>(i-i_suppr_top,j-j_suppr/2) = m1.at<float>(i,j);
        }
    }
    return result;
}


//#######################################################################
//CONVERSION MATRIX / VECTOR
//#######################################################################


Mat vectorise(Mat &picture){
    //transform a matrix into a vector row after row
    //the vector is of size nb_rows_matrix*nb_columns_matrix

    Mat image = Mat::zeros(picture.rows * picture.cols,1, picture.type());

    for (int i=0; i<picture.rows; i++){
        for (int j=0; j<picture.cols; j++){
            image.at<float>(i*picture.cols + j)= picture.at<float>(i, j);
        }
    }
    return image ;
}


Mat matricise(Mat &input_vector, int output_i, int output_j){
    //transform a vector into a matrix
    //fill the matrix row after row
    Mat output = Mat::zeros(output_i ,output_j, input_vector.type());

    for (int i=0; i<output.rows; i++){
        for (int j=0; j<output.cols; j++){
            output.at<float>(i,j)= (input_vector.at<float>(i*output.cols + j));
        }
    }
    return output ;
}

sparsematrix matrix_to_sparse(Mat &m1){
    //convert a dense matrix into a sparse matrix
    sparsematrix K;
    sparsecreate(m1.rows, m1.cols, K);
    for (int i=0; i<m1.rows; i++){
        for (int j=0; j<m1.cols; j++){
            if (m1.at<float>(i,j) != 0){
                sparseset(K, i, j, m1.at<float>(i,j));
            }
        }
    }
    return K;
}

real_1d_array matrix_to_vector_dense(Mat &m1){
    //transform a matrix into a 1D array
    real_1d_array result;
    result.setlength(m1.rows * m1.cols);
    for (int i=0; i<m1.rows; i++){
        for (int j=0; j<m1.cols; j++){
            result[i*m1.cols + j]= m1.at<float>(i, j);
        }
    }
    return result;
}


Mat tab_to_matrix(real_1d_array &x, Mat &input){
    //transform a 1D array into a matrix
    //the matrix is filled row after row
    Mat result = Mat::zeros(input.rows, input.cols, input.type());

    for (int i=0; i<result.rows; i++){
        for (int j=0; j<result.cols; j++){
            result.at<float>(i,j)= x[i*result.cols + j];
        }
    }
    return result;
}

//#######################################################################
//PRINT
//#######################################################################


void print_sparse(sparsematrix &m1){
    //print the content of a sparse matrix
    sparseconverttocrs(m1);
    ae_int_t nb_rows = sparsegetnrows(m1);
    real_1d_array result;
    for (ae_int_t i = 0; i<nb_rows; i++){
        sparsegetrow(m1, i, result);
        std::cout<<result;

    }
    
}

std::ostream & operator<<(std::ostream &o, const std::vector<Mat> &v){
    //overloading of operator <<
    //print out the content of a vector of matrices
    for (int i = 0; i<v.size(); i++){
        o<<v[i]<<std::endl;
    }
    o<<std::endl;
    return o;
}

std::ostream& operator<<(std::ostream &o, const real_1d_array &result){
    //overload of the operator <<
    //to print the content of a 1D array
    for (int i = 0; i<result.length(); i++){
        o<<result[i]<<" ";
    }
    o<<std::endl;
    return o;
}
 

