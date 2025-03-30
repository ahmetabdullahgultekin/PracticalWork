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
    printAllAntennas(*antennaList);
}

/**
 * @fn calculateAndPrintEffects
 * @brief Calculate and print the effect positions.
 * @param antennaList The list of antennas.
 * @param effectList The list of effect positions.
 */
void calculateAndPrintEffects(AntennaNode *antennaList, AntennaEffectNode **effectList) {
    computeEffectSpots(effectList, antennaList);
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
    if (choice < 1 || choice > 10) {
        return -1; // Invalid choice
    }
    return 0; // Valid choice
}

/**
 * @fn requestUserChoice
 * @brief Get the user's choice from the menu.
 * @return The user's choice.
 */
int requestUserChoice() {
    int choice;
    do {
        printf("Enter your choice (1-10): ");
        if (scanf_s("%d", &choice) == 1 && isChoiceValid(choice) == 0) {
            return choice; // Valid choice
        }
        while (getchar() != '\n'); // Clear the input buffer
        printf("Invalid input. Please enter a number between 1 and 10.\n");
        choice = -1; // Set choice to an invalid value
    } while (isChoiceValid(choice) == -1);
    return 0;
}

/**
 * @fn showMenu
 * @brief Display the menu options.
 */
void showMenu() {
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("                                  MENU\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("1. LOAD   - Antennas From Input Folder\n");
    printf("2. PRINT  - Antennas\n");
    printf("3. PRINT  - Effect Positions\n");
    printf("4. INSERT - A New Antenna\n");
    printf("5. REMOVE - An Existing Antenna\n");
    printf("6. SAVE   - (TABLE) Antennas To Output Folder\n");
    printf("7. SAVE   - (TABLE) Effect Positions To Output Folder\n");
    printf("8. SAVE   - (DOT MAP) Antennas To Output Folder With Dots\n");
    printf("9. SAVE   - (DOT MAP) Effect Positions To Output Folder With Dots\n");
    printf("10. QUIT  - Unsaved Changes Will Be Lost\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

/**
 * @fn proceedUserPreference
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
 * - case 8: Save antennas to a file with dots
 * \n
 * - case 9: Save effect positions to a file with dots
 * \n
 * - case 10: Quit the program
 *
 * @note If the user's input is invalid, print an error message.
 *
 * @note The antennaList and effectList are passed as pointers to pointers to update the lists.
 *
 * @return void
 */
void proceedUserPreference(int choice, AntennaNode **antennaList, AntennaEffectNode **effectList) {
    char fileName[256];
    char symbol;
    int coordinateX, coordinateY;

    switch (choice) {
        case 1:
            promptFilename(fileName, 1); // Input file
            loadAndPrintAntennas(fileName, antennaList);
            break;
        case 2:
            printAllAntennas(*antennaList);
            break;
        case 3:
            calculateAndPrintEffects(*antennaList, effectList);
            break;
        case 4:
            printf("Enter symbol, coordinateX, and column (0 1 2): ");
            if (scanf_s(" %c %d %d", &symbol, 1, &coordinateX, &coordinateY) != 3) {
                fprintf(stderr, "Invalid input. Try again.\n");
                break;
            }
            addNewAntenna(coordinateX, coordinateY, symbol, antennaList);
            break;
        case 5:
            printf("Enter symbol, coordinateX, and column (0 1 2): ");
            if (scanf_s(" %c %d %d", &symbol, 1, &coordinateX, &coordinateY) != 3) {
                fprintf(stderr, "Invalid input. Try again.\n");
                break;
            }
            deleteAntenna(coordinateX, coordinateY, symbol, antennaList);
            break;
        case 6:
            promptFilename(fileName, 0); // Output file
            saveAntennasToFile(fileName, *antennaList);
            break;
        case 7:
            promptFilename(fileName, 0); // Output file
            saveAntennaEffectsToFile(fileName, *effectList);
            break;
        case 8:
            promptFilename(fileName, 0); // Output file
            saveAntennasToFileWithDots(fileName, *antennaList);
            break;
        case 9:
            promptFilename(fileName, 0); // Output file
            saveAntennaEffectsToFileWithDots(*effectList, fileName);
            break;
        case 10:
            printf("Exiting the program. Unsaved changes will be lost.\n");
            clearAntennasList(*antennaList);
            clearAntennaEffectsList(*effectList);
            exit(EXIT_SUCCESS);
        default:
            printf("Invalid choice. Try again.\n");
    }
}
