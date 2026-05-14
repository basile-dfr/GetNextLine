/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdefer <bdefer@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 18:15:12 by bdefer            #+#    #+#             */
/*   Updated: 2026/05/14 18:15:15 by bdefer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_check_and_join(char *temp, char *buf)
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

void	ft_keepmem_startnewline(char **ptr_temp)
{
	char	*keep_temp;

	keep_temp = ft_strdup(ft_strchr(*ptr_temp, '\n') + 1);
	free(*ptr_temp);
	*ptr_temp = keep_temp;
}

char	*ft_newline_and_free(char **ptr_temp, ssize_t bytesread)
{
	char	*line;
	int		len;

	line = NULL;
	if (!*ptr_temp || !**ptr_temp)
		return (NULL);
	if (**ptr_temp && bytesread == 0)
	{
		line = ft_strdup(*ptr_temp);
		free(*ptr_temp);
		*ptr_temp = NULL;
		return (line);
	}
	if (ft_strchr(*ptr_temp, '\0') != NULL)
	{
		len = (ft_strlen(*ptr_temp) - ft_strlen(ft_strchr(*ptr_temp, '\n')));
		line = ft_substr(*ptr_temp, 0, len + 1);
		ft_keepmem_startnewline(ptr_temp);
		return (line);
	}
	free(*ptr_temp);
	*ptr_temp = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char		*temp;
	ssize_t			bytesread;
	char			*buf;

	buf = NULL;
	bytesread = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (bytesread != 0)
	{
		if (temp && ft_strchr(temp, '\n') != NULL)
			return (ft_newline_and_free(&temp, bytesread));
		buf = (char *)malloc(BUFFER_SIZE + 1);
		if (!buf)
			return (NULL);
		bytesread = read(fd, buf, BUFFER_SIZE);
		if (bytesread <= 0)
			return (free(buf), ft_newline_and_free(&temp, bytesread));
		buf[bytesread] = '\0';
		temp = ft_check_and_join(temp, buf);
		free(buf);
		buf = NULL;
	}
	return (ft_newline_and_free(&temp, bytesread));
}
/*
int	main(void)
{
	int		fd;	
	char	*line;

	line = NULL;
	fd = open("./long_line.txt", O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}*/