#include <fcntl.h>
#include <stdio.h>
#include "gtest/gtest.h"
#include <pthread.h>
#include "../include/processing_scheduling.h"

// Using a C library requires extern "C" to prevent function managling
extern "C" 
{
#include <dyn_array.h>
}


#define NUM_PCB 30
#define QUANTUM 5 // Used for Robin Round for process as the run time limit

unsigned int score;
unsigned int total;







/*TEST(dyn_array_create, ValidCapacity)
{
    ASSERT_EQ(true,true);
    //ASSERT_EQ(dyn_array_create(0,0,NULL),NULL);
}

TEST(dyn_array_insert, IncreasedMemorySize)
{
    ASSERT_EQ(true,true);
}*/

//Test if the input file is empty
TEST(load_process_control_blocks, BadInput)
{
    ASSERT_EQ(load_process_control_blocks(NULL),(dyn_array_t*)NULL);
    ASSERT_EQ(load_process_control_blocks(""),(dyn_array_t*)NULL);
    ASSERT_EQ(load_process_control_blocks("\n"),(dyn_array_t*)NULL);
    ASSERT_EQ(load_process_control_blocks("fake.file"),(dyn_array_t*)NULL);
}

//test if load_process_control_blocks returns a valid pointer
TEST(load_process_control_blocks, GoodInput)
{
    dyn_array_t *d = load_process_control_blocks("pcb.bin");
    ASSERT_NE(d,(dyn_array_t*)NULL);
}

//test if the input file vaild and the PCB number is correct
TEST(load_process_control_blocks, SuccessfulLoad) 
{
    // Load PCB
    const char* input_file = "pcb.bin";
    dyn_array_t* pcb_array = load_process_control_blocks(input_file);    
    
    // Validate PCB data
    ASSERT_TRUE(pcb_array != NULL);
    ASSERT_EQ(dyn_array_size(pcb_array), (size_t)4);

    ProcessControlBlock_t* pcb = (ProcessControlBlock_t*)dyn_array_at(pcb_array, 0);
    ASSERT_EQ(pcb->remaining_burst_time, (uint32_t)15);
    ASSERT_EQ(pcb->priority, (uint32_t)0);
    ASSERT_EQ(pcb->arrival, (uint32_t)0);

    pcb = (ProcessControlBlock_t*)dyn_array_at(pcb_array, 1);
    ASSERT_EQ(pcb->remaining_burst_time,(uint32_t)10);
    ASSERT_EQ(pcb->priority, (uint32_t)0);
    ASSERT_EQ(pcb->arrival, (uint32_t)1);

    
    pcb = (ProcessControlBlock_t*)dyn_array_at(pcb_array, 2);
    ASSERT_EQ(pcb->remaining_burst_time, (uint32_t)5);
    ASSERT_EQ(pcb->priority, (uint32_t)0);
    ASSERT_EQ(pcb->arrival, (uint32_t)2);


    pcb = (ProcessControlBlock_t*)dyn_array_at(pcb_array, 3);
    ASSERT_EQ(pcb->remaining_burst_time, (uint32_t)20);
    ASSERT_EQ(pcb->priority, (uint32_t)0);
    ASSERT_EQ(pcb->arrival, (uint32_t)3);


    //clean up
    dyn_array_destroy(pcb_array);
}

//Test if the input file is missing
TEST(first_come_first_serve, MissingFile) {
    // Create an empty ready queue
    dyn_array_t* ready_queue = load_process_control_blocks("NULL.bin");

    // Run FCFS scheduling
    ScheduleResult_t result;
    ASSERT_FALSE(first_come_first_serve(ready_queue, &result));

    // Cleanup
    dyn_array_destroy(ready_queue);
}

//Test if the input file is empty
TEST(first_come_first_serve, BadInput)
{
    dyn_array_t *ready_queue = load_process_control_blocks("pcb.bin");
    ScheduleResult_t result;
    ASSERT_EQ(first_come_first_serve(ready_queue,NULL),false);
    ASSERT_EQ(first_come_first_serve(NULL,&result),false);

    //clean up
    dyn_array_destroy(ready_queue);
}

//Test average turnaround time for shortest job first
TEST(first_come_first_serve, GoodTurnAround){
    dyn_array_t *ready_queue = load_process_control_blocks("pcb.bin");
    ScheduleResult_t result;
    first_come_first_serve(ready_queue,&result);
    ASSERT_EQ(result.average_turnaround_time,30);
}

//Test average waiting time for shortest job first
TEST(first_come_first_serve, GoodWait){
    dyn_array_t *ready_queue = load_process_control_blocks("pcb.bin");
    ScheduleResult_t result;
    first_come_first_serve(ready_queue,&result);
    ASSERT_EQ(result.average_waiting_time,17.5);
}

//Test total run time for shortest job first
TEST(first_come_first_serve, GoodTotal){
    dyn_array_t *ready_queue = load_process_control_blocks("pcb.bin");
    ScheduleResult_t result;
    first_come_first_serve(ready_queue,&result);
    ASSERT_EQ(result.total_run_time,50.00);
}

//Test if the input file is empty
TEST(shortest_job_first, BadInput)
{
    dyn_array_t *ready_queue = load_process_control_blocks("pcb.bin");
    ScheduleResult_t result;
    ASSERT_EQ(shortest_job_first(ready_queue,NULL),false);
    ASSERT_EQ(shortest_job_first(NULL,&result),false);

    //clean up
    dyn_array_destroy(ready_queue);
}

//Test average turnaround time for shortest job first
TEST(shortest_job_first, GoodTurnAround){
    dyn_array_t *ready_queue = load_process_control_blocks("pcb.bin");
    ScheduleResult_t result;
    shortest_job_first(ready_queue,&result);
    ASSERT_EQ(result.average_turnaround_time,25);
}

//Test average waiting time for shortest job first
TEST(shortest_job_first, GoodWait){
    dyn_array_t *ready_queue = load_process_control_blocks("pcb.bin");
    ScheduleResult_t result;
    shortest_job_first(ready_queue,&result);
    ASSERT_EQ(result.average_waiting_time,12.5);
}

//Test total run time for shortest job first
TEST(shortest_job_first, GoodTotal){
    dyn_array_t *ready_queue = load_process_control_blocks("pcb.bin");
    ScheduleResult_t result;
    shortest_job_first(ready_queue,&result);
    ASSERT_EQ(result.total_run_time,(size_t)50);
}

//Test if the input file is empty
TEST(priority, BadInput)
{
    dyn_array_t *ready_queue = load_process_control_blocks("pcb.bin");
    ScheduleResult_t result;
    ASSERT_EQ(priority(ready_queue,NULL),false);
    ASSERT_EQ(priority(NULL,&result),false);

    //clean up
    dyn_array_destroy(ready_queue);
}

//Test average turnaround time for priority
TEST(priority, GoodTurnAround){
    dyn_array_t *ready_queue = load_process_control_blocks("pcb.bin");
    ScheduleResult_t result;
    priority(ready_queue,&result);
    ASSERT_EQ(result.average_turnaround_time,30);
}

//Test average waiting time for priority
TEST(priority, GoodWait){
    dyn_array_t *ready_queue = load_process_control_blocks("pcb.bin");
    ScheduleResult_t result;
    priority(ready_queue,&result);
    ASSERT_EQ(result.average_waiting_time,17.5);
}

//Test total run time for priority
TEST(priority, GoodTotal){
    dyn_array_t *ready_queue = load_process_control_blocks("pcb.bin");
    ScheduleResult_t result;
    priority(ready_queue,&result);
    ASSERT_EQ(result.total_run_time,(size_t)50);
}

//Test if the input file is empty
TEST(round_robin, BadInput)
{
    dyn_array_t *ready_queue = load_process_control_blocks("pcb.bin");
    ScheduleResult_t result;
    size_t quantum = 0;
    ASSERT_EQ(round_robin(ready_queue,NULL,quantum),false);
    ASSERT_EQ(round_robin(NULL,&result,quantum),false);

    //clean up
    dyn_array_destroy(ready_queue);
}

//Test average turnaround time for round robin
TEST(round_robin, GoodTurnAround){
    dyn_array_t *ready_queue = load_process_control_blocks("pcb.bin");
    ScheduleResult_t result;
    size_t quantum = 3;
    round_robin(ready_queue,&result,quantum);
    ASSERT_EQ(result.average_turnaround_time,37.0);
}

//Test average waiting time for round robin
TEST(round_robin, GoodWait){
    dyn_array_t *ready_queue = load_process_control_blocks("pcb.bin");
    ScheduleResult_t result;
    size_t quantum = 3;
    round_robin(ready_queue,&result,quantum);
    ASSERT_EQ(result.average_waiting_time,24.5);
}

//Test total run time for round robin
TEST(round_robin, GoodTotal){
    dyn_array_t *ready_queue = load_process_control_blocks("pcb.bin");
    ScheduleResult_t result;
    size_t quantum = 3;
    round_robin(ready_queue,&result,quantum);
    ASSERT_EQ(result.total_run_time,(size_t)50);
}

//Test if the input file is empty
TEST(shortest_remaining_time_first, BadInput)
{
    dyn_array_t *ready_queue = load_process_control_blocks("pcb.bin");
    ScheduleResult_t result;
    ASSERT_EQ(shortest_remaining_time_first(ready_queue,NULL),false);
    ASSERT_EQ(shortest_remaining_time_first(NULL,&result),false);

    //clean up
    dyn_array_destroy(ready_queue);
}

//Test average turnaround time for shortest remaining time first
TEST(shortest_remaining_time_first, GoodTurnAround){
    dyn_array_t *ready_queue = load_process_control_blocks("pcb.bin");
    ScheduleResult_t result;
    shortest_remaining_time_first(ready_queue,&result);
    ASSERT_EQ(result.average_turnaround_time,24.25);
}

//Test average waiting time for shortest remaining time first
TEST(shortest_remaining_time_first, GoodWait){
    dyn_array_t *ready_queue = load_process_control_blocks("pcb.bin");
    ScheduleResult_t result;
    shortest_remaining_time_first(ready_queue,&result);
    ASSERT_EQ(result.average_waiting_time,11.75);
}

//Test total run time for shortest remaining time first
TEST(shortest_remaining_time_first, GoodTotal){
    dyn_array_t *ready_queue = load_process_control_blocks("pcb.bin");
    ScheduleResult_t result;
    shortest_remaining_time_first(ready_queue,&result);
    ASSERT_EQ(result.total_run_time,(size_t)50);
}

//Test if the input file is empty
TEST(shortest_remaining_time_first, NullResult) {
    dyn_array_t *ready_queue = dyn_array_create(0, sizeof(ProcessControlBlock_t), NULL);
    ScheduleResult_t *result = NULL;
    EXPECT_EQ(false, shortest_remaining_time_first(ready_queue, result));
    dyn_array_destroy(ready_queue);
}

//Test if the input file is empty
TEST(shortest_remaining_time_first, NullReadyQueue){
    dyn_array_t *ready_queue = NULL;
    ScheduleResult_t *result = new ScheduleResult_t;
    EXPECT_EQ(false, shortest_remaining_time_first(ready_queue, result));
    delete result;
}



/*
class GradeEnvironment : public testing::Environment 
{
    public:
        virtual void SetUp() 
        {
            score = 0;
            total = 210;
        }

        virtual void TearDown()
        {
            ::testing::Test::RecordProperty("points_given", score);
            ::testing::Test::RecordProperty("points_total", total);
            std::cout << "SCORE: " << score << '/' << total << std::endl;
        }
};
*/

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    // ::testing::AddGlobalTestEnvironment(new GradeEnvironment);
    return RUN_ALL_TESTS();
}
