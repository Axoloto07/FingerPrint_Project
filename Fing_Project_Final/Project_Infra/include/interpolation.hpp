#ifndef INTERPOLATION_HPP
#define INTERPOLATION_HPP

#include "class_image.hpp"

        /**
         * @brief filling the white slots that appeared in the image upon geometric opertions using nearest neighbor interpolation method
         * 
         * @return img 
         */
        img nearest_interpolation(img &image);

        /**
         * @brief filling the white slots that appeared in the image upon geometric opertions using bilinear interpolation method
         * 
         * @return img 
         */
        img bilinear_interpolation(img &image);

#endif