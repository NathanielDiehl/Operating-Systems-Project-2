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
    const char* input_file = "valid_pcb_data.bin";
    dyn_array_t* pcb_array = load_process_control_blocks(input_file);    
    
    ASSERT_TRUE(pcb_array != NULL);
    ASSERT_EQ(dyn_array_size(pcb_array), (size_t)3);

    dyn_array_destroy(pcb_array);
}


TEST(first_come_first_serve, FCFS_Success) {
    // Create a dynamic array and manually populate it with PCBs
    dyn_array_t* ready_queue = dyn_array_create(2, sizeof(ProcessControlBlock_t), NULL);
    ProcessControlBlock_t pcb1 = {10, 1, 0, false};
    ProcessControlBlock_t pcb2 = {20, 2, 5, false};
    dyn_array_push_back(ready_queue, &pcb1);
    dyn_array_push_back(ready_queue, &pcb2);

    // Run FCFS scheduling
    ScheduleResult_t result;
    ASSERT_TRUE(first_come_first_serve(ready_queue, &result));

    // Validate scheduling results
    float expected_avg_waiting_time = 5; // (0 + 10 - 5) / 2
    float expected_avg_turnaround_time = 20; // ((10 - 0) + (30 - 5)) / 2
    ASSERT_EQ(result.average_waiting_time, expected_avg_waiting_time);
    ASSERT_EQ(result.average_turnaround_time, expected_avg_turnaround_time);
    ASSERT_EQ(result.total_run_time, 30); // 10 + 20

    dyn_array_destroy(ready_queue);
}

TEST(first_come_first_serve, BadInput)
{
    dyn_array_t *ready_queue = load_process_control_blocks("pcb.bin");
    ScheduleResult_t result;
    ASSERT_EQ(first_come_first_serve(ready_queue,NULL),false);
    ASSERT_EQ(first_come_first_serve(NULL,&result),false);
}
TEST(shortest_job_first, BadInput)
{
    dyn_array_t *ready_queue = load_process_control_blocks("pcb.bin");
    ScheduleResult_t result;
    ASSERT_EQ(shortest_job_first(ready_queue,NULL),false);
    ASSERT_EQ(shortest_job_first(NULL,&result),false);
}
TEST(priority, BadInput)
{
    dyn_array_t *ready_queue = load_process_control_blocks("pcb.bin");
    ScheduleResult_t result;
    ASSERT_EQ(priority(ready_queue,NULL),false);
    ASSERT_EQ(priority(NULL,&result),false);
}
TEST(round_robin, BadInput)
{
    dyn_array_t *ready_queue = load_process_control_blocks("pcb.bin");
    ScheduleResult_t result;
    size_t quantum = 0;
    ASSERT_EQ(round_robin(ready_queue,NULL,quantum),false);
    ASSERT_EQ(round_robin(NULL,&result,quantum),false);
}
TEST(shortest_remaining_time_first, BadInput)
{
    dyn_array_t *ready_queue = load_process_control_blocks("pcb.bin");
    ScheduleResult_t result;
    ASSERT_EQ(shortest_remaining_time_first(ready_queue,NULL),false);
    ASSERT_EQ(shortest_remaining_time_first(NULL,&result),false);
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
