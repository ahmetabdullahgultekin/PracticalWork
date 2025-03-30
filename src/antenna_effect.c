/**
 * @file antenna_effect.c
 * @author Ahmet Abdullah GULTEKIN
 * @brief Implementation of the antenna effect functions.
 * The antenna effect functions are used to manage the list of antenna effects.
 *
 * @date 2025-03-30
 */

#include "../include/antenna_effect.h"
#include "../include/io_ops.h"

/**
 * @fn addNewAntennaEffect
 *
 * @brief Insert a new effect position node into the linked list.
 *
 * @param listHead The listHead of the linked list
 * @param coordinateX The coordinateX of the effect
 * @param coordinateY The column of the effect
 * @return The newly created node
 */
AntennaEffectNode *addNewAntennaEffect(int coordinateX, int coordinateY, AntennaEffectNode **listHead) {
    if (isAntennaEffectExist(coordinateX, coordinateY, *listHead))
        return *listHead;

    AntennaEffectNode *newAntennaEffect = (AntennaEffectNode *) malloc(sizeof(AntennaEffectNode));
    if (!newAntennaEffect) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newAntennaEffect->coordinateX = coordinateX;
    newAntennaEffect->coordinateY = coordinateY;
    newAntennaEffect->nextEffect = NULL;

    if (*listHead == NULL) {
        *listHead = newAntennaEffect;
    } else {
        AntennaEffectNode *searcherNode = *listHead;
        while (searcherNode->nextEffect) {
            searcherNode = searcherNode->nextEffect;
        }
        searcherNode->nextEffect = newAntennaEffect;
    }
    return newAntennaEffect;
}

/**
 * @fn isAntennaEffectExist
 *
 * @brief Check if an effect position exists in the linked list.
 *
 * @param effectsHead The effectsHead of the linked list
 * @param coordinateX The coordinateX of the effect
 * @param coordinateY The column of the effect
 * @return 1 if the effect position exists, 0 otherwise
 */
int isAntennaEffectExist(int coordinateX, int coordinateY, AntennaEffectNode *effectsHead) {
    while (effectsHead) {
        if (effectsHead->coordinateX == coordinateX && effectsHead->coordinateY == coordinateY)
            return 1;
        effectsHead = effectsHead->nextEffect;
    }
    return 0;
}

/**
 * @fn printAllAntennaEffects
 *
 * @brief Print the list of effect positions in a table format.
 *
 * @param listHead The head of the linked list
 */
void printAllAntennaEffects(AntennaEffectNode *listHead) {
    printf("| X | Y |\n");
    printf("+---+---+\n");
    while (listHead) {
        printf("  %d   %d\n", listHead->coordinateX, listHead->coordinateY);
        listHead = listHead->nextEffect;
    }
}

/**
 * @fn clearAntennaEffectsList
 *
 * @brief Clear the linked list of effect positions.
 *
 * @param listHead The head of the linked list
 */
void clearAntennaEffectsList(AntennaEffectNode *listHead) {
    AntennaEffectNode *temp;
    while (listHead) {
        temp = listHead;
        listHead = listHead->nextEffect;
        free(temp);
    }
}

/**
 * @fn computeEffectSpots
 *
 * @brief Compute the effect positions of the antennas.
 * formula 1 = (2 * row1 - row2, 2 * col1 - col2)
 * formula 2 = (2 * row2 - row1, 2 * col2 - col1)
 *
 * @param antennas The list of antennas
 * @param effects The list of effect positions
 */
void computeEffectSpots(AntennaEffectNode **effects, AntennaNode *antennas) {
    for (AntennaNode *a = antennas; a != NULL; a = a->nextAntenna) {
        for (AntennaNode *b = a->nextAntenna; b != NULL; b = b->nextAntenna) {
            if (a->symbol == b->symbol) {
                int l1_row = 2 * a->coordinateX - b->coordinateX;
                int l1_col = 2 * a->coordinateY - b->coordinateY;
                int l2_row = 2 * b->coordinateX - a->coordinateX;
                int l2_col = 2 * b->coordinateY - a->coordinateY;
                addNewAntennaEffect(l1_row, l1_col, effects);
                addNewAntennaEffect(l2_row, l2_col, effects);
            }
        }
    }
}

/**
 * @fn saveAntennaEffectsToFile
 *
 * @brief Save the list of antenna effects to a file.
 *
 * @param filename The name of the file to save antenna effects to
 * @param listHead The listHead of the linked list
 */
void saveAntennaEffectsToFile(const char *filename, AntennaEffectNode *listHead) {
    // Open the file for writing
    FILE *fp;

    // Declare file directory
    char fileDir[256] = OUTPUT_PATH;

    // Concatenate the filename to the directory
    if (strcat_s(fileDir, 256, filename) != 0) {
        fprintf(stderr, "Error concatenating file path\n");
        exit(1);
    }

    // Open the file for writing
    if (fopen_s(&fp, fileDir, "w") != 0) {
        printf("Cannot open file: %s\n", fileDir);
        exit(1);
    }

    // Write each antenna effect's details to the file
    while (listHead) {
        fprintf(fp, "%d %d\n", listHead->coordinateX, listHead->coordinateY);
        listHead = listHead->nextEffect;
    }

    // Close the file
    fclose(fp);
}

/**
 * @fn saveAntennaEffectsToFileWithDots
 * @brief Save the list of antenna effects to a file in the input format with dots.
 * @param fileName The name of the file to save antenna effects to
 * @param listHead The head of the linked list of antenna effects
 * @param maxCoordinateX The number of rows in the matrix
 * @param maxCoordinateY The number of columns in the matrix
 */
void saveAntennaEffectsToFileWithDots(AntennaEffectNode *listHead, const char *fileName) {
    // Declare file directory
    char filePath[256] = OUTPUT_PATH;

    // Concatenate the filename to the directory
    if (strcat_s(filePath, 256, fileName) != 0) {
        fprintf(stderr, "Error concatenating file path\n");
        exit(1);
    }

    // Open the file for writing
    FILE *fp;
    if (fopen_s(&fp, filePath, "w") != 0) {
        printf("Cannot open file: %s\n", fileName);
        exit(1);
    }

    // Find the maximum coordinates
    int maxCoordinateX = 0, maxCoordinateY = 0;
    AntennaEffectNode *temporary = listHead;
    while (temporary) {
        if (temporary->coordinateX > maxCoordinateX) {
            maxCoordinateX = temporary->coordinateX;
        }
        if (temporary->coordinateY > maxCoordinateY) {
            maxCoordinateY = temporary->coordinateY;
        }
        temporary = temporary->nextEffect;
    }

    // Allocate memory for the matrix
    char **matrix = (char **) malloc((maxCoordinateX + 1) * sizeof(char *));
    for (int i = 0; i <= maxCoordinateX; i++) {
        matrix[i] = (char *) malloc((maxCoordinateY + 1) * sizeof(char));
        for (int j = 0; j <= maxCoordinateY; j++) {
            matrix[i][j] = '.';
        }
    }

    // Place antenna effects in the matrix
    while (listHead) {
        if (listHead->coordinateX >= 0 && listHead->coordinateX < maxCoordinateX &&
            listHead->coordinateY >= 0 && listHead->coordinateY < maxCoordinateY) {
            matrix[listHead->coordinateX][listHead->coordinateY] = '#'; // '#' for effect
        }
        listHead = listHead->nextEffect;
    }

    // Write the matrix to the file
    for (int i = 0; i < maxCoordinateX; i++) {
        for (int j = 0; j < maxCoordinateY; j++) {
            fputc(matrix[i][j], fp);
        }
        fputc('\n', fp);
    }

    // Free the allocated memory for the matrix
    for (int i = 0; i < maxCoordinateX; i++) {
        free(matrix[i]);
    }
    free(matrix);

    // Close the file
    fclose(fp);
    // Print success message
    printf("Antenna effects saved to file: %s\n", filePath);
}