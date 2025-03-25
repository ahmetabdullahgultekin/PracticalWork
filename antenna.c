/**
 * \file antenna.c
 *
 * \brief This file contains the function definitions for managing the antennas.
 */
#include "antenna.h"

/**
 * \fn Check if a line consists only of numbers.
 *
 * \param line The line to check.
 */
int isNumericLine(const char *line) {
    for (int i = 0; line[i] != '\0'; i++) {
        if (!isspace(line[i]) && !isdigit(line[i]))
            return 0;
    }
    return 1;
}

/**
 * \fn Insert a new antenna node into the linked list.
 *
 * \param head The head of the linked list
 * \param frequency The frequency of the antenna
 * \param row The row of the antenna
 * \param col The column of the antenna
 * \return The newly created node
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
 * \fn Remove an existing antenna node from the linked list.
 *
 * \param head The head of the linked list
 * \param row The row of the antenna
 * \param col The column of the antenna
 * \param frequency The frequency of the antenna
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
 * \fn Print the list of antennas in a table format.
 *
 * \param head The head of the linked list
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
 * \fn Free all nodes in the antenna linked list.
 *
 * \param head The head of the linked list
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
 * \fn Load antennas from a file and insert them into the linked list.
 *
 * \param filename The name of the file to load antennas from
 * \param head The head of the linked list
 */
void loadAntennasFromFile(const char *filename, AntennaNode **head) {
    // Open the file for reading from concat upper directory
    FILE *fp = fopen(strcat("../", filename), "r");
    if (!fp) {
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