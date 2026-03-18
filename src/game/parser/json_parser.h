//
// JSON parser module for converting API responses to Grid structures
//

#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include "../../lib/cJSON/cJSON.h"
#include "../rules/grid.h"

/**
 * Parse JSON data from API and populate Grid structure.
 * Returns 0 on success, 1 for JSON parse error, 2 for invalid structure.
 */
int parseJsonData(Grid *result, char *jsonData);

#endif // JSON_PARSER_H
