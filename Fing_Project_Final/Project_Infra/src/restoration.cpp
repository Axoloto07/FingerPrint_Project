#include "../include/restoration.hpp"

//----------------Restoration---------------------

map<int, patch> dic_patch(img &image, std::map<std::pair<int, int>,int> mask, int nb_patch,  int size){

    // Initializing the random seed
    srand (time(NULL));

    // Initializing an empty dictionary
    map<int, patch> dico = {};

    // Looping on nb_patch
    for (int k = 0; k < nb_patch; k++){

    // Generating random coordonate in the image
        int i_coor = rand()%(image.get_rows()-size+1) + (size/2);
        int j_coor = rand()%(image.get_cols()-size+1) + (size/2);

        // Iterating on each pixel of the patch
        for (int i=0; i<size; i++){
            for (int j=0; j<size; j++){

                // We check that the patch that we've randomly choosen is not
                // on the part of the image to restor 
                if (mask.count(std::make_pair<int, int>(i_coor - size/2 + i, j_coor - size/2 + j)) == 1){
                    k -= 1;
                    goto pass;
                }

            }
        }

        // If the patch is correct we insert it in the dictionary
        dico.insert({k, patch(image, size, i_coor, j_coor)});

        // Otherwise we jump to pass
        pass:;
    }

    // Return the full dictionary
    return dico;

}



int best_patch(patch p, patch p_mask, map<int, patch> dico){

    // Initialization of minimum distance to perform a minimum search algorithm
    double min_dist = 1.0;
    double dist = 0.0;
    int best_pix = 0;

    // Iterating on all the entry of the dictionary
    for(map<int, patch>::iterator i=dico.begin(); i!=dico.end(); i++){

        // Compute the distance
        dist = p.dist((i->second).mult(p_mask));

        // Updating the best distance
        if(dist<min_dist){

            min_dist = dist;
            best_pix = i->second.get_pix_val(i->second.get_cols()/2, i->second.get_rows()/2);

        }

    }

    // Returning the middle pixel of the minimum distance patch
    return best_pix;

}


void restor_line(img &image, std::map<std::pair<int, int>,int> mask, int nb_patch, int size){

    // Creating the comparison dictionary
    map<int, patch> dic = dic_patch(image, mask, nb_patch, size);
    cout<<"[Dictionnary successfully created]"<<endl;

    // Iterating on the pixel of the mask
    for (std::map<std::pair<int, int>,int>::iterator it=mask.begin(); it!=mask.end(); it++){


            // Create the patch from the neighbor pixels
            patch p = patch(image, size, (it->first).first, (it->first).second);
            patch p_mask = patch(mask, size, (it->first).first, (it->first).second);
            // Modify the pixel with the best matching pixel
            image.modif_pix((it->first).first, (it->first).second, best_patch(p.mult(p_mask), p_mask, dic));

    }

}



// void restor_circle(img &image, img &mask, int nb_patch, int size){

//     // Creating the comparison dictionary
//     map<int, patch> dic = dic_patch(image, mask, nb_patch, size);
//         cout<<"[Dictionnary successfully created]"<<endl;

//     // Iterating on the pixel of the image in a spiral shape
    

// }
