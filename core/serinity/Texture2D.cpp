/******************************************************************************
* File name: Texture2D.cpp  File author(s): Elysium Hosack                    *
*                                                                             *
* File description:                                                           *
*                                                                             *
*                                                                             *
*                                                                             *
* Created: 9/19/2024        Edited last: 9/19/2024                            *
* Key Methods: Texture2D constructor and destructor                           *
*              Bind()                                                         *
******************************************************************************/

#include "Texture2D.h"

namespace serinity {
    Texture2D::Texture2D(const char *filePath, int filterMode, int wrapMode) {
        unsigned int texture;
        glGenTextures(1, &texture);

        //set wrap mode
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);

        //set filter mode
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);

        int nrChannels;
        unsigned char *data = stbi_load(filePath, &width, &height, &nrChannels, 0);

        if(data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "Failed to load texture" << std::endl;
        }

        ID = texture;
        stbi_image_free(data);

    }

    void Texture2D::Bind(unsigned int slot) {
        glActiveTexture(GL_TEXTURE0+slot);

        glBindTexture(GL_TEXTURE_2D, ID);
    }

    Texture2D::~Texture2D() = default;



} // serinity