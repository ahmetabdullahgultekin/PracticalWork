#include "antenna_effect.h"
#include "antenna.h"

// Insert a new effect node into the linked list if it does not already exist.
AntennaEffectNode *insertAntennaEffect(AntennaEffectNode **head, int row, int col) {
    if (isAntennaEffectExist(*head, row, col))
        return *head;

    AntennaEffectNode *newNode = (AntennaEffectNode *) malloc(sizeof(AntennaEffectNode));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->row = row;
    newNode->col = col;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        AntennaEffectNode *temp = *head;
        while (temp->next)
            temp = temp->next;
        temp->next = newNode;
    }
    return newNode;
}

// Check if an antenna effect at the given coordinates already exists in the list
int isAntennaEffectExist(AntennaEffectNode *head, int row, int col) {
    while (head) {
        if (head->row == row && head->col == col)
            return 1;
        head = head->next;
    }
    return 0;
}

// Print the list of effect positions in a table format.
void printAllAntennaEffects(AntennaEffectNode *head) {
    printf("Row | Column\n");
    printf("-------------\n");
    while (head) {
        printf(" %d  |   %d\n", head->row, head->col);
        head = head->next;
    }
}

// Free all nodes in the effect linked list.
void clearAntennaEffectsList(AntennaEffectNode *head) {
    AntennaEffectNode *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Calculate effect positions for every pair of antennas with the same frequency.
// Formulas used:
//   L1 = (2 * row1 - row2, 2 * col1 - col2)
//   L2 = (2 * row2 - row1, 2 * col2 - col1)
void computeEffectSpots(AntennaNode *antennas, AntennaEffectNode **effects) {
    for (AntennaNode *a = antennas; a != NULL; a = a->next) {
        for (AntennaNode *b = a->next; b != NULL; b = b->next) {
            if (a->frequency == b->frequency) {
                int l1_row = 2 * a->row - b->row;
                int l1_col = 2 * a->col - b->col;
                int l2_row = 2 * b->row - a->row;
                int l2_col = 2 * b->col - a->col;
                insertAntennaEffect(effects, l1_row, l1_col);
                insertAntennaEffect(effects, l2_row, l2_col);
            }
        }
    }
}