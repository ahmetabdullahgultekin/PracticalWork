#include "antenna.h"

// Helper function: checks if the line contains only numbers (used to skip matrix dimension lines)
int isNumericLine(const char *line) {
    for (int i = 0; line[i] != '\0'; i++) {
        if (!isspace(line[i]) && !isdigit(line[i]))
            return 0;
    }
    return 1;
}

// Insert a new antenna node into the linked list.
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

// Remove an antenna node with the specified frequency and coordinates from the list.
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

// Print the list of antennas in a table format.
void printAntennas(AntennaNode *head) {
    printf("Frequency | Row | Column\n");
    printf("-------------------------\n");
    while (head) {
        printf("    %c     |  %d  |   %d\n", head->frequency, head->row, head->col);
        head = head->next;
    }
}

// Clear the linked list of antennas and free the allocated memory
void clearAntennasList(AntennaNode *head) {
    AntennaNode *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}


// Load antenna data from a file and add them to the linked list.
// The file should contain a matrix with antenna characters. Lines that consist only of numbers
// (e.g., matrix dimensions) are skipped.
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