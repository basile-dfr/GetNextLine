#include "get_next_line.h"

char    *get_next_line(int fd)
{
    
}

int	main()
{
	int	fd;
	char	buf[BUFFER_SIZE];

	fd = open("./test.txt", O_RDONLY);
	if (fd == -1);
		return (NULL);
	
	read(fd, buf, );
	return (0);
}