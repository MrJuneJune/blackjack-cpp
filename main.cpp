#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <webp/decode.h>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>
#include "graphics/shader/ebo.h"
#include "graphics/shader/shader.h"
#include "graphics/shader/texture.h"
#include "graphics/shader/vao.h"
#include "graphics/shader/vbo.h"
#include "graphics/utils/util.h"

// Variables to store the camera's position
float camera_x = 0.0f, camera_y = 0.0f;
float scroll_sensitivity = 0.1f;

// Scroll callback function to handle mouse wheel scroll
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
  camera_y += yoffset * scroll_sensitivity;  // Scroll vertically
  camera_x += xoffset * scroll_sensitivity;  // Scroll horizontally
}

float vertices[] = {
    // positions         // texture coords
    1.0f,  1.0f,  0.0f, 1.0f, 1.0f,  // top right
    1.0f,  -1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,  // bottom left
    -1.0f, 1.0f,  0.0f, 0.0f, 1.0f   // top left
};
unsigned int indices[] = {
    0, 1, 3,  // first triangle
    1, 2, 3   // second triangle
};

int main() {
  // Initialize GLFW
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  // Set OpenGL version to 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create a window
  GLFWwindow* window =
      glfwCreateWindow(800, 600, "Blackjack game", nullptr, nullptr);
  if (!window) {
    std::cerr << "Failed to create window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // Initialize GLEW
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cerr << "Failed to initialize GLEW" << std::endl;
    return -1;
  }

  // scrolling
  glfwSetScrollCallback(window, scroll_callback);

  // Compile the vertex and fragment shaders from files
  Shader shader("./src/graphics/vertex_shader.glsl",
                "./src/graphics/fragment_shader.glsl");

  // Generates Vertex Array Object and binds it
  VAO VAO1;
  VAO1.Bind();

  // Generates Vertex Buffer Object and links it to vertices
  VBO VBO1(vertices, sizeof(vertices));
  // Generates Element Buffer Object and links it to indices
  EBO EBO1(indices, sizeof(indices));

  // Links VBO attributes such as coordinates and colors to VAO
  VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
  VAO1.LinkAttrib(VBO1, 1, 2, GL_FLOAT, 5 * sizeof(float),
                  (void*)(3 * sizeof(float)));

  // Unbind all to prevent accidentally modifying them
  VAO1.Unbind();
  VBO1.Unbind();
  EBO1.Unbind();

  // Load the WebP texture
  int img_width, img_height;
  // Texture
  Texture background("/Users/mingtongyuan/Downloads/background.webp",
                     GL_TEXTURE_2D);

  background.Bind();
  background.texUnit(shader, "texture1", 0);

  // Render loop
  while (!glfwWindowShouldClose(window)) {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Apply camera transformations (translate the image)
    glPushMatrix();
    glTranslatef(-camera_x, -camera_y,
                 0.0f);  // Adjust translation based on camera position

    // Tell OpenGL which Shader Program we want to use
    shader.Activate();

    // Bind texture and draw the quad
    background.current_x_ += 1;
    background.current_y_ += 1;

    background.render();
    background.Bind();

    // Bind the VAO so OpenGL knows to use it
    VAO1.Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glPopMatrix();
    // Swap buffers and poll events
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Delete all the objects we've created
  VAO1.Delete();
  VBO1.Delete();
  EBO1.Delete();
  shader.Delete();
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
