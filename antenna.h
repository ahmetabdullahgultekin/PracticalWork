#ifndef PRACTICALWORK_ANTENNA_H
#define PRACTICALWORK_ANTENNA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * AntennaNode structure for a single antenna in the linked list.
 * Structure members are:
 * \n
 * - row: Row coordinate of the antenna in the matrix (starting from 0 index ex: 0, 1, 2, 3)
 * \n
 * - col: Column coordinate of the antenna in the matrix (starting from 0 index ex: 0, 1, 2, 3)
 * \n
 * - frequency: Frequency of the antenna (character representation ex: 'A', 'B', 'C')
 * \n
 * - next: Pointer to the next node in the linked list (NULL if the last node)
 */
typedef struct AntennaNode {
    int row, col;             // Coordinates in the matrix (row, column)
    char frequency;           // Frequency of the antenna
    struct AntennaNode *next; // Pointer to the next node
} AntennaNode;

// Function prototypes
AntennaNode *insertAntenna(AntennaNode **head, char frequency, int row, int col);

void removeAntenna(AntennaNode **head, int row, int col, char frequency);

void printAntennas(AntennaNode *head);

void clearAntennasList(AntennaNode *head);

void loadAntennasFromFile(const char *filename, AntennaNode **head);

#endif //PRACTICALWORK_ANTENNA_H
