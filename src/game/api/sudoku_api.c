//
// API module for fetching Sudoku puzzles from external API
//

#include "sudoku_api.h"

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t totalSize = size * nmemb;
    ApiResponse *res = (ApiResponse *) userp;

    char *ptr = realloc(res->data, res->size + totalSize + 1); // +1 for the null terminator
    if (ptr == NULL) {
        fprintf(stderr, "Not enough memory (realloc failed)\n");
        return 0; // Signal an error to libcurl
    }

    res->data = ptr;
    memcpy(&res->data[res->size], contents, totalSize);
    res->size += totalSize;
    res->data[res->size] = '\0';

    return totalSize;
}

int apiRequest(char **result) {
    ApiResponse apiResponse = {NULL, 0};
    CURL *curl = curl_easy_init();

    if (curl) {
        CURLcode apiResCode;

        curl_easy_setopt(curl, CURLOPT_URL, "https://sudoku-api.vercel.app/api/dosuku");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &apiResponse);

        apiResCode = curl_easy_perform(curl);

        if (apiResCode != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(apiResCode));
        else
            *result = apiResponse.data;

        curl_easy_cleanup(curl);
    }

    return 0;
}
