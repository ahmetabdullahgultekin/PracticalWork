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

#define INPUT_PATH "../input/"
#define OUTPUT_PATH "../output/"

int getAllFiles(int fileLimit, char files[][256]);

void promptFileSelection(char files[][256], int fileCount, char *selectedFile);

void promptFilename(char *filename, int isInput);

#endif //PRACTICALWORK_IO_OPS_H
