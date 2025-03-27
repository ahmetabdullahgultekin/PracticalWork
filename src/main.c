/**
 * @file main.c
 *
 * @author Ahmet Abdullah GULTEKIN
 * @brief Main file for the antenna effect program.
 *
 * @mainpage Advanced Data Structures
 * \n
 * Practical Work - Term Project
 * \n
 * 2024-2025 Fall Semester
 * \n
 * Student ID: 51036
 * \n \n
 * CMake Minimum Version: 3.30
 * \n
 * C Standard: C23
 * \n
 * IDE: CLion
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
#include "io_ops.h"

/**
 * @fn promptFilename
 * @brief Prompt the user to enter a filename or select from a list.
 * @param filename The buffer to store the filename.
 * @param isInput A flag indicating whether the file is for input (1) or output (0).
 */
void promptFilename(char *filename, int isInput) {
    if (isInput) {
        char files[100][256];
        int fileCount = listFiles(files, 100);

        if (fileCount == 0) {
            printf("No files found in the input directory.\n");
            exit(EXIT_FAILURE);
        }

        promptFileSelection(files, fileCount, filename);
    } else {
        printf("\nEnter the filename: ");
        if (scanf_s("%s", filename, 256) != 1) {
            fprintf(stderr, "Error reading filename.\n");
            exit(EXIT_FAILURE);
        }
    }
}

/**
 * @fn loadAndPrintAntennas
 * @brief Load antennas from a file and print them.
 * @param filename The name of the file to load antennas from.
 * @param antennaList The list of antennas.
 */
void loadAndPrintAntennas(const char *filename, AntennaNode **antennaList) {
    loadAntennasFromFile(filename, antennaList);
    printf("\nLoaded antennas: \n");
    printAntennas(*antennaList);
}

/**
 * @fn calculateAndPrintEffects
 * @brief Calculate and print the effect positions.
 * @param antennaList The list of antennas.
 * @param effectList The list of effect positions.
 */
void calculateAndPrintEffects(AntennaNode *antennaList, AntennaEffectNode **effectList) {
    computeEffectSpots(antennaList, effectList);
    printf("\nCalculated effect positions: \n");
    printAllAntennaEffects(*effectList);
}

/**
 * @fn displayMenu
 * @brief Display the menu options.
 */
void displayMenu() {
    printf("\n============================\n");
    printf("        MAIN MENU\n");
    printf("============================\n");
    printf("1. LOAD   - Antennas From Input Folder\n");
    printf("2. PRINT  - Antennas\n");
    printf("3. PRINT  - Effect Positions\n");
    printf("4. INSERT - A New Antenna\n");
    printf("5. REMOVE - An Existing Antenna\n");
    printf("6. SAVE   - Antennas To Output Folder\n");
    printf("7. SAVE   - Effect Positions To Output Folder\n");
    printf("8. QUIT   - Unsaved Changes Will Be Lost\n");
    printf("============================\n");
    printf("Enter your choice: ");
}

/**
 * @fn handleMenuChoice
 *
 * @brief Handle the user's choice from the menu.
 *
 * @param choice The user's choice
 * @param antennaList The list of antennas
 * @param effectList The list of effect positions
 *
 * - case 1: Load antennas from a file
 * \n
 * - case 2: Print the list of antennas
 * \n
 * - case 3: Calculate and print the effect positions
 * \n
 * - case 4: Insert a new antenna
 * \n
 * - case 5: Remove an existing antenna
 * \n
 * - case 6: Save antennas to a file
 * \n
 * - case 7: Save effect positions to a file
 * \n
 * - case 8: Exit the program
 *
 * @note If the user's input is invalid, print an error message.
 *
 * @note The antennaList and effectList are passed as pointers to pointers to update the lists.
 *
 * @return void
 */
void handleMenuChoice(int choice, AntennaNode **antennaList, AntennaEffectNode **effectList) {
    char filename[256];
    char frequency;
    int row, col;

    switch (choice) {
        case 1:
            promptFilename(filename, 1); // Input file
            loadAndPrintAntennas(filename, antennaList);
            break;
        case 2:
            printAntennas(*antennaList);
            break;
        case 3:
            calculateAndPrintEffects(*antennaList, effectList);
            break;
        case 4:
            printf("Enter frequency, row, and column (0 1 2): ");
            if (scanf_s("%c %d %d", &frequency, &row, &col) != 3) {
                fprintf(stderr, "Invalid input. Try again.\n");
                break;
            }
            insertAntenna(antennaList, frequency, row, col);
            break;
        case 5:
            printf("Enter frequency, row, and column (0 1 2): ");
            if (scanf_s("%c %d %d", &frequency, &row, &col) != 3) {
                fprintf(stderr, "Invalid input. Try again.\n");
                break;
            }
            removeAntenna(antennaList, row, col, frequency);
            break;
        case 6:
            promptFilename(filename, 0); // Output file
            saveAntennasToFile(filename, *antennaList);
            break;
        case 7:
            promptFilename(filename, 0); // Output file
            saveAntennaEffectsToFile(filename, *effectList);
            break;
        case 8:
            clearAntennasList(*antennaList);
            clearAntennaEffectsList(*effectList);
            exit(EXIT_SUCCESS);
        default:
            printf("Invalid choice. Try again.\n");
    }
}

/**
 * @fn getChoice
 * @brief Get the user's choice from the menu.
 * @return The user's choice.
 */
int getChoice() {
    int choice;
    if (scanf_s("%d", &choice) != 1) {
        fprintf(stderr, "Invalid input. Try again.\n");
        exit(EXIT_FAILURE);
    }
    return choice;
}

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