
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
 * @return  0 if the program exits successfully
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
            case 6: // Insert
                if (!g) {
                    puts(TR(STR_ERR_FILE_NOT_LOADED));
                    break;
                }
                printf(TR(STR_INFO_VERTEX_INDEX), graph_vertex_count(g) - 1);
                idx1 = (size_t) read_int();
                printf(TR(STR_INFO_FREQUENCY_A));
                freqA = getchar();
                while (getchar() != '\n'); // Clear input buffer
                graph_insert_vertex(g, freqA, idx1, idx2);
                break;
            case 7: // Remove
                if (!g) {
                    puts(TR(STR_ERR_FILE_NOT_LOADED));
                    break;
                }
                printf(TR(STR_INFO_VERTEX_INDEX), graph_vertex_count(g) - 1);
                idx1 = (size_t) read_int();
                graph_remove_vertex(g, idx1);
                break;
            case 8: // Print antennas
                if (!g) {
                    puts(TR(STR_ERR_FILE_NOT_LOADED));
                    break;
                }
                for (size_t i = 0; i < g->n; ++i) {
                    const Vertex *v = graph_vertex_at(g, i);
                    printf("%c -> (%d,%d)\n", v->freq, v->col, v->row);
                }
                break;
            case 9: // Clear lists
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
            case 10: // Save matrix
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
