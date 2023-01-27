#include "../include/restoration.hpp"

int main(){

    // We load the image to restor
    img image("../Project_Infra/images/clean_finger.png");
    std::cout<<"[Image Loaded]"<<std::endl;

    // We create the mask
    mask mask_o(image);

    // Creating a patch on our original image and on the mask
    for(int i = 150; i<180; i++){
        for(int j =100; j<130; j++){

            image.modif_pix(i, j, 255);
            mask_o.modif_pix(i, j, 0);
            mask_o.add_vect(std::make_pair(i, j));

        }

    }
    // for (int i = 0; i<10000; i++){
    // patch(image, 9, 150, 100).save("patch.png");
    // }
    std::cout<<"[Loss of information created]"<<std::endl;

    // image.save("img_to_restor_black.png");

    // The restoration process
    restor_line(image, mask_o, 1000, 9);
    std::cout<<"[Image restored successfully]"<<std::endl;

    image.save("img_restored_black_patch.png");
    mask_o.save("mask.png");

    return 0;
}




