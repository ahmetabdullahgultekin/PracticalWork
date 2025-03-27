/**
 * @file io_ops.h
 * @brief This file contains the function declarations for managing the input/output operations.
 */

#ifndef PRACTICALWORK_IO_OPS_H
#define PRACTICALWORK_IO_OPS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int listFiles(char files[][256], int maxFiles);
void promptFileSelection(char files[][256], int fileCount, char *selectedFile);

#endif //PRACTICALWORK_IO_OPS_H
