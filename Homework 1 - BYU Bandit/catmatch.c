//
//  catmatch.c
//  Created by Hunter Casillas on 1/9/20.
//  CS 324 HW1
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv []) {
    // Check to see if input file was included
    if (argc < 2) {
        printf("You must include the command line input file.\n");
        return 0;
    }
    
    // Print pid
    printf("%d\n", getpid());
        
    // Open input file
    FILE* input;
    input = fopen(argv[1], "r");
    
    // Declare variables needed
    char buffer[128];
    char* env;
    char* found;
    env = getenv("CATMATCH_PATTERN");
    printf("\n");

    // Get each line
    while(fgets(buffer, sizeof(buffer), input) != NULL) {
        if (env != NULL) {
            // Check to see if env variable is in the current line
            found = strstr(buffer, env);
            
            // If it is, print 1 before the line
            if (found != NULL) {
                printf("%d ", 1);
                printf("%s", buffer);
            // Otherwise, print 0 before the line
            } else {
                printf("%d ", 0);
                printf("%s", buffer);
            }
        // If the env variable is null, print 0 before the line
        } else {
            printf("%d ", 0);
            printf("%s", buffer);
        }
    }
    printf("\n");
    
    // Close input file
    fclose(input);
    
    // End the program
    return 0;
}
