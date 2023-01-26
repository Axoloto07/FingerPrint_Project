#include <iostream>
#include <vector>
#include "../include/check_convergence.hpp"
#include "../include/convolution.hpp"
#include "../include/kernel.hpp"
#include "../include/class_image.hpp"


using namespace std;


//fonction to test the convolution 
int main(){

    //----------load the image----------------------------------------
        img fingerprint("images/clean_finger.png");
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

    if (0){
        Mat kernel= kernel_id_light_dark(5,3, 1);
        Mat result = discrete_conv(m1, kernel,'z');
        Mat result_fft = conv_using_fft(m1, kernel);
        Mat result_filter = conv_using_filter(m1, kernel, 'z');


        //save the result in a new image
        img convolution = img(result);
        img convolution_fft = img(result_fft);
        img convolution_filter = img(result_filter);


        convolution.save("conv_id.png");
        convolution_fft.save("conv_id_fft.png");
        convolution_filter.save("conv_id_filter.png");


        //check convergence
        float threshold = 0.01;
        cout<<"id"<<endl<<"prof/nous"<<endl;
        convergence("images/clean_finger.png","conv_id.png",threshold);
        cout<<"test methods"<<endl<<"prof/fft"<<endl;
        convergence("images/clean_finger.png","conv_id_fft.png",threshold);
        cout<<"prof/filter"<<endl;
        convergence("images/clean_finger.png","conv_id_filter.png",threshold);

    }
  

//#######################################################################
//TEST WITH BLUR KERNEL
//#######################################################################
  
    if(0){
        Mat kernel= kernel_blurred(5,5);
        Mat result = discrete_conv(m1, kernel,'z');
        Mat result_fft = conv_using_fft(m1, kernel);
        Mat result_filter = conv_using_filter(m1, kernel, 'z');

        //save the result in a new image
        img convolution = img(result);
        img convolution_fft = img(result_fft);
        img convolution_filter = img(result_filter);

        convolution.save("conv_blur.png");
        convolution_fft.save("conv_blur_fft.png");
        convolution_filter.save("conv_blur_filter.png");

        //check convergence
        float threshold = 0.05;
        cout<<"blur"<<endl<<"prof/nous"<<endl;
        convergence("images/blurred_finger.png","conv_blur.png",threshold);
        cout<<"test methods"<<endl<<"nous/fft"<<endl;
        convergence("conv_blur.png","conv_blur_fft.png",threshold);
        cout<<"filter/nous"<<endl;
        convergence("conv_blur_filter.png","conv_blur.png",threshold);
        cout<<"filter/fft"<<endl;
        convergence("conv_blur_filter.png","conv_blur_fft.png",threshold);

    }


//#######################################################################
//TEST WITH PULL KERNEL
//#######################################################################

    if(0){
        Mat kernel= kernel_pull(15,5, 0, 0, {0, 0});
        Mat kernel_1= kernel_pull(15,5, 0, 0, {0, 0});


        Mat result = discrete_conv(m1, kernel,'z');
        Mat result_fft = conv_using_fft(m1, kernel_1);
        Mat result_filter = conv_using_filter(m1, kernel_1, 'z');



        //save the result in a new image
        img convolution = img(result);
        img convolution_fft = img(result_fft);
        img convolution_filter = img(result_filter);

        convolution.save("conv_pull.png");
        convolution_fft.save("conv_pull_fft.png");
        convolution_filter.save("conv_pull_filter.png");



        //check convergence
        float threshold = 0.05;
        cout<<"pull"<<endl<<"prof/nous"<<endl;
        convergence("images/blurred_finger.png","conv_pull.png",threshold);
        cout<<"test methods"<<endl<<"filter/fft"<<endl;
        convergence("conv_pull_filter.png","conv_pull_fft.png",threshold);
        cout<<"filter/nous"<<endl;
        convergence("conv_pull_filter.png","conv_pull.png",threshold);
        cout<<"fft/nous"<<endl;
        convergence("conv_pull.png","conv_pull_fft.png",threshold);

    }


//#######################################################################
//TEST WITH GAUSSIAN FILTER
//#######################################################################
    
    if(0){
        Mat kernel= kernel_gaussian(10,10,5, 5);
        Mat kernel_1= kernel_gaussian(10,10,5, 5);

        Mat result = discrete_conv(m1, kernel,'r');
        Mat result_fft = conv_using_fft(m1, kernel_1);
        Mat result_filter = conv_using_filter(m1, kernel_1, 'z');


        //save the result in a new image
        img convolution = img(result);
        img convolution_fft = img(result_fft);
        img convolution_filter = img(result_filter);

        convolution.save("conv_gauss.png");
        convolution_fft.save("conv_gauss_fft.png");
        convolution_filter.save("conv_gauss_filter.png");

        //check convergence
        float threshold = 0.05;
        cout<<"gauss"<<endl<<"prof/nous"<<endl;
        convergence("images/blurred_finger.png","conv_pull.png",threshold);
        cout<<"test methods"<<endl<<"nous/filter"<<endl;
        convergence("conv_gauss.png","conv_gauss_filter.png",threshold);
        cout<<"fft/filter"<<endl;
        convergence("conv_gauss_fft.png","conv_gauss_filter.png",threshold);
        cout<<"fft/nous"<<endl;
        convergence("conv_gauss_fft.png","conv_gauss.png",threshold);

    }


//#######################################################################
//TEST WITH NON UNIFORM BLUR KERNELS - NON NORMALIZED
//#######################################################################

    if(0){  
        b = (float) 0.37*m1.cols;
        //Mat result = conv_x_y(m1, 15, 3, center, b, 2.0*b/3);
        Mat result = conv_x_y(m1, 15, 3, center, b, 3.0*b/4, 't', 'a');
        Mat result_1 = conv_x_y(result, 5,5,{m1.rows/2, m1.cols/2},120,120, 'b', 'a');
        //Mat result_2 = convol_energy(result_1, 3,3,center);
        Mat kernel = kernel_gaussian(1,1,3,3);
        Mat result_2 = discrete_conv(result_1, kernel, 'r');


        //save the result in a new image
        img convolution = img(result_2);
        convolution.save("conv_blur_nunif.png");
        
        //check convergence
        float threshold = 0.05;
        cout<<"blurr nunif"<<endl<<"prof/nous"<<endl;
        convergence("images/blurred_finger.png","conv_blur_nunif.png",threshold);
        
    }


//#######################################################################
//TEST WITH NON UNIFORM BLUR KERNELS - NORMALIZED
//#######################################################################

    if(0){  
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
        convolution.save("conv_blur_nunif_norm.png");
        
        //check convergence
        float threshold = 0.05;
        cout<<"blurr nunif"<<endl<<"prof/nous"<<endl;
        convergence("images/blurred_finger.png","conv_blur_nunif_norm.png",threshold);
        
    }


//#######################################################################
//TEST WITH KERNEL WITH DECREASING ENERGY
//#######################################################################

    if(0){
        Mat result = convol_energy(m1, 3,3,center); 
        //save the result in a new image
        img convolution = img(result);
        convolution.save("conv_energy.png");
    }

return 0;
}


