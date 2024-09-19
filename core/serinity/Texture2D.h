/******************************************************************************
* File name: Texture2D.h    File author(s): Elysium Hosack                    *
*                                                                             *
* File description:                                                           *
*                                                                             *
*                                                                             *
*                                                                             *
* Created: 9/19/2024        Edited last: 9/19/2024                            *
******************************************************************************/

#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "../ew/external/glad.h"
#include <glm/glm.hpp>
#include "../ew/external/stb_image.h"

#include <string>
#include <fstream>
#include <sstream>


namespace serinity {

    class Texture2D {
        unsigned int ID;
        int width, height;
    public:
        Texture2D(const char* filePath, int filterMode, int wrapMode);
        ~Texture2D();
        void Bind(unsigned int slot = 0);
    };

} // serinity

#endif //TEXTURE2D_H
