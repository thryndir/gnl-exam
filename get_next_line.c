#include "get_next_line.h"

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*backjoin(char *str1, char *str2, t_back back)
{
	int	i;
	int	j;
	char	eol;
	char	*result;

	i = 0;
	j = 0;
	if (back)
		eol = '\n';
	else
		eol = '\0';
	if (!str1 || !str2)
		return (NULL);
	result = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	while (str1[i])
	{
		result[i] = str1[i];
		i++;
	}
	while (str2[j] && str2[j - 1] != '\n')
	{
		result[i] = str2[j];
		i++;
		j++;
	}
	result[i] = '\0';
	return (result);
}

char *ft_strchr(char *str, char to_find)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == to_find)
			return (&str[i]);
		i++;
	}
	return (NULL);
}

int		backcpy(char *src, char *dest, t_pos pos)
{
	if (pos == BEFORE)
	{
		while (str[i] && str[i - 1] != '\n')
		{
			result[i] = str[i];
			i++;
		}
	}
	else
	{
		str = ft_strchr(str, '\n');
		if (!str)
			return (NULL);
		str++;
		while (str[i])
		{
			result[i] = str[i];
			i++;
		}
	}
}

char	*backdup(char *str, t_pos pos)
{
	char 	*result;
	int		i;

	i = 0;
	if (pos == BEFORE)
	{
		result = malloc(ft_strlen(str) + 1);
		while (str[i] && str[i - 1] != '\n')
		{
			result[i] = str[i];
			i++;
		}
	}
	else
	{
		str = ft_strchr(str, '\n');
		if (!str)
			return (NULL);
		str++;
		result = malloc(ft_strlen(str) + 1);
		while (str[i])
		{
			result[i] = str[i];
			i++;
		}
	}
	result[i] = '\0';
	return (result);
}

char *get_next_line(int fd)
{
	char		*clean_line;
	char		dirty_line[BUFFER_SIZE] = {0};
	static char *after_back;
	static int	bytes_read = BUFFER_SIZE;

	clean_line = NULL;
	if (after_back)
		clean_line = backdup(after_back, BEFORE);
	if (after_back && ft_strchr(after_back, '\n'))
		after_back = backdup(after_back, AFTER);
	while (!ft_strchr(dirty_line, '\n') && bytes_read)
	{
		if (clean_line && ft_strchr(clean_line, '\n'))
			return (clean_line);
		bytes_read = read(fd, dirty_line, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(clean_line);
			return (NULL);
		}
		dirty_line[bytes_read] = '\0';
		if (!clean_line)
			clean_line = backdup(dirty_line, BEFORE);
		else
			clean_line = backjoin(clean_line, dirty_line, YES);
	}
	if (after_back && ft_strchr(after_back, '\n'))
		after_back = backjoin(after_back, dirty_line, NO);
	after_back = backdup(dirty_line, AFTER);
	return (clean_line);
}

int main(int argc, char **argv)
{
	int	fd;
	char *line;
	(void)argc;

	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	printf("%s", line);
	while (line)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
	}
}