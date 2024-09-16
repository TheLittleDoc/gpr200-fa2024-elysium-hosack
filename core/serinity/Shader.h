/******************************************************************************
* File name: Shader.h       File author(s): Elysium Hosack                    *
*                                                                             *
* File description: Header for my learnopengl.com shader class. Includes      *
* methods specifically related to reading the shader from file, setting it to *
* be used, and modifying uniforms within each shader.                         *
*                                                                             *
* Created: 9/13/2024        Edited last: 9/13/2024                            *
******************************************************************************/

#ifndef SHADER_H
#define SHADER_H


#include "../ew/external/glad.h"
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


namespace serinity {
    // Shader class header from learnopengl.com
    class Shader {
    public:
        unsigned int ID;

        Shader(const char* vertexPath, const char* fragmentPath);

        void use();

        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;

    };

} // serinity

#endif //SHADER_H
