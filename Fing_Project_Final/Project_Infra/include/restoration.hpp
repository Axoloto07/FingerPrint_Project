#ifndef RESTORATION_HPP
#define RESTORATION_HPP

#include "class_patch.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief Sample numerous random patches from an image to restor and put them in a dictionary
 * 
 * @param image The image to sample the patches from
 * @param mask The mask to avoid sampling from the missing pixels
 * @param nb_patch The number of patches to sample
 * @param size The size of the patches to sample
 * @return map<int, patch> A dictionary with int as the key and patches as a object
 */
map<int, patch> dic_patch(img &image, std::map<std::pair<int, int>,int> mask, int nb_patch,  int size);

/**
 * @brief Find the patch that minimize the distance to p among a dictionnary
 * 
 * @param p The patch we want to minimize the distance to
 * @param dico The dictionary among wich we want to find the patche minimizing the distance
 * @return int The value of the middle pixel of the best patch
 */
int best_patch(patch p, patch m, map<int, patch> dico);

/**
 * @brief Performe a restoration of an image with missing pixels
 * 
 * @param image The image we want to restor
 * @param mask The mask indicating wich pixel to restor
 * @param nb_patch The number of patches to sample for the restoration process
 * @param size The size of the patches to use for the resoration process
 */
void restor_line(img &image, std::map<std::pair<int, int>,int> mask, int nb_patch, int size);


// void restor_circle(img &image, img &mask, int nb_patch, int size);

#endif
