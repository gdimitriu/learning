/*
 * errtest.c
 *
 *  Created on: Aug 11, 2020
 *      Author: Gabriel Dimitriu
 *   examples from Linux Programming Uleashed by Kurt Wall,
 *	 Mark Watson and Mark Whitis
 */

#include <stdio.h>
#include <stdlib.h>
#include "liberr.h"

#define ERR_QUIT_SKIP 1
#define LOG_QUIT_SKIP 1

int main(void) {
	FILE *pf;
	fputs("Testing err_ret() ... \n", stdout);
	if((pf = fopen("foo", "r")) == NULL)
		err_ret("%s %s","err_ret()","failed to open foo");
	fputs("Testing log_ret()...\n", stdout);
	if((pf = fopen("foo","r")) == NULL)
		log_ret("errtest.log", "%s %s", "log_ret()", "failed to open foo");
#ifndef ERR_QUIT_SKIP
	fputs("Testing err_quit() ... \n",stdout);
	if((pf = fopen("foo", "r")) == NULL)
			err_quit("%s %s","err_quit()","failed to open foo");
#endif
#ifndef LOG_QUIT_SKIP
	fputs("Testing log_quit()...\n", stdout);
	if((pf = fopen("foo","r")) == NULL)
		log_ret("errtest.log", "%s %s", "log_quit()", "failed to open foo");
#endif
	return EXIT_SUCCESS;
}
