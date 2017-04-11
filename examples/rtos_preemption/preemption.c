#include <stdio.h>
#include <stdlib.h>
#include <alchemy/task.h>
#include <alchemy/timer.h>

#define XNSCHED_HIGH_PRIO	99

#define RT_SEC 	1000000000
#define RT_MSEC	1000000
#define RT_USEC 1000
#define RT_NSEC 1

RT_TASK high_task, low_task;

#define HIGH_NITER	10
#define LOW_NITER	1 

void highTask(void *arg)
{
	int i;
	
	rt_task_set_periodic(NULL, TM_NOW, 5 * RT_MSEC);

	for (i = 0; i < HIGH_NITER; i++) {
		rt_task_wait_period(NULL);
			
		printf("+");

	}	

	fflush(stdout);
}


void lowTask(void *arg)
{
	int i, j;
	RTIME t0, t1;

	rt_task_set_periodic(NULL, TM_NOW, 100 * RT_MSEC);	
	
	for (i = 0; i < LOW_NITER; i++) {
		//rt_task_wait_period(NULL);
		
		for(j = 0; j < 50; j++) {
			t0 = rt_timer_read();
			while(1) {
				t1 = rt_timer_read();
				if(t1 - t0 > RT_MSEC) break;
			}
			printf("-");
		}
	}
	fflush(stdout);
}

int main(void) {

	rt_task_create(&high_task, "high", 0, XNSCHED_HIGH_PRIO, 0);
	rt_task_create(&low_task, "low", 0, XNSCHED_HIGH_PRIO - 2, 0);

	rt_task_start(&high_task, &highTask, NULL);
	rt_task_start(&low_task, &lowTask, NULL);

	pause();
	
	return 0;
}

