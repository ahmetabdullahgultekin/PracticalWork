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

AntennaEffectNode *addNewAntennaEffect(int coordinateX, int coordinateY, AntennaEffectNode **listHead);

int isAntennaEffectExist(int coordinateX, int coordinateY, AntennaEffectNode *effectsHead);

void printAllAntennaEffects(AntennaEffectNode *listHead);

void clearAntennaEffectsList(AntennaEffectNode *listHead);

void computeEffectSpots(AntennaEffectNode **effects, AntennaNode *antennas);

void saveAntennaEffectsToFile(const char *filename, AntennaEffectNode *listHead);

void saveAntennaEffectsToFileWithDots(AntennaEffectNode *listHead, const char *fileName);

#endif //PRACTICALWORK_ANTENNA_EFFECT_H
