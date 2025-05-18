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

/**
 * @struct AntennaEffectNode
 * @typedef AntennaEffectNode
 *
 * @brief AntennaEffectNode structure for a single antenna effect in the linked list.
 */
AntennaNode *addNewAntenna(int coordinateX, int coordinateY, char symbol, AntennaNode **listHead);

/**
 * @brief Function to delete an antenna from the linked list.
 *
 * @param coordinateX X coordinate of the antenna to be deleted.
 * @param coordinateY Y coordinate of the antenna to be deleted.
 * @param symbol Frequency of the antenna to be deleted.
 * @param listHead Pointer to the head of the linked list.
 */
void deleteAntenna(int coordinateX, int coordinateY, char symbol, AntennaNode **listHead);

/**
 * @brief Function to print all antennas in the linked list.
 *
 * @param listHead Pointer to the head of the linked list.
 */
void printAllAntennas(AntennaNode *listHead);

/**
 * @brief Function to find an antenna in the linked list.
 *
 * @param coordinateX X coordinate of the antenna to be found.
 * @param coordinateY Y coordinate of the antenna to be found.
 * @param symbol Frequency of the antenna to be found.
 * @param listHead Pointer to the head of the linked list.
 * @return 1 if the antenna is found, 0 otherwise.
 */
void clearAntennasList(AntennaNode *listHead);

/**
 * @brief Function to check if an antenna exists in the linked list.
 *
 * @param coordinateX X coordinate of the antenna to be checked.
 * @param coordinateY Y coordinate of the antenna to be checked.
 * @param symbol Frequency of the antenna to be checked.
 * @param listHead Pointer to the head of the linked list.
 * @return 1 if the antenna exists, 0 otherwise.
 */
void loadAntennasFromFile(const char *filename, AntennaNode **listHead);

/**
 * @brief Function to save antennas to a file.
 *
 * @param fileName Name of the file to save the antennas.
 * @param listHead Pointer to the head of the linked list.
 */
void saveAntennasToFile(const char *fileName, AntennaNode *listHead);

/**
 * @brief Function to save antennas to a file with dots.
 *
 * @param fileName Name of the file to save the antennas.
 * @param listHead Pointer to the head of the linked list.
 */
void saveAntennasToFileWithDots(const char *fileName, AntennaNode *listHead);

#endif //PRACTICALWORK_ANTENNA_H
