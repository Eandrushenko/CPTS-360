#include <stdio.h>
#include "type.h"

int enqueue(PROC **queue, PROC *p)
{
	PROC* Cur = *queue;
	if (*queue == NULL || (*queue)->priority <= p->priority)
	{
		p->next = *queue;
		*queue = p;
	}
	else
	{
		while (Cur->next != NULL && Cur->next->priority > p->priority)
		{
			Cur = Cur->next;
		}
		p->next = Cur->next;
		Cur->next = p;
	}
}

PROC *dequeue(PROC **queue)
{
	// remove and return first PROC from queue
	PROC* Cur = *queue;
	PROC* Prev = *queue;

	if (Cur->pid == 1)
	{
		return NULL;
	}
	else
	{
		Cur = Cur->next;
		Prev->next = Cur->next;
		return Cur;
	}
}

int printList(char *name, PROC *p)
{
	printf("%s = ", name);
	PROC* Cur = p;
	while (Cur)
	{
		printf("[%d %d] -> ", Cur->pid, Cur->priority);
		Cur = Cur->next;
	}
	printf("NULL\n");
	return 0;

	// print list elements as [pid priority] -> ....
}
