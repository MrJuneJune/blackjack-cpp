#include "./texture.h"
#include "../utils/util.h"

Texture::Texture(const char* image, GLenum texType) {
  int width, height;
  uint8_t* data = loadWebPImage(image, &width, &height);

  glGenTextures(1, &ID);
  glBindTexture(GL_TEXTURE_2D, ID);

  // Upload the image data to the texture
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, data);

  // Set texture parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  // Bind texture unit
  glActiveTexture(GL_TEXTURE0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit) {
  // Gets the location of the uniform
  GLuint texUni = glGetUniformLocation(shader.ID, uniform);
  // Shader needs to be activated before changing the value of a uniform
  shader.Activate();
  // Sets the value of the uniform
  glUniform1i(texUni, unit);
}

void Texture::Bind() {
  glBindTexture(type, ID);
}

void Texture::Unbind() {
  glBindTexture(type, 0);
}

void Texture::Delete() {
  glDeleteTextures(1, &ID);
}
