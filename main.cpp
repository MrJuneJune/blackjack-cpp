#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdint>
#include <iostream>
#include <string>
#include "gameplay/characters/player.h"
#include "gameplay/props/deck.h"
#include "graphics/utils/util.h"
#include "io/key_action.h"
#include "state/game.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

int main() {
  blackjack::Player player;
  blackjack::Player dealer;
  blackjack::Deck deck;

  blackjack::Game game(&player, &dealer, &deck);

  game.send_action(blackjack::KeyAction::HIT);
  game.send_action(blackjack::KeyAction::STAND);

  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  GLFWwindow* window =
      glfwCreateWindow(800, 600, "Card Game", nullptr, nullptr);
  if (!window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  while (!glfwWindowShouldClose(window)) {
    drawCard(0.7f, -0.5f, 0.3f, 0.5f, "10", "diamonds");

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}
