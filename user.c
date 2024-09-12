#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // Ensure the correct number of arguments are provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <iterations>\n", argv[0]);
        return 1;
    }

    // Convert the command-line argument to an integer
    int iterations = atoi(argv[1]);

    // Validate the iterations argument
    if (iterations <= 0) {
        fprintf(stderr, "Error: Iterations must be a positive integer.\n");
        return 1;
    }

    // Loop for the specified number of iterations
    for (int i = 0; i < iterations; i++) {
        // Print information before sleeping
        printf("USER PID:%d PPID:%d Iteration:%d before sleeping\n", getpid(), getppid(), i + 1);

        // Sleep for 1 second
        sleep(1);

        // Print information after sleeping
        printf("USER PID:%d PPID:%d Iteration:%d after sleeping\n", getpid(), getppid(), i + 1);
    }

    return 0;
}
