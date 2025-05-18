/**
 * @file io_ops.c
 * @brief Implementation of Input/Output operations for file handling. This file contains functions to list files in a directory,
 * prompt the user for file selection, and handle input/output operations.
 *
 * @date 2025-03-30
 * @author Ahmet Abdullah GULTEKIN
 */
#include "../include/io_ops.h"
#include "../include/strings.h"

/**
 * @fn getAllFiles
 * @brief List the files in the input directory.
 * @param files Array to store the filenames.
 * @param fileLimit Maximum number of files to list.
 * @return The number of files listed.
 */
int getAllFiles(int fileLimit, char files[][256]) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;
    int count = 0;
    char searchPath[260];

    snprintf(searchPath, sizeof(searchPath), "%s\\*", INPUT_PATH);
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
        } while (FindNextFile(hFind, &findFileData) != 0 && count < fileLimit);
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
Status promptFileSelection(char files[][256], int fileCount, char *selectedFile) {
    printf("\n%s", TR(STR_INFO_PROMPT_AVAILABLE_FILES));
    for (int i = 0; i < fileCount; i++) {
        printf("\n[%d] -> %s", i + 1, files[i]);
    }

    int choice;
    printf("\n\n%s [1,%d]: ", TR(STR_INFO_PROMPT_FILE_CHOICE), fileCount);
    if (scanf_s("%d", &choice) != 1 || choice < 1 || choice > fileCount) {
        return STATUS_INVALID;
    }

    // Concat the selected filename to the buffer
    snprintf(selectedFile, 256, "%s%s", INPUT_PATH, files[choice - 1]);
    //strncpy_s(selectedFile, 255, files[choice - 1], 255);
    selectedFile[255] = '\0';

    return STATUS_OK;
}

/**
 * @fn promptFilename
 * @brief Prompt the user to enter a filename or select from a list.
 * @param filename The buffer to store the filename.
 * @param isInput A flag indicating whether the file is for input (1) or output (0).
 */
Status promptFilename(char *filename, int isInput) {
    if (isInput) {
        char files[100][256];
        int fileCount = getAllFiles(10, files);

        if (fileCount == 0) {
            /*puts(TR(STR_ERR_FILE_NOT_FOUND));*/
            return STATUS_INVALID;
        }

        if (promptFileSelection(files, fileCount, filename) == STATUS_INVALID) {
            /*puts(TR(STR_ERR_INVALID_CHOICE));*/
            return STATUS_INVALID;
        }

        return STATUS_OK;
    } else {
        puts(TR(STR_INFO_PROMPT_PATH));
        if (scanf_s("%s", filename, 256) != 1) {
            puts(TR(STR_ERR_IO));
            return STATUS_INVALID;
        }
        return STATUS_OK;
    }
}

/**
 * @fn custom_getlines
 * @brief Custom getline() implementation to read lines from a file.
 * @param line Pointer to the line buffer.
 * @param n Pointer to the size of the line buffer.
 * @param stream File pointer to read from.
 * @return The length of the line read.
 */
size_t custom_getlines(char **line, size_t *n, FILE *stream) {
    if (!line || !n || !stream) return -1;

    size_t pos = 0;
    int c;

    if (*line == NULL || *n == 0) {
        *n = 128; // Initial buffer size
        *line = malloc(*n);
        if (!*line) return -1;
    }

    while ((c = fgetc(stream)) != EOF) {
        if (pos + 1 >= *n) {
            *n *= 2;
            char *new_ptr = realloc(*line, *n);
            if (!new_ptr) return -1;
            *line = new_ptr;
        }
        (*line)[pos++] = c;
        if (c == '\n') break;
    }

    if (pos == 0 && c == EOF) return -1;

    (*line)[pos] = '\0';
    return pos;
}

/**
 * @fn replace_newline
 * @brief Replace occurrences of "\n" in a string with actual newline characters.
 * @param str The input string.
 * @return A new string with "\n" replaced by newline characters.
 */
char *replace_newline(const char *str) {
    if (!str) return NULL;

    size_t len = strlen(str);
    char *result = malloc(len + 1); // Allocate memory for the result
    if (!result) return NULL;

    char *dst = result;
    for (const char *src = str; *src; ++src) {
        if (*src == '\\' && *(src + 1) == 'n') {
            *dst++ = '\n'; // Replace "\n" with a newline character
            ++src;         // Skip the 'n'
        } else {
            *dst++ = *src; // Copy other characters
        }
    }
    *dst = '\0'; // Null-terminate the result
    return result;
}