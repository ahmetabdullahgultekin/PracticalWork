/**
 * @file menu.c
 * @brief Implementation of Menu system for the antenna effect program.
 * @author Ahmet Abdullah GULTEKIN
 * @date 2025-03-30
 */

#include "../include/menu.h"
#include "../include/io_ops.h"

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
 * @fn isChoiceValid
 * @brief Check if the user's choice is valid.
 * @param choice The user's choice.
 * @return -1 if the choice is invalid, 0 otherwise.
 */
int isChoiceValid(int choice) {
    if (choice < 1 || choice > 8) {
        return -1; // Invalid choice
    }
    return 0; // Valid choice
}

/**
 * @fn getChoice
 * @brief Get the user's choice from the menu.
 * @return The user's choice.
 */
int getChoice() {
    int choice;
    do {
        printf("Enter your choice (1-8): ");
        if (scanf_s("%d", &choice) == 1 && isChoiceValid(choice) == 0) {
            return choice; // Valid choice
        }
        while (getchar() != '\n'); // Clear the input buffer
        printf("Invalid input. Please enter a number between 1 and 8.\n");
        choice = -1; // Set choice to an invalid value
    } while (isChoiceValid(choice) == -1);
    return 0;
}

/**
 * @fn displayMenu
 * @brief Display the menu options.
 */
void displayMenu() {
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("                    MENU\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("1. LOAD   - Antennas From Input Folder\n");
    printf("2. PRINT  - Antennas\n");
    printf("3. PRINT  - Effect Positions\n");
    printf("4. INSERT - A New Antenna\n");
    printf("5. REMOVE - An Existing Antenna\n");
    printf("6. SAVE   - Antennas To Output Folder\n");
    printf("7. SAVE   - Effect Positions To Output Folder\n");
    printf("8. QUIT   - Unsaved Changes Will Be Lost\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
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
            if (scanf_s(" %c %d %d", &frequency, 1, &row, &col) != 3) {
                fprintf(stderr, "Invalid input. Try again.\n");
                break;
            }
            insertAntenna(antennaList, frequency, row, col);
            break;
        case 5:
            printf("Enter frequency, row, and column (0 1 2): ");
            if (scanf_s(" %c %d %d ", &frequency, 1, &row, &col) != 3) {
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
