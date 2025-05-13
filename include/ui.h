#ifndef PRACTICALWORK_UI_H
#define PRACTICALWORK_UI_H

#include "../include/graph.h"

/**
 * @file ui.h
 * @brief Header file for the user interface functions.
 * @details This file contains the declarations of functions used for
 * interacting with the user via the console, including displaying menus,
 * reading input, and printing graph vertices.
 *
 * @author Ahmet Abdullah GULTEKIN
 * @date 2025-05-11
 */


/**
 * @brief Displays the main menu to the user.
 * @details This function prints the available options in the program's menu
 * and prompts the user to make a selection.
 */

void show_menu(void);

/**
 * @brief Reads an integer input from the user.
 * @details This function reads a line of input from the user, converts it
 * to an integer, and returns the result. If the input is invalid, it returns -1.
 *
 * @return The integer value entered by the user, or -1 if the input is invalid.
 */

int read_int(void);

/**
 * @brief Callback function to print a vertex.
 * @details This function is used as a callback during graph traversal
 * (e.g., DFS or BFS) to print the details of a vertex.
 *
 * @param v Pointer to the vertex to be printed.
 * @param ctx Context pointer (unused in this implementation).
 * @return `STATUS_OK` if the vertex is printed successfully.
 */

Status print_vertex(const Vertex *v, void *ctx);

#endif // PRACTICALWORK_UI_H
