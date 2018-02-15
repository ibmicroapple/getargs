#include <stdlib.h>
#include <stdio.h>
#include "getargs.h"

args_option options[] =
{
	{.s_opt = 'h', .l_opt = "help"},
	{.s_opt = 'v', .l_opt = "version"},
	{.s_opt = 'i', .l_opt = "intval"},
	{.s_opt = 'f', .l_opt = "floatval"},
	{.s_opt = 's', .l_opt = "stringval"},
	{0}
};

/* The ARGS Macro refers to int argc, char *argv[]
 * You do not have to use it, but it may simplify things
 */

int main(ARGS)
{
	int opt;

	while(opt = getargs(argc, argv, options))
	{
		switch(opt)
		{
			case 'h':
			{
				puts("Help message");
				break;
			}
			case 'v':
			{
				puts("version message");
				break;
			}
			case 'i':
			{
				if(argsstr)
					printf("You entered '%d'.\n", strtol(argsstr, 0, 10));
				else
					puts("You did not provide a number.");
				break;
			}
			case 'f':
			{
				if(argsstr)
					printf("You entered '%f'.\n", strtod(argsstr, 0));
				else
					puts("You did not provide a number.");
				break;
			}
			case 's':
			{
				if(argsstr)
					puts(argsstr);
				break;
			}
			default:
			{
				puts("Invalid argument.");
				return(-1);
			}
		}
	}

	return(0);
}