#include "../include/geometrical_op.hpp"

//function to test the rotation of an image
int main(){
    img rotation("../Project_Infra/images/strong_finger.png");

    img flipped = transform(rotation,2.0/3.0,-1.0/3.0,0,1.0/3.0,4.0/3.0,0);


    flipped.save("verif_results/rotation.png");
    return 0;
}
