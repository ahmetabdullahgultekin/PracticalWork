/**
 * @file io_ops.h
 * @brief Header file for the function declarations for managing the input/output operations.
 * @author Ahmet Abdullah GULTEKIN
 * @date 2025-03-30
 */

#ifndef PRACTICALWORK_IO_OPS_H
#define PRACTICALWORK_IO_OPS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "../include/graph.h"

#define INPUT_PATH "../input/"
#define OUTPUT_PATH "../output/"

/**
 * @fn getAllFiles
 * @brief List the files in the input directory.
 * @param files Array to store the filenames.
 * @param fileLimit Maximum number of files to list.
 * @return The number of files listed.
 */
int getAllFiles(int fileLimit, char files[][256]);

/**
 * @fn promptFileSelection
 * @brief Prompt the user to select a file from the list.
 * @param files Array of filenames.
 * @param fileCount Number of files in the array.
 * @param selectedFile Buffer to store the selected filename.
 * @return Status code indicating success or failure.
 */
Status promptFileSelection(char files[][256], int fileCount, char *selectedFile);

/**
 * @fn promptFilename
 * @brief Prompt the user to enter a filename or select from a list.
 * @param filename The buffer to store the filename.
 * @param isInput A flag indicating whether the file is for input (1) or output (0).
 * @return Status code indicating success or failure.
 */
Status promptFilename(char *filename, int isInput);

/**
 * @fn custom_getlines
 * @brief Custom getline() implementation to read lines from a file.
 * @param line Pointer to the line buffer.
 * @param n Pointer to the size of the line buffer.
 * @param stream File pointer to read from.
 * @return The length of the line read.
 */
size_t custom_getlines(char **line, size_t *n, FILE *stream);

/**
 * @fn replace_newline
 * @brief Replace the newline character in a string with a null terminator.
 * @param str Pointer to the string.
 * @return The length of the string after replacement.
 */
char *replace_newline(const char *str);

#endif //PRACTICALWORK_IO_OPS_H
