#include <iostream>

#include "../include/convolution.hpp"
#include "../include/check_convergence.hpp"

using namespace std;


//fonction to create the blurred finger
int main(){

    //----------load the image----------------------------------------
        //get the input image
        cout<<"Please enter the name of the image. (ex : clean_finger.png)"<<endl;
        string path;
        cin>>path;
        img fingerprint("../Project_Infra/images/" + path);
        //conversion to float
        img tmp = fingerprint.cast_to_float();
        //get the matrix
        Mat m1 = tmp.get_matrix();
        //choose the option to run
        bool non_norm;
        cout<<"Do you want the version with injection of energy? (enter 1 for yes, 0 for no)"<<endl;
        cin>>non_norm;
        bool norm;
        cout<<"Do you want the version with conservation of energy? (enter 1 for yes, 0 for no)"<<endl;
        cin>>norm;

    //--------load parameters-----------------------------------------

        float a = (float) (1*m1.rows)/8;
        float b = (float) (8*m1.cols)/32;

        vector<int> center = fingerprint.coord_center();


//#######################################################################
//NON UNIFORM BLUR KERNELS - NON NORMALIZED
//#######################################################################

    if(non_norm){  
        b = (float) 0.37*m1.cols;
        //Mat result = conv_x_y(m1, 15, 3, center, b, 2.0*b/3);
        Mat result = conv_x_y(m1, 15, 3, center, b, 3.0*b/4, 't', 'a');
        Mat result_1 = conv_x_y(result, 5,5,{m1.rows/2, m1.cols/2},120,120, 'b', 'a');
        //Mat result_2 = convol_energy(result_1, 3,3,center);
        Mat kernel = kernel_gaussian(1,1,3,3);
        Mat result_2 = discrete_conv(result_1, kernel, 'r');


        //save the result in a new image
        img convolution = img(result_2);
        convolution.save("demo_results/blurred_finger_non_norm.png");
        
        //check convergence
        float threshold = 0.05;
        convergence("../Project_Infra/images/blurred_finger.png","demo_results/blurred_finger_non_norm.png",threshold);
        mean_squared_error("../Project_Infra/images/blurred_finger.png", "demo_results/blurred_finger_non_norm.png");
        
    }


//#######################################################################
//NON UNIFORM BLUR KERNELS - NORMALIZED
//#######################################################################

    if(norm){  
        a = (float) (1*m1.rows)/8;
        b = (float) (8*m1.cols)/32;
        //Mat result = conv_x_y(m1, 15, 3, center, b, 2.0*b/3);
        Mat result = convol_energy(m1, 3,3,center);

        Mat result_1 = conv_x_y(result, 15, 3, center, b, 3.0*b/4, 't', 'n');
        Mat result_2 = conv_x_y(result_1, 5,5,{m1.rows/2, m1.cols/2},120,120, 'b', 'n');
        Mat kernel = kernel_gaussian(1,1,3,3);
        Mat result_3 = discrete_conv(result_2, kernel, 'r');


        //save the result in a new image
        img convolution = img(result_3);
        convolution.save("demo_results/blurred_finger_norm.png");
        
        //check convergence
        float threshold = 0.05;
        convergence("../Project_Infra/images/blurred_finger.png","demo_results/blurred_finger_norm.png",threshold);
        mean_squared_error("../Project_Infra/images/blurred_finger.png", "demo_results/blurred_finger_norm.png");
        
    }
return 0;
}


