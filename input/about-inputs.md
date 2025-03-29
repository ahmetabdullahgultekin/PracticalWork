# Input Folder

## Overview

The `input` folder contains all the input files required for the Antenna Mapping project. These files include the initial matrix configurations.

## File Structure

- `input/`: Directory containing all input files.

## Input File Format

Each input file should follow a specific format to be correctly processed by the program:

- The file should contain a matrix where dots (`.`) represent empty spaces and characters represent antennas.
- Each row of the matrix should be on a new line.
- The matrix should be rectangular, meaning all rows should have the same number of columns.

### Example

```
. . A . .
. B . . .
. . . C .
. . . . D
```

In this example:
- `A`, `B`, `C`, and `D` are antennas.
- `.` represents empty spaces.

## Usage

1. Place the input files in the `input` folder.
2. Ensure the files follow the specified format.
3. Run the program and select the option to load antennas from the input folder.