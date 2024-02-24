#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "dyn_array.h"
#include "processing_scheduling.h"


size_t current_time = 0;

// Compare functions
int compare_remaining_burst_time(const void *a, const void *b) {
  
    ProcessControlBlock_t *A = (ProcessControlBlock_t *)a;
    ProcessControlBlock_t *B = (ProcessControlBlock_t *)b;
  
    return (A->remaining_burst_time - B->remaining_burst_time);         //compares remaining burst time
}
int compare_priority(const void *a, const void *b) {
  
    ProcessControlBlock_t *A = (ProcessControlBlock_t *)a;
    ProcessControlBlock_t *B = (ProcessControlBlock_t *)b;
  
    return (A->priority - B->priority);                                 //compares priority
}
int compare_arrival(const void *a, const void *b) {
  
    ProcessControlBlock_t *A = (ProcessControlBlock_t *)a;
    ProcessControlBlock_t *B = (ProcessControlBlock_t *)b;
  
    return (A->arrival - B->arrival);                                   //compares arrival
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
    if (pcbptr == NULL) {                                                             //checs that the process isn't a Null pointer
        return;           
    }

    if(!pcbptr->started){                                                             //checks if the process is starting up or if it has already been running
        pcbptr->started = true;                                                       
        *totalWaitingTime += (*currentTime - pcbptr->last_time_ran );                 //adds the time the process has been waitign to the total time
    }
    if(pcbptr->remaining_burst_time <= run_time){                                     //if the process is finished
        *currentTime += pcbptr->remaining_burst_time;                                 //updates the currentTime
        pcbptr->remaining_burst_time = 0;
        *totalTurnaroundTime += *currentTime;                                         //updates the totalTurnaroundTime
    }
    else {
        *currentTime += run_time;                                                     //updates the currentTime
        pcbptr->remaining_burst_time -= run_time;                                     //updates the process remaining time
        pcbptr->last_time_ran = *currentTime;                                         //updates last_time_ran so we can accuritly update totalWaitingTime next time the process is run
        pcbptr->started = false;
    }
}

void run_ready_queue(dyn_array_t *ready_queue, ScheduleResult_t *result, size_t* num_elements) {
    ProcessControlBlock_t *pcbptr;
    size_t currentTime = 0;
    size_t totalWaitingTime = 0;
    size_t totalTurnaroundTime = 0;

    for (size_t i = 0; i < *num_elements; i++) {                                                                // loop through every element i nthe queue
        pcbptr = (ProcessControlBlock_t*)dyn_array_at(ready_queue, i);
        run_process(pcbptr, pcbptr->remaining_burst_time, &currentTime, &totalWaitingTime, &totalTurnaroundTime); //runs the process
    }

    result->average_waiting_time = (float)totalWaitingTime / *num_elements;                         // Calculate statistics
    result->average_turnaround_time = (float)totalTurnaroundTime / *num_elements;                   //** There seems to be some ambiguity in how arrival time needs to be used when calculating average_waiting_time and average_turnaround_time. After reading through the examples in the book and having a discussing with Vasserman we have decided to design the code as if all the processes arrived at the start (With the exception of shortest_remaining_time_first where arrival time was explicitly baked into the functioning of the algorithm). **//
    result->total_run_time = currentTime;                                                           //** This decision allows our code to replicate the exact behavior and outputs of every example provided in the textbook. **/
}


bool first_come_first_serve(dyn_array_t *ready_queue, ScheduleResult_t *result) {
    size_t num_elements;
    if ( !check_inputs(ready_queue, result, &num_elements)) {             // Validate input parameters
        return false; 
    }

    dyn_array_sort(ready_queue, compare_arrival);                         //sorrts queue
    run_ready_queue(ready_queue, result, &num_elements);                  //runs processes in queue
    return true;
}

bool shortest_job_first(dyn_array_t *ready_queue, ScheduleResult_t *result) 
{
    size_t num_elements;
    if ( !check_inputs(ready_queue, result, &num_elements)) {             // Validate input parameters
        return false; 
    }

    dyn_array_sort(ready_queue, compare_remaining_burst_time);            //sorrts queue
    run_ready_queue(ready_queue, result, &num_elements);                  //runs processes in queue
    return true;
}

bool priority(dyn_array_t *ready_queue, ScheduleResult_t *result) 
{
    size_t num_elements;
    if ( !check_inputs(ready_queue, result, &num_elements)) {             // Validate input parameters
        return false; 
    }
    
    dyn_array_sort(ready_queue, compare_priority);                        //sorrts queue
    run_ready_queue(ready_queue, result, &num_elements);                  //runs processes in queue
    return true;
}

bool round_robin(dyn_array_t *ready_queue, ScheduleResult_t *result, size_t quantum) 
{
    size_t num_elements;
    if ( !check_inputs(ready_queue, result, &num_elements) || quantum == 0) {             // Validate input parameters
        return false; 
    }
    
    dyn_array_sort(ready_queue, compare_arrival);                         //sorrts queue
    ProcessControlBlock_t *pcbptr;
    
    size_t currentTime = 0;
    size_t totalWaitingTime = 0;
    size_t totalTurnaroundTime = 0;

    while(!dyn_array_empty(ready_queue) ){
        pcbptr = (ProcessControlBlock_t*)dyn_array_at(ready_queue, 0);                          //grabs the front process
        run_process(pcbptr, quantum, &currentTime, &totalWaitingTime, &totalTurnaroundTime);    //runs the front process

        if(pcbptr->remaining_burst_time > 0)                //if the process isn't finished, then its added to the back of the queue
            dyn_array_push_back(ready_queue, pcbptr);
        if( !dyn_array_pop_front(ready_queue))              //the front element is removed from the queue
            return false;
    }
    

    result->average_waiting_time = (float)totalWaitingTime / num_elements;                                  // Calculate statistics
    result->average_turnaround_time = (float)totalTurnaroundTime / num_elements;
    result->total_run_time = currentTime;
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
    fread(&number_of_process_control, sizeof(uint32_t), 1, f);                                                 //reads the number of processes

    dyn_array_t * d = dyn_array_create(number_of_process_control, sizeof(ProcessControlBlock_t), NULL);
    
    ProcessControlBlock_t p;
    for( uint32_t i = 0; i < number_of_process_control; i++){
        fread(&p.remaining_burst_time, sizeof(uint32_t), 1, f);                                                 //reads the process's remaining bust time
        fread(&p.priority, sizeof(uint32_t), 1, f);                                                             //reads the process's priority 
        fread(&p.arrival, sizeof(uint32_t), 1, f);                                                              //reads the process's arrival
        p.started = false;
        p.last_time_ran = 0;
        if( !dyn_array_push_back(d,&p) ){                                                                       //adds process to queue
            return NULL;
        }
    }

    fclose(f);          //close file
    return d;
}

bool shortest_remaining_time_first(dyn_array_t *ready_queue, ScheduleResult_t *result) 
{
    size_t num_elements;
    if ( !check_inputs(ready_queue, result, &num_elements)) {             // Validate input parameters
        return false; 
    }

    dyn_array_t *use_queue = dyn_array_create(dyn_array_capacity(ready_queue), sizeof(ProcessControlBlock_t), NULL);        //makes a new queue to hold all the process that have arrived
    dyn_array_insert_sorted(use_queue, dyn_array_front(ready_queue), compare_remaining_burst_time);                         //adds first process to use_queue
    dyn_array_pop_front(ready_queue);                                                                                       //removes that process from ready_queue
    ProcessControlBlock_t *pcbptr;

    size_t currentTime = 0;
    size_t totalWaitingTime = 0;
    size_t totalTurnaroundTime = 0;
    
    while(!dyn_array_empty(use_queue) || !dyn_array_empty(ready_queue) ){                                                      //loop untill both the ready_queue and the use_queue are empty
        pcbptr = (ProcessControlBlock_t*)dyn_array_front(use_queue);                                                           //grab the shortest process in the use_queue
        run_process(pcbptr, 1, &currentTime, &totalWaitingTime, &totalTurnaroundTime);                                         //runs the process

        if(pcbptr->remaining_burst_time > 0){                                                                                   //if the process isn't complete, added back the the queue
            current_time = currentTime;
            dyn_array_insert_sorted(use_queue, pcbptr, compare_remaining_burst_time);
        }
        if( !dyn_array_pop_front(use_queue))                                                                                    //removes the front element from the queue
            return false;

        if(!dyn_array_empty(ready_queue) && ((ProcessControlBlock_t*)dyn_array_front(ready_queue))->arrival <= currentTime){        //checks if any more processes have arrived
            dyn_array_insert_sorted(use_queue, dyn_array_front(ready_queue), compare_remaining_burst_time);                         //moves element from 
            totalWaitingTime    -= ((ProcessControlBlock_t*)dyn_array_front(ready_queue))->arrival;                                 //removes error from arrival
            totalTurnaroundTime -= ((ProcessControlBlock_t*)dyn_array_front(ready_queue))->arrival;                                 //removes error from arrival
            dyn_array_pop_front(ready_queue);                                                                                       //removes the front element from the queue
        }
    }
    


    result->average_waiting_time = (float)totalWaitingTime / num_elements;                                  // Calculate statistics
    result->average_turnaround_time = (float)totalTurnaroundTime / num_elements;
    result->total_run_time = currentTime;
    return true;
}
