#pragma once

#include <vector>
#include <iostream>
#include <GL/glew.h>

#include "../Utils/camera.h"
#include <glm/glm.hpp>
#include "../Utils/fileutils.h"

namespace Graphics {

    class Shader
    {
    private:
        GLuint shaderID;
        const char* vertp;
        const char* fragp;
    public:
        Shader(const char* vertpath, const char* fragpath) : vertp(vertpath), fragp(fragpath) { shaderID = load(); }
        ~Shader() { glDeleteProgram(shaderID); }

        GLint getUniformLocation(const GLchar* name) { return glGetUniformLocation(shaderID, name); }

        void setUniform1i(const GLchar* name, int value) { glUniform1i(getUniformLocation(name), value); }
        void setUnuform1iV(const GLint location, GLsizei count, const GLint *value) { glUniform1iv(location, count, value);}
        void setUniform1f(const GLchar* name, float value) { glUniform1f(getUniformLocation(name), value); }
        void setUniform2f(const GLchar* name, const glm::vec2& vector) { glUniform2f(getUniformLocation(name), vector.x, vector.y); }
        void setUniform3f(const GLchar* name, const glm::vec3& vector) { glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z); }
        void setUniform4f(const GLchar* name, const glm::vec4& vector) { glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w); }
        void setUniformMat4(const GLchar* name, const Graphics::Camera& matrix) { glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements); }

        void bind() const { glUseProgram(shaderID); }
        void unbind() const { glUseProgram(0); }
    private:
        GLuint load()
    {
        GLuint program = glCreateProgram();
        GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

        std::string vertStrSource = Utils::read_file(vertp);
        std::string fragStrSource = Utils::read_file(fragp);

        const char* vertSource = vertStrSource.c_str();
        const char* fragSource = fragStrSource.c_str();

        glShaderSource(vertex, 1, &vertSource, NULL);
        glCompileShader(vertex);

        GLint result;
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE)
        {
            GLint length;
            glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> error(length);
            glGetShaderInfoLog(vertex, length, &length, &error[0]);
            std::cout << &error[0] << std::endl;
            glDeleteShader(vertex);
            return 0;
        }

        glShaderSource(fragment, 1, &fragSource, NULL);
        glCompileShader(fragment);

        glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE)
        {
            GLint length;
            glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> error(length);
            glGetShaderInfoLog(fragment, length, &length, &error[0]);
            std::cout << &error[0] << std::endl;
            glDeleteShader(fragment);
            return 0;
        }

        glAttachShader(program, vertex);
        glAttachShader(program, fragment);

        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vertex);
        glDeleteShader(fragment);

        return program;
    }
    };
    
}
