/**
 *
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
#include "antenna.h"
#include "antenna_effect.h"

int main() {
    AntennaNode *antennaList = NULL;
    AntennaEffectNode *effectList = NULL;
    char filename[256];

    printf("Enter the filename with the antenna data: ");
    scanf("%s", filename);

    // Load antennas from the file.
    loadAntennasFromFile(filename, &antennaList);

    printf("\nLoaded antennas:\n");
    printAntennas(antennaList);

    // Calculate effect positions for antenna pairs with the same frequency.
    computeEffectSpots(antennaList, &effectList);

    printf("\nCalculated effect positions:\n");
    printAllAntennaEffects(effectList);

    // Example: Insert and remove operations.
    printf("\nInserting a new antenna (example: frequency 'B', row 2, col 5)...\n");
    insertAntenna(&antennaList, 'B', 2, 5);
    printAntennas(antennaList);

    printf("\nRemoving an existing antenna (example: frequency 'B', row 2, col 5)...\n");
    removeAntenna(&antennaList, 2, 5, 'B');
    printAntennas(antennaList);

    // Free allocated memory.
    clearAntennasList(antennaList);
    clearAntennaEffectsList(effectList);

    return 0;
}