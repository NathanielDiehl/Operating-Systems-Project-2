#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "dyn_array.h"
#include "processing_scheduling.h"


// You might find this handy.  I put it around unused parameters, but you should
// remove it before you submit. Just allows things to compile initially.
#define UNUSED(x) (void)(x)

// Compare functions
int compare_remaining_burst_time(const void *a, const void *b) {
  
    ProcessControlBlock_t *A = (ProcessControlBlock_t *)a;
    ProcessControlBlock_t *B = (ProcessControlBlock_t *)b;
  
    return (A->remaining_burst_time - B->remaining_burst_time);
}
int compare_priority(const void *a, const void *b) {
  
    ProcessControlBlock_t *A = (ProcessControlBlock_t *)a;
    ProcessControlBlock_t *B = (ProcessControlBlock_t *)b;
  
    return (A->priority - B->priority);
}
int compare_arrival(const void *a, const void *b) {
  
    ProcessControlBlock_t *A = (ProcessControlBlock_t *)a;
    ProcessControlBlock_t *B = (ProcessControlBlock_t *)b;
  
    return (A->arrival - B->arrival);
}





// private function
void virtual_cpu(ProcessControlBlock_t *process_control_block) 
{
    // decrement the burst time of the pcb
    --process_control_block->remaining_burst_time;
}

bool check_inputs(dyn_array_t *ready_queue, ScheduleResult_t *result, size_t* num_elements) {
    if (ready_queue == NULL || result == NULL) {
        return false; // Validate input parameters
    }

    *num_elements = dyn_array_size(ready_queue);
    if (*num_elements == 0) {
        return false; // No PCBs to process
    }

    return true;
}

void run_process(ProcessControlBlock_t *pcbptr, size_t  run_time,
                size_t* currentTime, size_t* totalWaitingTime, size_t* totalTurnaroundTime  ){
    if (pcbptr == NULL) {
        return;           
    }

    if(!pcbptr->started){
        pcbptr->started = true;
        if(pcbptr->arrival <= *currentTime)                                  //this can't be right
            *totalWaitingTime += *currentTime - pcbptr->arrival;
    }
    if(pcbptr->remaining_burst_time <= run_time){
        *currentTime += pcbptr->remaining_burst_time;
        pcbptr->remaining_burst_time = 0;
        if(pcbptr->arrival <= *currentTime)                                  //this can't be right
            *totalTurnaroundTime += *currentTime - pcbptr->arrival;
    }
    else {
        *currentTime += run_time;
        pcbptr->remaining_burst_time -= run_time;
    }
}

void run_ready_queue(dyn_array_t *ready_queue, ScheduleResult_t *result, size_t* num_elements) {
    ProcessControlBlock_t *pcbptr;
    size_t currentTime = 0;
    size_t totalWaitingTime = 0;
    size_t totalTurnaroundTime = 0;

    for (size_t i = 0; i < *num_elements; i++) {
        pcbptr = (ProcessControlBlock_t*)dyn_array_at(ready_queue, i);
        
        run_process(pcbptr, pcbptr->remaining_burst_time, &currentTime, &totalWaitingTime, &totalTurnaroundTime);
    }

    // Calculate average waiting and turnaround times.
    result->average_waiting_time = (float)totalWaitingTime / *num_elements;
    result->average_turnaround_time = (float)totalTurnaroundTime / *num_elements;
    result->total_run_time = currentTime; // Total run time is the current time after all PCBs have been processed.
}


bool first_come_first_serve(dyn_array_t *ready_queue, ScheduleResult_t *result) {
    size_t num_elements;
    if ( !check_inputs(ready_queue, result, &num_elements)) {             // Validate input parameters
        return false; 
    }

    dyn_array_sort(ready_queue, compare_arrival);
    run_ready_queue(ready_queue, result, &num_elements);
    return true;
}

bool shortest_job_first(dyn_array_t *ready_queue, ScheduleResult_t *result) 
{
    size_t num_elements;
    if ( !check_inputs(ready_queue, result, &num_elements)) {             // Validate input parameters
        return false; 
    }

    dyn_array_sort(ready_queue, compare_remaining_burst_time);
    run_ready_queue(ready_queue, result, &num_elements);
    return true;
}

bool priority(dyn_array_t *ready_queue, ScheduleResult_t *result) 
{
    size_t num_elements;
    if ( !check_inputs(ready_queue, result, &num_elements)) {             // Validate input parameters
        return false; 
    }
    
    dyn_array_sort(ready_queue, compare_priority);
    run_ready_queue(ready_queue, result, &num_elements);
    return true;
}

bool round_robin(dyn_array_t *ready_queue, ScheduleResult_t *result, size_t quantum) 
{
    size_t num_elements;
    if ( !check_inputs(ready_queue, result, &num_elements) || quantum == 0) {             // Validate input parameters
        return false; 
    }
    
    dyn_array_sort(ready_queue, compare_arrival);
    ProcessControlBlock_t *pcbptr;
    
    size_t currentTime = 0;
    size_t totalWaitingTime = 0;
    size_t totalTurnaroundTime = 0;

    while(!dyn_array_empty(ready_queue) ){
        pcbptr = (ProcessControlBlock_t*)dyn_array_at(ready_queue, 0);
        run_process(pcbptr, quantum, &currentTime, &totalWaitingTime, &totalTurnaroundTime);

        if(pcbptr->remaining_burst_time > 0)
            dyn_array_push_back(ready_queue, pcbptr);
        if( !dyn_array_pop_front(ready_queue))
            return false;
    }
    

    // Calculate average waiting and turnaround times.
    result->average_waiting_time = (float)totalWaitingTime / num_elements;
    result->average_turnaround_time = (float)totalTurnaroundTime / num_elements;
    result->total_run_time = currentTime; // Total run time is the current time after all PCBs have been processed.
    return true;
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
}

bool shortest_remaining_time_first(dyn_array_t *ready_queue, ScheduleResult_t *result) 
{
    size_t num_elements;
    if ( !check_inputs(ready_queue, result, &num_elements)) {             // Validate input parameters
        return false; 
    }
    
    dyn_array_sort(ready_queue, compare_remaining_burst_time);
    ProcessControlBlock_t *pcbptr;

    size_t currentTime = 0;
    size_t totalWaitingTime = 0;
    size_t totalTurnaroundTime = 0;
    
    while(!dyn_array_empty(ready_queue) ){
        pcbptr = (ProcessControlBlock_t*)dyn_array_at(ready_queue, 0);
        run_process(pcbptr, 1, &currentTime, &totalWaitingTime, &totalTurnaroundTime);

        if(pcbptr->remaining_burst_time > 0)
            dyn_array_insert_sorted(ready_queue, pcbptr, compare_remaining_burst_time);
        if( !dyn_array_pop_front(ready_queue))
            return false;
    }
    

    // Calculate average waiting and turnaround times.
    result->average_waiting_time = (float)totalWaitingTime / num_elements;
    result->average_turnaround_time = (float)totalTurnaroundTime / num_elements;
    result->total_run_time = currentTime; // Total run time is the current time after all PCBs have been processed.
    return true;
}
