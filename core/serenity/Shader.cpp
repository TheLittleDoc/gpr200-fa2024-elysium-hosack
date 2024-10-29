/******************************************************************************
* File name: Shader.cpp     File author(s): Elysium Hosack                    *
*                                                                             *
* File description: Implementation of learnopengl.com's shader class tutorial *
* in order to read shaders from file and present them to use elsewhere        *
*                                                                             *
*                                                                             *
* Created: 9/13/2024        Edited last: 9/16/2024                            *
* Key Methods: Shader() Constructor                                           *
*              use()                                                          *
******************************************************************************/

#include "Shader.h"

namespace serinity {
    Shader::Shader(const char *vertexPath, const char *fragmentPath) {
        std::ifstream vertexFile;
        std::ifstream fragmentFile;

        std::string vertexCode;
        std::string fragmentCode;

        vertexFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fragmentFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            vertexFile.open(vertexPath);
            fragmentFile.open(fragmentPath);

            std::stringstream vShaderStream, fShaderStream;

            vShaderStream << vertexFile.rdbuf();
            fShaderStream << fragmentFile.rdbuf();

            vertexFile.close();
            fragmentFile.close();

            vertexCode   = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch(std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }

        const char* vertexCodeC = vertexCode.c_str();
        const char * fragmentCodeC = fragmentCode.c_str();

        unsigned int vertex, fragment;
        int status;
        char infoLog[512];

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertexCodeC, nullptr);
        glCompileShader(vertex);
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &status);
        if(!status)
        {
            glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragmentCodeC, nullptr);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &status);
        if(!status)
        {
            glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        glGetProgramiv(ID, GL_LINK_STATUS, &status);
        if(!status)
        {
            glGetProgramInfoLog(ID, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        glDeleteShader(vertex);
        glDeleteShader(fragment);

    }
    void Shader::use() {
        glUseProgram(ID);
    }

    void Shader::setBool(const std::string &name, bool value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }

    void Shader::setInt(const std::string &name, int value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    void Shader::setFloat(const std::string &name, float value) const {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

    void Shader::setSampler2D(const std::string &name, unsigned int value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    void Shader::setMat4(const std::string &name, glm::mat4 value) const {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
        //std::cout << "Matrix: " << value[0][0] << std::endl;
    }

    void Shader::setVec2(const std::string &name, glm::vec2 value) const {
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
    }

    void Shader::setVec3(const std::string &name, glm::vec3 value) const {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
    }

    void Shader::setVec3(const std::string &name, float x, float y, float z) const {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(glm::vec3(x, y, z)));
    }
} // serenity