/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 20:50:49 by junmlee           #+#    #+#             */
/*   Updated: 2023/11/05 11:35:48 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	find_newline(char *arr)
{
	ssize_t	i;

	i = 0;
	while (arr[i])
	{
		if (arr[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}

int	read_line(t_buf *buf, int fd)
{
	ssize_t	read_byte;
	char	*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (1);
	read_byte = BUFFER_SIZE;
	while (read_byte > 0)
	{
		buf->n_idx = find_newline(buf->data);
		if (buf->n_idx != 0)
		{
			free(buffer);
			return (0);
		}
		read_byte = read(fd, buffer, BUFFER_SIZE);
		buffer[read_byte] = '\0';
		buf->data = ft_strjoin(buf->data, buffer);
		buf->read_byte += read_byte;
	}
	free(buffer);
	return (1);
}

char	*get_next_line(int fd)
{
	static t_buf	arr[OPEN_MAX];

	if (0 > fd || fd > OPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	if (arr[fd].data == NULL)
		arr[fd].data = ft_strndup("", 1);
	arr[fd].read_byte = ft_strlen(arr[fd].data);
	arr[fd].end_flag = read_line(&(arr[fd]), fd);
	return (make_ret(&(arr[fd])));
}

char	*make_ret(t_buf *buf)
{
	char	*temp;
	char	*ret;
	char	*start;

	if (buf->end_flag == 0)
	{
		temp = buf->data;
		ret = ft_strndup(buf->data, buf->n_idx + 1);
		start = buf->data + (buf->n_idx + 1);
		buf->data = ft_strndup(start, buf->read_byte - buf->n_idx);
		free(temp);
		return (ret);
	}
	else if (buf->read_byte != 0)
	{
		ret = ft_strndup(buf->data, buf->read_byte);
		free(buf->data);
		buf->data = NULL;
		return (ret);
	}
	return (NULL);
}
