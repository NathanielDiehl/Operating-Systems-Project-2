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

TEST(load_process_control_blocks, BadInput)
{
    ASSERT_EQ(load_process_control_blocks(NULL),(dyn_array_t*)NULL);
    ASSERT_EQ(load_process_control_blocks(""),(dyn_array_t*)NULL);
    ASSERT_EQ(load_process_control_blocks("\n"),(dyn_array_t*)NULL);
    ASSERT_EQ(load_process_control_blocks("fake.file"),(dyn_array_t*)NULL);
}
TEST(load_process_control_blocks, GoodInput)
{
    dyn_array_t *d = load_process_control_blocks("pcb.bin");
    ASSERT_NE(d,(dyn_array_t*)NULL);
}

//test if the input file vaild and the PCB number is correct
TEST(load_process_control_blocks, SuccessfulLoad) 
{
    // Load PCB
    const char* input_file = "valid_pcb_data.bin";
    dyn_array_t* pcb_array = load_process_control_blocks(input_file);    
    
    // Validate PCB data
    ASSERT_TRUE(pcb_array != NULL);
    ASSERT_EQ(dyn_array_size(pcb_array), (size_t)3);

    ProcessControlBlock_t* pcb = (ProcessControlBlock_t*)dyn_array_at(pcb_array, 0);
    ASSERT_EQ(pcb->remaining_burst_time, (uint32_t)10);
    ASSERT_EQ(pcb->priority, (uint32_t)1);
    ASSERT_EQ(pcb->arrival, (uint32_t)0);

    pcb = (ProcessControlBlock_t*)dyn_array_at(pcb_array, 1);
    ASSERT_EQ(pcb->remaining_burst_time,(uint32_t)5);
    ASSERT_EQ(pcb->priority, (uint32_t)2);
    ASSERT_EQ(pcb->arrival, (uint32_t)1);
    
    pcb = (ProcessControlBlock_t*)dyn_array_at(pcb_array, 2);
    ASSERT_EQ(pcb->remaining_burst_time, (uint32_t)20);
    ASSERT_EQ(pcb->priority, (uint32_t)3);
    ASSERT_EQ(pcb->arrival, (uint32_t)2);

    //clean up
    dyn_array_destroy(pcb_array);
}


TEST(first_come_first_serve, Success) {
    // Load PCBs from the binary file created earlier
    dyn_array_t* ready_queue = load_process_control_blocks("valid_pcb_data.bin");
    ASSERT_TRUE(ready_queue != NULL);

    // Run FCFS scheduling
    ScheduleResult_t result;
    ASSERT_TRUE(first_come_first_serve(ready_queue, &result));

    /*
    PCB1 waits 0 time units, turns around at 10
    PCB2 waits 10 time units, turns around at 15
    PCB3 waits 15 time units, turns around at 35
    */ 
    float expected_avg_waiting_time = (0 + 10 + 15) / 3.0f;
    float expected_avg_turnaround_time = (10 + 15 + 35) / 3.0f;
    ASSERT_NEAR(result.average_waiting_time, expected_avg_waiting_time, 1);//0.001);
    ASSERT_NEAR(result.average_turnaround_time, expected_avg_turnaround_time, 0.001);

    // Cleanup
    dyn_array_destroy(ready_queue);
}

TEST(first_come_first_serve, Empty_file) {
    // Create an empty ready queue
    dyn_array_t* ready_queue = dyn_array_create(0, sizeof(ProcessControlBlock_t), NULL);

    // Run FCFS scheduling
    ScheduleResult_t result;
    ASSERT_FALSE(first_come_first_serve(ready_queue, &result));

    // Cleanup
    dyn_array_destroy(ready_queue);
}

TEST(first_come_first_serve, BadInput)
{
    dyn_array_t *ready_queue = load_process_control_blocks("pcb.bin");
    ScheduleResult_t result;
    ASSERT_EQ(first_come_first_serve(ready_queue,NULL),false);
    ASSERT_EQ(first_come_first_serve(NULL,&result),false);

    //clean up
    dyn_array_destroy(ready_queue);
}
TEST(shortest_job_first, BadInput)
{
    dyn_array_t *ready_queue = load_process_control_blocks("pcb.bin");
    ScheduleResult_t result;
    ASSERT_EQ(shortest_job_first(ready_queue,NULL),false);
    ASSERT_EQ(shortest_job_first(NULL,&result),false);

    //clean up
    dyn_array_destroy(ready_queue);
}
TEST(priority, BadInput)
{
    dyn_array_t *ready_queue = load_process_control_blocks("pcb.bin");
    ScheduleResult_t result;
    ASSERT_EQ(priority(ready_queue,NULL),false);
    ASSERT_EQ(priority(NULL,&result),false);

    //clean up
    dyn_array_destroy(ready_queue);
}
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
TEST(shortest_remaining_time_first, BadInput)
{
    dyn_array_t *ready_queue = load_process_control_blocks("pcb.bin");
    ScheduleResult_t result;
    ASSERT_EQ(shortest_remaining_time_first(ready_queue,NULL),false);
    ASSERT_EQ(shortest_remaining_time_first(NULL,&result),false);

    //clean up
    dyn_array_destroy(ready_queue);
}



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


int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new GradeEnvironment);
    return RUN_ALL_TESTS();
}
