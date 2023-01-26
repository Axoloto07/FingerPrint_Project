#ifndef CLASS_PATCH
#define CLASS_PATCH


#include <unordered_map>
#include "class_image.hpp"




class patch : public img{

    public:
        /**
         * @brief Construct a new patch object
         * 
         * @param image The image in which we want to sample the patch
         * @param size The size of the patch (length of the square side)
         * @param ci The i coordonate in the original image (will be the center of the patch)
         * @param cj The j coordonate in the original image (will be the center of the patch)
         */
        patch(img image, int size, int ci, int cj);

        /**
         * @brief Default constructor for a patch
         * 
         */
        patch();

        /**
         * @brief Construct a new empty patch object
         * 
         * @param rows The number of rows
         * @param cols The number of columns
         */
        patch(int rows, int cols);

        /**
         * @brief Construct a new patch object with only 1 and 0 in it
         * 
         * @param ci The i coordonate in the original image (will be the center of the patch)
         * @param cj The j coordonate in the original image (will be the center of the patch)
         * @param unordered_map<std::vector<int>,int> The dictionnary with the pixel of the mask
         */
        patch(std::map<std::pair<int, int>,int> mask, int ci, int cj, int size);

        /**
         * @brief Calculat the distance between two images using mean square error
         * 
         * @param p the patch with which we want to compute the distance
         * @return float The distance beetween the two patches
         */
        double dist(patch p);

        /**
         * @brief Perform an out of place multiplication coefficient by coefficient
         * 
         * @param p The patch with which we want to perform the multiplication
         * @return patch A new patches were the multiplication has been performed
         */
        patch mult(patch p);


};






#endif
