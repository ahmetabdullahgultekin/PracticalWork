/**
 * @file antenna.c
 * @brief Implementation of the antenna functions. The antenna functions are used to manage the list of antennas.
 * @author Ahmet Abdullah GULTEKIN
 * @date 2025-03-30
 */

#include "../include/antenna.h"
#include "../include/io_ops.h"

/**
 * @fn isNumericLine
 *
 * @brief Check if a line contains only numeric characters.
 *
 * @param line The line to check.
 */
int isNumericLine(const char *line) {
    for (int i = 0; line[i] != '\0'; i++) {
        if (!isspace(line[i]) && !isdigit(line[i]))
            return 0;
    }
    return 1;
}

/**
 * @fn insertAntenna
 *
 * @brief Insert a new antenna node into the linked list.
 *
 * @param head The head of the linked list
 * @param frequency The frequency of the antenna
 * @param row The row of the antenna
 * @param col The column of the antenna
 * @return The newly created node
 */
AntennaNode *insertAntenna(AntennaNode **head, char frequency, int row, int col) {

    // Create a new node and allocate memory for it
    AntennaNode *newNode = (AntennaNode *) malloc(sizeof(AntennaNode));

    // Check if memory allocation was successful
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    // Assign values to the new node
    newNode->frequency = frequency;
    newNode->row = row;
    newNode->col = col;
    newNode->next = NULL;

    // If the list is empty, assign the new node as the head
    if (*head == NULL) {
        *head = newNode;
    }
        // Otherwise, traverse the list and add the new node to the end
    else {
        AntennaNode *temp = *head;
        while (temp->next)
            temp = temp->next;
        temp->next = newNode;
    }
    return newNode;
}

/**
 * @fn removeAntenna
 *
 * @brief Remove an existing antenna node from the linked list.
 *
 * @param head The head of the linked list
 * @param row The row of the antenna
 * @param col The column of the antenna
 * @param frequency The frequency of the antenna
 */
void removeAntenna(AntennaNode **head, int row, int col, char frequency) {
    AntennaNode *temp = *head;
    AntennaNode *prev = NULL;
    while (temp != NULL) {
        if (temp->row == row && temp->col == col && temp->frequency == frequency) {
            if (prev == NULL) { // Removing the head node
                *head = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            printf("AntennaNode (%c, %d, %d) removed.\n", frequency, row, col);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("AntennaNode not found: (%c, %d, %d).\n", frequency, row, col);
}

/**
 * @fn printAntennas
 *
 * @brief Print the list of antennas in a table format.
 *
 * @param head The head of the linked list
 */
void printAntennas(AntennaNode *head) {
    printf("\nFrequency | Row | Column\n");
    printf("-------------------------\n");
    while (head) {
        printf("    %c     |  %d  |   %d\n", head->frequency, head->row, head->col);
        head = head->next;
    }
}

/**
 * @fn clearAntennasList
 *
 * @brief Clear the linked list of antennas.
 *
 * @param head The head of the linked list
 */
void clearAntennasList(AntennaNode *head) {
    AntennaNode *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

/**
 * @fn loadAntennasFromFile
 *
 * @brief Load antennas from a file and insert them into the linked list.
 *
 * @param filename The name of the file to load antennas from
 * @param head The head of the linked list
 */
void loadAntennasFromFile(const char *filename, AntennaNode **head) {
    // Open the file for reading from concat upper directory
    FILE *fp;
    // Declare file directory
    char directory[256] = INPUT_DIR;
    // Concatenate the filename to the directory
    strcat_s(directory, 256, filename);
    if (fopen_s(&fp, directory, "r") != 0) {
        printf("Cannot open file: %s\n", filename);
        exit(1);
    }
    char line[1024];
    int row = 0;
    while (fgets(line, sizeof(line), fp)) {
        // Remove newline characters
        line[strcspn(line, "\r\n")] = 0;
        // Skip empty lines or lines containing only numbers
        if (strlen(line) == 0 || isNumericLine(line))
            continue;
        for (int col = 0; line[col] != '\0'; col++) {
            // If the character is not '.', consider it as an antenna.
            if (line[col] != '.') {
                insertAntenna(head, line[col], row, col);
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
 * @param filename The name of the file to save antennas to
 * @param head The head of the linked list
 */
void saveAntennasToFile(const char *filename, AntennaNode *head) {
    // Declare file directory
    char fileDir[256] = OUTPUT_DIR;
    // Concatenate the filename to the directory
    strcat_s(fileDir, 256, filename);
    // Check if the file exists
    if (_access(fileDir, 0) == 0) {
        char choice;
        printf("File %s already exists. Do you want to overwrite it? (y/n): ", filename);
        if (scanf_s(" %c", &choice, 1) != 1 || (choice != 'y' && choice != 'Y')) {
            printf("File not overwritten.\n");
            return;
        }
    }

    // Open the file for writing
    FILE *fp;
    if (fopen_s(&fp, fileDir, "w") != 0) {
        printf("Cannot open file: %s\n", filename);
        exit(1);
    }

    // Write each antenna's details to the file
    while (head) {
        fprintf(fp, "%c %d %d\n", head->frequency, head->row, head->col);
        head = head->next;
    }

    // Close the file
    fclose(fp);
    printf("Antennas saved to file: %s\n", fileDir);
}