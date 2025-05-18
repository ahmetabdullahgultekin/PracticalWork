/**
 * @file antenna_effect.h
 * @author Ahmet Abdullah GULTEKIN
 * @brief Header file for the function declarations for managing the effect positions of the antennas.
 * @date 2025-03-30
 */
#ifndef PRACTICALWORK_ANTENNA_EFFECT_H
#define PRACTICALWORK_ANTENNA_EFFECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "antenna.h"

/**
 * @struct AntennaEffectNode [antenna_effect.h] antenna_effect.h
 * @typedef AntennaEffectNode
 *
 * @brief AntennaEffectNode structure for a single effect position in the linked list.
 */
typedef struct AntennaEffectNode {
    int coordinateX, coordinateY;                   /**< Row coordinate of the effect position in the matrix */
    struct AntennaEffectNode *nextEffect; /**< Pointer to the nextAntenna node in the linked list */
} AntennaEffectNode;                /**< Typedef for AntennaEffectNode */

/**
 * @brief Function to add a new antenna effect to the linked list.
 *
 * @param coordinateX X coordinate of the antenna effect.
 * @param coordinateY Y coordinate of the antenna effect.
 * @param listHead Pointer to the head of the linked list.
 * @return Pointer to the newly created AntennaEffectNode.
 */
AntennaEffectNode *addNewAntennaEffect(int coordinateX, int coordinateY, AntennaEffectNode **listHead);

/**
 * @brief Function to delete an antenna effect from the linked list.
 *
 * @param coordinateX X coordinate of the antenna effect to be deleted.
 * @param coordinateY Y coordinate of the antenna effect to be deleted.
 * @param effectsHead Pointer to the head of the linked list.
 */
int isAntennaEffectExist(int coordinateX, int coordinateY, AntennaEffectNode *effectsHead);

/**
 * @brief Function to print all antenna effects in the linked list.
 *
 * @param listHead Pointer to the head of the linked list.
 */
void printAllAntennaEffects(AntennaEffectNode *listHead);

/**
 * @brief Function to clear the antenna effects list.
 *
 * @param listHead Pointer to the head of the linked list.
 */
void clearAntennaEffectsList(AntennaEffectNode *listHead);

/**
 * @brief Function to compute the effect positions of antennas.
 *
 * @param effects Pointer to the head of the linked list of antenna effects.
 * @param antennas Pointer to the head of the linked list of antennas.
 */
void computeEffectSpots(AntennaEffectNode **effects, AntennaNode *antennas);

/**
 * @brief Function to save the antenna effects to a file.
 *
 * @param filename Name of the file to save the antenna effects.
 * @param listHead Pointer to the head of the linked list.
 */
void saveAntennaEffectsToFile(const char *filename, AntennaEffectNode *listHead);

/**
 * @brief Function to load antenna effects from a file.
 *
 * @param filename Name of the file to load the antenna effects from.
 * @param listHead Pointer to the head of the linked list.
 */
void saveAntennaEffectsToFileWithDots(AntennaEffectNode *listHead, const char *fileName);

#endif //PRACTICALWORK_ANTENNA_EFFECT_H
