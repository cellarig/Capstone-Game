# Snake-Crossing Game Project

This is a repo for the Capstone project submission in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The provided templated code was modified and extended with texture rendering offered by SDL2 library.

---
## Expected Behavior

<img src="snake_game.gif"/>

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## Capstone Project Rubric

Following described rubric points addressed.

### 1. README (All Rubric Points REQUIRED)

* A README with instructions is included with the project [x]
* The README indicates which project is chosen []
* The README includes information about each rubric point addressed [x]

### 2. Compiling and Testing (All Rubric Points REQUIRED)

* The submission must compile and run []

### 3. Loops, Functions, I/O

* The project demonstrates an understanding of C++ functions and control structures [x]
* The project reads data from a file and process the data, or the program writes data to a file [x]
* The project accepts user input and processes the input [x]

### 4. Object Oriented Programming

* The project uses Object Oriented Programming techniques [x]
* Classes use appropriate access specifiers for class members [x]
* Class constructors utilize member initialization lists [x]
* Classes abstract implementation details from their interfaces []
* Classes encapsulate behavior []
* Classes follow an appropriate inheritance hierarchy []
* Overloaded functions allow the same function to operate on different parameters []
* Derived class functions override virtual base class functions []
* Templates generalize functions in the project []

### 5. Memory Management

* The project makes use of references in function declarations []
* The project uses destructors appropriately []
* The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate []
* The project follows the Rule of 5 []
* The project uses move semantics to move data, instead of copying it, where possible []
* The project uses smart pointers instead of raw pointers []

### 6. Concurrency

* The project uses multithreading []
* A promise and future is used in the project []
* A mutex or lock is used in the project []
* A condition variable is used in the project []
