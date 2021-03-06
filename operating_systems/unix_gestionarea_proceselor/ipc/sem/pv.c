/*
 * pv.c
 *
 *  Created on: Sep 10, 2020
 *      Author: Gabriel Dimitriu
 *  examples from:UNIX - Gestionarea Proceselor by Iosif Ignat and Adrian Kacso
 */

#include "pv.h"

static void semcall(int semid, int op)
{
	struct sembuf pbuf;
	pbuf.sem_num = 0;
	pbuf.sem_op = op;
	pbuf.sem_flg = 0;
	if (semop(semid, &pbuf, 1) < 0)
		err_sys("Error semop");
}

void P(int semid)
{
	semcall(semid, -1);
}

void V(int semid)
{
	semcall(semid, 1);
}
