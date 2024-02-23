#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint32_t remaining_burst_time;
    uint32_t priority;
    uint32_t arrival;
} ProcessControlBlock;

int main() {
    /*ProcessControlBlock pcbs[] = {
        {10, 1, 0},
        {5, 2, 1},
        {20, 3, 2}
    };*/
    ProcessControlBlock pcbs[] = {
        {24,  1, 0},
        {3,  2, 1},
        {3, 3, 2}
    };
    /*ProcessControlBlock pcbs[] = {
        {10, 3, 0},
        {1, 1, 1},
        {2, 4, 2},
        {1, 5, 3},
        {5, 2, 4}
    };*/
    size_t numPcbs = sizeof(pcbs) / sizeof(pcbs[0]);

    //FILE* file = fopen("valid_pcb_data.bin", "wb");
    FILE* file = fopen("RR.bin", "wb");

    fwrite(&numPcbs, sizeof(size_t), 1, file);
    if (fwrite(pcbs, sizeof(ProcessControlBlock), numPcbs, file) != numPcbs) {
        perror("Failed to write PCB data to file");
        fclose(file);
        return 1;
    }

    fclose(file);
    return 0;
}
