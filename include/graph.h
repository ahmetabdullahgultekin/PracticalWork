/**
 * @file graph.h
 * @brief Header file for the graph data structure and its operations.
 *
 * This file contains the definition of the graph data structure,
 * as well as the function prototypes for various operations
 * that can be performed on the graph.
 *
 * @details
 * This header file is part of the Advanced Data Structures
 * course project. It includes the necessary data structures
 * and function prototypes for working with graphs.
 *
 * @note
 * The graph is represented as an adjacency list, where each vertex
 * is associated with a list of its neighbors. The graph can be
 * used to represent various types of data, such as networks,
 * social connections, or any other relationships.
 *
 * @author Ahmet Abdullah GULTEKIN
 * @date 2025-04-24
 *
 */

#ifndef PRACTICALWORK_GRAPH_H
#define PRACTICALWORK_GRAPH_H

#pragma once //the same

/**
 * graph.h – Phase 2 (Graph‑based solution)
 * ------------------------------------------------------------
 *  This header contains the public API for the GR (graph) data
 *  structure used in Phase 2.  All functions are pure business
 *  logic: no direct console I/O; they return a Status code so
 *  callers can react or propagate errors.  See docs/GRAPH.md for
 *  usage examples.
 *
 *  Differences vs Phase 1:
 *    • No printf() here – that lives in ui.c only.
 *    • All functions return Status (never void).
 *    • Single‑responsibility: one clear job each.
 * ------------------------------------------------------------
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <stddef.h> /* size_t */
#include <stdint.h> /* int32_t */
#include <stdbool.h>

/* --------------------------------------------------------- */
/* Generic status codes shared by all Phase 2 modules        */
/* --------------------------------------------------------- */

typedef enum {
    STATUS_OK = 0,
    STATUS_ALLOC,      /* memory allocation failed           */
    STATUS_IO,         /* file or stream error                */
    STATUS_INVALID,    /* invalid argument or corrupt input   */
    STATUS_NOT_FOUND   /* requested item does not exist       */
} Status;

/* --------------------------------------------------------- */
/* Fundamental data types                                    */
/* --------------------------------------------------------- */

typedef struct {
    char   freq;   /* antenna frequency (printable ASCII) */
    int32_t row;   /* matrix row index                    */
    int32_t col;   /* matrix column index                 */
} Vertex;

/* Forward declaration so caller doesn’t see implementation. */
typedef struct Graph Graph;

/* Visitor callback used by DFS/BFS traversals. Return value:
   • STATUS_OK        → continue traversal
   • any other Status → traversal aborts and propagates code  */
typedef Status (*VisitFn)(const Vertex *v, void *ctx);

/* Container for a variable‑length path (sequence of indices) */
typedef struct {
    size_t *idx;       /* dynamic array of vertex indices */
    size_t  len;
} Path;

/* Collection of paths (e.g., “all paths between two vertices”) */
typedef struct {
    Path  *path;       /* dynamic array */
    size_t count;
} PathSet;

/* Helper for intersection results (row, col pairs) */
typedef struct {
    int32_t row;
    int32_t col;
} Coord;

typedef struct {
    Coord  *coord;     /* dynamic array */
    size_t  count;
} CoordList;

/* --------------------------------------------------------- */
/* Public API                                                */
/* --------------------------------------------------------- */

/* Allocate an empty graph with a reserve capacity.          */
Status graph_init(Graph **g, size_t reserve);

/* Release all internal memory and *g itself; sets *g=NULL.  */
Status graph_free(Graph **g);

/* Build a graph from a matrix stored in a text file.        */
Status graph_from_matrix_file(Graph **g, const char *path);

/* Depth‑first search starting at vertex index start.        */
Status graph_dfs(const Graph *g, size_t start, VisitFn fn, void *ctx);

/* Breadth‑first search starting at vertex index start.      */
Status graph_bfs(const Graph *g, size_t start, VisitFn fn, void *ctx);

/* Enumerate ALL simple paths between src and dst.           */
Status graph_all_paths(const Graph *g, size_t src, size_t dst, PathSet *out);

/* Given two frequencies A & B, return list of coordinate
   pairs that are intersections of any antenna with freq A
   and any antenna with freq B (PDF requirement 3.d).        */
Status graph_intersections(const Graph *g, char freqA, char freqB, CoordList *out);

/*
 * Custom getline() implementation to read lines from a file.
 * This function dynamically allocates memory for the line
 * and resizes it as needed.
 * Returns the length of the line read.
 *
 */
size_t custom_getlines(char **line, size_t *n, FILE *stream);

/* Convenience getters (do not expose internals).            */
size_t graph_vertex_count(const Graph *g);
const Vertex *graph_vertex_at(const Graph *g, size_t idx);

#endif /* GRAPH_H */


#endif //PRACTICALWORK_GRAPH_H
