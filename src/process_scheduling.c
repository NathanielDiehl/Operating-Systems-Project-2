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

bool first_come_first_serve(dyn_array_t *ready_queue, ScheduleResult_t *result) 
{
    if(ready_queue == NULL || result == NULL)                                       //checks for improper inputs
        return false;
    return true;
    //UNUSED(ready_queue);
    //UNUSED(result);
    //return false;
}

bool shortest_job_first(dyn_array_t *ready_queue, ScheduleResult_t *result) 
{
    if(ready_queue == NULL || result == NULL)                                       //checks for improper inputs
        return false;
    return true;

    //UNUSED(ready_queue);
    //UNUSED(result);
    //return false;   
}

bool priority(dyn_array_t *ready_queue, ScheduleResult_t *result) 
{
    if(ready_queue == NULL || result == NULL)                                       //checks for improper inputs
        return false;
    return true;
    
    //UNUSED(ready_queue);
    //UNUSED(result);
    //return false;   
}

bool round_robin(dyn_array_t *ready_queue, ScheduleResult_t *result, size_t quantum) 
{
    if(ready_queue == NULL || result == NULL)                                       //checks for improper inputs
        return false;
    return true;
    
    //UNUSED(ready_queue);
    //UNUSED(result);
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
        if( dyn_array_push_back(d,&p) ){
            return NULL;
        }
    }
 
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
    //UNUSED(result);
    //return false;
}
