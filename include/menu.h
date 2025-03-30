/**
 * @file menu.h
 * @brief Header file for menu functions.
 * @author Ahmet Abdullah GULTEKIN
 * @date 2025-03-30
 */
#ifndef PRACTICALWORK_MENU_H
#define PRACTICALWORK_MENU_H

#include "antenna.h"
#include "antenna_effect.h"

void showMenu();

int requestUserChoice();

void proceedUserPreference(int choice, AntennaNode **antennaList, AntennaEffectNode **effectList);

int isChoiceValid(int choice);

#endif //PRACTICALWORK_MENU_H
