//
// API module for fetching Sudoku puzzles from external API
//

#ifndef SUDOKU_API_H
#define SUDOKU_API_H

#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct apiResponse {
    char *data;
    size_t size; // needed to dynamically allocate memory
} ApiResponse;

/**
 * Perform HTTP request to Sudoku API and return JSON data.
 * Returns 0 on success, non-zero on failure.
 */
int apiRequest(char **result);

#endif // SUDOKU_API_H
