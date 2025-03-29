# Source Folder

## Overview

The `src` folder contains all the source code files for the Antenna Mapping project. These files implement the core functionalities of the project, including reading input files, processing antenna data, calculating effect positions, and handling user interactions through the menu.

## File Structure

- `src/`: Directory containing all source code files.
    - `main.c`: The main entry point of the program.
    - `menu.c`: Implementation of menu-related functions.
    - `io_ops.c`: Implementation of input/output operations, including file reading and writing.
    - `antenna.c`: Implementation of antenna-related functions.
    - `antenna_effect.c`: Implementation of antenna effect calculation functions.

## Description of Files

### `main.c`

This file contains the `main` function, which initializes the program, displays the main menu, and handles user input.

### `menu.c`

This file implements the functions related to displaying the menu, getting user choices, and handling those choices.

### `antenna.c`

This file contains functions for managing antennas, including loading antennas from a file, inserting new antennas, removing existing antennas, and printing the current antenna map.

### `antenna_effect.c`

This file implements the functions for calculating and managing the effect positions of antennas based on the given formulas.

## Usage

1. Ensure all source files are in the `src` folder.
2. Build the project using the provided `CMakeLists.txt` file.
3. Run the executable generated after building the project.