#include "GLSLProgram.hpp"


#include <vector>

#include "Errors.hpp"
#include "utility.hpp"


namespace GameEngine {
    GLSLProgram::GLSLProgram() : _programID(0), _vertexShaderID(0) ,_fragmentShaderID(0), _numAttributes(0){
    }


    GLSLProgram::~GLSLProgram(){
        if(_programID != 0)
            glDeleteProgram(_programID);
    }

    void GLSLProgram::compileShaders(const std::string& vertexShaderFile, const std::string& fragmentSahderFile){
        _programID= glCreateProgram();

        _vertexShaderID= glCreateShader(GL_VERTEX_SHADER);
        if(_vertexShaderID == 0){
            fatalError("Could not create the vertex Shader");
        }

        _fragmentShaderID= glCreateShader(GL_FRAGMENT_SHADER);
        if(_fragmentShaderID == 0){
            fatalError("Could not create the fragment Shader");
        }

        compileShader(vertexShaderFile, _vertexShaderID);
        compileShader(fragmentSahderFile, _fragmentShaderID);
    }

    void GLSLProgram::compileShader(const std::string& shaderFile, GLuint shaderID){
        std::string fileContent= readFile(shaderFile);
        const char* shaderSource= fileContent.c_str();
        glShaderSource(shaderID, 1,&shaderSource, nullptr);
        glCompileShader(shaderID);
        GLint isCompiled= 0;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);

        if(isCompiled == GL_FALSE){
            GLint maxLength= 0;
            glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<char> errorLog(maxLength);
            glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);

            glDeleteShader(shaderID);

            std::printf("%s\n", &(errorLog[0]));
            fatalError("Shader "+ shaderFile +" failed to compile");
        }
    }

    void GLSLProgram::linkShaders(){
        glAttachShader(_programID, _vertexShaderID);
        glAttachShader(_programID, _fragmentShaderID);

        GLint isLinked= 0;
        glLinkProgram(_programID);

        glGetProgramiv(_programID, GL_LINK_STATUS, &isLinked);
        if(isLinked == GL_FALSE){
            GLint maxLength= 0;
            glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<char> errorLog(maxLength);
            glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

            glDeleteProgram(_programID);

            glDeleteShader(_vertexShaderID);
            glDeleteShader(_fragmentShaderID);

            std::printf("%s\n", &(errorLog[0]));
            fatalError("Shaders failed to link!");
        }

        glDetachShader(_programID, _vertexShaderID);
        glDetachShader(_programID,_fragmentShaderID);
        glDeleteShader(_vertexShaderID);
        glDeleteShader(_fragmentShaderID);
    }

    void GLSLProgram::addAttribute(const std::string& attributeName){
        glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
    }

    GLint GLSLProgram::getUniformLocation(const std::string& uniformName){
        GLint location= glGetUniformLocation(_programID, uniformName.c_str());
        if(location == GL_INVALID_INDEX){
            fatalError("Uniform "+ uniformName +" not found in shader!");
        }

        return location;
    }

    void GLSLProgram::use(){
        glUseProgram(_programID);
        for (int i = 0; i < _numAttributes; i++){
            glEnableVertexAttribArray(i);
        }
    }

    void GLSLProgram::unuse(){
        glUseProgram(0);
        for (int i = 0; i < _numAttributes; i++){
            glDisableVertexAttribArray(i);
        }
    }
}
