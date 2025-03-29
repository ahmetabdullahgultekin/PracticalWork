# About the Project

## Overview

This project is a practical work for the Advanced Data Structures course. It involves reading a matrix from a file where
dots represent empty spaces and characters represent antennas. The program calculates the effect positions of the
antennas using specific formulas and provides functionalities to insert, remove, print antennas, and clear the lists.

## Features

- Load antennas from an input file
- Print the current antenna map
- Print the effect positions of antennas
- Insert a new antenna
- Remove an existing antenna
- Save antennas to an output file
- Save effect positions to an output file

## Requirements

- CMake Minimum Version: 3.30
- C Standard: C23
- IDE: CLion

## Usage

### Main Menu

```
============================
        MAIN MENU
============================
1. LOAD   - Antennas From Input Folder
2. PRINT  - Antennas
3. PRINT  - Effect Positions
4. INSERT - A New Antenna
5. REMOVE - An Existing Antenna
6. SAVE   - Antennas To Output Folder
7. SAVE   - Effect Positions To Output Folder
8. QUIT   - Unsaved Changes Will Be Lost
============================
Enter your choice (1-8):
```

### Input Format

- For inserting a new antenna: `Enter frequency, row, and column (0 1 2): A 1 1`
- For removing an antenna: `Enter frequency, row, and column (0 1 2): A 1 1`

### Effect Position Calculation

The effect positions are calculated using the following formulas:

- `L1 = (2 * row1 - row2, 2 * col1 - col2)`
- `L2 = (2 * row2 - row1, 2 * col2 - col1)`

## File Structure

- `src/`: Contains the source code files.
- `include/`: Contains the header files.
- `docs/`: Contains the documentation files.
- `CMakeLists.txt`: CMake configuration file.

## Building the Project

1. Clone the repository.
2. Open the project in CLion.
3. Configure the CMake settings.
4. Build the project.

## Running the Project

1. Run the executable generated after building the project.
2. Follow the main menu instructions to interact with the program.