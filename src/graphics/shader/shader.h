#pragma once

#include <GL/glew.h>
#include <cerrno>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

std::string get_file_contents(const char* filename);

class Shader {
 public:
  // Reference ID of the Shader Program
  GLuint ID;
  Shader(const char* vertexFile, const char* fragmentFile);

  void Activate();
  void Delete();

 private:
  GLuint compile_shader(const char* filepath, GLenum shaderType);
};
