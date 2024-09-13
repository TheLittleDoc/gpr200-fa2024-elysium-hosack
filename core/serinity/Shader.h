//
// Created by elysium.hosack on 9/13/2024.
//

#ifndef SERINITYSHADER_H
#define SERINITYSHADER_H


#include "../ew/external/glad.h"
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


namespace serinity {

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

#endif //SERINITYSHADER_H
