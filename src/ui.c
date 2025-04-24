/*
 * ui.c – Console front‑end (Phase 2)
 * -------------------------------------------------------------
 *  All stdout/stderr interaction lives here so that core logic
 *  (graph.c, lang.c, …) stays pure and testable.
 *
 *  Usage
 *  -----
 *      $ ./antenna_phase2
 *      Choose language [en/pt] > pt
 *      ============================
 *              MENU PRINCIPAL
 *      ============================
 *      1. Carregar matriz
 *      2. DFS a partir de antena
 *      3. BFS a partir de antena
 *      4. Todos os caminhos entre duas antenas
 *      5. Intersecções (freq A vs B)
 *      0. Sair
 * -------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/lang.h"

/* ---------------------------------------------------------------- */
/*  Helpers                                                         */
/* ---------------------------------------------------------------- */

static void show_menu(void)
{
    puts(tr(MSG_MENU_TITLE));
    printf("%s", tr(MSG_MENU_OPTIONS));
    fputs(tr(MSG_PROMPT_CHOICE), stdout);
    fflush(stdout);
}

static int read_int(void)
{
    char buf[32];
    if (!fgets(buf, sizeof(buf), stdin)) return -1;
    return (int)strtol(buf, NULL, 10);
}

/* Callback that prints a vertex (used by DFS/BFS) */
static Status print_vertex(const Vertex *v, void *ctx)
{
    (void)ctx;
    printf("(%d,%d) %c\n", v->row, v->col, v->freq);
    return STATUS_OK;
}

/* ---------------------------------------------------------------- */
/*  Main interactive loop                                           */
/* ---------------------------------------------------------------- */

int main(void)
{
    Status st = STATUS_OK;
    /* ask language */
    printf("Choose language [en/pt/tr] > ");
    char lang[4] = "en";
    fgets(lang, sizeof(lang), stdin);
    lang[strcspn(lang, "\n")] = '\0';
    st = lang_init(lang);
    switch (st) {
        case STATUS_OK:
            break;
        case STATUS_IO:
            puts("Language file not found, falling back to English\n");
            lang_init("en");
            break;
        default:
            puts("Unknown error, falling back to English\n");
            lang_init("en");
    }

    Graph *g = NULL;

    for (;;) {
        show_menu();
        int choice = read_int();
        if (choice < 0) continue;

        if (choice == 0) {
            puts(tr(MSG_SUCCESS_QUIT));
            break;
        }

        /*Status st = STATUS_OK;*/
        char path[128];
        size_t idx1, idx2;
        char freqA, freqB;
        PathSet paths;
        CoordList inters;

        switch (choice) {
            case 1: /* load */
                printf("File path: ");
                if (!fgets(path, sizeof(path), stdin)) break;
                path[strcspn(path, "\n")] = '\0';
                st = graph_from_matrix_file(&g, path);
                puts(st == STATUS_OK ? tr(MSG_SUCCESS_LOAD) : tr(MSG_ERR_IO));
                break;

            case 2: /* DFS */
                if (!g) { puts("Load matrix first\n"); break; }
                printf("Vertex index (0-%zu): ", graph_vertex_count(g)-1);
                idx1 = (size_t)read_int();
                graph_dfs(g, idx1, print_vertex, NULL);
                break;

            case 3: /* BFS */
                if (!g) { puts("Load matrix first\n"); break; }
                printf("Vertex index (0-%zu): ", graph_vertex_count(g)-1);
                idx1 = (size_t)read_int();
                graph_bfs(g, idx1, print_vertex, NULL);
                break;

            case 4: /* all paths */
                if (!g) { puts("Load matrix first\n"); break; }
                printf("Source index: "); idx1 = (size_t)read_int();
                printf("Dest   index: "); idx2 = (size_t)read_int();
                st = graph_all_paths(g, idx1, idx2, &paths);
                if (st != STATUS_OK) { puts("Not implemented\n"); break; }
                for (size_t p = 0; p < paths.count; ++p) {
                    for (size_t s = 0; s < paths.path[p].len; ++s) {
                        const Vertex *v = graph_vertex_at(g, paths.path[p].idx[s]);
                        printf("(%d,%d)%s", v->row, v->col, s+1==paths.path[p].len?"":" -> ");
                    }
                    puts("");
                }
                /* TODO free PathSet helper */
                break;

            case 5: /* intersections */
                if (!g) { puts("Load matrix first\n"); break; }
                printf("Frequency A: "); freqA = getchar(); while(getchar()!='\n');
                printf("Frequency B: "); freqB = getchar(); while(getchar()!='\n');
                st = graph_intersections(g, freqA, freqB, &inters);
                if (st != STATUS_OK) { puts("Not implemented\n"); break; }
                for (size_t i = 0; i < inters.count; ++i)
                    printf("(%d,%d)\n", inters.coord[i].row, inters.coord[i].col);
                /* TODO free CoordList helper */
                break;

            default:
                puts("Unknown option\n");
        }
    }

    graph_free(&g);
    lang_close();
    return 0;
}