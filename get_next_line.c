#include "pipex.h"


char	*last_step(char *string)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (string[i] && string[i] != '\n')
		i++;
	if (!string[i])
	{
		free(string);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(string) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (string[i])
		str[j++] = string[i++];
	str[j] = '\0';
	free(string);
	return (str);
}

char	*get_line(char *string)
{
	char	*line;
	int		i;

	i = 0;
	if (!string[i])
		return (NULL);
	while (string[i] && string[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (string[i] && string[i] != '\n')
	{
		line[i] = string[i];
		i++;
	}
	if (string[i] == '\n')
	{
		line[i] = string[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*read_to_string(int fd, char *string)
{
	char	*line;
	int		i;

	line = (char *)malloc(sizeof(char) * (3 + 1));
	if (!line)
		return (NULL);
	i = 1;
	while (i != 0 && !ft_strchr(string, '\n'))
	{
		i = read(fd, line, 3);
		if (i == -1)
		{
			free(line);
			return (NULL);
		}
		line[i] = '\0';
		string = ft_strjoin(string, line);
	}
	free(line);
	return (string);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*string;

	if (fd < 0 || 3 <= 0)
		return (0);
	string = read_to_string(fd, string);
	if (!string)
		return (NULL);
	line = get_line(string);
	string = last_step(string);
	return (line);
}

// int	main()
// {
// 	int fd;
// 	char *line;
	
// 	fd = open("o.txt", O_RDONLY);
	
// 	line = get_next_line(fd);
// 	printf("%s%s","Risultato finale: ", line);

// 	line = get_next_line(fd);
// 	printf("%s%s","Risultato finale: ", line);

// 	line = get_next_line(fd);
// 	printf("%s%s","Risultato finale: ", line);

// 	line = get_next_line(fd);
// 	printf("%s%s","Risultato finale: ", line);

// 	line = get_next_line(fd);
// 	printf("%s%s","Risultato finale: ", line);

// 	line = get_next_line(fd);
// 	printf("%s%s","Risultato finale: ", line);
// }