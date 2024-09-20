#pragma once
#include "shader.h"

class Texture {
 public:
  GLuint ID;
  GLenum type;
  Texture(const char* image, GLenum texType);

  // Assigns a texture unit to a texture
  void texUnit(Shader& shader, const char* uniform, GLuint unit);
  // Binds a texture
  void Bind();
  // Unbinds a texture
  void Unbind();
  // Deletes a texture
  void Delete();
};
