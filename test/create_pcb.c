#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint32_t remaining_burst_time;
    uint32_t priority;
    uint32_t arrival;
    bool started;
} ProcessControlBlock;

int main() {
    ProcessControlBlock pcbs[] = {
        {10, 1, 0, false},
        {5, 2, 1, false},
        {20, 3, 2, false}
    };
    size_t numPcbs = sizeof(pcbs) / sizeof(pcbs[0]);

    FILE* file = fopen("valid_pcb_data.bin", "wb");


    if (fwrite(pcbs, sizeof(ProcessControlBlock), numPcbs, file) != numPcbs) {
        perror("Failed to write PCB data to file");
        fclose(file);
        return 1;
    }

    fclose(file);
    return 0;
}
