#include <stdio.h>
#include <stdlib.h>
#include <alchemy/task.h>
#include <alchemy/timer.h>

#define XNSCHED_PRIO_MAX	99
#define RT_MSEC	1000000
#define HIGH_NITER	10

RT_TASK high_task, low_task;

void high_task_routine(void *arg)
{
	int i;
	
	rt_task_set_periodic(NULL, TM_NOW, 5 * RT_MSEC);

	for (i = 0; i < HIGH_NITER; i++) {
		rt_task_wait_period(NULL);
			
		printf("+");
		fflush(0);
	}	
	return;
}

void low_task_routine(void *arg)
{
	int i;
	RTIME t0, t1;

	for(i = 0; i < 50; i++) {
		t0 = rt_timer_read();
		while(1) {
			t1 = rt_timer_read();
			if(t1 - t0 > RT_MSEC) break;
		}
		printf("-");
		fflush(0);
	}	
	return;
}

int main(void) {

	rt_task_create(&high_task, 
		"high_task_name", 0, XNSCHED_PRIO_MAX, 0);
	rt_task_create(&low_task, 
		"low_task_name", 0, XNSCHED_PRIO_MAX - 1, 0);

	rt_task_start(&high_task, &high_task_routine, NULL);
	rt_task_start(&low_task, &low_task_routine, NULL);

	pause();
	
	return 0;
}

