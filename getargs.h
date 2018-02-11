#ifndef GETARGS_H
#define GETARGS_H

#include <string.h>

#define ARGS int argc, char *argv[]

typedef struct
{
	char	s_opt;
	char*	l_opt;
} args_option;

const char *argsstr = 0;

static char* stringcompare(char *str1, char *str2);
int getargs(ARGS, args_option *options);
int args_split(char ** args, int size, char * const text);

static char* stringcompare(char *str1, char *str2)
{
	while(*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}

	if((!*str1 && *str2 == '=') || (*str1 == *str2)) return(str2);

	return(0);
}

int getargs(ARGS, args_option *options)
{
	static int largc = 1;
	args_option* optptr;
	char* endptr;

	if(largc >= argc)
	{
		argsstr = 0;
		largc = 1;
		return(0);
	}

	if(argv[largc][0] == '-')
	{
		if(argv[largc][1] == '-') /* long option */
		{
			for(optptr = options; optptr->l_opt; optptr++)
			{
				if((endptr = stringcompare(optptr->l_opt, &argv[largc][2])))
				{
					if((largc + 1) < argc)
					{
						if(argv[largc + 1][0] != '-')
						{
							largc++;
							argsstr = argv[largc];
							break;
						}
					}

					if(*endptr != '\0' && *endptr == '=')
					{
						endptr++;

						if(*endptr)
						{
							argsstr = endptr;
						}
					}

					break;
				}
			}
		}
		else /* short option */
		{
			for(optptr = options; optptr->s_opt; optptr++)
			{
				if(argv[largc][1] == optptr->s_opt)
				{
					if((largc + 1) < argc)
					{
						if(argv[largc + 1][0] != '-')
						{
							largc++;
							argsstr = argv[largc];
							break;
						}
					}

					if(argv[largc][2])
					{
						if(argv[largc][2] == '=')
						{
							if(argv[largc][3])
							{
								argsstr = &argv[largc][3];
							}
						}
						else
						{
							argsstr = &argv[largc][2];
						}
					}

					break;
				}
			}
		}
	}
	else /* no option */
	{
		argsstr = argv[largc];
		largc++;
		return(1);
	}

	largc++;

	return(optptr->s_opt);
}

int args_split(char ** args, int size, char * const text)
{
	char*	sptr;
	int	i;

	sptr = text;

	for(i = 0; (*sptr != '\0') && (i < size); i++)
	{
		while(*sptr == ' ') sptr++;

		if(*sptr == '\0') break;
/*
		if(*sptr == '"')
		{
			args[i] = ++sptr;
			sptr = strchr(sptr, '"');
			if(!sptr) break;
			sptr++;
		}
		else FIXME: Cuz i don't work!*/
		{
			args[i] = sptr;
			sptr = strchr(sptr, ' ');
			if(!sptr) break;
			*sptr = '\0';
			sptr++;
		}
	}

	return(i + 1);
}

#endif /* GETARGS_H */