#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

void drawCircle(float cx, float cy, float r, int num_segments);
void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
void drawHeart(float x, float y, float size);
void drawSpade(float x, float y, float size);
void drawDiamond(float x, float y, float size);
void drawClub(float x, float y, float size);
void drawNumber(float x, float y, float size);
void drawCard(float x, float y, float width, float height,
              const std::string& rank, const std::string& suit);
uint8_t* loadWebPImage(const char* filepath, int* width, int* height);
std::string load_file_as_string(const char* filepath);
