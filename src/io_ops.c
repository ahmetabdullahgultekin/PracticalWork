/**
 * @file io_ops.c
 * @brief Implementation of Input/Output operations for file handling. This file contains functions to list files in a directory,
 * prompt the user for file selection, and handle input/output operations.
 *
 * @date 2025-03-30
 * @author Ahmet Abdullah GULTEKIN
 */
#include "../include/io_ops.h"

/**
 * @fn listFiles
 * @brief List the files in the input directory.
 * @param files Array to store the filenames.
 * @param maxFiles Maximum number of files to list.
 * @return The number of files listed.
 */
int listFiles(char files[][256], int maxFiles) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;
    int count = 0;
    char searchPath[260];

    snprintf(searchPath, sizeof(searchPath), "%s\\*", INPUT_DIR);
    hFind = FindFirstFile(searchPath, &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        perror("Could not open input directory");
        exit(EXIT_FAILURE);
    } else {
        do {
            if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                strncpy_s(files[count], 255, findFileData.cFileName, 255);
                files[count][255] = '\0';
                count++;
            }
        } while (FindNextFile(hFind, &findFileData) != 0 && count < maxFiles);
        FindClose(hFind);
    }
    return count;
}

/**
 * @fn promptFileSelection
 * @brief Prompt the user to select a file from the list.
 * @param files Array of filenames.
 * @param fileCount Number of files in the array.
 * @param selectedFile Buffer to store the selected filename.
 */
void promptFileSelection(char files[][256], int fileCount, char *selectedFile) {
    printf("\nAvailable files:\n");
    for (int i = 0; i < fileCount; i++) {
        printf("%d. %s\n", i + 1, files[i]);
    }

    int choice;
    printf("Select a file by number: ");
    if (scanf_s("%d", &choice) != 1 || choice < 1 || choice > fileCount) {
        fprintf(stderr, "Invalid selection. Exiting.\n");
        exit(EXIT_FAILURE);
    }

    // Copy the selected filename to the buffer
    strncpy_s(selectedFile, 255, files[choice - 1], 255);
    selectedFile[255] = '\0';
}

/**
 * @fn promptFilename
 * @brief Prompt the user to enter a filename or select from a list.
 * @param filename The buffer to store the filename.
 * @param isInput A flag indicating whether the file is for input (1) or output (0).
 */
void promptFilename(char *filename, int isInput) {
    if (isInput) {
        char files[100][256];
        int fileCount = listFiles(files, 100);

        if (fileCount == 0) {
            printf("No files found in the input directory.\n");
            exit(EXIT_FAILURE);
        }

        promptFileSelection(files, fileCount, filename);
    } else {
        printf("\nEnter the filename: ");
        if (scanf_s("%s", filename, 256) != 1) {
            fprintf(stderr, "Error reading filename.\n");
            exit(EXIT_FAILURE);
        }
    }
}