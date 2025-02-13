/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpisani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:01:21 by mpisani           #+#    #+#             */
/*   Updated: 2025/02/13 20:19:31 by mpisani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_read_to_save(int fd, char *save)
{
	char	*buffer;
	int		bytes_read;

	bytes_read = 1;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (!gnl_strchr(save, '\n') && bytes_read)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		save = gnl_strjoint(save, buffer);
	}
	free(buffer);
	return (save);
}

static char	*ft_extract_line(char *save)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!save || !save[0])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	line = gnl_substr(save, 0, i);
	return (line);
}

static char	*ft_update_save(char *save)
{
	char	*new_save;
	size_t	i;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	if (!save[i + 1])
	{
		free(save);
		return (NULL);
	}
	new_save = gnl_strdup(save + i + 1);
	free(save);
	return (new_save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = ft_read_to_save(fd, save);
	if (!save)
		return (NULL);
	line = ft_extract_line(save);
	save = ft_update_save(save);
	return (line);
}
