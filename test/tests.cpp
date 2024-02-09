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
    ASSERT_EQ(dyn_array_size(pcb_array), 3);

    dyn_array_destroy(pcb_array);
}


TEST(first_come_first_serve, BadInput)
{
    //dyn_array_t *ready_queue = load_process_control_blocks("pcb.bin");
    ScheduleResult_t *result = NULL;
    ASSERT_EQ(first_come_first_serve(NULL,result),false);
}
TEST(shortest_job_first, BadInput)
{
    //dyn_array_t *ready_queue = load_process_control_blocks("pcb.bin");
    ScheduleResult_t *result = NULL;
    ASSERT_EQ(first_come_first_serve(NULL,result),false);
}
TEST(priority, BadInput)
{
    //dyn_array_t *ready_queue = load_process_control_blocks("pcb.bin");
    ScheduleResult_t *result = NULL;
    ASSERT_EQ(first_come_first_serve(NULL,result),false);
}
TEST(round_robin, BadInput)
{
    //dyn_array_t *ready_queue = load_process_control_blocks("pcb.bin");
    ScheduleResult_t *result = NULL;
    ASSERT_EQ(first_come_first_serve(NULL,result),false);
}
TEST(shortest_remaining_time_first, BadInput)
{
    //dyn_array_t *ready_queue = load_process_control_blocks("pcb.bin");
    ScheduleResult_t *result = NULL;
    ASSERT_EQ(first_come_first_serve(NULL,result),false);
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
