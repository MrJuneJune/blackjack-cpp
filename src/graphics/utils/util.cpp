#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

// Using old API, CPU usages of it
void drawCircle(float cx, float cy, float r, int num_segments) {
  glBegin(GL_TRIANGLE_FAN);
  glVertex2f(cx, cy);  // Center of circle
  for (int i = 0; i <= num_segments; i++) {
    float theta = 2.0f * 3.1415926f * static_cast<float>(i) /
                  static_cast<float>(num_segments);
    float x = r * cosf(theta);  // Calculate the x component
    float y = r * sinf(theta);  // Calculate the y component
    glVertex2f(x + cx, y + cy);
  }
  glEnd();
}

// Utility function to draw a filled triangle
void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
  glBegin(GL_TRIANGLES);
  glVertex2f(x1, y1);
  glVertex2f(x2, y2);
  glVertex2f(x3, y3);
  glEnd();
}

// Draw the heart suit (simple example)
void drawHeart(float x, float y, float size) {
  drawCircle(x - size / 2, y, size / 2, 30);
  drawCircle(x + size / 2, y, size / 2, 30);
  drawTriangle(x - size, y, x + size, y, x, y - size);
}

// Draw the spade suit
void drawSpade(float x, float y, float size) {
  drawCircle(x, y + size / 2, size / 2, 30);  // Circle at the top
  drawTriangle(x - size, y, x + size, y, x,
               y + size);  // Triangle at the bottom
}

// Draw the diamond suit
void drawDiamond(float x, float y, float size) {
  drawTriangle(x - size / 2, y, x, y + size, x + size / 2, y);
  drawTriangle(x - size / 2, y, x, y - size, x + size / 2, y);
}

// Draw the club suit
void drawClub(float x, float y, float size) {
  drawCircle(x - size / 2, y + size / 4, size / 3, 30);
  drawCircle(x + size / 2, y + size / 4, size / 3, 30);
  drawCircle(x, y + size / 2, size / 3, 30);
  drawTriangle(x - size / 4, y - size / 4, x + size / 4, y - size / 4, x, y);
}

// Draw a simple "10" as two vertical lines (as a placeholder for numbers)
void drawNumber(float x, float y, float size) {
  glBegin(GL_LINES);
  glVertex2f(x, y);
  glVertex2f(x, y + size);

  glVertex2f(x + size / 2, y);
  glVertex2f(x + size / 2, y + size);
  glEnd();
}

// Draw a card
void drawCard(float x, float y, float width, float height,
              const std::string& rank, const std::string& suit) {
  // Draw card rectangle
  glColor3f(1.0f, 1.0f, 1.0f);  // White color for card background
  glBegin(GL_QUADS);
  glVertex2f(x, y);
  glVertex2f(x + width, y);
  glVertex2f(x + width, y + height);
  glVertex2f(x, y + height);
  glEnd();

  // Draw border
  glColor3f(0.0f, 0.0f, 0.0f);  // Black border
  glBegin(GL_LINE_LOOP);
  glVertex2f(x, y);
  glVertex2f(x + width, y);
  glVertex2f(x + width, y + height);
  glVertex2f(x, y + height);
  glEnd();

  glColor3f(0.0f, 0.0f, 0.0f);
  drawNumber(x + 0.05f * width, y + 0.85f * height, 0.1f * height);

  if (suit == "hearts") {
    glColor3f(1.0f, 0.0f, 0.0f);
    drawHeart(x + width / 2, y + height / 2, 0.2f * height);
  } else if (suit == "spades") {
    glColor3f(0.0f, 0.0f, 0.0f);
    drawSpade(x + width / 2, y + height / 2, 0.2f * height);
  } else if (suit == "diamonds") {
    glColor3f(1.0f, 0.0f, 0.0f);
    drawDiamond(x + width / 2, y + height / 2, 0.2f * height);
  } else if (suit == "clubs") {
    glColor3f(0.0f, 0.0f, 0.0f);
    drawClub(x + width / 2, y + height / 2, 0.2f * height);
  }
}
