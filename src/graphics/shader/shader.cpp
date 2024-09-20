#include "./shader.h"
#include "./utils/util.h"

// Constructor that build the Shader Program from 2 different shaders
Shader::Shader(const char* vertexFile, const char* fragmentFile) {
  // Compile the vertex and fragment shaders from files
  GLuint vertexShader =
      compile_shader("./src/graphics/vertex_shader.glsl", GL_VERTEX_SHADER);
  GLuint fragmentShader =
      compile_shader("./src/graphics/fragment_shader.glsl", GL_FRAGMENT_SHADER);

  // Create Shader Program Object and get its reference
  ID = glCreateProgram();

  // Attach the Vertex and Fragment Shaders to the Shader Program
  glAttachShader(ID, vertexShader);
  glAttachShader(ID, fragmentShader);

  // Wrap-up/Link all the shaders together into the Shader Program
  glLinkProgram(ID);

  // Delete the now useless Vertex and Fragment Shader objects
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

// Activates the Shader Program
void Shader::Activate() {
  glUseProgram(ID);
}

// Deletes the Shader Program
void Shader::Delete() {
  glDeleteProgram(ID);
}

GLuint Shader::compile_shader(const char* filepath, GLenum shaderType) {
  std::string shaderSource = load_file_as_string(filepath);
  const char* shaderCode = shaderSource.c_str();

  GLuint shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &shaderCode, nullptr);
  glCompileShader(shader);

  GLint success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetShaderInfoLog(shader, 512, nullptr, infoLog);
    std::cerr << "Error: Shader compilation failed for " << filepath << "\n"
              << infoLog << std::endl;
    return 0;
  }

  return shader;
}
