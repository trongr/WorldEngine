#include <fstream>
#include <vector>
#include "GLSLProgram.h"
#include "Errors.h"

namespace GameEngine {
    GLSLProgram::GLSLProgram() : _numAttrs(0), _programID(0), _vertexShaderID(0), _fragmentShaderID(0)
    {

    }


    GLSLProgram::~GLSLProgram()
    {
    }

    void GLSLProgram::compileshaders(const std::string &vertexShaderFilepath, const std::string &fragmentShaderFilepath){
        _programID = glCreateProgram();

        _vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        if (_vertexShaderID == 0){
            fatalerror("couldn't create vertex shader");
        }

        _fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        if (_fragmentShaderID == 0){
            fatalerror("couldn't create fragment shader");
        }

        compileshader(vertexShaderFilepath, _vertexShaderID);
        compileshader(fragmentShaderFilepath, _fragmentShaderID);
    }

    void GLSLProgram::linkshaders(){
        //Attach our shaders to our program
        glAttachShader(_programID, _vertexShaderID);
        glAttachShader(_programID, _fragmentShaderID);

        //Link our program
        glLinkProgram(_programID);

        //Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

            //The maxLength includes the NULL character
            std::vector<GLchar> errorLog(maxLength);
            glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

            //We don't need the program anymore.
            glDeleteProgram(_programID);
            //Don't leak shaders either.
            glDeleteShader(_vertexShaderID);
            glDeleteShader(_fragmentShaderID);

            std::printf("%s\n", &(errorLog[0]));
            fatalerror("couldn't link shader");
        }

        //Always detach shaders after a successful link.
        glDetachShader(_programID, _vertexShaderID);
        glDetachShader(_programID, _fragmentShaderID);
        glDeleteShader(_vertexShaderID);
        glDeleteShader(_fragmentShaderID);
    }

    void GLSLProgram::compileshader(const std::string filepath, GLuint& id){
        std::ifstream vertexFile(filepath);
        if (vertexFile.fail()){
            perror(filepath.c_str());
            fatalerror("couldn't open " + filepath);
        }

        std::string fileContents = "";
        std::string line;
        while (std::getline(vertexFile, line)){
            fileContents += line + "\n";
        }
        vertexFile.close();

        const char* contentsptr = fileContents.c_str();
        glShaderSource(id, 1, &contentsptr, nullptr);

        glCompileShader(id);

        GLint success = 0;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<char> errorLog(maxLength);
            glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

            // Provide the infolog in whatever manor you deem best.
            // Exit with failure.
            glDeleteShader(id); // Don't leak the shader.

            std::printf("%s\n", &(errorLog[0]));
            fatalerror("couldn't compile shader " + filepath);
        }
    }

    void GLSLProgram::addAttr(const std::string& attrName){
        glBindAttribLocation(_programID, _numAttrs++, attrName.c_str());
    }

    void GLSLProgram::use(){
        glUseProgram(_programID);
        for (int i = 0; i < _numAttrs; i++){
            glEnableVertexAttribArray(i);
        }
    }

    void GLSLProgram::unuse(){
        glUseProgram(0);
        for (int i = 0; i < _numAttrs; i++){
            glDisableVertexAttribArray(i);
        }
    }

    GLint GLSLProgram::getUniformLocation(const std::string& uniformName){
        GLint location = glGetUniformLocation(_programID, uniformName.c_str());
        if (location == GL_INVALID_INDEX){
            fatalerror("uniform " + uniformName + " not found in shader");
        }
        return location;
    }
}