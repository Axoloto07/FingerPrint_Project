#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "../include/check_convergence.hpp"

//#######################################################################
//COMPARISON PIXEL PER PIXEL
//#######################################################################

float convergence(string filename1, string filename2, float threshold){
    //load two images
    img m1 = img(filename1);
    img m2 = img(filename2);
    int counter = 0;
    //if the sizes of the images are not the same we can't make the comparison
    if (m1.get_rows()!= m2.get_rows() || m1.get_cols() != m2.get_cols()){
        cout<<"Matrices' sizes are not matching"<<endl;
        cout<<"M1's size : " << m1.get_rows()<<" x "<<m1.get_cols()<<endl;
        cout<<"M2's size : " << m2.get_rows()<<" x "<<m2.get_cols()<<endl;
    }
    else{
        //when the sizes of both images are the same, we perform the comparison pixel by pixel
        for (int i = 0; i<m1.get_rows(); i++){
            for (int j = 0; j<m1.get_cols(); j++){
                //we fix a confidence threshold 
                //if the difference between the pixels' intensity (located at the same position in both images)
                //is lower than this threshold, we increase the counter
                if(abs(m1.get_pix_val(i,j)-m2.get_pix_val(i,j))<=threshold){
                    counter++;
                }
            }    
        }
    }

    //return the proportion of pixels "close enough" (given the threshold) in both images
    float result = (float)counter/(m1.get_rows()*m1.get_cols())*100;

    //print the name of the image
    size_t pos_1 = filename1.find_last_of('/');
    filename1 = filename1.substr(pos_1+1);
    size_t pos_2 = filename2.find_last_of('/');
    filename2 = filename2.substr(pos_2+1);
    
    cout<<filename1<<" VS "<<filename2<<endl;
    cout<< "Proportion of matching coefficients : " << result<<" %"<<endl;
    cout<<endl;
    return result;
}


//#######################################################################
//MEAN SQUARED ERROR
//#######################################################################

float mean_squared_error(string filename1, string filename2){
    //load two images
    img m1 = img(filename1);
    img m2 = img(filename2);
    float sum =-1;
    //if the sizes of the images are not the same we can't make the comparison
    if (m1.get_rows()!= m2.get_rows() || m1.get_cols() != m2.get_cols()){
        cout<<"Matrices' sizes are not matching"<<endl;
        cout<<"M1's size : " << m1.get_rows()<<" x "<<m1.get_cols()<<endl;
        cout<<"M2's size : " << m2.get_rows()<<" x "<<m2.get_cols()<<endl;
    }
    else{
        sum =0;
        //when the sizes of both images are the same, we perform the computation
        for (int i = 0; i<m1.get_rows(); i++){
            for (int j = 0; j<m1.get_cols(); j++){
                sum += pow(m1.get_pix_val(i,j)-m2.get_pix_val(i,j),2);
            }    
        }
        sum/=(m1.get_cols()*m1.get_rows());
    
    }
    //print the name of the image
    size_t pos_1 = filename1.find_last_of('/');
    filename1 = filename1.substr(pos_1+1);
    size_t pos_2 = filename2.find_last_of('/');
    filename2 = filename2.substr(pos_2+1);

    cout<<filename1<<" VS "<<filename2<<endl;
    cout<< "Mean squared error : " << sum<<endl;
    cout<<endl;
    return sum;
}


//#######################################################################
//HISTOGRAM OF GRAY LEVELS
//#######################################################################

void histrogram(string filename){
    img fingerprint(filename);
    Mat input = fingerprint.get_matrix();
    //define the x axis
    int histSize = 256;
    float range[] = {0, 256};
    const float* histRange[] = {range};
    bool uniform = true, accumulate = false;
    Mat g_hist;
    calcHist(&input, 1, 0, Mat(), g_hist, 1, &histSize, histRange, uniform, accumulate);
    //set the size of the histogram display
    int hist_i = 600;
    int hist_j = 500;
    Mat histo = Mat::zeros(hist_i, hist_j, CV_8U);
    int bin_w = cvRound((double) hist_i / histSize);
    normalize(g_hist, g_hist, 0, histo.rows, NORM_MINMAX, -1, Mat());
    //plot the histogram
    for (int i=1; i<histSize; i++){
        line(histo, Point(bin_w*(i-1), hist_j - cvRound(g_hist.at<float>(i-1))), Point(bin_w*(i), hist_j - cvRound(g_hist.at<float>(i))), Scalar(255,0,0),2,8,0);

    }
    //save the result into an image
    img resu = img(histo);
    size_t pos = filename.find_last_of('/');
    filename = filename.substr(pos+1);
    filename = "histogram_" + filename;
    resu.save(filename);
    cout<<"The file "<<filename<< " has been created."<<endl;
}