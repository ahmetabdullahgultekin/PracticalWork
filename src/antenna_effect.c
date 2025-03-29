/**
 * @file antenna_effect.c
 * @author Ahmet Abdullah GULTEKIN
 * @brief Implementation of the antenna effect functions.
 * The antenna effect functions are used to manage the list of antenna effects.
 *
 * @date 2025-03-30
 */

#include "../include/antenna_effect.h"
#include "../include/antenna.h"
#include "../include/io_ops.h"

/**
 * @fn insertAntennaEffect
 *
 * @brief Insert a new effect position node into the linked list.
 *
 * @param head The head of the linked list
 * @param row The row of the effect
 * @param col The column of the effect
 * @return The newly created node
 */
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

/**
 * @fn isAntennaEffectExist
 *
 * @brief Check if an effect position exists in the linked list.
 *
 * @param head The head of the linked list
 * @param row The row of the effect
 * @param col The column of the effect
 * @return 1 if the effect position exists, 0 otherwise
 */
int isAntennaEffectExist(AntennaEffectNode *head, int row, int col) {
    while (head) {
        if (head->row == row && head->col == col)
            return 1;
        head = head->next;
    }
    return 0;
}

/**
 * @fn printAllAntennaEffects
 *
 * @brief Print the list of effect positions in a table format.
 *
 * @param head The head of the linked list
 */
void printAllAntennaEffects(AntennaEffectNode *head) {
    printf("Row | Column\n");
    printf("-------------\n");
    while (head) {
        printf(" %d  |   %d\n", head->row, head->col);
        head = head->next;
    }
}

/**
 * @fn clearAntennaEffectsList
 *
 * @brief Clear the linked list of effect positions.
 *
 * @param head The head of the linked list
 */
void clearAntennaEffectsList(AntennaEffectNode *head) {
    AntennaEffectNode *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

/**
 * @fn computeEffectSpots
 *
 * @brief Compute the effect positions of the antennas.
 * formula 1 = (2 * row1 - row2, 2 * col1 - col2)
 * formula 2 = (2 * row2 - row1, 2 * col2 - col1)
 *
 * @param antennas The list of antennas
 * @param effects The list of effect positions
 */
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

/**
 * @fn saveAntennaEffectsToFile
 *
 * @brief Save the list of antenna effects to a file.
 *
 * @param filename The name of the file to save antenna effects to
 * @param head The head of the linked list
 */
void saveAntennaEffectsToFile(const char *filename, AntennaEffectNode *head) {
    // Open the file for writing
    FILE *fp;
    // Declare file directory
    char fileDir[256] = OUTPUT_DIR;
    // Concatenate the filename to the directory
    strcat_s(fileDir, 256, filename);
    fopen_s(&fp, fileDir, "w");
    if (!fp) {
        printf("Cannot open file: %s\n", fileDir);
        exit(1);
    }

    // Write each antenna effect's details to the file
    while (head) {
        fprintf(fp, "%d %d\n", head->row, head->col);
        head = head->next;
    }

    // Close the file
    fclose(fp);
}