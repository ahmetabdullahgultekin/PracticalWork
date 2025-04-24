/**
 * @file antenna.h
 * @author Ahmet Abdullah GULTEKIN
 * @brief Header file for antenna system functions.
 * @date 2025-03-30
 */
#ifndef PRACTICALWORK_ANTENNA_H
#define PRACTICALWORK_ANTENNA_H

#pragma once //the same

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
    int coordinateX, coordinateY; /**< Coordinates of the antenna in the matrix (starting from 0 index ex: 0, 1, 2, 3) */
    char symbol; /**< Frequency of the antenna (A, B, C, D, E, F, G, H, I, J) */
    struct AntennaNode *nextAntenna; /**< Pointer to the nextAntenna node in the linked list */
} AntennaNode;

AntennaNode *addNewAntenna(int coordinateX, int coordinateY, char symbol, AntennaNode **listHead);

void deleteAntenna(int coordinateX, int coordinateY, char symbol, AntennaNode **listHead);

void printAllAntennas(AntennaNode *listHead);

void clearAntennasList(AntennaNode *listHead);

void loadAntennasFromFile(const char *filename, AntennaNode **listHead);

void saveAntennasToFile(const char *fileName, AntennaNode *listHead);

void saveAntennasToFileWithDots(const char *fileName, AntennaNode *listHead);

#endif //PRACTICALWORK_ANTENNA_H
