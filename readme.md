# Blackjack

## Introduction

Blackjack is a console-based game created using C++ for educational purposes. This project demonstrates:

- Usage of **unique pointers** and pointer ownership concepts.
- General structure and organization of a C++ project.
- Implementation of **modern C++** features and best practices.
- How to compile a project using **CMake**.

## Prerequisites

- **CMake**: For configuring the build process.
- **Make**: For compiling the project using the provided Makefile.
- **C++ Compiler**: A compiler that supports C++17 or later.

## How to Build and Run

Clone the repository and navigate to the project directory:

```bash
git clone https://github.com/MrJuneJune/blackjack-cpp.git
cd blackjack
```

### Build Using CMake

```bash
mkdir build
cd build
cmake ..
./blackjack
```

### Build Using Make

```bash
make
./build/blackjack
```

## How to Play

- **Start the Game**: Run the executable to begin a new game.
- **Player Actions**:
  - **Hit**: Draw a card to add to your hand.
  - **Stand**: End your turn without drawing.
- **Objective**: Achieve a hand value as close as possible to 21 without exceeding it to beat the dealer.

## TODO / Future Ideas

- **User Interface**: Implement a graphical UI using libraries like GLFW.
- **API Integration**: Expose game functionalities through an API for external entities.
- **Networking**: Add multiplayer support over a network.
- **Testing**: Implement unit tests for better reliability.
- **Documentation**: Generate documentation using tools like Doxygen.

## Contributions

Contributions are welcome! Feel free to open issues or submit pull requests for improvements and bug fixes.

## License

This project is open-source and available under the [MIT License](LICENSE).
