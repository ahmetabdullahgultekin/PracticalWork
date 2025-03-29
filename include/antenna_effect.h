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
    int row, col;                   /**< Row coordinate of the effect position in the matrix */
    struct AntennaEffectNode *next; /**< Pointer to the next node in the linked list */
} AntennaEffectNode;                /**< Typedef for AntennaEffectNode */

AntennaEffectNode *insertAntennaEffect(AntennaEffectNode **head, int row, int col);

int isAntennaEffectExist(AntennaEffectNode *head, int row, int col);

void printAllAntennaEffects(AntennaEffectNode *head);

void clearAntennaEffectsList(AntennaEffectNode *head);

void computeEffectSpots(AntennaNode *antennas, AntennaEffectNode **effects);

void saveAntennaEffectsToFile(const char *filename, AntennaEffectNode *head);

#endif //PRACTICALWORK_ANTENNA_EFFECT_H
