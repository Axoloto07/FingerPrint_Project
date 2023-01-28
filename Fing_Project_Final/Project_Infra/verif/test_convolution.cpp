#include <iostream>

#include "../include/convolution.hpp"
#include "../include/check_convergence.hpp"


using namespace std;


//fonction to test the convolution process
int main(){

    cout<<"PLEASE CHOOSE THE OPTION YOU WANT TO RUN : enter 'if(1)' instead of 'if(0)'"<<endl;

    
//#######################################################################
//GET THE INPUTS
//####################################################################### 

    //----------load the image----------------------------------------
        img fingerprint("../Project_Infra/images/clean_finger.png");
        //conversion to float
        img tmp = fingerprint.cast_to_float();
        //get the matrix
        Mat m1 = tmp.get_matrix();
    
    //--------load parameters-----------------------------------------

        float a = (float) (1*m1.rows)/8;
        float b = (float) (8*m1.cols)/32;

        vector<int> center = fingerprint.coord_center();


//#######################################################################
//TEST WITH IDENTITY KERNEL
//#######################################################################

    if (1){
        Mat kernel= kernel_id_light_dark(5,3, 1);
        Mat result = discrete_conv(m1, kernel,'z');
        Mat result_fft = conv_using_fft(m1, kernel);
        Mat result_filter = conv_using_filter(m1, kernel, 'z');


        //save the result in new images
        img convolution = img(result);
        img convolution_fft = img(result_fft);
        img convolution_filter = img(result_filter);

        convolution.save("verif_results/conv_id.png");
        convolution_fft.save("verif_results/conv_id_fft.png");
        convolution_filter.save("verif_results/conv_id_filter.png");


        //check convergence
        float threshold = 0.01;
        cout<<"Identity kernel :"<<endl;
        convergence("../Project_Infra/images/clean_finger.png","verif_results/conv_id.png",threshold);
        cout<<"Verifications :"<<endl;
        convergence("../Project_Infra/images/clean_finger.png","verif_results/conv_id_fft.png",threshold);
        convergence("../Project_Infra/images/clean_finger.png","verif_results/conv_id_filter.png",threshold);
    }
  

//#######################################################################
//TEST WITH UNIFORM BLUR KERNEL
//#######################################################################
  
    if(1){
        Mat kernel= kernel_blurred(5,5);
        Mat result = discrete_conv(m1, kernel,'z');
        Mat result_fft = conv_using_fft(m1, kernel);
        Mat result_filter = conv_using_filter(m1, kernel, 'z');

        //save the result in new images
        img convolution = img(result);
        img convolution_fft = img(result_fft);
        img convolution_filter = img(result_filter);

        convolution.save("verif_results/conv_blur.png");
        convolution_fft.save("verif_results/conv_blur_fft.png");
        convolution_filter.save("verif_results/conv_blur_filter.png");

        //check convergence
        float threshold = 0.05;
        cout<<"Uniform blur kernel :"<<endl;
        convergence("../Project_Infra/images/blurred_finger.png","verif_results/conv_blur.png",threshold);
        cout<<"Verifications : "<<endl;
        convergence("verif_results/conv_blur.png","verif_results/conv_blur_fft.png",threshold);
        convergence("verif_results/conv_blur_filter.png","verif_results/conv_blur.png",threshold);
        convergence("verif_results/conv_blur_filter.png","verif_results/conv_blur_fft.png",threshold);
        histogram("verif_results/conv_blur_filter.png","verif_results/conv_blur.png", "verif_results");
    }


//#######################################################################
//TEST WITH PULL KERNEL
//#######################################################################

    if(1){
        Mat kernel= kernel_pull(15,5, 0, 0, {0, 0});
        Mat kernel_1= kernel_pull(15,5, 0, 0, {0, 0});


        Mat result = discrete_conv(m1, kernel,'z');
        Mat result_fft = conv_using_fft(m1, kernel_1);
        Mat result_filter = conv_using_filter(m1, kernel_1, 'z');



        //save the result in new images
        img convolution = img(result);
        img convolution_fft = img(result_fft);
        img convolution_filter = img(result_filter);

        convolution.save("verif_results/conv_pull.png");
        convolution_fft.save("verif_results/conv_pull_fft.png");
        convolution_filter.save("verif_results/conv_pull_filter.png");

        //check convergence
        float threshold = 0.05;
        cout<<"Pull kernel :"<<endl;
        convergence("../Project_Infra/images/blurred_finger.png","verif_results/conv_pull.png",threshold);
        cout<<"Verifications :"<<endl;
        convergence("verif_results/conv_pull_filter.png","verif_results/conv_pull_fft.png",threshold);
        convergence("verif_results/conv_pull_filter.png","verif_results/conv_pull.png",threshold);
        convergence("verif_results/conv_pull.png","verif_results/conv_pull_fft.png",threshold);

    }


//#######################################################################
//TEST WITH GAUSSIAN FILTER
//#######################################################################
    
    if(1){
        Mat kernel= kernel_gaussian(10,10,5, 5);
        Mat kernel_1= kernel_gaussian(10,10,5, 5);

        Mat result = discrete_conv(m1, kernel,'r');
        Mat result_fft = conv_using_fft(m1, kernel_1);
        Mat result_filter = conv_using_filter(m1, kernel_1, 'z');


        //save the result in new images
        img convolution = img(result);
        img convolution_fft = img(result_fft);
        img convolution_filter = img(result_filter);

        convolution.save("verif_results/conv_gauss.png");
        convolution_fft.save("verif_results/conv_gauss_fft.png");
        convolution_filter.save("verif_results/conv_gauss_filter.png");

        //check convergence
        float threshold = 0.05;
        cout<<"Gaussian kernel :"<<endl;
        convergence("../Project_Infra/images/blurred_finger.png","verif_results/conv_pull.png",threshold);
        cout<<"Verifications :"<<endl;
        convergence("verif_results/conv_gauss.png","verif_results/conv_gauss_filter.png",threshold);
        convergence("verif_results/conv_gauss_fft.png","verif_results/conv_gauss_filter.png",threshold);
        convergence("verif_results/conv_gauss_fft.png","verif_results/conv_gauss.png",threshold);

    }


//#######################################################################
//TEST WITH NON UNIFORM BLUR KERNELS - NON NORMALIZED
//#######################################################################

    if(1){  
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
        convolution.save("verif_results/conv_blur_nunif.png");

        //check convergence
        float threshold = 0.05;
        cout<<"Blurr nunif kernels :"<<endl;
        convergence("../Project_Infra/images/blurred_finger.png","verif_results/conv_blur_nunif.png",threshold);
        mean_squared_error("../Project_Infra/images/blurred_finger.png","verif_results/conv_blur_nunif.png");
        histogram("../Project_Infra/images/blurred_finger.png", "verif_results/conv_blur_nunif.png", "verif_results");
    }


//#######################################################################
//TEST WITH NON UNIFORM BLUR KERNELS - NORMALIZED
//#######################################################################

    if(1){  
        a = (float) (1*m1.rows)/8;
        b = (float) (8*m1.cols)/32;

        //apply a kernel with decreasing energy to have a lightened image
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
        convolution.save("verif_results/conv_blur_nunif_norm.png");
        
        //check convergence
        float threshold = 0.05;
        cout<<"Blurr nunif normalized kernels :"<<endl;
        convergence("../Project_Infra/images/blurred_finger.png","verif_results/conv_blur_nunif_norm.png",threshold);
        mean_squared_error("../Project_Infra/images/blurred_finger.png","verif_results/conv_blur_nunif_norm.png");
        histogram("../Project_Infra/images/blurred_finger.png","verif_results/conv_blur_nunif_norm.png", "verif_results");
    }


//#######################################################################
//TEST WITH KERNEL WITH DECREASING ENERGY
//#######################################################################

    if(1){
        //apply a decreasing energy kernel
        Mat result = convol_energy(m1, 3,3,center); 
        
        //save the result in a new image
        img convolution = img(result);
        convolution.save("verif_results/conv_energy.png");
    }

return 0;
}


