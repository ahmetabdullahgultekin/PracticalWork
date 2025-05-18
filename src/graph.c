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

#include <stdio.h>      /* FILE, fgets – internal only */
#include <stdlib.h>     /* malloc, free */
#include <string.h>     /* strlen */
#include <ctype.h>      /* isprint */
#include "../include/graph.h"

#define MAX_DANGER 1024

/**
 * ---------------------------------------------------------
 *  Graph data structure
 * ---------------------------------------------------------
 */
/**
 * @fn ensure_capacity
 * @brief Ensures that the graph has enough capacity to store the given number of vertices.
 * @param g Pointer to the graph.
 * @return Status indicating success or failure.
 */
static Status ensure_capacity(Graph *g);

/**
 * @fn add_vertex
 * @brief Adds a vertex to the graph.
 * @param g Pointer to the graph.
 * @param freq Frequency of the vertex.
 * @param row Row index of the vertex.
 * @param col Column index of the vertex.
 * @param out_idx Pointer to store the index of the added vertex.
 * @return Status indicating success or failure.
 */
static Status add_vertex(Graph *g, char freq, int row, int col, size_t *out_idx);

/**
 * @fn add_edge
 * @brief Adds an edge between two vertices in the graph.
 * @param g Pointer to the graph.
 * @param src Source vertex index.
 * @param dst Destination vertex index.
 * @return Status indicating success or failure.
 */
static Status add_edge(Graph *g, size_t src, size_t dst);

/**
 * @fn graph_init
 * @brief Initializes a graph with a given initial capacity.
 * @param pg Pointer to the graph pointer.
 * @param reserve Initial capacity of the graph.
 * @return Status indicating success or failure.
 */
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

/**
 * @fn graph_free
 * @brief Frees the memory allocated for the graph.
 * @param pg Pointer to the graph pointer.
 * @return Status indicating success or failure.
 */
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

/**
 * @fn graph_clear_lists
 * @brief Clears the adjacency lists of the graph.
 * @param g Pointer to the graph.
 * @return Status indicating success or failure.
 */
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

/**
 * @fn graph_save_matrix
 * @brief Saves the graph as a matrix to a file.
 * @param g Pointer to the graph.
 * @param path Path to the output file.
 * @return Status indicating success or failure.
 */
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

/**
 * @fn is_antenna
 * @brief Checks if a character is an antenna.
 * @param c Character to check.
 * @return True if the character is an antenna, false otherwise.
 */
static inline bool is_antenna(char c) { return isprint((unsigned char) c) && c != '.' && c != '\n' && c != '\r'; }

/**
 * @fn graph_from_matrix_file
 * @brief Reads a matrix from a file and constructs a graph.
 * @param out_g Pointer to the graph pointer.
 * @param path Path to the input file.
 * @return Status indicating success or failure.
 */
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

/**
 * @fn graph_insert_vertex
 * @brief Inserts a vertex into the graph and connects it to existing vertices with the same frequency.
 * @param g Pointer to the graph.
 * @param freq Frequency of the vertex.
 * @param row Row index of the vertex.
 * @param col Column index of the vertex.
 * @return Status indicating success or failure.
 */
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

/**
 * @fn graph_remove_vertex
 * @brief Removes a vertex from the graph and its associated edges.
 * @param g Pointer to the graph.
 * @param idx Index of the vertex to remove.
 * @return Status indicating success or failure.
 */
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

/**
 * @fn graph_dfs
 * @brief Performs a depth-first search on the graph.
 * @param g Pointer to the graph.
 * @param start Starting vertex index.
 * @param fn Function to call for each visited vertex.
 * @param ctx Context pointer to pass to the function.
 * @return Status indicating success or failure.
 */
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

/**
 * @fn graph_bfs
 * @brief Performs a breadth-first search on the graph.
 * @param g Pointer to the graph.
 * @param start Starting vertex index.
 * @param fn Function to call for each visited vertex.
 * @param ctx Context pointer to pass to the function.
 * @return Status indicating success or failure.
 */
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

/**
 * @fn save_path
 * @brief Saves a path to the output structure.
 * @param out Pointer to the output structure.
 * @param path Pointer to the path array.
 * @param len Length of the path.
 * @return Status indicating success or failure.
 */
static Status save_path(PathSet *out, size_t *path, size_t len) {
    Path *new_paths = realloc(out->path, (out->count + 1) * sizeof(Path));
    if (!new_paths) return STATUS_ALLOC;
    out->path = new_paths;
    out->path[out->count].idx = malloc(len * sizeof(size_t));
    if (!out->path[out->count].idx) return STATUS_ALLOC;
    memcpy(out->path[out->count].idx, path, len * sizeof(size_t));
    out->path[out->count].len = len;
    out->count++;
    return STATUS_OK;
}

/**
 * @fn dfs_all_paths
 * @brief Depth-first search to find all paths from src to dst.
 * @param g Pointer to the graph.
 * @param current Current vertex index.
 * @param dst Destination vertex index.
 * @param visited Array of visited vertices.
 * @param path Array to store the current path.
 * @param path_len Length of the current path.
 * @param out Pointer to the output structure.
 * @return Status indicating success or failure.
 */
static Status dfs_all_paths(const Graph *g, size_t current, size_t dst,
                            bool *visited, size_t *path, size_t path_len,
                            PathSet *out) {
    visited[current] = true;
    path[path_len++] = current;

    if (current == dst) {
        Status st = save_path(out, path, path_len);
        visited[current] = false;
        return st;
    }

    for (EdgeNode *e = g->adj[current]; e; e = e->next) {
        if (!visited[e->dest]) {
            Status st = dfs_all_paths(g, e->dest, dst, visited, path, path_len, out);
            if (st != STATUS_OK) return st;
        }
    }

    visited[current] = false;
    return STATUS_OK;
}

/**
 * @fn graph_all_paths
 * @brief Finds all paths from src to dst in the graph.
 * @param g Pointer to the graph.
 * @param src Source vertex index.
 * @param dst Destination vertex index.
 * @param out Pointer to the output structure.
 * @return Status indicating success or failure.
 */
Status graph_all_paths(const Graph *g, size_t src, size_t dst, PathSet *out) {
    if (!g || src >= g->n || dst >= g->n || !out) return STATUS_INVALID;

    out->path = NULL;
    out->count = 0;

    bool *visited = calloc(g->n, sizeof(bool));
    if (!visited) return STATUS_ALLOC;

    size_t *path = malloc(g->n * sizeof(size_t));
    if (!path) {
        free(visited);
        return STATUS_ALLOC;
    }

    Status st = dfs_all_paths(g, src, dst, visited, path, 0, out);
    free(visited);
    free(path);

    return st;
}

/**
 * @fn graph_intersections
 * @brief Finds intersections of two frequencies in the graph.
 * @param g Pointer to the graph.
 * @param freqA Frequency A.
 * @param freqB Frequency B.
 * @param out Pointer to the output structure.
 * @return Status indicating success or failure.
 */
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

/**
 * @fn add_unique_coord
 * @brief Adds a unique coordinate to the array.
 * @param arr Array of coordinates.
 * @param count Pointer to the count of coordinates.
 * @param c Coordinate to add.
 */
static void add_unique_coord(Coord *arr, size_t *count, Coord c) {
    for (size_t i = 0; i < *count; ++i) {
        if (arr[i].row == c.row && arr[i].col == c.col) return;
    }
    arr[(*count)++] = c;
}

/**
 * @fn coord_in_set
 * @brief Checks if a coordinate is in the set.
 * @param arr Array of coordinates.
 * @param count Count of coordinates.
 * @param c Coordinate to check.
 * @return True if the coordinate is in the set, false otherwise.
 */
static bool coord_in_set(const Coord *arr, size_t count, Coord c) {
    for (size_t i = 0; i < count; ++i) {
        if (arr[i].row == c.row && arr[i].col == c.col) return true;
    }
    return false;
}

/**
 * @fn compute_danger_points
 * @brief Computes danger points based on the graph and frequency.
 * @param g Pointer to the graph.
 * @param freq Frequency to check.
 * @param danger Array to store danger points.
 * @param count Pointer to the count of danger points.
 */
static void compute_danger_points(const Graph *g, char freq, Coord *danger, size_t *count) {
    *count = 0;
    for (size_t i = 0; i < g->n; ++i) {
        if (g->v[i].freq != freq) continue;
        for (size_t j = i + 1; j < g->n; ++j) {
            if (g->v[j].freq != freq) continue;
            int dr = g->v[j].row - g->v[i].row;
            int dc = g->v[j].col - g->v[i].col;
            // Check alignment and double distance (horizontal, vertical, or diagonal)
            if ((dr == 0 && abs(dc) == 2) ||
                (dc == 0 && abs(dr) == 2) ||
                (abs(dr) == 2 && abs(dc) == 2)) {
                // Points between i and j, and the two sides:
                int mr = g->v[i].row + dr / 2;
                int mc = g->v[i].col + dc / 2;
                Coord c1 = {mr, mc};
                // Add both directions (i->j and j->i) for symmetry
                add_unique_coord(danger, count, c1);
            }
        }
    }
}

/**
 * @fn graph_danger_overlaps
 * @brief Finds overlapping danger points between two frequencies.
 * @param g Pointer to the graph.
 * @param freqA Frequency A.
 * @param freqB Frequency B.
 * @param out Pointer to the output structure.
 * @return Status indicating success or failure.
 */
Status graph_danger_overlaps(const Graph *g, char freqA, char freqB, CoordList *out) {
    if (!g || !out) return STATUS_INVALID;

    Coord dangerA[MAX_DANGER], dangerB[MAX_DANGER];
    size_t countA, countB;
    compute_danger_points(g, freqA, dangerA, &countA);
    compute_danger_points(g, freqB, dangerB, &countB);

    // Allocate for the worst case
    size_t capacity = countA < countB ? countA : countB;
    if (capacity == 0) capacity = 1;
    out->coord = malloc(capacity * sizeof(Coord));
    if (!out->coord) return STATUS_ALLOC;
    out->count = 0;

    // Find intersection
    for (size_t i = 0; i < countA; ++i) {
        if (coord_in_set(dangerB, countB, dangerA[i])) {
            out->coord[out->count++] = dangerA[i];
        }
    }
    return STATUS_OK;
}


/**
 * @fn graph_vertex_count
 * @brief Returns the number of vertices in the graph.
 * @param g Pointer to the graph.
 * @return Number of vertices in the graph.
 */
size_t graph_vertex_count(const Graph *g) { return g ? g->n : 0; }

/**
 * @fn graph_vertex_at
 * @brief Returns the vertex at the specified index.
 * @param g Pointer to the graph.
 * @param idx Index of the vertex.
 * @return Pointer to the vertex, or NULL if not found.
 */
const Vertex *graph_vertex_at(const Graph *g, size_t idx) {
    return (g && idx < g->n) ? &g->v[idx] : NULL;
}

/**
 * @fn ensure_capacity
 * @brief Ensures that the graph has enough capacity to store the given number of vertices.
 * @param g Pointer to the graph.
 * @return Status indicating success or failure.
 */
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

/**
 * @fn add_vertex
 * @brief Adds a vertex to the graph.
 * @param g Pointer to the graph.
 * @param freq Frequency of the vertex.
 * @param row Row index of the vertex.
 * @param col Column index of the vertex.
 * @param out_idx Pointer to store the index of the added vertex.
 * @return Status indicating success or failure.
 */
static Status add_vertex(Graph *g, char freq, int row, int col, size_t *out_idx) {
    Status st = ensure_capacity(g);
    if (st != STATUS_OK) return st;

    size_t idx = g->n++;
    g->v[idx] = (Vertex) {.freq = freq, .row = row, .col = col};
    if (out_idx) *out_idx = idx;
    return STATUS_OK;
}

/**
 * @fn add_edge
 * @brief Adds an edge between two vertices in the graph.
 * @param g Pointer to the graph.
 * @param src Source vertex index.
 * @param dst Destination vertex index.
 * @return Status indicating success or failure.
 */
static Status add_edge(Graph *g, size_t src, size_t dst) {
    EdgeNode *node = malloc(sizeof(EdgeNode));
    if (!node) return STATUS_ALLOC;
    node->dest = dst;
    node->next = g->adj[src];
    g->adj[src] = node;
    return STATUS_OK;
}