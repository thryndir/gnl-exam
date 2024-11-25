#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
# endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

typedef enum e_back
{
	NO,
	YES
}	t_back;

typedef enum e_pos
{
	BEFORE,
	AFTER
}	t_pos;

# endif