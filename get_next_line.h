#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
#endif

# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

void	*ft_calloc(size_t nbelement, size_t sizelement);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *str1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_startnewline(char **ptr);
char	*ft_newline_n_free(char **ptr_temp, ssize_t i);
char	*ft_check_n_join(char *temp, char *buf);
char    *get_next_line(int fd);

#endif