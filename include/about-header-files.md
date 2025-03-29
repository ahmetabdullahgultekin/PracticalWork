# Include Folder

## Overview

The `include` folder contains all the header files for the Antenna Mapping project. These files declare the functions and data structures used throughout the project, providing the necessary interfaces for the source code files.

## File Structure

- `include/`: Directory containing all header files.
    - `menu.h`: Header file for the `menu.c` file.
    - `io_ops.h`: Header file for the `io_ops.c` file.
    - `antenna.h`: Header file for the `antenna.c` file.
    - `antenna_effect.h`: Header file for the `antenna_effect.c` file.

## Description of Files

### `menu.h`

This file declares the functions related to displaying the menu, getting user choices, and handling those choices.

### `io_ops.h`

This file declares the functions for input/output operations, including file reading and writing.

### `antenna.h`

This file contains the declarations for functions managing antennas, including loading antennas from a file, inserting new antennas, removing existing antennas, and printing the current antenna map.

### `antenna_effect.h`

This file declares the functions for calculating and managing the effect positions of antennas based on the given formulas.

## Usage

1. Ensure all header files are in the `include` folder.
2. Include the necessary header files in your source code files to use the declared functions and data structures.