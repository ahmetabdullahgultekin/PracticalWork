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
void show_menu(void) {
    puts(TR(STR_INFO_MENU_TITLE));
    puts(TR(STR_INFO_MENU_OPTIONS));
    fputs(TR(STR_INFO_PROMPT_CHOICE), stdout);
    fflush(stdout);
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
    printf("(%d,%d) %c\n", v->row, v->col, v->freq);
    return STATUS_OK;
}

/*int main(void) {
    Graph *g = NULL;

    for (;;) {
        show_menu();
        int choice = read_int();
        if (choice < 0) continue;

        if (choice == 0) {
            puts(TR(STR_INFO_SUCCESS_QUIT));
            break;
        }

        char path[128];
        size_t idx1, idx2;
        char freqA, freqB;
        PathSet paths;
        CoordList inters;

        switch (choice) {
            case 1:
                promptFilename(path, 1);
                path[strcspn(path, "\n")] = '\0';
                if (graph_from_matrix_file(&g, path) == STATUS_OK)
                    puts(TR(STR_INFO_SUCCESS_LOAD));
                else
                    puts(TR(STR_ERR_IO));
                break;

            case 2: // DFS
                if (!g) {
                    puts(TR(STR_ERR_FILE_NOT_LOADED));
                    break;
                }
                printf(TR(STR_INFO_VERTEX_INDEX), graph_vertex_count(g) - 1);
                idx1 = (size_t) read_int();
                graph_dfs(g, idx1, print_vertex, NULL);
                break;

            case 3: // BFS
                if (!g) {
                    puts(TR(STR_ERR_FILE_NOT_LOADED));
                    break;
                }
                printf(TR(STR_INFO_VERTEX_INDEX), graph_vertex_count(g) - 1);
                idx1 = (size_t) read_int();
                graph_bfs(g, idx1, print_vertex, NULL);
                break;

            case 4: // All paths
                if (!g) {
                    puts(TR(STR_ERR_FILE_NOT_LOADED));
                    break;
                }
                printf(TR(STR_INFO_SOURCE_INDEX));
                idx1 = (size_t) read_int();
                printf(TR(STR_INFO_DEST_INDEX));
                idx2 = (size_t) read_int();
                if (graph_all_paths(g, idx1, idx2, &paths) != STATUS_OK) {
                    puts(TR(STR_ERR_NOT_IMPLEMENTED));
                    break;
                }
                for (size_t p = 0; p < paths.count; ++p) {
                    for (size_t s = 0; s < paths.path[p].len; ++s) {
                        const Vertex *v = graph_vertex_at(g, paths.path[p].idx[s]);
                        printf("(%d,%d)%s", v->row, v->col, s + 1 == paths.path[p].len ? "" : " -> ");
                    }
                    puts("");
                }
                // TODO free PathSet helper
                break;

            case 5: // Intersections
                if (!g) {
                    puts(TR(STR_ERR_FILE_NOT_LOADED));
                    break;
                }

                // Initialize CoordList
                inters.coord = NULL;
                inters.count = 0;

                printf(TR(STR_INFO_FREQUENCY_A));
                freqA = getchar();
                while (getchar() != '\n'); // Clear input buffer

                printf(TR(STR_INFO_FREQUENCY_B));
                freqB = getchar();
                while (getchar() != '\n'); // Clear input buffer

                // Call graph_intersections and check for errors
                if (graph_intersections(g, freqA, freqB, &inters) != STATUS_OK) {
                    puts(TR(STR_ERR_NOT_IMPLEMENTED));
                    break;
                }

                // Print intersections
                for (size_t i = 0; i < inters.count; ++i) {
                    printf("(%d,%d)\n", inters.coord[i].row, inters.coord[i].col);
                }

                // Free CoordList resources
                free(inters.coord);
                inters.coord = NULL;
                break;

            default:
                puts(TR(STR_ERR_INVALID_CHOICE));
        }
    }

    graph_free(&g);
    return 0;
}*/
