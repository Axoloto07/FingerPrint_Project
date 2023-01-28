#ifndef CLASS_HPP
#define CLASS_HPP


#include <iostream> 
#include <stdio.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <map>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;


/**
 * @brief definition of the class img
 * contains one attribute (the matrix of pixel intensities)
 * 
 */
class img{
    friend ostream &operator<<(ostream &o, const img &image);
    protected:
        Mat matrix;

    public:

        //#######################################################################
        //CONSTRUCTORS
        //#######################################################################
  
        /**
         * @brief Construct a new img object taking value in [0;255] from the filename
         * 
         * @param filename 
         */
        img(string filename);

        /**
         * @brief Construct a new img object from a Mat
         * 
         * @param mat 
         */
        img(Mat mat);

        /**
         * @brief Construct a new img object
         * 
         */
        img();

        //#######################################################################
        //SAVE THE IMAGE
        //#######################################################################

        /**
         * @brief Save the image under the name filename
         * 
         * @param filename 
         */
        void save(string filename);


        //#######################################################################
        //GETTERS
        //#######################################################################

        /**
         * @brief Get the value of the pixel (i, j)
         * 
         * @param i line
         * @param j column
         * @return int 
         */
        virtual int get_pix_val(int i, int j);

        /**
         * @brief Get the nb of rows
         * 
         * @return int 
         */
        virtual int get_rows();

        /**
         * @brief Get the nb of columns
         * 
         * @return int 
         */
        virtual int get_cols();

        /**
         * @brief Get the matrix
         * 
         * @return Mat
         */
        Mat get_matrix();


        //#######################################################################
        //MODIFICATION OF TYPE / VALUE OF PIXELS
        //#######################################################################

        /**
         * @brief Modify the pixel at coord (i, j) with the value val
         * 
         */
        void modif_pix(int i, int j, int val);

        /**
         * @brief Convert the values of the Mat in float
         * 
         * 
         * @return img with float numbers
         */
        img cast_to_float();

        /**
         * @brief Put the values of the Mat from [0, 1] to [0,255]
         * go from a float matrix to a uchar matrix
         * 
         * @return img 
         */

        img convert_to_0_1();

        /**
         * @brief Put the values of the Mat from [0, 1] to [0,255]
         * go from a float matrix to a uchar matrix
         * 
         * @return img 
         */
        img convert_to_0_255();


        //#######################################################################
        //MAXIMUM / MINIMUM
        //#######################################################################

        /**
         * @brief Find the maximum color value in the image
         * 
         * @return vector containing the coordinates of the maximal value as well as this value
         */
        vector<int> max();

        /**
         * @brief Find the minimum color value of the image
         * 
         * @return vector containing the coordinates of the minimal value as well as this value
         */
        vector<int> min();


        //#######################################################################
        //SYMMETRIES
        //#######################################################################

        /**
         * @brief Create a matrice corresponding to the symmetry with respect
         * to the y axis of the original image
         * 
         * @return the transformed image
         */
        img sym_y();

        /**
         * @brief Create a matrice corresponding to the symmetry woth respect
         * to the x axis of the original image
         * 
         * @return the transformed image 
         */
        img sym_x();

        /**
         * @brief Create a matrice corresponding to the symmetry with respect
         * to the diagonal of the original image
         * 
         * @return the transformed image 
         */
        img sym_diag();

        /**
         * @brief Create a matrice corresponding to the symmetry with respect
         * to the other diagonal of the original image
         * 
         * @return the transformed image 
         */
        img sym_diag_inv();


        //#######################################################################
        //CENTER OF THE FINGER
        //#######################################################################

        /**
         * @brief return the point of high pressure of the fingerprint
         * 
         * @return vector containing the coordinates of the center 
         */
        vector<int> coord_center();
        

        //#######################################################################
        //OPTIMIZATION FOR IMAGE REGISTRATION
        //#######################################################################

        /**
         * @brief perform a translation of the image of tx pixels according to the x-axis and ty pixels
         * according to the y-axis
         * 
         * @param tx  translation along x
         * @param ty  translation along y
         * @return the transformed image 
         */
        img translation(float tx, float ty);

        /**
         * @brief perform a translation of the image of tx pixels according to the x-axis and ty pixels
         * more precisely than the previous one, used in loss_function_pderivative_x
         * 
         * @param tx translation along x
         * @param ty translation along y
         * @return the transformed image 
         */
        img translation_precize(double tx, double ty);



        /**
         * @brief compute the difference between 2 images for the
         * function loss_function_diff
         * the derivative of the loss function with respect to the translation
         * along the x-axis
         * @param image 
         * @return img 
         */
        img difference(img image);


        /**
         * @brief compute the mean of an image
         * 
         */
        float mean();

};





#endif