/**
 * @file antenna.c
 * @brief Implementation of the antenna functions. The antenna functions are used to manage the list of antennas.
 * @author Ahmet Abdullah GULTEKIN
 * @date 2025-03-30
 */

#include "../include/antenna.h"
#include "../include/io_ops.h"

  /**
 * @fn addNewAntenna
 *
 * @brief Insert a new antenna node into the linked list.
 *
 * @param listHead The listHead of the linked list
 * @param symbol The symbol of the antenna
 * @param coordinateX The coordinateX of the antenna
 * @param coordinateY The column of the antenna
 * @return The newly created node
 */
AntennaNode *addNewAntenna(int coordinateX, int coordinateY, char symbol, AntennaNode **listHead) {

    // Create a new node and allocate memory for it
    AntennaNode *newAntenna = (AntennaNode *) malloc(sizeof(AntennaNode));

    // Check if memory allocation was successful
    if (!newAntenna) {
        fprintf(stderr, "Memory allocation failed for new antenna node.\n");
        exit(EXIT_FAILURE);
    }

    // Assign values to the new node
    newAntenna->symbol = symbol;
    newAntenna->coordinateX = coordinateX;
    newAntenna->coordinateY = coordinateY;
    newAntenna->nextAntenna = NULL;

    // If the list is empty, new node should be the listHead
    if (*listHead == NULL) {
        *listHead = newAntenna;
    } else { // If not, we should find the last node and link it to the new node
        AntennaNode *searcherNode = *listHead;
        while (searcherNode->nextAntenna) {
            searcherNode = searcherNode->nextAntenna;
        }
        searcherNode->nextAntenna = newAntenna;
    }
    return newAntenna;
}

/**
 * @fn deleteAntenna
 *
 * @brief Remove an existing antenna node from the linked list.
 *
 * @param listHead The head node of the linked list
 * @param coordinateX The x coordinate of the antenna
 * @param coordinateY The y coordinate of the antenna
 * @param symbol The frequency symbol of the antenna
 */
void deleteAntenna(int coordinateX, int coordinateY, char symbol, AntennaNode **listHead) {
    AntennaNode *previousNode = NULL, *searcherNode = *listHead;

    while (searcherNode != NULL) {
        if (searcherNode->coordinateX == coordinateX && searcherNode->coordinateY == coordinateY &&
            searcherNode->symbol == symbol) {
            if (previousNode == NULL) { // Removing the listHead node
                *listHead = searcherNode->nextAntenna;
            } else {
                previousNode->nextAntenna = searcherNode->nextAntenna;
            }
            free(searcherNode);
            printf("AntennaNode (%c, %d, %d) removed.\n", symbol, coordinateX, coordinateY);
            return;
        }
        previousNode = searcherNode;
        searcherNode = searcherNode->nextAntenna;
    }
    printf("AntennaNode not found: (%c, %d, %d).\n", symbol, coordinateX, coordinateY);
}

/**
 * @fn printAllAntennas
 *
 * @brief Print the list of antennas in a table format.
 *
 * @param listHead The head of the linked list
 */
void printAllAntennas(AntennaNode *listHead) {
    printf("\n| F | X | Y |\n");
    printf("+---+---+---+\n");
    while (listHead) {
        printf("  %c   %d   %d\n", listHead->symbol, listHead->coordinateX, listHead->coordinateY);
        listHead = listHead->nextAntenna;
    }
}

/**
 * @fn clearAntennasList
 *
 * @brief Clear the linked list of antennas.
 *
 * @param listHead The head of the linked list
 */
void clearAntennasList(AntennaNode *listHead) {
    AntennaNode *temp;
    while (listHead) {
        temp = listHead;
        listHead = listHead->nextAntenna;
        free(temp);
    }
}

/**
 * @fn loadAntennasFromFile
 *
 * @brief Load antennas from a file and insert them into the linked list.
 *
 * @param filename The name of the file to load antennas from
 * @param listHead The listHead of the linked list
 */
void loadAntennasFromFile(const char *filename, AntennaNode **listHead) {
    // Open the file for reading from concat upper directory
    FILE *fp;

    // Declare file directory
    char directory[256] = INPUT_PATH;

    // Concatenate the filename to the directory
    if (strcat_s(directory, 256, filename) != 0) {
        fprintf(stderr, "Error concatenating directory and filename.\n");
        exit(EXIT_FAILURE);
    }

    // Check if the file exists
    if (fopen_s(&fp, directory, "r") != 0) {
        printf("Cannot open file: %s\n", filename);
        exit(1);
    }

    char line[1024];
    int row = 0;
    while (fgets(line, sizeof(line), fp)) {
        // Remove newline characters
        line[strcspn(line, "\r\n")] = 0;
        // Skip empty lines
        if (strlen(line) == 0)
            continue;
        for (int col = 0; line[col] != '\0'; col++) {
            // If the character is not '.', consider it as an antenna.
            if (line[col] != '.') {
                 addNewAntenna(row, col, line[col], listHead);
            }
        }
        row++;
    }
    fclose(fp);
}

/**
 * @fn saveAntennasToFile
 *
 * @brief Save the list of antennas to a file.
 *
 * @param fileName The name of the file to save antennas to
 * @param listHead The head of the linked list
 */
void saveAntennasToFile(const char *fileName, AntennaNode *listHead) {
    // Declare file directory
    char newPath[256] = OUTPUT_PATH;

    // Concatenate the filename to the directory
    if (strcat_s(newPath, 256, fileName) != 0) {
        fprintf(stderr, "Error concatenating file path\n");
        exit(1);
    }

    // Check if the file exists
    if (_access(newPath, 0) == 0) {
        char userChoice;
        printf("File %s already exists. Do you want to overwrite it? (y/n): ", fileName);
        if (scanf_s(" %c", &userChoice, 1) != 1 || (userChoice != 'y' && userChoice != 'Y')) {
            printf("File not overwritten.\n");
            return;
        }
    }

    // Open the file for writing
    FILE *fp;
    if (fopen_s(&fp, newPath, "w") != 0) {
        printf("Cannot open file: %s\n", fileName);
        exit(1);
    }

    // Write each antenna's details to the file
    while (listHead) {
        fprintf(fp, "%c %d %d\n", listHead->symbol, listHead->coordinateX, listHead->coordinateY);
        listHead = listHead->nextAntenna;
    }

    // Close the file
    fclose(fp);
    printf("Antennas saved to file: %s\n", newPath);
}

/**
 * @fn saveAntennasToFileWithDots
 * @brief Save the list of antennas to a file in the input format with dots.
 * @param fileName The name of the file to save antennas to
 * @param listHead The listHead of the linked list
 * @param maxCoordinateX The number of rows in the matrix
 * @param maxCoordinateY The number of columns in the matrix
 */
void saveAntennasToFileWithDots(const char *fileName, AntennaNode *listHead) {
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
    AntennaNode *temporary = listHead;
    while (temporary) {
        if (temporary->coordinateX > maxCoordinateX) {
            maxCoordinateX = temporary->coordinateX;
        }
        if (temporary->coordinateY > maxCoordinateY) {
            maxCoordinateY = temporary->coordinateY;
        }
        temporary = temporary->nextAntenna;
    }

    // Allocate memory for the matrix
    char **matrix = (char **) malloc((maxCoordinateX + 1) * sizeof(char *));
    for (int i = 0; i <= maxCoordinateX; i++) {
        matrix[i] = (char *) malloc((maxCoordinateY + 1) * sizeof(char));
        for (int j = 0; j <= maxCoordinateY; j++) {
            matrix[i][j] = '.';
        }
    }

    // Place antennas in the matrix
    while (listHead) {
        matrix[listHead->coordinateX][listHead->coordinateY] = listHead->symbol;
        listHead = listHead->nextAntenna;
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
    printf("Antennas saved to file: %s\n", filePath);
}