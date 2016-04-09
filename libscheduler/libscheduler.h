/** @file libscheduler.h
 */

#ifndef LIBSCHEDULER_H_
#define LIBSCHEDULER_H_
#include "../libpriqueue/libpriqueue.h"

//
//	Constants which represent the different scheduling algorithms
//
typedef enum {FCFS = 0, SJF, PSJF, PRI, PPRI, RR} scheme_t;

void	scheduler_start_up					(int cores, scheme_t scheme);
int		scheduler_new_job					(int job_number, int time, int running_time, int priority);
int		scheduler_job_finished				(int core_id, int job_number, int time);
int		scheduler_quantum_expired			(int core_id, int time);
float	scheduler_average_turnaround_time	();
float	scheduler_average_waiting_time		();
float	scheduler_average_response_time		();
void	scheduler_clean_up					();
void	scheduler_show_queue				();

//	------------------------------------------------------------------------------------------
//	Custom Helper Functions
//	------------------------------------------------------------------------------------------
void	inc_wait							(int t);
void	inc_resp							(int t);
void	inc_turn							(int t);

//	------------------------------------------------------------------------------------------
//	Stores information making up a job to be scheduled including any statistics.
//	You may need to define some global variables or a struct to store your job queue elements. 
//	------------------------------------------------------------------------------------------
typedef struct _job_t_
{
	int arr_t;			//	Job arrival time
	int run_t;			//	Job run time
	int rem_t;			//	Job time remaining
	
	int pri;			//	Job Priority 
	int jid;			//	Job ID

	int init_core_t;	//	Initial Core time
	int updt_core_t;	//	Last updated cores time
} job_t;

//	------------------------------------------------------------------------------------------
//	Useful global cores structure
//	------------------------------------------------------------------------------------------
typedef struct _core_t_
{
	job_t** jobs;
	int count;
} core_t;

//	------------------------------------------------------------------------------------------
//	Global Var/Struct Initializations
//	------------------------------------------------------------------------------------------
priqueue_t* jobs;
scheme_t sch_type;
core_t cores;
int cur_t;


#endif /* LIBSCHEDULER_H_ */
