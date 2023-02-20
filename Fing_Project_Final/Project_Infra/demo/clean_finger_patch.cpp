#include "../include/restoration.hpp"

int main(){

//#######################################################################
//GET THE INPUTS
//#######################################################################  
    std::cout<<"Please enter the name of the image. (ex : clean_finger.png)"<<std::endl;
    std::string path;
    std::cin>>path;
    img image("../Project_Infra/images/" + path);
    std::cout<<"[Image Loaded]"<<std::endl;



    int size_mask;
    int i;
    int j;
    int nb_patch;
    int size_patch;


    std::cout<<"Choose the size of the mask"<<std::endl;
    std::cin>>size_mask;

    std::cout<<"Choose the i coordonate of the mask"<<std::endl;
    std::cin>>i;

    std::cout<<"Choose the j coordonate of the mask"<<std::endl;
    std::cin>>j;

    std::cout<<"How many patches do you want to sample ?"<<std::endl;
    std::cin>>nb_patch;

    std::cout<<"What size of patch do you want ?"<<std::endl;
    std::cin>>size_patch;

    
//#######################################################################
//LINE BY LINE RESTORATION
//#######################################################################

    mask mask_o(image);
    
    for(int i_coor = i ; i_coor<i+size_mask; i_coor++){
        for(int j_coor =j; j_coor<j+size_mask; j_coor++){
            image.modif_pix(i_coor, j_coor, 0);
            mask_o.modif_pix(i_coor, j_coor, 0);
            mask_o.add_vect(std::make_pair(i_coor, j_coor));
        }
    }
    std::map<int, patch> dic = dic_patch(image, mask_o, nb_patch, size_patch);
    restor_patch(image, mask_o, nb_patch, size_patch, dic);
    image.save("demo_results/img_restored_black_line_patch.png");


//#######################################################################
//SPIRAL SCHEME RESTORATION
//#######################################################################

    mask mask_o2(image);
    int dir_i = 0;
    int dir_j = 1;
    int i_or = i;
    int j_or = j;
    int iter = 0;

    // The following lines perform a spiral iteration from the outside of a square
    for (int k = 0; k<size_mask*size_mask; k++){
        image.modif_pix(i, j, 0);
        mask_o2.modif_pix(i, j, 0);
        mask_o2.add_vect(std::make_pair(i, j));
        if ((i == i_or + iter)&&(j == j_or + size_mask-1-iter)){
            dir_i = 1;
            dir_j = 0;
        } else if ((i == i_or + size_mask -1 - iter)&&(j == j_or + size_mask-1-iter))
        {
            dir_i = 0;
            dir_j = -1;
        } else if ((i == i_or + size_mask -1 - iter)&&(j == j_or + iter))
        {
            dir_i = -1;
            dir_j = 0;
        } else if ((i == i_or + iter + 1)&&(j == j_or + iter))
        {
            dir_i = 0;
            dir_j = 1;
            iter++;
        }
        i += dir_i;
        j += dir_j;
        
    }

    restor_patch(image, mask_o2, nb_patch, size_patch, dic);
    image.save("demo_results/img_restored_black_spiral_patch.png");

    return 0;
}




