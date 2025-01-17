#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Include ctype.h for isdigit

#define MAX_LINE_LENGTH 1024

void extract_logs(const char *input_file, const char *date, const char *output_dir) {
    FILE *infile, *outfile;
    char line[MAX_LINE_LENGTH];
    char output_file[MAX_LINE_LENGTH];

    // Create output file path
    snprintf(output_file, sizeof(output_file), "%s/output_%s.txt", output_dir, date);

    // Open input file
    infile = fopen(input_file, "r");
    if (infile == NULL) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    // Open output file
    outfile = fopen(output_file, "w");
    if (outfile == NULL) {
        perror("Error creating output file");
        fclose(infile);
        exit(EXIT_FAILURE);
    }

    // Read the log file line by line
    while (fgets(line, sizeof(line), infile)) {
        // Check if the line starts with the specified date
        if (strncmp(line, date, strlen(date)) == 0) {
            fputs(line, outfile);
        }
    }

    // Close files
    fclose(infile);
    fclose(outfile);

    printf("Logs for %s have been saved to %s\n", date, output_file);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input_file> <YYYY-MM-DD>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input_file = argv[1];
    const char *date = argv[2];
    const char *output_dir = "output";

    // Validate the date format (basic check for YYYY-MM-DD)
    if (strlen(date) != 10 || date[4] != '-' || date[7] != '-' ||
        !isdigit(date[0]) || !isdigit(date[1]) || !isdigit(date[2]) || !isdigit(date[3]) ||
        !isdigit(date[5]) || !isdigit(date[6]) || !isdigit(date[8]) || !isdigit(date[9])) {
        printf("Error: Date must be in YYYY-MM-DD format.\n");
        return EXIT_FAILURE;
    }

    // Create the output directory if it doesn't exist
    if (system("mkdir -p output") != 0) {
        perror("Error creating output directory");
        return EXIT_FAILURE;
    }

    // Extract logs for the specified date
    extract_logs(input_file, date, output_dir);

    return EXIT_SUCCESS;
}
