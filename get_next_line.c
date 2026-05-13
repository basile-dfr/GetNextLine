#include "get_next_line.h"

char	*ft_check_n_join(char *temp, char *buf)
{
	char	*keep_temp;
	int		len;

	len = 0;
	keep_temp = NULL;
	if (temp)
	{
		keep_temp = ft_strdup(temp);
		free(temp);
		len = ft_strlen(keep_temp) + ft_strlen(buf);
		temp = (char *)malloc(len + 1);
		if (!temp)
			return (NULL);
		ft_memcpy(temp, keep_temp, ft_strlen(keep_temp) + 1);
		temp[ft_strlen(keep_temp)] = '\0';
		ft_memcpy(ft_strchr(temp, '\0'), buf, ft_strlen(buf));
		temp[len] = '\0';
		free(keep_temp);
	}
	if (!temp)
		temp = ft_strdup(buf);
	return (temp);
}

void	ft_startnewline(char **ptr)
{
	char	*keep_temp;

	keep_temp = ft_strdup(ft_strchr(*ptr, '\n') + 1);
	free(*ptr);
	*ptr = keep_temp;
}

char	*ft_newline_n_free(char **ptr_temp, ssize_t i)
{
	char	*line;

	line = NULL;
	if (!*ptr_temp)
		return(NULL);
	if (**ptr_temp && i == 0) 
	{
		line = ft_strdup(*ptr_temp);
		free(*ptr_temp);
		*ptr_temp = NULL;
		return (line);
	}
	if (ft_strchr(*ptr_temp, '\n') != NULL)
	{
		line = ft_substr(*ptr_temp, 0, (ft_strlen(*ptr_temp) - ft_strlen(ft_strchr(*ptr_temp, '\n'))) + 1);
		ft_startnewline(ptr_temp);
		return (line);
	}
	free(*ptr_temp);
	*ptr_temp = NULL;
	return (NULL);
}

char    *get_next_line(int fd)
{
	static char	*temp;
	char		*buf;
	ssize_t		read_bytes;

	buf = NULL;
	read_bytes = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (read_bytes != 0)
	{
		if (temp && ft_strchr(temp, '\n') != NULL)
			return (ft_newline_n_free(&temp, read_bytes));
		buf = (char *)malloc(BUFFER_SIZE + 1);
		if (!buf)
			return (NULL);
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes <= 0)
			return (free(buf), ft_newline_n_free(&temp, read_bytes));
		buf[read_bytes] = '\0';
		temp = ft_check_n_join(temp, buf);
		free (buf);
		buf = NULL;
	}
	return (ft_newline_n_free(&temp, read_bytes));
}

int	main()
{
	int		fd;
	char	*result;

	result = NULL;
	fd = open("./test.txt", O_RDONLY);
	if (fd < 0)
		return (0);
	result = get_next_line(fd);
	while (result != NULL)
	{
		printf("%s", result);
		free(result);
		result = get_next_line(fd);
	}
	close(fd);
	return (0);
}