#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

// Function to print usage/help message
void print_usage() {
    printf("Usage: oss [-h] [-n proc] [-s simul] [-t iter]\n");
    printf("  -h          : Show this help message\n");
    printf("  -n proc     : Number of user processes to launch\n");
    printf("  -s simul    : Maximum number of simultaneous user processes\n");
    printf("  -t iter     : Number of iterations each user process should run\n");
}

int main(int argc, char *argv[]) {
    int opt;
    int num_processes = 0;      // Total number of user processes to launch
    int max_simultaneous = 0;   // Max number of simultaneous processes
    int iterations = 0;         // Number of iterations for each user process

    // Parse command line arguments
    while ((opt = getopt(argc, argv, "hn:s:t:")) != -1) {
        switch (opt) {
            case 'h':
                print_usage();
                return 0;
            case 'n':
                num_processes = atoi(optarg);
                break;
            case 's':
                max_simultaneous = atoi(optarg);
                break;
            case 't':
                iterations = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Invalid option\n");
                print_usage();
                return 1;
        }
    }

    // Validate arguments
    if (num_processes <= 0 || max_simultaneous <= 0 || iterations <= 0) {
        fprintf(stderr, "Invalid parameters: proc, simul, and iter must be positive integers.\n");
        print_usage();
        return 1;
    }

    int running_processes = 0; // Track the number of processes running simultaneously
    pid_t pid;

    // Main loop to launch user processes
    for (int i = 0; i < num_processes; i++) {
        // If maximum simultaneous processes reached, wait for any child to finish
        if (running_processes >= max_simultaneous) {
            wait(NULL);
            running_processes--;
        }

        // Fork a new process
        pid = fork();

        if (pid == 0) {
            // Child process: Execute the user program
            char iterations_str[10];
            snprintf(iterations_str, sizeof(iterations_str), "%d", iterations);
            execl("./user", "user", iterations_str, (char *)NULL);

            // If execl fails
            perror("execl failed");
            exit(1);
        } else if (pid > 0) {
            // Parent process: Increment running processes counter
            running_processes++;
        } else {
            // Fork failed
            perror("fork failed");
            exit(1);
        }
    }

    // Wait for remaining children to finish
    while (running_processes > 0) {
        wait(NULL);
        running_processes--;
    }

    printf("All user processes have finished.\n");
    return 0;
}
