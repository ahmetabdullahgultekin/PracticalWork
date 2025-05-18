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

/**
 * @fn showMenu
 * @brief Displays the main menu to the user.
 */
void showMenu();

/**
 * @fn requestUserChoice
 * @brief Prompts the user for a choice from the menu.
 * @return The user's choice as an integer.
 */
int requestUserChoice();

/**
 * @fn proceedUserPreference
 * @brief Processes the user's choice and executes the corresponding action.
 * @param choice The user's choice as an integer.
 * @param antennaList Pointer to the list of antennas.
 * @param effectList Pointer to the list of antenna effects.
 */
void proceedUserPreference(int choice, AntennaNode **antennaList, AntennaEffectNode **effectList);

/**
 * @fn isChoiceValid
 * @brief Validates the user's choice.
 * @param choice The user's choice as an integer.
 * @return 1 if the choice is valid, 0 otherwise.
 */
int isChoiceValid(int choice);

#endif //PRACTICALWORK_MENU_H
