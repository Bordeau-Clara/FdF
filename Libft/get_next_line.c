/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 10:13:48 by cbordeau          #+#    #+#             */
/*   Updated: 2024/11/26 10:46:47 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = {0};
	char		*line;
	int			i;

	i = 1;
	line = NULL;
	if (fd < -1)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, buffer, 0) == -1)
		return (ft_empty_buf2(buffer), NULL);
	while (ft_is_line(line) != 1 && i != 0)
	{
		line = ft_empty_buf(buffer, line);
		if (!line)
			return (NULL);
		if (buffer[0] == '\0' && ft_is_line(line) != 1)
		{
			i = read(fd, buffer, BUFFER_SIZE);
			if (i < 0)
				return (free(line), NULL);
			if (i == 0 && line[0] == '\0')
				return (free(line), NULL);
		}
	}
	return (line);
}

void	ft_empty_buf2(char *buffer)
{
	int	i;

	i = 0;
	if (BUFFER_SIZE < 1)
		return ;
	while (i <= BUFFER_SIZE)
	{
		buffer[i] = '\0';
		i++;
	}
}

int	ft_is_line(char *line)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (0);
	while (line[i])
	{
		if (line[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_empty_buf(char *buffer, char *line)
{
	int (i) = 0;
	int (j) = 0;
	if (line != NULL)
		while (line[j])
			j++;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	char *(temp) = malloc((i + j + 2) * sizeof(char));
	if (!temp)
		return (free(line), NULL);
	temp[i + j] = '\0';
	ft_strcpy(temp, line, buffer);
	free(line);
	line = ft_strdup_gnl(temp);
	if (!line)
		return (NULL);
	free(temp);
	if (buffer[i] == '\n')
		i++;
	j = 0;
	while (buffer[i])
		buffer[j++] = buffer[i++];
	while (j < BUFFER_SIZE)
		buffer[j++] = '\0';
	return (line);
}

void	ft_strcpy(char *temp, char *line, char *buffer)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	if (line != NULL)
	{
		while (line[i])
		{
			temp[i] = line[i];
			i++;
		}
	}
	while (buffer[a] && buffer[a] != '\n')
		temp[i++] = buffer[a++];
	if (buffer[a] == '\n')
	{
		temp[i] = buffer[a];
		temp[i + 1] = '\0';
	}
	else
		temp[i] = '\0';
}
