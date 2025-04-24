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

/* --------------------------------------------------------- */
/* Internal structures & helpers                             */
/* --------------------------------------------------------- */

typedef struct EdgeNode {
    size_t dest;            /* index of destination vertex */
    struct EdgeNode *next;
} EdgeNode;

struct Graph {
    Vertex   *v;            /* dynamic array of vertices           */
    EdgeNode **adj;         /* array of adjacency lists            */
    size_t    n;            /* current vertex count                */
    size_t    cap;          /* allocated capacity                  */
};

/* Forward declarations (private) */
static Status ensure_capacity(Graph *g);
static Status add_vertex(Graph *g, char freq, int row, int col, size_t *out_idx);
static Status add_edge(Graph *g, size_t src, size_t dst);

/* --------------------------------------------------------- */
/* Public API                                                */
/* --------------------------------------------------------- */

Status graph_init(Graph **pg, size_t reserve)
{
    if (!pg) return STATUS_INVALID;
    *pg = NULL;

    Graph *g = calloc(1, sizeof(Graph));
    if (!g) return STATUS_ALLOC;

    g->cap = reserve ? reserve : 4;
    g->v   = calloc(g->cap, sizeof(Vertex));
    g->adj = calloc(g->cap, sizeof(EdgeNode*));
    if (!g->v || !g->adj) {
        free(g->v); free(g->adj); free(g);
        return STATUS_ALLOC;
    }

    *pg = g;
    return STATUS_OK;
}

Status graph_free(Graph **pg)
{
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

/* --------------------------------------------------------- */
/* Graph construction from matrix file                       */
/* --------------------------------------------------------- */

/* Helper: push vertex if char is printable & not dot. */
static inline bool is_antenna(char c) { return isprint((unsigned char)c) && c != '.' && c != '\n' && c != '\r'; }

Status graph_from_matrix_file(Graph **out_g, const char *path)
{
    if (!out_g || !path) return STATUS_INVALID;

    FILE *fp = fopen(path, "r");
    if (!fp) return STATUS_IO;

    Status st = graph_init(out_g, 16);
    if (st != STATUS_OK) {
        fclose(fp);
        return st;
    }
    Graph *g = *out_g;

    char *line = NULL; size_t len = 0;
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

/* --------------------------------------------------------- */
/* Traversals (DFS & BFS)                                     */
/* --------------------------------------------------------- */

Status graph_dfs(const Graph *g, size_t start, VisitFn fn, void *ctx)
{
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

Status graph_bfs(const Graph *g, size_t start, VisitFn fn, void *ctx)
{
    if (!g || start >= g->n || !fn) return STATUS_INVALID;
    Status st;

    bool *vis = calloc(g->n, sizeof(bool));
    size_t *queue = calloc(g->n, sizeof(size_t));
    if (!vis || !queue) { free(vis); free(queue); return STATUS_ALLOC; }

    size_t head = 0, tail = 0;
    queue[tail++] = start; vis[start] = true;

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

/* TODO: full backtracking implementation.  Currently stub. */
Status graph_all_paths(const Graph *g, size_t src, size_t dst, PathSet *out)
{
    (void)g; (void)src; (void)dst; (void)out;
    return STATUS_INVALID;
}

/* TODO: compute intersections (freqA vs freqB). */
Status graph_intersections(const Graph *g, char freqA, char freqB, CoordList *out)
{
    (void)g; (void)freqA; (void)freqB; (void)out;
    return STATUS_INVALID;
}

/* --------------------------------------------------------- */
/* Getters                                                   */
/* --------------------------------------------------------- */

size_t graph_vertex_count(const Graph *g) { return g ? g->n : 0; }

const Vertex *graph_vertex_at(const Graph *g, size_t idx)
{
    return (g && idx < g->n) ? &g->v[idx] : NULL;
}

/* --------------------------------------------------------- */
/* Private helpers                                           */
/* --------------------------------------------------------- */

static Status ensure_capacity(Graph *g)
{
    if (g->n < g->cap) return STATUS_OK;
    size_t new_cap = g->cap * 2;
    Vertex   *nv = realloc(g->v,   new_cap * sizeof(Vertex));
    EdgeNode **na = realloc(g->adj, new_cap * sizeof(EdgeNode*));
    if (!nv || !na) return STATUS_ALLOC;

    /* zero new adj slots */
    memset(na + g->cap, 0, (new_cap - g->cap) * sizeof(EdgeNode*));

    g->v   = nv;
    g->adj = na;
    g->cap = new_cap;
    return STATUS_OK;
}

static Status add_vertex(Graph *g, char freq, int row, int col, size_t *out_idx)
{
    Status st = ensure_capacity(g);
    if (st != STATUS_OK) return st;

    size_t idx = g->n++;
    g->v[idx] = (Vertex){ .freq = freq, .row = row, .col = col };
    if (out_idx) *out_idx = idx;
    return STATUS_OK;
}

static Status add_edge(Graph *g, size_t src, size_t dst)
{
    EdgeNode *node = malloc(sizeof(EdgeNode));
    if (!node) return STATUS_ALLOC;
    node->dest = dst;
    node->next = g->adj[src];
    g->adj[src] = node;
    return STATUS_OK;
}



