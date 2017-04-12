#include <stdio.h>
#include <stdlib.h>
#include <alchemy/task.h>
#include <alchemy/timer.h>

#define XNSCHED_PRIO_MAX 	99
#define RT_SEC	1000000000
#define NITER	10

RT_TASK task_instance;

void task_routine(void *arg)
{
	int i;
	
	rt_task_set_periodic(NULL, TM_NOW, RT_SEC);

	for (i = 0; i < NITER; i++) {
		rt_task_wait_period(NULL);
		printf("+");
		fflush(0);
	}	
	return;
}

int main(void) 
{
	rt_task_create(&task_instance, 
		"task_name", 0, XNSCHED_PRIO_MAX, 0);
	rt_task_start(&task_instance, &task_routine, NULL);

	pause();
	return 0;
}

