#pragma once
#include <string>
#include <GL/glew.h>

namespace GameEngine {
    class GLSLProgram
    {
    public:
        GLSLProgram();
        ~GLSLProgram();
        void compileshaders(const std::string &vertexShaderFilepath, const std::string &fragmentShaderFilepath);
        void linkshaders();
        void addAttr(const std::string& attrName);
        void use();
        void unuse();
        GLint getUniformLocation(const std::string& uniformName);
    private:
        int _numAttrs;
        GLuint _programID;
        GLuint _vertexShaderID;
        GLuint _fragmentShaderID;

        void compileshader(const std::string filepath, GLuint& id);
    };
}