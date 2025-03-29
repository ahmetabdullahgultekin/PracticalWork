/**
 * @file antenna.h
 * @author Ahmet Abdullah GULTEKIN
 * @brief Header file for antenna system functions.
 * @date 2025-03-30
 */
#ifndef PRACTICALWORK_ANTENNA_H
#define PRACTICALWORK_ANTENNA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <io.h>

/**
 * @struct AntennaNode
 * @typedef AntennaNode
 *
 * @brief AntennaNode structure for a single antenna in the linked list.
 */
typedef struct AntennaNode {
    int row, col; /**< Row coordinate of the antenna in the matrix (starting from 0 index ex: 0, 1, 2, 3) */
    char frequency; /**< Frequency of the antenna (A, B, C, D, E, F, G, H, I, J) */
    struct AntennaNode *next; /**< Pointer to the next node in the linked list */
} AntennaNode;

AntennaNode *insertAntenna(AntennaNode **head, char frequency, int row, int col);

void removeAntenna(AntennaNode **head, int row, int col, char frequency);

void printAntennas(AntennaNode *head);

void clearAntennasList(AntennaNode *head);

void loadAntennasFromFile(const char *filename, AntennaNode **head);

void saveAntennasToFile(const char *filename, AntennaNode *head);

#endif //PRACTICALWORK_ANTENNA_H
