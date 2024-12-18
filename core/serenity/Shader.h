﻿/******************************************************************************
* File name: Shader.h       File author(s): Elysium Hosack                    *
*                                                                             *
* File description: Header for my learnopengl.com shader class. Includes      *
* methods specifically related to reading the shader from file, setting it to *
* be used, and modifying uniforms within each shader.                         *
*                                                                             *
* Created: 9/13/2024        Edited last: 9/19/2024                            *
******************************************************************************/

#ifndef SHADER_H
#define SHADER_H


#include "../ew/external/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// #include "../ew/external/stb_image.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


namespace serinity {
    // Shader class header from learnopengl.com
    class Shader {
        unsigned int ID;
    public:

        Shader(const char* vertexPath, const char* fragmentPath);

        void use();

        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;

        void setSampler2D(const std::string &name, unsigned int value) const;
        void setVec2(const std::string &name, glm::vec2 value) const;
        void setVec3(const std::string &name, glm::vec3 value) const;
        void setVec3(const std::string &name, float x, float y, float z) const;
        void setMat4(const std::string &name, glm::mat4 value) const;
    };

} // serenity

#endif //SHADER_H
