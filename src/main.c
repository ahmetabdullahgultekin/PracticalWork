/**
 * @file main.c
 *
 * @author Ahmet Abdullah GULTEKIN
 * @brief Main file for the antenna effect program.
 *
 * @mainpage Summary
 * \n
 * Advanced Data Structures
 * \n
 * Practical Work - Term Project
 * \n
 * 2024-2025 Fall Semester
 * \n
 * Student ID: 51036
 * \n
 * Ahmet Abdullah GULTEKIN
 * \n \n
 * CMake Minimum Version: 3.30
 * \n
 * C Standard: C23
 * \n
 * IDE: CLion
 * \n \n
 *
 * @details This program reads a matrix from a file, where dots represent empty spaces and characters represent
 * identical antennas. The program then calculates the effect positions.
 * The effect positions are calculated by using the following formulas:
 * \n
 * L1 = (2 * row1 - row2, 2 * col1 - col2)
 * \n
 * L2 = (2 * row2 - row1, 2 * col2 - col1).
 * \n
 * The program also provides the functionality to insert, remove, print antennas and clear the lists.
 */

#include "../include/antenna.h"
#include "../include/antenna_effect.h"
#include "../include/menu.h"

/**
 * @fn main
 *
 * @brief Main function for the antenna effect program.
 * Start an infinite loop to display the menu, read the user's choice, and handle the choice.
 *
 * @return  0 if the program exits successfully
 *
 * @return EXIT_FAILURE if there is an error
 */
int main() {
    // Initialize the linked lists
    AntennaNode *antennaList = NULL;
    AntennaEffectNode *effectList = NULL;

    // Main loop
    while (1) {
        // Display the menu
        displayMenu();
        // Read the user's choice and Handle the user's choice
        handleMenuChoice(getChoice(), &antennaList, &effectList);
    }
}