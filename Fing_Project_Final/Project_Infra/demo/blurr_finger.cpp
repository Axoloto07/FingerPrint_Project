#include <iostream>

#include "../include/convolution.hpp"
#include "../include/check_convergence.hpp"

//using namespace std;


//fonction to create the blurred finger
int main(){

//#######################################################################
//GET THE INPUTS
//#######################################################################  
        std::cout<<"Please enter the name of the image. (ex : clean_finger.png)"<<std::endl;
        std::string path;
        std::cin>>path;
        img fingerprint("../Project_Infra/images/" + path);
        //conversion to float
        img tmp = fingerprint.cast_to_float();
        //get the matrix
        Mat m1 = tmp.get_matrix();

        //choose the option to run
        bool non_norm;
        std::cout<<"Do you want the version with injection of energy? (enter 1 for yes, 0 for no)"<<std::endl;
        std::cin>>non_norm;
        bool norm;
        std::cout<<"Do you want the version with conservation of energy? (enter 1 for yes, 0 for no)"<<std::endl;
        std::cin>>norm;

//#######################################################################
//LOAD PARAMETERS
//#######################################################################

        float a = (float) (1*m1.rows)/8;
        float b = (float) (8*m1.cols)/32;

        std::vector<int> center = fingerprint.coord_center();


//#######################################################################
//NON UNIFORM BLUR KERNELS - NON NORMALIZED
//#######################################################################

    if(non_norm){  
        b = (float) 0.37*m1.cols;
        

        //pull filter depending on the pixel's location on the top of the finger 
        Mat result = conv_x_y(m1, 15, 3, center, b, 3.0*b/4, 't', 'a');
        //box blurr filter depending on the pixel's location on the bottom of the finger 
        Mat result_1 = conv_x_y(result, 5,5,{m1.rows/2, m1.cols/2},120,120, 'b', 'a');
        //Gaussian uniform blurr on the whole finger
        Mat kernel = kernel_gaussian(1,1,3,3);
        Mat result_2 = discrete_conv(result_1, kernel, 'r');

        //save the result in a new image
        img convolution = img(result_2);
        convolution.save("demo_results/blurred_finger_non_norm.png");
        
        //check convergence
        float threshold = 0.05;
        convergence("../Project_Infra/images/blurred_finger.png","demo_results/blurred_finger_non_norm.png",threshold);
        mean_squared_error("../Project_Infra/images/blurred_finger.png", "demo_results/blurred_finger_non_norm.png");
        histogram("../Project_Infra/images/blurred_finger.png", "demo_results/blurred_finger_non_norm.png", "demo_results");
    }


//#######################################################################
//NON UNIFORM BLUR KERNELS - NORMALIZED
//#######################################################################

    if(norm){  
        a = (float) (1*m1.rows)/8;
        b = (float) (8*m1.cols)/32;

        //decreasing energy to have a lighten image
        Mat result = convol_energy(m1, 3,3,center);

        //pull filter depending on the pixel's location on the top of the finger 
        Mat result_1 = conv_x_y(result, 15, 3, center, b, 3.0*b/4, 't', 'n');
        //box blurr filter depending on the pixel's location on the bottom of the finger 
        Mat result_2 = conv_x_y(result_1, 5,5,{m1.rows/2, m1.cols/2},120,120, 'b', 'n');
        //Gaussian uniform blurr on the whole finger
        Mat kernel = kernel_gaussian(1,1,3,3);
        Mat result_3 = discrete_conv(result_2, kernel, 'r');


        //save the result in a new image
        img convolution = img(result_3);
        convolution.save("demo_results/blurred_finger_norm.png");
        
        //check convergence
        float threshold = 0.05;
        convergence("../Project_Infra/images/blurred_finger.png","demo_results/blurred_finger_norm.png",threshold);
        mean_squared_error("../Project_Infra/images/blurred_finger.png", "demo_results/blurred_finger_norm.png");
        histogram("../Project_Infra/images/blurred_finger.png","demo_results/blurred_finger_norm.png", "demo_results");
    }
return 0;
}


