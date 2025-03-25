/**
 * \file main.c
 * \brief Main file for the antenna effect program.
 * Advanced Data Structures
 * \n
 * Practical Term Project
 * \n
 * 2024-2025 Fall Semester
 * \n \n
 * CMake Minimum Version: 3.30
 * \n
 * C Standard: C23
 * \n
 * IDE: CLion
 * \n \n
 * Ahmet Abdullah GULTEKIN
 * \n
 * Student ID: 51036
 * \n \n
 * This program reads a matrix from a file, where dots represent empty spaces
 * and characters represent identical antennas. The program then calculates the effect positions.
 * The effect positions are calculated by using the following formulas:
 * \n
 * L1 = (2 * row1 - row2, 2 * col1 - col2)
 * \n
 * L2 = (2 * row2 - row1, 2 * col2 - col1).
 * \n
 * The program also provides the functionality to insert, remove, print antennas and clear the lists.
 *
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "antenna.h"
#include "antenna_effect.h"

/**
 * \fn Prompt the user to enter a filename.
 * \param filename The buffer to store the filename.
 */
void promptFilename(char *filename) {
    printf("\nEnter the filename with the antenna data: ");
    if (scanf("%255s", filename) != 1) {
        fprintf(stderr, "Error reading filename.\n");
        exit(EXIT_FAILURE);
    }
}

/**
 * \fn Load antennas from a file and print them.
 * \param filename The name of the file to load antennas from.
 * \param antennaList The list of antennas.
 */
void loadAndPrintAntennas(const char *filename, AntennaNode **antennaList) {
    loadAntennasFromFile(filename, antennaList);
    printf("\nLoaded antennas: \n");
    printAntennas(*antennaList);
}

/**
 * \fn Calculate and print the effect positions.
 * \param antennaList The list of antennas.
 * \param effectList The list of effect positions.
 */
void calculateAndPrintEffects(AntennaNode *antennaList, AntennaEffectNode **effectList) {
    computeEffectSpots(antennaList, effectList);
    printf("\nCalculated effect positions: \n");
    printAllAntennaEffects(*effectList);
}

/**
 * \fn Display the menu.
 */
void displayMenu() {
    printf("\nMenu:\n");
    printf("1. Load antennas from file\n");
    printf("2. Print antennas\n");
    printf("3. Calculate and print effect positions\n");
    printf("4. Insert a new antenna\n");
    printf("5. Remove an existing antenna\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

/**
 * \fn Handle the user's choice from the menu.
 *
 * \param choice The user's choice
 * \param antennaList The list of antennas
 * \param effectList The list of effect positions
 *
 * case 1: Load antennas from a file
 * case 2: Print the list of antennas
 * case 3: Calculate and print the effect positions
 * case 4: Insert a new antenna
 * case 5: Remove an existing antenna
 * case 6: Exit the program
 *
 * If the user's choice is invalid, print an error message.
 *
 * \note The antennaList and effectList are passed as pointers to pointers to update the lists.
 *
 * \return void
 */
void handleMenuChoice(int choice, AntennaNode **antennaList, AntennaEffectNode **effectList) {
    char filename[256];
    char frequency;
    int row, col;

    switch (choice) {
        case 1:
            promptFilename(filename);
            loadAndPrintAntennas(filename, antennaList);
            break;
        case 2:
            printAntennas(*antennaList);
            break;
        case 3:
            calculateAndPrintEffects(*antennaList, effectList);
            break;
        case 4:
            printf("Enter frequency, row, and column: ");
            if (scanf(" %c %d %d", &frequency, &row, &col) != 3) {
                fprintf(stderr, "Invalid input. Try again.\n");
                break;
            }
            insertAntenna(antennaList, frequency, row, col);
            break;
        case 5:
            printf("Enter frequency, row, and column: ");
            if (scanf(" %c %d %d", &frequency, &row, &col) != 3) {
                fprintf(stderr, "Invalid input. Try again.\n");
                break;
            }
            removeAntenna(antennaList, row, col, frequency);
            break;
        case 6:
            clearAntennasList(*antennaList);
            clearAntennaEffectsList(*effectList);
            printf("Exiting.\n");
            exit(0);
        default:
            printf("Invalid choice. Try again.\n");
    }
}

/**
 * \fn Get the user's choice from the menu.
 * \return The user's choice.
 */
int getChoice() {
    int choice;
    if (scanf("%d", &choice) != 1) {
        fprintf(stderr, "Invalid input. Try again.\n");
        exit(EXIT_FAILURE);
    }
    return choice;
}

/**
 * \fn Main function. Initialize the linked lists for antennas and effect positions.
 * Start an infinite loop to display the menu, read the user's choice, and handle the choice.
 *
 * \return  0 if the program exits successfully
 *
 * \return EXIT_FAILURE if there is an error
 */
int main() {
    // Initialize the linked lists
    AntennaNode *antennaList = NULL;
    AntennaEffectNode *effectList = NULL;
    int choice;

    // Main loop
    while (1) {
        // Display the menu
        displayMenu();
        // Read the user's choice
        choice = getChoice();
        // Handle the user's choice
        handleMenuChoice(choice, &antennaList, &effectList);
    }
}