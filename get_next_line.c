#include "get_next_line.h"

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_strlcat(char *src, char *dest, int size)
{
	int		i;
	int		destlen;
	int		space_left;

	i = 0;	
	destlen = ft_strlen(dest);
	space_left = size - destlen - 1;
	if (size < destlen)
		return (0);
	while (src[i] && i <= space_left)
	{
		dest[destlen + i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(dest));
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
	free(str1);
	while (str2[j] && str2[j - 1] != eol)
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
	int		i;

	i = 0;
	if (pos == BEFORE)
	{
		while (src[i] && src[i - 1] != '\n')
		{
			dest[i] = src[i];
			i++;
		}
	}
	else
	{
		src = ft_strchr(src, '\n');
		if (!src)
		{
			dest[0] = '\0';
			return (0);
		}
		src++;
		while (src[i])
		{
			dest[i] = src[i];
			i++;
		}
	}
	dest[i] = '\0';
	return (ft_strlen(dest));
}

char	*backdup(char *str, t_pos pos)
{
	char 	*result;

	result = malloc(ft_strlen(str) + 1);
	backcpy(str, result, pos);
	return (result);
}

char *get_next_line(int fd)
{
	char		*clean_line;
	char		dirty_line[BUFFER_SIZE] = {0};
	static char after_back[BUFFER_SIZE] = {0};
	static int	bytes_read = BUFFER_SIZE;
	// char		*temp;

	clean_line = NULL;
	if (after_back[0])
		clean_line = backdup(after_back, BEFORE);
	if (ft_strchr(after_back, '\n'))
		backcpy(after_back, after_back, AFTER);
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
	if (ft_strchr(after_back, '\n'))
		ft_strlcat(dirty_line, after_back, BUFFER_SIZE);
	backcpy(dirty_line, after_back, AFTER);
	return (clean_line);
}

int main(int argc, char **argv)
{
	int	fd;
	char *line;
	(void)argc;
	int		i;

	i = 0;
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	while (line && i <= 15)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
	}
}