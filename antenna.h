/**
 * \file antenna.h
 *
 * \brief This file contains the function declarations for managing the antennas.
 */
#ifndef PRACTICALWORK_ANTENNA_H
#define PRACTICALWORK_ANTENNA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * \struct
 * AntennaNode structure for a single antenna in the linked list.
 * Structure members are:
 *
 * \var row: Row coordinate of the antenna in the matrix (starting from 0 index ex: 0, 1, 2, 3)
 * \var col: Column coordinate of the antenna in the matrix (starting from 0 index ex: 0, 1, 2, 3)
 * \var frequency: Frequency of the antenna (A, B, C, D, E, F, G, H, I, J)
 * \var next: Pointer to the next node in the linked list
 *
 */
typedef struct AntennaNode {
    int row, col;             // Coordinates in the matrix (row, column)
    char frequency;           // Frequency of the antenna
    struct AntennaNode *next; // Pointer to the next node
} AntennaNode;


AntennaNode *insertAntenna(AntennaNode **head, char frequency, int row, int col);

void removeAntenna(AntennaNode **head, int row, int col, char frequency);

void printAntennas(AntennaNode *head);

void clearAntennasList(AntennaNode *head);

void loadAntennasFromFile(const char *filename, AntennaNode **head);

#endif //PRACTICALWORK_ANTENNA_H
