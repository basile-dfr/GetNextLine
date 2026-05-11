#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
    size_t	count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}

char	*ft_strdup(const char *str1)
{
	char	*str2;
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (str1[len])
		len++;
	str2 = malloc(len + 1);
	if (!str2)
		return (NULL);
	while (i < len)
	{
		str2[i] = str1[i];
		i++;
	}
	str2[i] = '\0';
	return (str2);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str1;
	size_t	i;
	size_t	lenstr;

	i = 0;
	lenstr = ft_strlen(s);
	if (!s)
		return (NULL);
	if (start > lenstr)
		return (ft_calloc(1, 1));
	if (start + len > lenstr)
		len = lenstr - start;
	str1 = malloc(sizeof(char) * len + 1);
	if (!str1)
		return (NULL);
	while (i < len)
	{
		str1[i] = s[start];
		i++;
		start++;
	}
	str1[i] = '\0';
	return (str1);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dupdst;
	const char	*dupsrc;
	size_t		count;

	count = 0;
	dupdst = dst;
	dupsrc = src;
	while (count < n)
	{
		dupdst[count] = dupsrc[count];
		count ++;
	}
	return (dst);
}