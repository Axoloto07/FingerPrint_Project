#include "../include/check_convergence.hpp"


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
                //is lesser than this threshold, we increase the counter
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