#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "dyn_array.h"
#include "processing_scheduling.h"


// You might find this handy.  I put it around unused parameters, but you should
// remove it before you submit. Just allows things to compile initially.
#define UNUSED(x) (void)(x)

// private function
void virtual_cpu(ProcessControlBlock_t *process_control_block) 
{
    // decrement the burst time of the pcb
    --process_control_block->remaining_burst_time;
}
/*
bool first_come_first_serve(dyn_array_t *ready_queue, ScheduleResult_t *result) 
{

    if (ready_queue == NULL || result == NULL) {
        return false;
    }
    
    

    size_t num_elements = dyn_array_size(ready_queue);
    ProcessControlBlock_t* pcbptr;

    for (size_t i = 0; i < num_elements; i++){
        pcbptr = (ProcessControlBlock_t*)dyn_array_at(ready_queue, i);

        if (pcbptr != NULL){

                printf("burst time: %u", pcbptr->remaining_burst_time);
                printf("priority: %u",pcbptr->priority);
                printf("arrival time: %u",pcbptr->arrival);
        }

    }

    return false;
}
*/
bool first_come_first_serve(dyn_array_t *ready_queue, ScheduleResult_t *result) {
   if (ready_queue == NULL || result == NULL) {
        return false; // Validate input parameters
    }

    size_t num_elements = dyn_array_size(ready_queue);
    if (num_elements == 0) {
        return false; // No PCBs to process
    }

    ProcessControlBlock_t *pcbptr;
    size_t currentTime = 0;
    size_t totalWaitingTime = 0;
    size_t totalTurnaroundTime = 0;

    for (size_t i = 0; i < num_elements; i++) {
    pcbptr = (ProcessControlBlock_t*)dyn_array_at(ready_queue, i);

    if (pcbptr != NULL) {
            
            if (pcbptr->arrival > currentTime) {
                currentTime = pcbptr->arrival;
            }

            size_t startTime = currentTime; 
            size_t endTime = startTime + pcbptr->remaining_burst_time;

            
            size_t waitingTime = startTime - pcbptr->arrival; // This will now be 0 or positive.
            size_t turnaroundTime = endTime - pcbptr->arrival; 
            totalWaitingTime += waitingTime;
            totalTurnaroundTime += turnaroundTime;

            // Update the current time to the end time of the process.
            currentTime = endTime;

            // Print PCB information
            printf("PCB #%zu: Start Time: %zu, End Time: %zu, Waiting Time: %zu, Turnaround Time: %zu\n", i+1, startTime, endTime, waitingTime, turnaroundTime);
        }
    }

    // Calculate average waiting and turnaround times.
    result->average_waiting_time = (float)totalWaitingTime / num_elements;
    result->average_turnaround_time = (float)totalTurnaroundTime / num_elements;
    result->total_run_time = currentTime; // Total run time is the current time after all PCBs have been processed.
    return true;
}

bool shortest_job_first(dyn_array_t *ready_queue, ScheduleResult_t *result) 
{
    if(ready_queue == NULL || result == NULL)                                       //checks for improper inputs
        return false;
    return true;

    //UNUSED(ready_queue);
    UNUSED(result);
    //return false;   
}

bool priority(dyn_array_t *ready_queue, ScheduleResult_t *result) 
{
    if(ready_queue == NULL || result == NULL)                                       //checks for improper inputs
        return false;
    return true;
    
    //UNUSED(ready_queue);
    UNUSED(result);
    //return false;   
}

bool round_robin(dyn_array_t *ready_queue, ScheduleResult_t *result, size_t quantum) 
{
    if(ready_queue == NULL || result == NULL)                                       //checks for improper inputs
        return false;
    return true;
    
    //UNUSED(ready_queue);
    UNUSED(result);
    UNUSED(quantum);
    //return false;
}

dyn_array_t *load_process_control_blocks(const char *input_file) 
{
    if(input_file == NULL || *input_file == '\0' || *input_file == '\n')                                       //checks for improper inputs
        return NULL;

    FILE* f = fopen(input_file, "r");
    if(f == NULL)                                                                                             //checks if file opens correctly
        return NULL;

    uint32_t number_of_process_control;
    fread(&number_of_process_control, sizeof(uint32_t), 1, f);                                                 //reads lines and stores it to buffer

    dyn_array_t * d = dyn_array_create(number_of_process_control, sizeof(ProcessControlBlock_t), NULL);
    
    ProcessControlBlock_t p;
    for( uint32_t i = 0; i < number_of_process_control; i++){
        fread(&p.remaining_burst_time, sizeof(uint32_t), 1, f);
        fread(&p.priority, sizeof(uint32_t), 1, f);
        fread(&p.arrival, sizeof(uint32_t), 1, f);
        p.started = false;
        if( !dyn_array_push_back(d,&p) ){
            return NULL;
        }
    }

    fclose(f);
    return d;
    //UNUSED(input_file);
    //return NULL;
}

bool shortest_remaining_time_first(dyn_array_t *ready_queue, ScheduleResult_t *result) 
{
    if(ready_queue == NULL || result == NULL)                                       //checks for improper inputs
        return false;
    return true;
    
    //UNUSED(ready_queue);
    UNUSED(result);
    //return false;
}
