#include "../include/image.hpp"


//function test to draw squares on the image
//test of the method modif_pix
int main(){

//#######################################################################
//GET THE INPUTS
//####################################################################### 

    img picture("../Project_Infra/images/clean_finger.png");

//#######################################################################
//DRAW RECTANGLES
//####################################################################### 

    //draw a white rectangle
    for (int i=100; i < 130; i++ ){
        for (int j=80; j<140; j++){
            picture.modif_pix(i,j,255);
        }

    }
    //draw a black rectangle
    for (int i=150; i < 230; i++ ){
        for (int j=150; j<200; j++){
            picture.modif_pix(i,j,0);
        }

    }
    
    picture.save("verif_results/squares.png");
return 0;
}