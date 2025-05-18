/**
 * @file ui.c
 * @brief Console front-end implementation for the antenna effect program.
 * @details This file contains the implementation of user interface functions
 * for interacting with the user via the console. It includes functions to
 * display menus, read user input, and print graph vertices. All stdout/stderr
 * interaction is handled here to keep core logic pure and testable.
 *
 * @note Language strings are embedded at compile time via `strings.h`.
 * @author Ahmet Abdullah GULTEKIN
 * @date 2025-05-11
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/strings.h"
#include "../include/graph.h"
#include "../include/ui.h"
#include "../include/io_ops.h"

/**
 * @brief Displays the main menu to the user.
 * @details Prints the program's menu options and prompts the user to make a selection.
 */
int show_menu(void) {
    puts(TR(STR_INFO_MENU_TITLE));
    puts(TR(STR_INFO_MENU_OPTIONS));
    printf("%s [0,13]:", TR(STR_INFO_PROMPT_CHOICE));
    fflush(stdout);

    return 0;
}

/**
 * @brief Reads an integer input from the user.
 * @details Reads a line of input, converts it to an integer, and returns the result.
 * If the input is invalid, it returns -1.
 *
 * @return The integer value entered by the user, or -1 if the input is invalid.
 */
int read_int(void) {
    char buf[32];
    if (!fgets(buf, sizeof(buf), stdin)) return -1;
    char *conversionResult;
    int value = (int) strtol(buf, &conversionResult, 10);

    // Check that input contained a number and consumed only the newline.
    if (conversionResult == buf || (*conversionResult != '\n' && *conversionResult != '\0')) {
        return -1;
    }
    return value;
}

/**
 * @brief Callback function to print a vertex during graph traversal.
 * @details Prints the details of a vertex, including its row, column, and frequency.
 *
 * @param v Pointer to the vertex to be printed.
 * @param ctx Context pointer (unused in this implementation).
 * @return `STATUS_OK` if the vertex is printed successfully.
 */
Status print_vertex(const Vertex *v, void *ctx) {
    (void) ctx;
    printf("\n%s (%d,%d) | %s %c",
           TR(STR_INFO_COORDINATES), v->col, v->row,
           TR(STR_INFO_FREQUENCY), v->freq);
    return STATUS_OK;
}