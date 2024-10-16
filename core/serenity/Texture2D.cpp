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
#include <string>
#include <iostream>

namespace serinity {
    Texture2D::Texture2D(const char *filePath, int filterMode, int wrapMode) {
        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);

        int width, height, nrChannels;

        unsigned char *data = stbi_load(filePath, &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
        std::cout << "Texture loaded from " << filePath << " with ID " << ID << std::endl;

    }

    void Texture2D::Bind(int slot) {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, this->ID);

    }

    void Texture2D::SetActive() {
        glBindTexture(GL_TEXTURE_2D, this->ID);
    }



    Texture2D::~Texture2D() {
        std::cout << "Deleting texture with ID " << ID << std::endl;
    }

    //copy constructor

    Texture2D::Texture2D(const Texture2D &other) {
        std::cout << "Copying texture with ID " << other.ID << std::endl;
        this->ID = other.ID;
        this->width = other.width;
        this->height = other.height;
    }



} // serenity