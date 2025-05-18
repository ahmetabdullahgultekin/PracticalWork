/**
 * @file main.c
 * @brief Main file for the antenna effect program.
 *
 * This file contains the main function and the implementation of the menu system.
 * It allows the user to interact with the program and perform various operations related to antennas and their effects.
 *
 * @author Ahmet Abdullah GULTEKIN
 * @date 2025-05-18
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/strings.h"
#include "../include/graph.h"
#include "../include/io_ops.h"
#include "../include/ui.h"

/**
 * @fn main
 *
 * @brief Main function for the antenna effect program.
 * Start an infinite loop to display the menu, read the user's choice, and handle the choice.
 *
 * @return 0 if the program exits successfully
 *
 * @return EXIT_FAILURE if there is an error
 */
/* Fase 1 main function
int main() {
    // Initialize the linked lists
    AntennaNode *antennaList = NULL;
    AntennaEffectNode *effectList = NULL;

    // Main loop
    while (1) {
        // Display the menu
        showMenu();
        // Read the user's choice and Handle the user's choice
        proceedUserPreference(requestUserChoice(), &antennaList, &effectList);
    }
}*/

/**
 * @fn main
 *
 * @brief Main function for the antenna program.
 * Start an infinite loop to display the menu, read the user's choice, and handle the choice.
 *
 * @return 0 if the program exits successfully
 *
 * @return EXIT_FAILURE if there is an error
 */
int main(void) {
    Graph *g = NULL;

    for (;;) {
        show_menu();
        int choice = read_int();
        if (choice < 0) continue;

        if (choice == 0) {
            puts(TR(STR_INFO_SUCCESS_QUIT));
            break;
        }

        char path[128] = INPUT_PATH;
        size_t idx1, idx2 = 0;
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
                printf("\n%s [0-%zu]:", TR(STR_INFO_VERTEX_INDEX), graph_vertex_count(g) - 1);
                idx1 = (size_t) read_int();
                if (graph_dfs(g, idx1, print_vertex, NULL) != STATUS_OK) {
                    puts(TR(STR_ERR_NOT_IMPLEMENTED));
                    break;
                }
                break;

            case 3: // BFS
                if (!g) {
                    puts(TR(STR_ERR_FILE_NOT_LOADED));
                    break;
                }
                printf("\n%s [0-%zu]:", TR(STR_INFO_VERTEX_INDEX), graph_vertex_count(g) - 1);
                idx1 = (size_t) read_int();
                graph_bfs(g, idx1, print_vertex, NULL);
                break;

            case 4: // All paths
                if (!g) {
                    puts(TR(STR_ERR_FILE_NOT_LOADED));
                    break;
                }
                printf("\n%s [0-%zu]:", TR(STR_INFO_SOURCE_INDEX), graph_vertex_count(g) - 1);
                idx1 = (size_t) read_int();
                printf("\n%s [0-%zu]:", TR(STR_INFO_DEST_INDEX), graph_vertex_count(g) - 1);
                idx2 = (size_t) read_int();

                // Check if frequencies are equal
                if (graph_vertex_at(g, idx1)->freq != graph_vertex_at(g, idx2)->freq) {
                    puts(TR(STR_ERR_FREQUENCY_NOT_EQUAL));
                    break;
                }

                if (graph_all_paths(g, idx1, idx2, &paths) != STATUS_OK) {
                    puts(TR(STR_ERR_NOT_IMPLEMENTED));
                    break;
                }

                printf("\n%s:", TR(STR_INFO_PATHS_FOUND));
                // Print paths
                for (size_t p = 0; p < paths.count; ++p) {
                    printf("\n%zu. %s\n", p + 1, TR(STR_INFO_PATH));
                    for (size_t s = 0; s < paths.path[p].len; ++s) {
                        const Vertex *v = graph_vertex_at(g, paths.path[p].idx[s]);
                        printf("%s %zu | %s %c | %s (%d,%d)\n",
                               TR(STR_INFO_INDEX), paths.path[p].idx[s],
                               TR(STR_INFO_FREQUENCY), v->freq,
                               TR(STR_INFO_COORDINATES), v->col, v->row);
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

                printf("\n%s", TR(STR_INFO_FREQUENCY_A));
                freqA = getchar();
                while (getchar() != '\n'); // Clear input buffer

                printf("\n%s", TR(STR_INFO_FREQUENCY_B));
                freqB = getchar();
                while (getchar() != '\n'); // Clear input buffer

                // Call graph_intersections and check for errors
                if (graph_intersections(g, freqA, freqB, &inters) != STATUS_OK) {
                    puts(TR(STR_ERR_NOT_IMPLEMENTED));
                    break;
                }

                // Check if intersections were found
                if (inters.count == 0) {
                    printf("\n%s", TR(STR_ERR_INTERSECTIONS_NOT_FOUND));
                    goto endIntersections;
                }

                // Print intersections
                for (size_t i = 0; i < inters.count; ++i) {
                    printf("\n(%d,%d)", inters.coord[i].row, inters.coord[i].col);
                }

            endIntersections:
                // Free CoordList resources
                free(inters.coord);
                inters.coord = NULL;
                break;
            case 6: // Danger overlaps
                if (!g) {
                    puts(TR(STR_ERR_GRAPH_COULD_NOT_FIND));
                    break;
                }
                printf("\n%s", TR(STR_INFO_FREQUENCY_A));
                freqA = getchar();
                while (getchar() != '\n'); // Clear input buffer

                printf("\n%s", TR(STR_INFO_FREQUENCY_B));
                freqB = getchar();
                while (getchar() != '\n'); // Clear input buffer

                if (graph_danger_overlaps(g, freqA, freqB, &inters) != STATUS_OK) {
                    puts(TR(STR_ERR_NOT_IMPLEMENTED));
                    break;
                }

                if (inters.count == 0) {
                    printf("\n%s", TR(STR_ERR_INTERSECTIONS_NOT_FOUND));
                    goto endOverlaps;
                }

                printf("\n%s:", TR(STR_INFO_DANGER_OVERLAPS));

                for (size_t i = 0; i < inters.count; ++i) {
                    printf("(%d,%d)\n", inters.coord[i].row, inters.coord[i].col);
                }


            endOverlaps:
                free(inters.coord);
                inters.coord = NULL;
                break;
            case 7: // Insert
                if (!g) {
                    puts(TR(STR_ERR_FILE_NOT_LOADED));
                    break;
                }
                printf("\n%s(x):", TR(STR_INFO_COORDINATES));
                idx1 = (size_t) read_int();
                printf("\n%s(y):", TR(STR_INFO_COORDINATES));
                idx2 = (size_t) read_int();
                printf("\n%s", TR(STR_INFO_FREQUENCY_A));
                freqA = getchar();
                while (getchar() != '\n'); // Clear input buffer
                graph_insert_vertex(g, freqA, idx1, idx2);
                break;
            case 8: // Remove
                if (!g) {
                    puts(TR(STR_ERR_FILE_NOT_LOADED));
                    break;
                }
                printf(TR(STR_INFO_VERTEX_INDEX), graph_vertex_count(g) - 1);
                idx1 = (size_t) read_int();
                graph_remove_vertex(g, idx1);
                break;
            case 9: // Print antennas
                if (!g) {
                    puts(TR(STR_ERR_FILE_NOT_LOADED));
                    break;
                }
                if (graph_vertex_count(g) == 0) {
                    puts(TR(STR_ERR_GRAPH_COULD_NOT_FIND));
                    break;
                }
                for (size_t i = 0; i < g->n; ++i) {
                    const Vertex *v = graph_vertex_at(g, i);
                    printf("\n%s %zu | %s %c | %s (%d,%d)",
                           TR(STR_INFO_INDEX), i,
                           TR(STR_INFO_FREQUENCY), v->freq,
                           TR(STR_INFO_COORDINATES), v->col, v->row);
                }
                break;
            case 10: // Print edges
                if (!g) {
                    puts(TR(STR_ERR_FILE_NOT_LOADED));
                    break;
                }
                if (graph_vertex_count(g) == 0) {
                    puts(TR(STR_ERR_GRAPH_COULD_NOT_FIND));
                    break;
                }
                for (size_t i = 0; i < g->n; ++i) {
                    const Vertex *v = graph_vertex_at(g, i);
                    printf("\n%s %zu | %s %c | %s (%d,%d)",
                           TR(STR_INFO_INDEX), i,
                           TR(STR_INFO_FREQUENCY), v->freq,
                           TR(STR_INFO_COORDINATES), v->col, v->row);
                    for (EdgeNode *e = g->adj[i]; e != NULL; e = e->next) {
                        printf(" -> %zu", e->dest);
                    }
                }
                break;
            case 11: // Print Danger Points
                if (!g) {
                    puts(TR(STR_ERR_FILE_NOT_LOADED));
                    break;
                }
                if (graph_vertex_count(g) == 0) {
                    puts(TR(STR_ERR_GRAPH_COULD_NOT_FIND));
                    break;
                }
                char frequenceA;
                printf("\n%s", TR(STR_INFO_FREQUENCY_A));
                int ch;
                do { ch = getchar(); } while (ch == '\n' || ch == ' ');
                frequenceA = (char) ch;
                while (getchar() != '\n'); // clear buffer

                Coord danger[2048];
                size_t count = 0;
                Status st = compute_danger_points(g, frequenceA, danger, &count);
                if (st != STATUS_OK)
                    puts(TR(STR_ERR_NOT_IMPLEMENTED));

                printf("\n%s %c:\n", TR(STR_INFO_DANGER_POINTS), frequenceA);
                for (size_t i = 0; i < count; ++i) {
                    printf("(%d, %d)\n", danger[i].row, danger[i].col);
                }
                if (count == 0) puts("None.");
                break;
            case 12: // Clear lists
                if (!g) {
                    puts(TR(STR_ERR_GRAPH_COULD_NOT_FIND));
                    break;
                }
                if (graph_clear_lists(g) != STATUS_OK) {
                    puts(TR(STR_ERR_GRAPH_COULD_NOT_CLEARED));
                    break;
                }
                puts(TR(STR_INFO_LISTS_CLEARED));
                break;
            case 13: // Save matrix
                if (!g) {
                    puts(TR(STR_ERR_FILE_NOT_LOADED));
                    break;
                }
                promptFilename(path, 0);
                path[strcspn(path, "\n")] = '\0';
                if (graph_save_matrix(g, path) == STATUS_OK)
                    puts(TR(STR_INFO_SUCCESS_SAVE));
                else
                    puts(TR(STR_ERR_IO));
                break;
            default:
                puts(TR(STR_ERR_INVALID_CHOICE));
        }
    }

    graph_free(&g);
    return 0;
}
