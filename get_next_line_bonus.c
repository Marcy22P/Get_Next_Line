/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpisani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:22:18 by mpisani           #+#    #+#             */
/*   Updated: 2025/02/14 20:14:37 by mpisani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_read_to_save(int fd, char *save)
{
	char	*buffer;
	char	*tmp;
	int		bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!gnl_strchr(save, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			free(save);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		tmp = gnl_strjoint(save, buffer);
		free(save);
		save = tmp;
	}
	free(buffer);
	return (save);
}

static char	*ft_extract_line(char *save)
{
	char	*line;
	size_t	i;

	if (!save || !save[0])
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
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
	if (save[i] == '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	new_save = gnl_strdup(save + i);
	free(save);
	return (new_save);
}

char	*get_next_line(int fd)
{
	static char *save[FOPEN_MAX];
	char *line;

	if (fd < 0 || fd >= FOPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	save[fd] = ft_read_to_save(fd, save[fd]);
	if (!save[fd])
		return (NULL);
	line = ft_extract_line(save[fd]);
	save[fd] = ft_update_save(save[fd]);
	return (line);
}