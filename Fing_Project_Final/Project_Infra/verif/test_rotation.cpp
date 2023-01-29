#include "../include/image.hpp"

//function to test the rotation of an image
void test_rotation(){
    img rotation("../Project_Infra/images/strong_finger.png");

    img flipped = rotation.transform(2.0/3.0,-1.0/3.0,0,1.0/3.0,4.0/3.0,0);


    flipped.save("verif_results/rotation.png");
}