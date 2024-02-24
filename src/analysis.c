#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dyn_array.h"
#include "processing_scheduling.h"

#define FCFS "FCFS"
#define P "P"
#define RR "RR"
#define SJF "SJF"

// Add and comment your analysis code in this function.
// THIS IS NOT FINISHED.
int main(int argc, char **argv) 
{
    if (argc < 3) {
        printf("%s <pcb file> <schedule algorithm> [quantum]\n", argv[0]);
        return EXIT_FAILURE;
    }
    printf("Arguments provided:\n");

    for (int i = 0; i < argc; i++) {
        printf("Argument %d: %s\n", i, argv[i]);
    }
    const char* input_file = argv[1]; // Path to the binary file containing PCBs
    // Load PCBs from the binary file into a dynamic array
    dyn_array_t* pcb_dyn_array = load_process_control_blocks(input_file);

    if (strcmp(argv[2], "FCFS") == 0) {
        if (pcb_dyn_array == NULL) {
            fprintf(stderr, "Failed to load PCBs from file: %s\n", input_file);
            return EXIT_FAILURE; // Exit if PCBs couldn't be loaded
        }

        // Initialize the structure to store the results of the scheduling
        ScheduleResult_t result;

        // Run the First Come First Serve scheduling algorithm
        if (!first_come_first_serve(pcb_dyn_array, &result)) {
            fprintf(stderr, "FCFS scheduling failed.\n");
            dyn_array_destroy(pcb_dyn_array); // Clean up the dynamic array
            return EXIT_FAILURE; // Exit if scheduling failed
        }

        // Output the results of the scheduling
        printf("FCFS Scheduling Results:\n");
        printf("Average Waiting Time: %.2f\n", result.average_waiting_time);
        printf("Average Turnaround Time: %.2f\n", result.average_turnaround_time);
        printf("Total Run Time: %lu\n", result.total_run_time);
    }
     else if(strcmp(argv[2], "SJF") == 0) {

        if (pcb_dyn_array == NULL) {
            fprintf(stderr, "Failed to load PCBs from file: %s\n", input_file);
            return EXIT_FAILURE; // Exit if PCBs couldn't be loaded
        }

        // Initialize the structure to store the results of the scheduling
        ScheduleResult_t result;

        // Run the First Come First Serve scheduling algorithm
        if (!shortest_job_first(pcb_dyn_array, &result)) {
            fprintf(stderr, "SJF scheduling failed.\n");
            dyn_array_destroy(pcb_dyn_array); // Clean up the dynamic array
            return EXIT_FAILURE; // Exit if scheduling failed
        }

        // Output the results of the scheduling
        printf("SJF Scheduling Results:\n");
        printf("Average Waiting Time: %.2f\n", result.average_waiting_time);
        printf("Average Turnaround Time: %.2f\n", result.average_turnaround_time);
        printf("Total Run Time: %lu\n", result.total_run_time);
    }
    else if(strcmp(argv[2], "P") == 0) {

        if (pcb_dyn_array == NULL) {
            fprintf(stderr, "Failed to load PCBs from file: %s\n", input_file);
            return EXIT_FAILURE; // Exit if PCBs couldn't be loaded
        }

        // Initialize the structure to store the results of the scheduling
        ScheduleResult_t result;

        // Run the First Come First Serve scheduling algorithm
        if (!priority(pcb_dyn_array, &result)) {
            fprintf(stderr, "Priority scheduling failed.\n");
            dyn_array_destroy(pcb_dyn_array); // Clean up the dynamic array
            return EXIT_FAILURE; // Exit if scheduling failed
        }

        // Output the results of the scheduling
        printf("Priority Scheduling Results:\n");
        printf("Average Waiting Time: %.2f\n", result.average_waiting_time);
        printf("Average Turnaround Time: %.2f\n", result.average_turnaround_time);
        printf("Total Run Time: %lu\n", result.total_run_time);
    }
    else if(strcmp(argv[2], "RR") == 0) {
        
        if (pcb_dyn_array == NULL) {
            fprintf(stderr, "Failed to load PCBs from file: %s\n", input_file);
            return EXIT_FAILURE; // Exit if PCBs couldn't be loaded
        }

        // Initialize the structure to store the results of the scheduling
        ScheduleResult_t result;

        // Run the First Come First Serve scheduling algorithm
        if (argc < 4 || !round_robin(pcb_dyn_array, &result, atoi(argv[3]))) {
            fprintf(stderr, "Round Robin scheduling failed.\n");
            dyn_array_destroy(pcb_dyn_array); // Clean up the dynamic array
            return EXIT_FAILURE; // Exit if scheduling failed
        }

        // Output the results of the scheduling
        printf("Round Robin Scheduling Results:\n");
        printf("Average Waiting Time: %.2f\n", result.average_waiting_time);
        printf("Average Turnaround Time: %.2f\n", result.average_turnaround_time);
        printf("Total Run Time: %lu\n", result.total_run_time);
    }
    else if(strcmp(argv[2], "SRTF") == 0) {

        if (pcb_dyn_array == NULL) {
            fprintf(stderr, "Failed to load PCBs from file: %s\n", input_file);
            return EXIT_FAILURE; // Exit if PCBs couldn't be loaded
        }

        // Initialize the structure to store the results of the scheduling
        ScheduleResult_t result;

        // Run the First Come First Serve scheduling algorithm
        if (!shortest_remaining_time_first(pcb_dyn_array, &result)) {
            fprintf(stderr, "SRTF scheduling failed.\n");
            dyn_array_destroy(pcb_dyn_array); // Clean up the dynamic array
            return EXIT_FAILURE; // Exit if scheduling failed
        }

        // Output the results of the scheduling
        printf("STRF Scheduling Results:\n");
        printf("Average Waiting Time: %.2f\n", result.average_waiting_time);
        printf("Average Turnaround Time: %.2f\n", result.average_turnaround_time);
        printf("Total Run Time: %lu\n", result.total_run_time);


    }
    else{
        printf("Not a scheduling algorithm");
    }
    // Clean up by destroying the dynamic array of PCBs
    dyn_array_destroy(pcb_dyn_array);
    return EXIT_SUCCESS;
}