/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 20:50:49 by junmlee           #+#    #+#             */
/*   Updated: 2023/11/06 20:11:44 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	update_buf(t_buf *buf)
{
	ssize_t	i;
	int		once;

	buf->n_idx = -1;
	if (buf->data == NULL)
	{
		buf->len_data = 0;
		buf->end_flag = 1;
	}
	else
	{
		once = 1;
		i = 0;
		while (buf->data[i] != '\0')
		{
			if (buf->data[i] == '\n' && once)
			{
				buf->n_idx = i;
				once = 0;
			}
			i++;
		}
		buf->len_data = i;
		buf->end_flag = 0;
	}
}

int	read_line(t_buf *buf, char *buffer, int fd)
{
	char	*temp;

	while (1)
	{
		update_buf(buf);
		if (buf->n_idx >= 0)
			return (0);
		buf->ret_read = read(fd, buffer, BUFFER_SIZE);
		if (buf->ret_read == 0)
			return (2);
		if (buf->ret_read == -1)
		{
			free(buf->data);
			buf->data = NULL;
			return (2);
		}
		buffer[buf->ret_read] = '\0';
		temp = buf->data;
		buf->data = gnl_append(buf->data, buffer);
		if (buf->data == NULL)
			return (1);
		free(temp);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static t_buf	arr[OPEN_MAX];
	char			*buffer;

	if (0 > fd || fd > OPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	//update_buf(&(arr[fd]));
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		arr[fd].end_flag = 1;
	else
	{
		arr[fd].end_flag = read_line(&(arr[fd]), buffer, fd);
		free(buffer);
	}
	return (make_ret(&(arr[fd])));
}

char	*make_ret(t_buf *buf)
{
	char	*temp;
	char	*ret;

	if (buf->end_flag == 1)
		return (NULL);
	else if (buf->n_idx >= 0)
	{
		temp = buf->data;
		ret = g_strndup(temp, buf->n_idx + 1);
		buf->data = g_strndup(temp + buf->n_idx + 1, buf->len_data - buf->n_idx);
		free(temp);
		return (ret);
	}
	else
	{
		ret = g_strndup(buf->data, buf->len_data);
		free(buf->data);
		buf->data = NULL;
		return (ret);
	}
}
