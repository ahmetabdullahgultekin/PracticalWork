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

#include <stddef.h> /* size_t */
#include <stdint.h> /* int32_t */
#include <stdbool.h>

/**
 * @struct Status
 *
 * @brief Status codes for various operations.

 * These status codes are used to indicate the success or failure
 * of various operations performed on the graph data structure.
 * Each status code corresponds to a specific type of error or
 * condition that may occur during the operation.
 */

typedef enum {
    STATUS_OK = 0,
    STATUS_ALLOC,      /* memory allocation failed           */
    STATUS_IO,         /* file or stream error                */
    STATUS_INVALID,    /* invalid argument or corrupt input   */
    STATUS_NOT_FOUND,   /* the requested item does not exist       */
    STATUS_WRITE,      /* write error                        */
    STATUS_READ,       /* read error                         */
    STATUS_EMPTY,      /* empty data structure                */
    STATUS_OVERFLOW,   /* overflow error                     */
    STATUS_UNDERFLOW,  /* underflow error                    */
    STATUS_UNSUPPORTED /* unsupported operation              */
} Status;

/**
 * @struct EdgeNode
 *
 * @brief EdgeNode structure representing an edge in the graph.
 * Each edge is represented as a linked list node
 * pointing to the destination vertex.
 *
 */
typedef struct EdgeNode {
    size_t dest;            /* index of destination vertex */
    struct EdgeNode *next;
} EdgeNode;

/**
 * @struct Vertex
 *
 * @brief Vertex structure representing a vertex in the graph.
 * Each vertex contains a frequency,
 * row index, and column index.
 */
typedef struct {
    char freq;   /* antenna frequency (printable ASCII) */
    int32_t row;   /* matrix row index                    */
    int32_t col;   /* matrix column index                 */
} Vertex;

/**
 * @struct Graph
 *
 * @brief Graph structure representing a graph.
 * It contains an array of vertices,
 * an array of adjacency lists,
 * and the current vertex count.
 */
struct Graph {
    Vertex *v;           /* dynamic array of vertices           */
    EdgeNode **adj;      /* array of adjacency lists            */
    size_t n;            /* current vertex count                */
    size_t cap;          /* allocated capacity                  */
};

/**
 * Forward declaration of the Graph structure for use in function prototypes.
 */
typedef struct Graph Graph;

/**
 * Function pointer type for visiting vertices during traversal.
 * The function should return a Status code indicating success or failure.
 */
typedef Status (*VisitFn)(const Vertex *v, void *ctx);

/**
 * @struct Path
 *
 * @brief Path structure representing a path in the graph.
 * It contains an array of vertex indices
 * and the length of the path.
 */
typedef struct {
    size_t *idx;       /* dynamic array of vertex indices */
    size_t len;
} Path;

/**
 * @struct PathSet
 *
 * @brief PathSet structure representing a set of paths.
 * It contains a dynamic array of paths
 * and the count of paths.
 */
typedef struct {
    Path *path;       /* dynamic array */
    size_t count;
} PathSet;

/**
 * @struct Coord
 *
 * @brief Coord structure representing a coordinate in the graph.
 * It contains row and column indices.
 */
typedef struct {
    int32_t row;
    int32_t col;
} Coord;

/**
 * @struct CoordList
 *
 * @brief CoordList structure representing a list of coordinates.
 * It contains a dynamic array of coordinates
 * and the count of coordinates.
 */
typedef struct {
    Coord *coord;     /* dynamic array */
    size_t count;
} CoordList;

/**
 * @brief Initialize a graph with a given capacity.
 * @param g Pointer to the graph to be initialized.
 * @param reserve Initial capacity of the graph.
 *
 * @return Status code indicating success or failure.
 */
Status graph_init(Graph **g, size_t reserve);

/**
 * @brief Free the graph and its resources.
 * @param g Pointer to the graph to be freed.
 *
 * @return Status code indicating success or failure.
 */
Status graph_free(Graph **g);

/**
 * @brief Clear the adjacency lists of the graph.
 * @param g Pointer to the graph to be cleared.
 *
 * @return Status code indicating success or failure.
 */
Status graph_clear_lists(Graph *g);

/**
 * @brief Save the graph to a file.
 * @param g Pointer to the graph to be saved.
 * @param path Path to the file where the graph will be saved.
 *
 * @return Status code indicating success or failure.
 */
Status graph_save_matrix(const Graph *g, const char *path);

/**
 * @brief Insert a vertex into the graph.
 * @param g Pointer to the graph.
 * @param freq Frequency of the vertex.
 * @param row Row index of the vertex.
 * @param col Column index of the vertex.
 *
 * @return Status code indicating success or failure.
 */
Status graph_insert_vertex(Graph *g, char freq, int row, int col);

/**
 * @brief Remove a vertex from the graph.
 * @param g Pointer to the graph.
 * @param idx Index of the vertex to be removed.
 *
 * @return Status code indicating success or failure.
 */
Status graph_remove_vertex(Graph *g, size_t idx);

/**
 * @brief Load a graph from a matrix file.
 * @param g Pointer to the graph to be loaded.
 * @param path Path to the matrix file.
 *
 * @return Status code indicating success or failure.
 */
Status graph_from_matrix_file(Graph **g, const char *path);

/**
 * @brief Depth-first search starting at vertex index start.
 * @param g Pointer to the graph.
 * @param start Starting vertex index.
 * @param fn Function to be called for each visited vertex.
 * @param ctx Context pointer to be passed to the function.
 *
 * @return Status code indicating success or failure.
 */
Status graph_dfs(const Graph *g, size_t start, VisitFn fn, void *ctx);

/**
 * @brief Breadth-first search starting at vertex index start.
 * @param g Pointer to the graph.
 * @param start Starting vertex index.
 * @param fn Function to be called for each visited vertex.
 * @param ctx Context pointer to be passed to the function.
 *
 * @return Status code indicating success or failure.
 */
Status graph_bfs(const Graph *g, size_t start, VisitFn fn, void *ctx);

/**
 * @brief Find all paths from src to dst in the graph.
 * @param g Pointer to the graph.
 * @param src Source vertex index.
 * @param dst Destination vertex index.
 * @param out Pointer to the PathSet to store the found paths.
 *
 * @return Status code indicating success or failure.
 */
Status graph_all_paths(const Graph *g, size_t src, size_t dst, PathSet *out);

/**
 * @brief Find all intersections between two frequencies in the graph.
 * @param g Pointer to the graph.
 * @param freqA First frequency.
 * @param freqB Second frequency.
 * @param out Pointer to the CoordList to store the intersections.
 *
 * @return Status code indicating success or failure.
 */
Status graph_intersections(const Graph *g, char freqA, char freqB, CoordList *out);

/**
 * @brief Find all dangerous points for a given frequency.
 * @param g Pointer to the graph.
 * @param freq Frequency to check for dangerous points.
 * @param danger Pointer to the CoordList to store the dangerous points.
 * @param count Pointer to store the count of dangerous points.
 */
static void compute_danger_points(const Graph *g, char freq, Coord *danger, size_t *count);

/**
 * @brief Find all dangerous point intersections between two frequencies.
 * @param g Pointer to the graph.
 * @param freqA First frequency.
 * @param freqB Second frequency.
 * @param out Pointer to the CoordList to store the intersections.
 *
 * @return Status code indicating success or failure.
 */
Status graph_danger_overlaps(const Graph *g, char freqA, char freqB, CoordList *out);

/**
 * @brief Custom getline() implementation to read lines from a file.
 * @param line Pointer to the line buffer.
 * @param n Pointer to the size of the line buffer.
 * @param stream File pointer to read from.
 *
 * @return The length of the line read.
 */
size_t custom_getlines(char **line, size_t *n, FILE *stream);

/**
 * @brief Replace occurrences of "\n" in a string with actual newline characters.
 * @param str The input string.
 *
 * @return A new string with "\n" replaced by newline characters.
 */
size_t graph_vertex_count(const Graph *g);

/**
 * @brief Get the vertex at a specific index in the graph.
 * @param g Pointer to the graph.
 * @param idx Index of the vertex to retrieve.
 *
 * @return Pointer to the Vertex structure at the specified index.
 */
const Vertex *graph_vertex_at(const Graph *g, size_t idx);

#endif //PRACTICALWORK_GRAPH_H
