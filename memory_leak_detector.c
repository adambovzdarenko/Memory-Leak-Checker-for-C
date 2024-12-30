#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 1024

// Function to strip leading and trailing whitespace from a string
char* trim(char* str) {
    char* end;

    // Trim leading spaces
    while (*str == ' ' || *str == '\t') str++;

    // Trim trailing spaces
    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t')) end--;

    // Write the new null-terminator
    *(end + 1) = '\0';

    return str;
}

// Function to check if a line contains a comment and split off the comment part
bool has_comment(char *line, char **code_part, char **comment_part) {
    *code_part = line;
    *comment_part = NULL;

    // Check for single-line comment
    char *single_comment = strstr(line, "//");
    if (single_comment) {
        *comment_part = single_comment;  // Everything after "//" is the comment
        *single_comment = '\0';  // Null-terminate the code part
        return true;
    }

    // Check for multi-line comment
    char *start_comment = strstr(line, "/*");
    if (start_comment) {
        *comment_part = start_comment;  // Everything after "/*" is the comment
        *start_comment = '\0';  // Null-terminate the code part
        return true;
    }

    return false;
}

// Function to check for memory leaks by analyzing a C script
void check_memory_leaks(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file %s\n", filename);
        return;
    }

    char line[MAX_LINE_LENGTH];
    int malloc_count = 0;
    int free_count = 0;
    int line_number = 0;

    while (fgets(line, sizeof(line), file)) {
        line_number++;

        // Trim the line to avoid leading/trailing spaces
        char *trimmed_line = trim(line);

        // Split the line into code part and comment part (if any)
        char *code_part = NULL;
        char *comment_part = NULL;
        if (has_comment(trimmed_line, &code_part, &comment_part)) {
            // Only analyze the code part of the line
            trimmed_line = trim(code_part);
        }

        // Skip lines that are empty or only contain a comment
        if (strlen(trimmed_line) == 0) {
            continue;
        }

        // Check if the line contains 'malloc' or 'free'
        if (strstr(trimmed_line, "malloc") != NULL) {
            malloc_count++;
            printf("Found malloc at line %d: %s\n", line_number, line);
        }
        if (strstr(trimmed_line, "free") != NULL) {
            free_count++;
            printf("Found free at line %d: %s\n", line_number, line);
        }
    }

    // Report if there's a mismatch between malloc and free calls
    if (malloc_count > free_count) {
        printf("Warning: Potential memory leak detected! (%d malloc calls, %d free calls)\n", malloc_count, free_count);
    } else if (malloc_count == free_count) {
        printf("Memory management appears balanced (%d malloc calls, %d free calls)\n", malloc_count, free_count);
    } else {
        printf("Something seems off! (%d malloc calls, %d free calls)\n", malloc_count, free_count);
    }

    fclose(file);
}

int main() {
    char filename[256];

    // Ask the user for the file name to check
    printf("Enter the name of the C script to check for memory leaks: ");
    scanf("%s", filename);

    // Check the memory usage for the specified C script
    check_memory_leaks(filename);

    return 0;
}
