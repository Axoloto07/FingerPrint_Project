#include "../include/class_image.hpp"

void test_rotation(){
    img rotation("images/strong_finger.png");

    img flipped = rotation.transform(2.0/3.0,-1.0/3.0,0,1.0/3.0,4.0/3.0,0);


    flipped.save("rotation.png");
}