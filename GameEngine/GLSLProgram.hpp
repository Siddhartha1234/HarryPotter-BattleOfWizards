#pragma once

#include <GL/glew.h>
#include <string>
namespace GameEngine {
    class GLSLProgram
    {
    public:
        GLSLProgram();
        ~GLSLProgram();

        void compileShaders(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
        void linkShaders();

        void addAttribute(const std::string& attributeName);

        GLint getUniformLocation(const std::string& uniformName);

        void use();
        void unuse();

    private:
        // Variablen
        GLuint _programID;
        GLuint _vertexShaderID;
        GLuint _fragmentShaderID;
        int _numAttributes;

        // Methoden
        void compileShader(const std::string& shaderFile, GLuint shaderID);
    };

}
