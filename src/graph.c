/**
 * @file graph.c
 * @brief Implementation of the graph data structure and its functions.
 *
 * This file contains the implementation of the graph data structure
 * and its associated functions. The graph is represented as an
 * adjacency list, where each vertex is associated with a list
 * of its neighbors.
 *
 * @details
 * This implementation includes functions for initializing
 * the graph, adding vertices and edges, performing
 * depth-first and breadth-first searches, and
 * computing intersections.
 *
 * @note
 * The graph is designed to be memory-safe and printf-free.
 *
 * @author Ahmet Abdullah GULTEKIN
 * @date 2025-04-24
 *
 * @see graph.h for the header file containing the function prototypes
 * and data structures.
 *
 */

/**
 * ------------------------------------------------------------
 *  Memory-safe, printf-free implementation of the GR data type
 *  declared in graph.h.  All functions return Status codes.
 *  Stub bodies are marked TODO – fill them with full logic as
 *  you progress.  The current version *compiles* (tests build)
 *  but several functions still return STATUS_INVALID.
 * ------------------------------------------------------------
 */

#include <stdio.h>      /* FILE, fgets – internal only */
#include <stdlib.h>     /* malloc, free */
#include <string.h>     /* strlen */
#include <ctype.h>      /* isprint */
#include "../include/graph.h"

/**
 * ---------------------------------------------------------
 *  Graph data structure
 * ---------------------------------------------------------
 */
static Status ensure_capacity(Graph *g);

static Status add_vertex(Graph *g, char freq, int row, int col, size_t *out_idx);

static Status add_edge(Graph *g, size_t src, size_t dst);

/* --------------------------------------------------------- */
/* Public API                                                */
/* --------------------------------------------------------- */

Status graph_init(Graph **pg, size_t reserve) {
    if (!pg) return STATUS_INVALID;
    *pg = NULL;

    Graph *g = calloc(1, sizeof(Graph));
    if (!g) return STATUS_ALLOC;

    g->cap = reserve ? reserve : 4;
    g->v = calloc(g->cap, sizeof(Vertex));
    g->adj = calloc(g->cap, sizeof(EdgeNode *));
    if (!g->v || !g->adj) {
        free(g->v);
        free(g->adj);
        free(g);
        return STATUS_ALLOC;
    }

    *pg = g;
    return STATUS_OK;
}

Status graph_free(Graph **pg) {
    if (!pg || !*pg) return STATUS_INVALID;

    Graph *g = *pg;
    for (size_t i = 0; i < g->n; ++i) {
        EdgeNode *e = g->adj[i];
        while (e) {
            EdgeNode *tmp = e;
            e = e->next;
            free(tmp);
        }
    }
    free(g->adj);
    free(g->v);
    free(g);
    *pg = NULL;
    return STATUS_OK;
}

Status graph_clear_lists(Graph *g) {
    if (!g) return STATUS_INVALID;

    for (size_t i = 0; i < g->n; ++i) {
        EdgeNode *e = g->adj[i];
        while (e) {
            EdgeNode *tmp = e;
            e = e->next;
            free(tmp);
        }
        g->adj[i] = NULL;
    }
    return STATUS_OK;
}

Status graph_save_matrix(const Graph *g, const char *path) {
    if (!g || !path)
        return STATUS_INVALID;

    // Determine grid dimensions based on vertices.
    int max_row = 0, max_col = 0;
    for (size_t i = 0; i < g->n; i++) {
        if (g->v[i].row > max_row)
            max_row = g->v[i].row;
        if (g->v[i].col > max_col)
            max_col = g->v[i].col;
    }
    int rows = max_row + 1;
    int cols = max_col + 1;

    // Allocate 2D matrix (array of pointers to rows).
    char **matrix = malloc(rows * sizeof(char *));
    if (!matrix)
        return STATUS_ALLOC;

    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc((cols + 1) * sizeof(char)); // +1 for null-terminator.
        if (!matrix[i]) {
            for (int j = 0; j < i; j++)
                free(matrix[j]);
            free(matrix);
            return STATUS_ALLOC;
        }
        // Fill row with dots and terminate with null.
        memset(matrix[i], '.', cols);
        matrix[i][cols] = '\0';
    }

    // Place each vertex's frequency in the matrix.
    for (size_t i = 0; i < g->n; i++) {
        int r = g->v[i].row;
        int c = g->v[i].col;
        if (r < rows && c < cols)
            matrix[r][c] = g->v[i].freq;
    }

    // Open file for writing.
    FILE *fp = fopen(path, "w");
    if (!fp) {
        for (int i = 0; i < rows; i++)
            free(matrix[i]);
        free(matrix);
        return STATUS_WRITE;
    }

    // Write the matrix line by line.
    for (int i = 0; i < rows; i++) {
        if (fprintf(fp, "%s\n", matrix[i]) < 0) {
            fclose(fp);
            for (int j = 0; j < rows; j++)
                free(matrix[j]);
            free(matrix);
            return STATUS_WRITE;
        }
    }

    fclose(fp);

    // Clean up.
    for (int i = 0; i < rows; i++)
        free(matrix[i]);
    free(matrix);

    return STATUS_OK;
}

/* --------------------------------------------------------- */
/* Graph construction from matrix file                       */
/* --------------------------------------------------------- */

/* Helper: push vertex if char is printable & not dot. */
static inline bool is_antenna(char c) { return isprint((unsigned char) c) && c != '.' && c != '\n' && c != '\r'; }

Status graph_from_matrix_file(Graph **out_g, const char *path) {
    if (!out_g || !path) return STATUS_INVALID;

    FILE *fp = fopen(path, "r");
    if (!fp) return STATUS_IO;

    Status st = graph_init(out_g, 16);
    if (st != STATUS_OK) {
        fclose(fp);
        return st;
    }
    Graph *g = *out_g;

    char *line = NULL;
    size_t len = 0;
    size_t read;
    int row = 0;

    while ((read = custom_getlines(&line, &len, fp)) != -1) {
        for (int col = 0; col < read; ++col) {
            char c = line[col];
            if (is_antenna(c)) {
                size_t idx;
                st = add_vertex(g, c, row, col, &idx);
                if (st != STATUS_OK) { goto done; }
            }
        }
        row++;
    }

    /* Connect equal-frequency antennas with edges (undirected).  */
    for (size_t i = 0; i < g->n; ++i) {
        for (size_t j = i + 1; j < g->n; ++j) {
            if (g->v[i].freq == g->v[j].freq) {
                add_edge(g, i, j);
                add_edge(g, j, i);
            }
        }
    }

    st = STATUS_OK;

    done:
    free(line);
    fclose(fp);
    if (st != STATUS_OK) graph_free(out_g);
    return st;
}

// Insert a vertex into the graph
Status graph_insert_vertex(Graph *g, char freq, int row, int col) {
    if (!g) return STATUS_INVALID;
    size_t idx;
    Status st = add_vertex(g, freq, row, col, &idx);
    if (st != STATUS_OK) return st;

    // Connect the new vertex to existing vertices with the same frequency
    for (size_t i = 0; i < g->n - 1; ++i) {
        if (g->v[i].freq == freq) {
            add_edge(g, idx, i);
            add_edge(g, i, idx);
        }
    }
    return STATUS_OK;
}

// Remove a vertex from the graph
Status graph_remove_vertex(Graph *g, size_t idx) {
    if (!g || idx >= g->n) return STATUS_INVALID;

    // Free the edges of the vertex to be removed
    EdgeNode *e = g->adj[idx];
    while (e) {
        EdgeNode *tmp = e;
        e = e->next;
        free(tmp);
    }
    g->adj[idx] = NULL;

    // Shift vertices and edges down
    for (size_t i = idx; i < g->n - 1; ++i) {
        g->v[i] = g->v[i + 1];
        g->adj[i] = g->adj[i + 1];
    }
    g->n--;

    return STATUS_OK;
}

/* --------------------------------------------------------- */
/* Traversals (DFS & BFS)                                     */
/* --------------------------------------------------------- */

Status graph_dfs(const Graph *g, size_t start, VisitFn fn, void *ctx) {
    if (!g || start >= g->n || !fn) return STATUS_INVALID;
    Status st;

    bool *vis = calloc(g->n, sizeof(bool));
    if (!vis) return STATUS_ALLOC;

    // Iterative stack to avoid deep recursion
    size_t *stack = calloc(g->n, sizeof(size_t));
    if (!stack) {
        free(vis);
        return STATUS_ALLOC;
    }
    size_t top = 0;
    stack[top++] = start;

    while (top) {
        size_t v = stack[--top];
        if (vis[v]) continue;
        vis[v] = true;

        st = fn(&g->v[v], ctx);
        if (st != STATUS_OK) goto done;

        for (EdgeNode *e = g->adj[v]; e; e = e->next) {
            if (!vis[e->dest]) stack[top++] = e->dest;
        }
    }
    st = STATUS_OK;

    done:
    free(stack);
    free(vis);
    return st;
}

Status graph_bfs(const Graph *g, size_t start, VisitFn fn, void *ctx) {
    if (!g || start >= g->n || !fn) return STATUS_INVALID;
    Status st;

    bool *vis = calloc(g->n, sizeof(bool));
    size_t *queue = calloc(g->n, sizeof(size_t));
    if (!vis || !queue) {
        free(vis);
        free(queue);
        return STATUS_ALLOC;
    }

    size_t head = 0, tail = 0;
    queue[tail++] = start;
    vis[start] = true;

    while (head < tail) {
        size_t v = queue[head++];
        st = fn(&g->v[v], ctx);
        if (st != STATUS_OK) goto done;
        for (EdgeNode *e = g->adj[v]; e; e = e->next) {
            if (!vis[e->dest]) {
                vis[e->dest] = true;
                queue[tail++] = e->dest;
            }
        }
    }
    st = STATUS_OK;

    done:
    free(vis);
    free(queue);
    return st;
}

Status graph_all_paths(const Graph *g, size_t src, size_t dst, PathSet *out) {
    if (!g || src >= g->n || dst >= g->n || !out) return STATUS_INVALID;

    out->path = NULL;
    out->count = 0;

    size_t *stack = calloc(g->n, sizeof(size_t));
    bool *visited = calloc(g->n, sizeof(bool));
    if (!stack || !visited) {
        free(stack);
        free(visited);
        return STATUS_ALLOC;
    }

    size_t top = 0;
    stack[top++] = src;

    Path current_path = {.idx = calloc(g->n, sizeof(size_t)), .len = 0};
    if (!current_path.idx) {
        free(stack);
        free(visited);
        return STATUS_ALLOC;
    }

    Status st = STATUS_OK;

    while (top) {
        size_t v = stack[--top];
        visited[v] = true;
        current_path.idx[current_path.len++] = v;

        if (v == dst) {
            Path *new_paths = realloc(out->path, (out->count + 1) * sizeof(Path));
            if (!new_paths) {
                st = STATUS_ALLOC;
                break;
            }
            out->path = new_paths;
            out->path[out->count].idx = malloc(current_path.len * sizeof(size_t));
            if (!out->path[out->count].idx) {
                st = STATUS_ALLOC;
                break;
            }
            memcpy(out->path[out->count].idx, current_path.idx, current_path.len * sizeof(size_t));
            out->path[out->count].len = current_path.len;
            out->count++;
        } else {
            for (EdgeNode *e = g->adj[v]; e; e = e->next) {
                if (!visited[e->dest]) {
                    stack[top++] = e->dest;
                }
            }
        }

        if (top && stack[top - 1] != dst) {
            visited[v] = false;
            current_path.len--;
        }
    }

    free(stack);
    free(visited);
    free(current_path.idx);

    if (st != STATUS_OK) {
        for (size_t i = 0; i < out->count; ++i) {
            free(out->path[i].idx);
        }
        free(out->path);
        out->path = NULL;
        out->count = 0;
    }

    return st;
}

Status graph_intersections(const Graph *g, char freqA, char freqB, CoordList *out) {
    if (!g || !out) return STATUS_INVALID;

    out->coord = NULL;
    out->count = 0;

    // Allocate memory for storing intersections
    size_t capacity = 16;
    out->coord = malloc(capacity * sizeof(Coord));
    if (!out->coord) return STATUS_ALLOC;

    for (size_t i = 0; i < g->n; ++i) {
        if (g->v[i].freq == freqA) {
            for (size_t j = 0; j < g->n; ++j) {
                if (g->v[j].freq == freqB && g->v[i].row == g->v[j].row && g->v[i].col == g->v[j].col) {
                    // Resize if necessary
                    if (out->count == capacity) {
                        capacity *= 2;
                        Coord *new_coord = realloc(out->coord, capacity * sizeof(Coord));
                        if (!new_coord) {
                            free(out->coord);
                            return STATUS_ALLOC;
                        }
                        out->coord = new_coord;
                    }
                    // Add intersection
                    out->coord[out->count++] = (Coord) {.row = g->v[i].row, .col = g->v[i].col};
                }
            }
        }
    }

    return STATUS_OK;
}

/* --------------------------------------------------------- */
/* Getters                                                   */
/* --------------------------------------------------------- */

size_t graph_vertex_count(const Graph *g) { return g ? g->n : 0; }

const Vertex *graph_vertex_at(const Graph *g, size_t idx) {
    return (g && idx < g->n) ? &g->v[idx] : NULL;
}

/* --------------------------------------------------------- */
/* Private helpers                                           */
/* --------------------------------------------------------- */

static Status ensure_capacity(Graph *g) {
    if (g->n < g->cap) return STATUS_OK;
    size_t new_cap = g->cap * 2;
    Vertex *nv = realloc(g->v, new_cap * sizeof(Vertex));
    EdgeNode **na = realloc(g->adj, new_cap * sizeof(EdgeNode *));
    if (!nv || !na) return STATUS_ALLOC;

    /* zero new adj slots */
    memset(na + g->cap, 0, (new_cap - g->cap) * sizeof(EdgeNode *));

    g->v = nv;
    g->adj = na;
    g->cap = new_cap;
    return STATUS_OK;
}

static Status add_vertex(Graph *g, char freq, int row, int col, size_t *out_idx) {
    Status st = ensure_capacity(g);
    if (st != STATUS_OK) return st;

    size_t idx = g->n++;
    g->v[idx] = (Vertex) {.freq = freq, .row = row, .col = col};
    if (out_idx) *out_idx = idx;
    return STATUS_OK;
}

static Status add_edge(Graph *g, size_t src, size_t dst) {
    EdgeNode *node = malloc(sizeof(EdgeNode));
    if (!node) return STATUS_ALLOC;
    node->dest = dst;
    node->next = g->adj[src];
    g->adj[src] = node;
    return STATUS_OK;
}