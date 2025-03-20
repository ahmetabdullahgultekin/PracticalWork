#ifndef PRACTICALWORK_ANTENNA_EFFECT_H
#define PRACTICALWORK_ANTENNA_EFFECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "antenna.h"

/**
 * AntennaEffectNode structure for a single effect position in the linked list.
 *
 *
 */
typedef struct AntennaEffectNode {
    int row, col;                    // Coordinates of the effect position
    struct AntennaEffectNode *next;  // Pointer to the next node
} AntennaEffectNode;


AntennaEffectNode *insertAntennaEffect(AntennaEffectNode **head, int row, int col);

int isAntennaEffectExist(AntennaEffectNode *head, int row, int col);

void printAllAntennaEffects(AntennaEffectNode *head);

void clearAntennaEffectsList(AntennaEffectNode *head);

void computeEffectSpots(AntennaNode *antennas, AntennaEffectNode **effects);


#endif //PRACTICALWORK_ANTENNA_EFFECT_H
